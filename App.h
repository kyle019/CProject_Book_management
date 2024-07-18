#pragma once
typedef struct _App App;
#include "EHArray.h"
#include "Genre.h"
#include <stdio.h>
struct _App
{
    char fname[FILENAME_MAX];
    int last_gnum;
    EHArray *genres;
};

App *NewApp(const char *fname);
void AppRun(App *app);
void DeleteApp(App *app);