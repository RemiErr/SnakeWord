#include <conio.h>
#include <graphics.h>
#include <bits/stdc++.h>
using namespace std;

#define SIZE 30
#define WINDOW_SIZE_WIDTH 600
#define WINDOW_SIZE_HIGH 450
#define BOARD_SIZE_WIDTH 320
#define ART_LEN 6

// 計算生成邊界，並向內縮2格
int sizeW = (WINDOW_SIZE_WIDTH / SIZE) - 2, sizeH = (WINDOW_SIZE_HIGH / SIZE) - 2;

string ascii_art[ART_LEN] = {
"╔═══╗─────╔╗─────╔╗╔╗╔╗──────╔╗",
"║╔═╗║─────║║─────║║║║║║──────║║",
"║╚══╦═╗╔══╣║╔╦══╗║║║║║╠══╦═╦═╝║",
"╚══╗║╔╗╣╔╗║╚╝╣║═╣║╚╝╚╝║╔╗║╔╣╔╗║",
"║╚═╝║║║║╔╗║╔╗╣║═╣╚╗╔╗╔╣╚╝║║║╚╝║",
"╚═══╩╝╚╩╝╚╩╝╚╩══╝─╚╝╚╝╚══╩╝╚══╝"};

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

// 蛇功能
void paintSnake()
{
    setcolor(CYAN);
    outtextxy(sk.pos[0].x, sk.pos[0].y ,"※");
    setcolor( rand() % 13 + 2 );
    for (int i=sk.n-1; i>0; i--)
    {
        outtextxy(sk.pos[i].x, sk.pos[i].y, "＊");
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

// 字功能
void S2C(char A[], string B)
{ // string 逐個丟入 char[]，同時考慮字串連接問題
    string temp = B;
    A[ strlen(A) + temp.length() ] = '\0'; // 尾端需以'\0'做結尾，否則會亂碼
    while(temp.length())
    {
        A[ strlen(A) + temp.length() - 1 ] = temp [ temp.length() - 1 ];
        temp.erase( temp.length() - 1, 1 ); // 刪除一個元素
    }
}


void loadWord()
{
    // 讀取外部檔案中的單字
    ifstream file("words.txt");

    if (file)
    {
        int i = 0;
        while (!file.eof())
        {
            getline(file, wd.dict[i]); // 建立字典
            cout<<"dict: "<<wd.dict[i]<<endl; // #debug
            i++;
        }
        wd.n = i; // 取得檔案總行數
        cout<<"dict count: "<<wd.n<<endl; // #debug
        file.close();
    }else{
        printf("開啟檔案時遇到錯誤");
    }
}

void randWordPos()
{   
    for (int i=0; i < wd.line.length(); i++)
    {
        wd.pos[i].x = (rand() % sizeW + 1)*SIZE;
        wd.pos[i].y = (rand() % sizeH + 1)*SIZE;

        // 若字元生成在蛇身上，再次設定 x y 座標
        for (int j=0; j < sk.n; j++)
        {
            if (wd.pos[i].x == sk.pos[j].x && wd.pos[i].y == sk.pos[i].y)
            {
                wd.pos[i].x = (rand() % sizeW + 1)*SIZE;
                wd.pos[i].y = (rand() % sizeH + 1)*SIZE;
            }
        }
    }

    // 若字元生成在字身上，再次設定 x y 座標
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
            wd.line.erase(i, 1); // 從 第i個, 刪除 1個值
        }
    }
}

// 記分板
void showBoard()
{
    setcolor(GREEN);
    outtextxy(WINDOW_SIZE_WIDTH + SIZE, 0, "= = = = = = = < S.N.A.K.E > = = = = = = =");
    outtextxy(WINDOW_SIZE_WIDTH + SIZE*2, SIZE, "   -  -   -<   ← ↑ ↓ →   >-   -  -   ");
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

// 遊戲功能
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
    outtextxy((WINDOW_SIZE_WIDTH + BOARD_SIZE_WIDTH) / 2.3, WINDOW_SIZE_HIGH / 3 + SIZE*2, "P鍵暫停遊戲");
    delay(2000);
}

void GameCore()
{
    // 撞牆
    // if (sk.pos[0].x < 0 || sk.pos[0].y < 0 || sk.pos[0].x > WINDOW_SIZE_WIDTH || sk.pos[0].y > WINDOW_SIZE_HIGH)
    //     GameCore();

    // 無邊界
    if (sk.pos[0].x < 0) sk.pos[0].x = WINDOW_SIZE_WIDTH - SIZE;
    if (sk.pos[0].y < 0) sk.pos[0].y = WINDOW_SIZE_HIGH - SIZE;
    if (sk.pos[0].x > WINDOW_SIZE_WIDTH - SIZE)  sk.pos[0].x = 0;
    if (sk.pos[0].y > WINDOW_SIZE_HIGH - SIZE)   sk.pos[0].y = 0;

    // 自撞
    for (int i = sk.n-1; i > 0; i--)
    {
        if (sk.pos[0].x == sk.pos[i].x && sk.pos[0].y == sk.pos[i].y)
        {
            cleardevice();
            setcolor(RED);
            outtextxy((WINDOW_SIZE_WIDTH + BOARD_SIZE_WIDTH) / 2.4, WINDOW_SIZE_HIGH / 3, "Game Over!");
            outtextxy((WINDOW_SIZE_WIDTH + BOARD_SIZE_WIDTH) / 3.1, WINDOW_SIZE_HIGH / 3 + SIZE*2, "在另一個小黑窗中，輸入任意鍵重新開始");
            system("pause");
            delay(1000);
            initGame();
        }
    }
}