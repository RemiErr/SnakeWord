#include <conio.h>
#include <graphics.h>
#include <bits/stdc++.h>
using namespace std;

#define SIZE 30
#define WINDOW_SIZE_WIDTH 600
#define WINDOW_SIZE_HIGH 450
#define BOARD_SIZE_WIDTH 320
#define ART_LEN 6

// �p��ͦ���ɡA�æV���Y2��
int sizeW = (WINDOW_SIZE_WIDTH / SIZE) - 2, sizeH = (WINDOW_SIZE_HIGH / SIZE) - 2;

string ascii_art[ART_LEN] = {
"�ݢ������ߢw�w�w�w�w���ߢw�w�w�w�w�����������ߢw�w�w�w�w�w����",
"���ݢ������w�w�w�w�w�����w�w�w�w�w�������������w�w�w�w�w�w����",
"���㢤���ޢ����ݢ����������ޢ����������������ࢤ���ޢ��ޢ�����",
"�㢤����������������������������������������������������������",
"���㢤��������������������������������������������������������",
"�㢤�����������������������䢤����w���������㢤�������㢤����"};

struct xy
{
    int x;
    int y;
};

enum path {STOP, UP, DOWN, LEFT, RIGHT};
struct snake
{
    int n;
    bool flag;
    xy pos[255];
    path pt;
}sk;

struct word
{
    int n;
    int row;
    int score;
    xy pos[255];
    string dict[255];
    string line;
    string spell;
    string ans;
}wd;

// �D�\��
void paintSnake()
{
    setcolor(CYAN);
    outtextxy(sk.pos[0].x, sk.pos[0].y ,"��");
    setcolor( rand() % 13 + 2 );
    for (int i=sk.n-1; i>0; i--)
    {
        outtextxy(sk.pos[i].x, sk.pos[i].y, "��");
    }
}

void moveSnake()
{
    for (int i=sk.n-1; i > 0; i--)
    {
        sk.pos[i].x = sk.pos[i-1].x;
        sk.pos[i].y = sk.pos[i-1].y;
    }

    switch (sk.pt)
    {
    case UP:
        sk.pos[0].y -= SIZE;
        delay(5);
        sk.flag = false;
        break;
    case DOWN:
        sk.pos[0].y += SIZE;
        delay(5);
        sk.flag = false;
        break;
    case LEFT:
        sk.pos[0].x -= SIZE;
        delay(5);
        sk.flag = false;
        break;
    case RIGHT:
        sk.pos[0].x += SIZE;
        delay(5);
        sk.flag = false;
        break;
    }
}

void changePath()
{
    switch (getch())
    {
    case 72:
        if (sk.flag == false && sk.pt != DOWN)
        {
            sk.flag = true;
            sk.pt = UP;
        }
        break;
    case 80:
        if (sk.flag == false && sk.pt != UP)
        {
            sk.flag = true;
            sk.pt = DOWN;
        }
        break;
    case 75:
        if (sk.flag == false && sk.pt != RIGHT)
        {
            sk.flag = true;
            sk.pt = LEFT;
        }
        break;
    case 77:
        if (sk.flag == false && sk.pt != LEFT)
        {
            sk.flag = true;
            sk.pt = RIGHT; 
        }
        break;
    case 112:
        system("pause");
        delay(2000);
        break;
    }
}

// �r�\��
void S2C(char A[], string B)
{ // string �v�ӥ�J char[]�A�P�ɦҼ{�r��s�����D
    string temp = B;
    A[ strlen(A) + temp.length() ] = '\0'; // ���ݻݥH'\0'�������A�_�h�|�ýX
    while(temp.length())
    {
        A[ strlen(A) + temp.length() - 1 ] = temp [ temp.length() - 1 ];
        temp.erase( temp.length() - 1, 1 ); // �R���@�Ӥ���
    }
}


void loadWord()
{
    // Ū���~���ɮפ�����r
    ifstream file("words.txt");

    if (file)
    {
        int i = 0;
        while (!file.eof())
        {
            getline(file, wd.dict[i]); // �إߦr��
            cout<<"dict: "<<wd.dict[i]<<endl; // #debug
            i++;
        }
        wd.n = i; // ���o�ɮ��`���
        cout<<"dict count: "<<wd.n<<endl; // #debug
        file.close();
    }else{
        printf("�}���ɮ׮ɹJ����~");
    }
}

void randWordPos()
{   
    for (int i=0; i < wd.line.length(); i++)
    {
        wd.pos[i].x = (rand() % sizeW + 1)*SIZE;
        wd.pos[i].y = (rand() % sizeH + 1)*SIZE;

        // �Y�r���ͦ��b�D���W�A�A���]�w x y �y��
        for (int j=0; j < sk.n; j++)
        {
            if (wd.pos[i].x == sk.pos[j].x && wd.pos[i].y == sk.pos[i].y)
            {
                wd.pos[i].x = (rand() % sizeW + 1)*SIZE;
                wd.pos[i].y = (rand() % sizeH + 1)*SIZE;
            }
        }
    }

    // �Y�r���ͦ��b�r���W�A�A���]�w x y �y��
    for (int i = wd.line.length(); i > 0; i--)
    {
        if (wd.pos[i].x == wd.pos[i-1].x && wd.pos[i].y == wd.pos[i-1].y)
        {
            wd.pos[i].x = (rand() % sizeW + 1)*SIZE;
            wd.pos[i].y = (rand() % sizeH + 1)*SIZE;
        }
    }
}

void printWord()
{
    setcolor(MAGENTA);
    for (int i=0; i < wd.line.length(); i++)
    {
        char buf[80] = { wd.line[i] };
        outtextxy(wd.pos[i].x, wd.pos[i].y, buf);
    }
}

void eatWord()
{
    for (int i=0; i < wd.line.length(); i++)
    {
        if (sk.pos[0].x == wd.pos[i].x && sk.pos[0].y == wd.pos[i].y)
        {
            sk.n++;
            wd.spell += wd.line[i];
            randWordPos();
            wd.line.erase(i, 1); // �q ��i��, �R�� 1�ӭ�
        }
    }
}

// �O���O
void showBoard()
{
    setcolor(GREEN);
    outtextxy(WINDOW_SIZE_WIDTH + SIZE, 0, "= = = = = = = < S.N.A.K.E > = = = = = = =");
    outtextxy(WINDOW_SIZE_WIDTH + SIZE*2, SIZE, "   -  -   -<   �� �� �� ��   >-   -  -   ");
    for (int i=0; i < WINDOW_SIZE_HIGH; i+=SIZE)
    {
        outtextxy(WINDOW_SIZE_WIDTH, i, "|        ");
    }

    char buf[40] = {};
    char buf_spell[100] = "Spell: ";
    const int WB_WIDTH = WINDOW_SIZE_WIDTH + 20;
    sprintf(buf, "Score: %d", wd.score);
    outtextxy(WB_WIDTH, 100, buf);

    S2C(buf_spell, wd.spell);
    outtextxy(WB_WIDTH, 200, buf_spell);

    sprintf(buf,"X: %3d, Y: %3d",sk.pos[0].x,sk.pos[0].y);
    outtextxy(WB_WIDTH + 10, WINDOW_SIZE_HIGH - SIZE, buf);
}

// �C���\��
void initGame()
{
    cleardevice();

    sk.pos[0].x = (rand() % sizeW + 1)*SIZE;
    sk.pos[0].y = (rand() % sizeH + 1)*SIZE;
    sk.n = 1;
    sk.pt = STOP;
    sk.flag = false;

    wd.row = 0;
    wd.score = 0;
    wd.line = "";
    wd.spell = "";

    cleardevice();
    setcolor(WHITE);
    for (int i=0; i < ART_LEN; i++)
    {
        char Abuf[255] = "";
        S2C(Abuf, ascii_art[i]);
        outtextxy((WINDOW_SIZE_WIDTH + BOARD_SIZE_WIDTH) / 4.6, 20*(i+1), Abuf);
    }
    outtextxy((WINDOW_SIZE_WIDTH + BOARD_SIZE_WIDTH) / 2.3, WINDOW_SIZE_HIGH / 3 + SIZE*2, "P��Ȱ��C��");
    delay(2000);
}

void GameCore()
{
    // ����
    // if (sk.pos[0].x < 0 || sk.pos[0].y < 0 || sk.pos[0].x > WINDOW_SIZE_WIDTH || sk.pos[0].y > WINDOW_SIZE_HIGH)
    //     GameCore();

    // �L���
    if (sk.pos[0].x < 0) sk.pos[0].x = WINDOW_SIZE_WIDTH - SIZE;
    if (sk.pos[0].y < 0) sk.pos[0].y = WINDOW_SIZE_HIGH - SIZE;
    if (sk.pos[0].x > WINDOW_SIZE_WIDTH - SIZE)  sk.pos[0].x = 0;
    if (sk.pos[0].y > WINDOW_SIZE_HIGH - SIZE)   sk.pos[0].y = 0;

    // �ۼ�
    for (int i = sk.n-1; i > 0; i--)
    {
        if (sk.pos[0].x == sk.pos[i].x && sk.pos[0].y == sk.pos[i].y)
        {
            cleardevice();
            setcolor(RED);
            outtextxy((WINDOW_SIZE_WIDTH + BOARD_SIZE_WIDTH) / 2.4, WINDOW_SIZE_HIGH / 3, "Game Over!");
            outtextxy((WINDOW_SIZE_WIDTH + BOARD_SIZE_WIDTH) / 3.1, WINDOW_SIZE_HIGH / 3 + SIZE*2, "�b�t�@�Ӥp�µ����A��J���N�䭫�s�}�l");
            system("pause");
            delay(1000);
            initGame();
        }
    }
}