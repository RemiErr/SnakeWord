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
    // �禡�ŧi
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