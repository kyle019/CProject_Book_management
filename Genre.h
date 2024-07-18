#include "Book.h"
#include "EHArray.h"
typedef struct _Genre Genre;
#define MAX_GNAME_LEN 20
struct _Genre
{
    char name[MAX_GNAME_LEN+1];
    int gnum;
    int last_bnum;
    EHArray *books;
};
Genre *NewGenre(int gnum,const char *gname);
Genre *NewGenre2(FILE *fp);
void DeleteGenre(Genre *genre);
const char *GenreGetName(Genre *genre);
void GenreView(Genre *genre);
void GenreAddBook(Genre *genre,const char *title,const char *author);
void GenreViewAll(Genre *genre);
Book *GenreFindBookByNum(Genre *genre,int bnum);
Book *GenreFindBookByTitle(Genre *genre,const char *title);
void GenreSerialize(Genre *genre,FILE *fp);