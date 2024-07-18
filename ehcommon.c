//ehcommon.c
#include "ehcommon.h"
#include <stdlib.h>
#include <stdio.h>

void clrscr() {
    printf("\e[1;1H\e[2J"); // ANSI escape code for clearing the screen
}

int getkey() {
    int key = getchar();
    if (key == 27) {
        return ESC;
    }
    switch (key) {
        case '1': return KEY_1;
        case '2': return KEY_2;
        case '3': return KEY_3;
        case '4': return KEY_4;
        case '5': return KEY_5;
        case '6': return KEY_6;
        case '7': return KEY_7;
        case '8': return KEY_8;
        case '9': return KEY_9;
        case '0': return KEY_10;
        default: return NO_DEFINED;
    }
}