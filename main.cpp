/********貪食蛇小遊戲*******
# 需先在編譯器注入 WinBGIm
# 編譯器可用 TDM-gcc 32bit
# Build 前先初始化 C++ 組態
***************************/

/*********編譯器引數********
-lbgi
-lgdi32
-lcomdlg32
-luuid
-loleaut32
-lole32
***************************/

#include "gameFunction.h"

int main ()
{
    srand(time(NULL) + getpid());
    initwindow(WINDOW_SIZE_WIDTH + BOARD_SIZE_WIDTH, WINDOW_SIZE_HIGH);
    setbkcolor(BLACK);
    initGame();
    loadWord();
    while (true)
    {
        while (!kbhit())
        {
            if (wd.line.empty())
            {
                wd.spell = "";
                wd.line = wd.dict[ rand() % wd.n ];
                cout<<wd.line<<endl; // #debug
                randWordPos();
            }
            cleardevice();
            printWord();
            moveSnake();
            paintSnake();
            eatWord();
            showBoard();
            delay(sk.n < 50 ? 220 - (sk.n * 2) : 100);
            GameCore();
        }
        changePath();
    }
}