// Book.h
#pragma once
#include <stdio.h>
typedef struct _Book Book;
#define MAX_TNAME_LEN     100
#define MAX_ANAME_LEN 20
struct _Book
{
    char title[MAX_TNAME_LEN+1];
    char author[MAX_ANAME_LEN+1];
    int bnum;
};
Book *NewBook(int bnum,const char *title,const char *author);
Book *NewBook2(FILE *fp);
void DeleteBook(Book *book);
void BookView(Book *book);
int BookGetNum(Book *book);
const char *BookGetTitle(Book *book);
void BookSerialize(Book *book,FILE *fp);