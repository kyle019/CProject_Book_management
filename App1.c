//App.c
#pragma warning(disable:4996)
#include "App.h"
#include "ehcommon.h"
#include <stdio.h>
#include <memory.h>
#include <string.h>
#include <stdlib.h>


void AppApp(App *app,const char *fname);
void AppTApp(App *app);
void AppLoad(App *app);
void AppSave(App *app);

int AppSelectMenu(App *app);
void AppAddGenre(App *app);
void AppRemoveGenre(App *app);
void AppListGenre(App *app);
void AppListBookAtGenre(App *app); 
void AppAddBook(App *app); 
void AppFindBookByNum(App *app); 
void AppFindBookByTitle(App *app); 
void AppListAll(App *app); 

App *NewApp(const char *fname)
{
    App *app = 0;
    app = (App *)malloc(sizeof(App));
    AppApp(app,fname);
    return app;
}

void AppApp(App *app,const char *fname)
{
    memset(app->fname,0,sizeof(app->fname));
    strncpy(app->fname,fname,FILENAME_MAX);
    app->genres = NewEHArray(0,0);
    app->last_gnum = 0;
    AppLoad(app);
    printf("아무 키나 누르세요.\n");
    getkey();
}

void AppDeserialize(App *app,FILE *fp);
void AppLoad(App *app)
{
    FILE *fp = 0;
    fp = fopen(app->fname,"r");
    if(fp)
    {
        AppDeserialize(app,fp);
    }
    else
    {
        printf("환영합니다.\n");
    }
}
void AppDeserialize(App *app,FILE *fp)
{
    int n = 0;
    int i = 0;
    Genre *genre=0;
    fread(&(app->last_gnum),sizeof(int),1,fp);
    fread(&n,sizeof(int),1,fp);
    for( i=0 ;i<n;i++)
    {
        genre = NewGenre2(fp);
        EHArrayPushBack(app->genres,genre);
    }
}




void AppRun(App *app)
{
    int key = 0;
    while((key = AppSelectMenu(app))!=ESC)
    {
        switch(key)
        {
        case KEY_1: AppAddGenre(app); break;
        case KEY_2: AppRemoveGenre(app); break;
        case KEY_3: AppListGenre(app); break;
        case KEY_4: AppListBookAtGenre(app); break;
        case KEY_5: AppAddBook(app); break;
        case KEY_6: AppFindBookByNum(app); break;
        case KEY_7: AppFindBookByTitle(app); break;
        case KEY_8: AppListAll(app); break;
        default: printf("잘못 선택하였습니다.\n"); break;
        }
        printf("아무 키나 누르세요.\n");
        getkey();
    }
} 
int AppSelectMenu(App *app)
{
    clrscr();
    printf("장르별 도서관리 프로그램 \n");
    printf("1:장르 추가 2: 장르 삭제 3: 전체 장르 보기\n");
    printf("4: 특정 장르의 도서 목록 보기\n");
    printf("5:도서 추가 6: 도서 검색(일련번호) 7: 도서검색(제목)\n");
    printf("8: 전체 도서 보기 ESC: 종료\n");
    return getkey();
}

Iterator AppFindGenre(App *app,const char *gname);
void AppAddGenre(App *app)
{
    char gname[MAX_GNAME_LEN+1]="";
    Iterator seek = 0;
    Genre *genre = 0;

    printf("%d번째 추가할 장르명을 입력하세요.\n",app->last_gnum+1);
    fgets(gname,MAX_GNAME_LEN,stdin);

    seek = AppFindGenre(app,gname);
    if(seek != EHArrayEnd(app->genres))
    {
        printf("이미 존재하는 장르입니다.\n");
        return;
    }
    genre = NewGenre(app->last_gnum+1,gname);
    app->last_gnum++;
    EHArrayPushBack(app->genres,genre);
}
Iterator AppFindGenre(App *app,const char *gname)
{
    Iterator seek;
    Iterator end;
    Genre *sgenre=0;
    const char *sgname=0;

    seek = EHArrayBegin(app->genres);
    end = EHArrayEnd(app->genres);

    for(  ;seek != end; ++seek)
    {
        sgenre = (Genre *)(*seek);
        sgname = GenreGetName(sgenre);
        if(strcmp(sgname,gname)==0)
        {
            break;
        }
    }
    return seek;
}

void AppRemoveGenre(App *app)
{
    char gname[MAX_GNAME_LEN+1]="";
    Iterator seek = 0;
    Genre *genre = 0;
    AppListGenre(app);
    printf("삭제할 장르명을 입력하세요.\n");
    fgets(gname,MAX_GNAME_LEN,stdin);
    seek = AppFindGenre(app,gname);
    if(seek == EHArrayEnd(app->genres))
    {
         printf("잘못 선택하였습니다.\n");
        return;
    }
    genre = (Genre *)(*seek);
    DeleteGenre(genre);
    EHArrayErase(app->genres,seek);
}

void AppListGenre(App *app)
{
    Iterator seek= EHArrayBegin(app->genres);
    Iterator end= EHArrayEnd(app->genres);
    Genre *sgenre=0;
    for(  ;seek != end; ++seek)
    {
        sgenre = (Genre *)(*seek);
        GenreView(sgenre);
    }
}

void AppListBookAtGenre(App *app)
{
    char gname[MAX_GNAME_LEN+1]="";
    Iterator seek = 0;
    Genre *genre = 0;
    AppListGenre(app);
    printf("도서 목록을 확인할 장르명을 입력하세요.\n");
    fgets(gname,MAX_GNAME_LEN,stdin);
    seek = AppFindGenre(app,gname);
    if(seek == EHArrayEnd(app->genres))
    {
        printf("잘못 선택하였습니다.\n");
        return;
    }
    genre = (Genre *)(*seek);
    GenreViewAll(genre);
}

void AppAddBook(App *app)
{
    char gname[MAX_GNAME_LEN+1]="";
    char author[MAX_ANAME_LEN+1]="";
    char title[MAX_TNAME_LEN+1]="";
    Iterator seek = 0;
    Genre *genre = 0;
    AppListGenre(app);
    printf("도서를 추가할 장르명을 입력하세요.\n");
    fgets(gname,MAX_GNAME_LEN,stdin);
    seek = AppFindGenre(app,gname);
    if(seek == EHArrayEnd(app->genres))
    {
        printf("잘못 선택하였습니다.\n");
        return;
    }
    printf("도서명을 입력하세요.\n");
    fgets(title,MAX_TNAME_LEN,stdin);
    printf("저자명을 입력하세요.\n");
    fgets(author,MAX_ANAME_LEN,stdin);
    genre = (Genre *)(*seek);
    GenreAddBook(genre,title,author);
}
void AppFindBookByNum(App *app)
{
    char gname[MAX_GNAME_LEN+1]="";
    int bnum=0;
    Iterator seek = 0;
    Genre *genre = 0;
    Book *book = 0;
    AppListGenre(app);
    printf("검색할 장르명을 입력하세요.\n");
    fgets(gname,MAX_GNAME_LEN,stdin);
    seek = AppFindGenre(app,gname);
    if(seek == EHArrayEnd(app->genres))
    {
        printf("잘못 선택하였습니다.\n");
        return;
    }
    printf("도서 번호를 입력하세요.\n");
    scanf("%d", &bnum);
    genre = (Genre *)(*seek);
    book = GenreFindBookByNum(genre,bnum);
    if(book)
    {
        BookView(book);
    }
    else
    {
        printf("도서를 찾지 못했습니다.\n");
    }
}
void AppFindBookByTitle(App *app)
{
    char gname[MAX_GNAME_LEN+1]="";
    char title[MAX_TNAME_LEN+1]="";
    Iterator seek = 0;
    Genre *genre = 0;
    Book *book = 0;

    AppListGenre(app);
    printf("검색할 장르명을 입력하세요.\n");
    fgets(gname,MAX_GNAME_LEN,stdin);
    seek = AppFindGenre(app,gname);
    if(seek == EHArrayEnd(app->genres))
    {
        printf("잘못 선택하였습니다.\n");
        return;
    }
    printf("도서 제목을 입력하세요.\n");
    fgets(title,MAX_TNAME_LEN,stdin);
    genre = (Genre *)(*seek);
    book = GenreFindBookByTitle(genre,title);
    if(book)
    {
        BookView(book);
    }
    else
    {
        printf("도서를 찾지 못했습니다.\n");
    }
}
void AppListAll(App *app)
{
    Iterator seek= EHArrayBegin(app->genres);
    Iterator end= EHArrayEnd(app->genres);
    Genre *genre=0;
    for(  ;seek != end; ++seek)
    {
        genre = (Genre *)(*seek);
        GenreViewAll(genre);
    }
}

void DeleteApp(App *app)
{
    AppSave(app);
    AppTApp(app);
    free(app);
}
void AppTApp(App *app)
{
    DeleteEHArray(app->genres);
}

void AppSerialize(App *app,FILE *fp);
void AppSave(App *app)
{
    FILE *fp =fopen(app->fname,"w");
    if(fp)
    {
        AppSerialize(app,fp);
    }
    else
    {
       printf("오류!!!데이터 저장 실패\n");
    }
}

void AppSerialize(App *app,FILE *fp)
{
    Iterator seek;
    Iterator end;
    int n = 0;
    Genre *genre=0;
    fwrite(&(app->last_gnum),sizeof(int),1,fp);
    n = EHArrayGetSize(app->genres);
    fwrite(&n,sizeof(int),1,fp);
    seek= EHArrayBegin(app->genres);
    end= EHArrayEnd(app->genres);
    for(  ;seek != end; ++seek)
    {
        genre = (Genre *)(*seek);
        GenreSerialize(genre,fp);
    }
}
