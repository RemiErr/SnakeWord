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
    int flag_ans;
    while (true)
    {
        char buf[30] = {};
        while (!kbhit())
        {
            if (wd.line.empty())
            {
                if (!wd.spell.empty())
                {
                    if (wd.spell == wd.ans)
                    {
                        flag_ans = 1;
                    }else{
                        flag_ans = 2;
                    }
                    wd.spell = "";
                }

                int index = rand() % wd.n;
                wd.line = wd.dict[index];
                wd.ans = wd.dict[index];
                cout<<"Ans: "<<wd.ans<<endl; // #debug
                randWordPos();
            }else{
                flag_ans = 0;
            }

            cleardevice();
            showBoard();
            if (flag_ans == 1)
            {
                sprintf(buf, "< �� �� �� �� >");
                outtextxy(WINDOW_SIZE_WIDTH + BOARD_SIZE_WIDTH / 3, 300, buf);
                delay(1000);
            }
            else if (flag_ans == 2)
            {
                sprintf(buf, "< �� �h Ū �� >");
                outtextxy(WINDOW_SIZE_WIDTH + BOARD_SIZE_WIDTH / 3, 300, buf);
                delay(1000);
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