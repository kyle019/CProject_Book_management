#include "App.h"

#define DEF_FNAME    "member.ehd" //초기 파일 이름

int main(int argc, char **argv)
{
    App *app = 0;
    if(argc != 2)
    {
        app = NewApp(DEF_FNAME);
    }
    else
    {
        app = NewApp(argv[1]);
    }
    AppRun(app);
    DeleteApp(app);
    return 0;
}
