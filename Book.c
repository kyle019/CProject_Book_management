//Book.c
#pragma warning(disable:4996)
#include "Book.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
void BookBook(Book *book,int bnum,const char *title,const char *author);
Book *NewBook(int bnum,const char *title,const char *author)
{
    Book *book = 0;
    book = (Book *)malloc(sizeof(Book));
    BookBook(book,bnum,title,author);
    return book;
}
void BookDeserialize(Book *book,FILE *fp);
Book *NewBook2(FILE *fp)
{
    Book *book = 0;
    book = NewBook(0,"","");
    BookDeserialize(book,fp);
    return book;
}
void BookDeserialize(Book *book,FILE *fp)
{
    fread(book,sizeof(Book),1,fp);
}


void BookBook(Book *book,int bnum,const char *title,const char *author)
{
    book->bnum = bnum;
    memset(book->title,0,sizeof(book->title));
    strncpy(book->title,title,MAX_TNAME_LEN);
    memset(book->author,0,sizeof(book->author));
    strncpy(book->author,author,MAX_ANAME_LEN);
}
void DeleteBook(Book *book)
{
    free(book);
}
void BookView(Book *book)
{
    printf("제목:%s\n",book->title);
    printf("\t도서번호:%d 저자명:%s\n",book->bnum,book->author);
}
int BookGetNum(Book *book)
{
    return book->bnum;
}

const char *BookGetTitle(Book *book)
{
    return book->title;
} 
void BookSerialize(Book *book,FILE *fp)
{
    fwrite(book,sizeof(Book),1,fp);
}
