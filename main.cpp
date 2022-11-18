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
    // 函式宣告
    void GameStart();
    void GameOver();
    void paintSnake();
    void moveSnake();
    void changePath();
    void randomizeWord();
    void printWord();
    void eatWord();
    void loadWord();

    initwindow(winSizeX, winSizeY);
    setbkcolor(BLACK);
    GameStart();
    while (true)
    {
        while (isGameNow && !kbhit())
        {
            if (wd.flag == 0)
            {
                loadWord();
                randomizeWord();
            }
            cleardevice();
            printWord();
            moveSnake();
            paintSnake();
            eatWord();
            Sleep(200 - (sk.n * 2));
            if (sk.flag) GameOver();
        }
        if (!isGameNow) GameStart();
        changePath();
    }
}