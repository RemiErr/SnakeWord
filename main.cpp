/********�g���D�p�C��*******
# �ݥ��b�sĶ���`�J WinBGIm
# �sĶ���i�� TDM-gcc 32bit
# Build �e����l�� C++ �պA
***************************/

/*********�sĶ���޼�********
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