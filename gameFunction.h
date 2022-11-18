#include <conio.h>
#include <graphics.h>
#include <bits/stdc++.h>
using namespace std;

#define SIZE 30
#define winSizeX 960
#define winSizeY 720

bool isGameNow = true;
string FFF = "SNAKE";
struct xy
{
    int x;
    int y;
};

enum path {UP = 72, DOWN = 80, LEFT = 75, RIGHT = 77, P = 112}; //Scancode
struct snake
{
    int n;
    int flag;
    xy body[100];
    path pt;
}sk;

struct word
{
    int n;
    int flag;
    xy chr[100];
}wd;

// �D�\��
void paintSnake()
{
    setcolor(CYAN);
    outtextxy(sk.body[0].x, sk.body[0].y ,"��");
    setcolor( rand() % 13 + 2 );
    for (int i=sk.n-1; i>0; i--)
    {
        outtextxy(sk.body[i].x, sk.body[i].y, "��");
    }
}

void moveSnake()
{
    sk.flag = 1;
    for (int i=sk.n-1; i > 0; i--)
    {
        sk.body[i].x = sk.body[i-1].x;
        sk.body[i].y = sk.body[i-1].y;
    }

    setcolor(GREEN);
    char arr[50];
    sprintf(arr,"X:%d , Y:%d",sk.body[0].x,sk.body[0].y);
    outtextxy(0,700,arr);


    switch (sk.pt)
    {
    case UP:
        sk.body[0].y -= SIZE;
        break;
    case DOWN:
        sk.body[0].y += SIZE;
        break;
    case LEFT:
        sk.body[0].x -= SIZE;
        break;
    case RIGHT:
        sk.body[0].x += SIZE;
        break;
    }
}

void changePath()
{
    switch (getch())
    {
    case 72:
        if (sk.pt != DOWN)
            sk.pt = UP;
        break;
    case 80:
        if (sk.pt != UP)
            sk.pt = DOWN;
        break;
    case 75:
        if (sk.pt != RIGHT)
            sk.pt = LEFT;
        break;
    case 77:
        if (sk.pt != LEFT)
            sk.pt = RIGHT;
        break;
    case 112:
        system("pause");
        Sleep(2000);
        break;
    }
}

// �r�\��
void loadWord()
{
    // #�ݷs�W - Ū���~���ɮפ�����r
    if (FFF.empty())
        FFF = "WORD";
}

void randomizeWord()
{
    srand(time(NULL));
    for (int i=0; i < FFF.length(); i++)
    {
        wd.chr[i].x = (rand() % 28 + 2)*SIZE;
        wd.chr[i].y = (rand() % 20 + 2)*SIZE;
        wd.flag=1; //������
    }
}

void printWord()
{
    setcolor(MAGENTA);
    for (int i=0; i < FFF.length(); i++)
    {
        char arr[50];
        sprintf(arr,"%c",FFF[i]);
        outtextxy(wd.chr[i].x, wd.chr[i].y, arr);
    }
}

void eatWord()
{
    for (int i=0; i < FFF.length(); i++)
    {
        if (sk.body[0].x == wd.chr[i].x && sk.body[0].y == wd.chr[i].y)
        {
            sk.n++;
            FFF.erase(i,1); // �q ��i��, �R�� 1�ӭ�
            wd.flag=0;
        }
    }
}

// �C���\��
void GameStart()
{
    cleardevice();

    isGameNow = true;

    sk.body[0].x = (rand() % 31 + 1)*SIZE;
    sk.body[0].y = (rand() % 24 + 1)*SIZE;
    sk.n = 1;
    sk.pt = P;
    sk.flag = 0;
    wd.flag = 0;

    cleardevice();
    setcolor(WHITE);
    outtextxy(400,250, "Game Start!");
    outtextxy(400,350, "�� P �Ȱ�");
    Sleep(2000);
}

void GameOver()
{
    // ����
    // if (sk.body[0].x < 0 || sk.body[0].y < 0 || sk.body[0].x > 960 || sk.body[0].y > 720)
    //     GameOver();

    // �L���
    if (sk.body[0].x < 0) sk.body[0].x = 960;
    if (sk.body[0].y < 0) sk.body[0].y = 720;
    if (sk.body[0].x > 960) sk.body[0].x = 0;
    if (sk.body[0].y > 720) sk.body[0].y = 0;

    // �ۼ�
    for (int i = sk.n-1; i > 0; i--)
    {
        if (sk.body[0].x == sk.body[i].x && sk.body[0].y == sk.body[i].y)
        {
            isGameNow = false;
            cleardevice();
            setcolor(RED);
            outtextxy(400,250,"Game Over!");
            Sleep(500);
            outtextxy(300,350, "�b�t�@�Ӥp�µ����A��J���N�䭫�s�}�l");
            system("pause");
            Sleep(1000);
        }
    }
}