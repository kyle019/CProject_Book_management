//Genre.c
#pragma warning(disable:4996)
#include "Genre.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void GenreGenre(Genre *genre,int gnum,const char *gname);
Genre *NewGenre(int gnum,const char *gname)
{
    Genre *genre = 0;
    genre = (Genre *)malloc(sizeof(Genre));
    GenreGenre(genre,gnum,gname);
    return genre;
}
void GenreGenre(Genre *genre,int gnum,const char *gname)
{
    genre->gnum = gnum;
    memset(genre->name,0,sizeof(genre->name));
    strncpy(genre->name,gname,MAX_GNAME_LEN);
    genre->books = NewEHArray(0,0);
    genre->last_bnum = 0;
}
void GenreDeserialize(Genre *genre,FILE *fp);
Genre *NewGenre2(FILE *fp)
{
    Genre *genre = 0;
    genre = NewGenre(0,"");
    GenreDeserialize(genre,fp);
    return genre;
}
void GenreDeserialize(Genre *genre,FILE *fp)
{
    Book *book=0;
    int i = 0;
    int n = 0;
    fread(genre->name,sizeof(genre->name),1,fp);
    fread(&(genre->gnum),sizeof(int),1,fp);
    fread(&(genre->last_bnum),sizeof(int),1,fp);
    fread(&n,sizeof(int),1,fp);
    for(i=0  ;i<n; i++)
    {
        book = NewBook2(fp);
        EHArrayPushBack(genre->books,book);
    }
}

void GenreTGenre(Genre *genre);
void DeleteGenre(Genre *genre)
{
    GenreTGenre(genre);
    free(genre);
}
void GenreTGenre(Genre *genre)
{
    Book *book=0;
    Iterator seek= EHArrayBegin(genre->books);
    Iterator end= EHArrayEnd(genre->books);
    for(  ;seek != end; ++seek)
    {
        book = (Book *)(*seek);
        DeleteBook(book);
    }
    DeleteEHArray(genre->books);
}

int GenreGetNum(Genre *genre)
{
    return genre->gnum;
}

const char *GenreGetName(Genre *genre)
{
    return genre->name;
}
void GenreView(Genre *genre)
{
    printf("장르 번호:%d 장르 이름:%s\n",genre->gnum,genre->name);
}

void GenreAddBook(Genre *genre,const char *title,const char *author)
{
    Book *book = 0;
    genre->last_bnum++;
    book = NewBook(genre->last_bnum,title,author);
    EHArrayPushBack(genre->books,book);
    printf("도서번호:%d 로 추가하였습니다.\n",genre->last_bnum);
}
void GenreViewAll(Genre *genre)
{
    Iterator seek= EHArrayBegin(genre->books);
    Iterator end= EHArrayEnd(genre->books);
    Book *sbook=0;
    GenreView(genre);
    for(  ;seek != end; ++seek)
    {
        sbook = (Book *)(*seek);
        BookView(sbook);
    }
}

Book *GenreFindBookByNum(Genre *genre,int bnum)
{
    Iterator seek;
    Iterator end;
    Book *book=0;

    seek= EHArrayBegin(genre->books);
    end= EHArrayEnd(genre->books);

    GenreView(genre);

    for(  ;seek != end; ++seek)
    {
        book = (Book *)(*seek);

        if(BookGetNum(book) == bnum)
        {
            return book;
        }
    }

    return 0;
}
Book *GenreFindBookByTitle(Genre *genre,const char *title)
{
    Iterator seek;
    Iterator end;
    Book *book=0;
    const char *stitle = 0;

    seek= EHArrayBegin(genre->books);
    end= EHArrayEnd(genre->books);

    GenreView(genre);
    for(  ;seek != end; ++seek)
    {
        book = (Book *)(*seek);
        stitle = BookGetTitle(book);
        if(strcmp(stitle,title)==0)
        {
            return book;
        }
    }
    return 0;
}
void GenreSerialize(Genre *genre,FILE *fp)
{
    Iterator seek;
    Iterator end;
    Book *book=0;
    int n = 0;

    fwrite(genre->name,sizeof(genre->name),1,fp);
    fwrite(&(genre->gnum),sizeof(int),1,fp);
    fwrite(&(genre->last_bnum),sizeof(int),1,fp);

    n = EHArrayGetSize(genre->books);
    fwrite(&n,sizeof(int),1,fp);
    seek= EHArrayBegin(genre->books);
    end= EHArrayEnd(genre->books);

    for(  ;seek != end; ++seek)
    {
        book = (Book *)(*seek);
        BookSerialize(book,fp);
    }
}
