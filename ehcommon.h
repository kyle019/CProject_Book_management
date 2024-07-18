// ehcommon.h
#pragma once


typedef enum _key key;
enum _key
{
    NO_DEFINED, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9, KEY_10, ESC
};

void clrscr();
int getkey();
