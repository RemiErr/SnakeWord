#include <conio.h>
#include <graphics.h>
#include <bits/stdc++.h>
using namespace std;

#define SIZE 30
#define WINDOW_SIZE_WIDTH 960
#define WINDOW_SIZE_HIGH 720
#define BOARD_SIZE_WIDTH 320

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
void loadWord()
{
    // 讀取外部檔案中的單字
    ifstream file("words.txt");

    if (!file) printf("開啟檔案時遇到錯誤");

    // 取得檔案長度
    file.seekg(0, ios::end); // 移動到檔案尾端
    wd.n = file.tellg() / 5; // 取得檔案總行數
    cout<<"seekg: "<<wd.n<<endl; // #debug
    file.seekg(0); // 回到頂端
    
    int i = 0;
    while (!file.eof())
    {
        getline(file, wd.dict[i]); // 建立字典
        cout<<"dict: "<<wd.dict[i]<<endl; // #debug
        i++;
    }
    file.close();
}

void randWordPos()
{
    for (int i=0; i < wd.line.length(); i++)
    {
        wd.pos[i].x = (rand() % 30 + 1)*SIZE; // (950 / 30) = 32，邊界向內縮2格
        wd.pos[i].y = (rand() % 22 + 1)*SIZE; // (720 / 30) = 24

        // 若字元生成在蛇身上，再次設定 x y 座標
        for (int j=0; j < sk.n; j++)
        {
            if (wd.pos[i].x == sk.pos[j].x && wd.pos[i].y == sk.pos[i].y)
            {
                wd.pos[i].x = (rand() % 30 + 1)*SIZE;
                wd.pos[i].y = (rand() % 22 + 1)*SIZE;
            }
        }
    }
}

void printWord()
{
    setcolor(MAGENTA);
    for (int i=0; i < wd.line.length(); i++)
    {
        char buf[50];
        sprintf(buf,"%c", wd.line[i]);
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
            // wd.pos[i].x = wd.pos[i+1].x;
            // wd.pos[i].y = wd.pos[i+1].y;
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
    const int WB_WIDTH = WINDOW_SIZE_WIDTH + 20;
    for (int i=0; i < WINDOW_SIZE_HIGH; i+=SIZE)
    {
        outtextxy(WINDOW_SIZE_WIDTH, i, "|    ");
    }

    char buf[20] = {};
    sprintf(buf, "Score: %d", (sk.n - 1)*10);
    outtextxy(WB_WIDTH, 200, buf);

    char buf_spell[50] = "";
    sprintf (buf_spell,"Spell: ");
    for (int i = 0; i < wd.spell.length(); i++)
    {
        buf_spell[i + 7] = wd.spell[i];
    }
    buf_spell[wd.spell.length() + 7] = '\0';
    outtextxy(WB_WIDTH, 300, buf_spell);

    sprintf(buf,"X: %3d, Y: %3d",sk.pos[0].x,sk.pos[0].y);
    outtextxy(WB_WIDTH + 10, WINDOW_SIZE_HIGH - SIZE, buf);
}

// 遊戲功能
void initGame()
{
    cleardevice();

    sk.pos[0].x = (rand() % 31 + 1)*SIZE;
    sk.pos[0].y = (rand() % 24 + 1)*SIZE;
    sk.n = 1;
    sk.pt = STOP;
    sk.flag = false;

    wd.row = 0;
    wd.line = "";
    wd.spell = "";

    cleardevice();
    setcolor(WHITE);
    outtextxy((WINDOW_SIZE_WIDTH + BOARD_SIZE_WIDTH) / 2.3, WINDOW_SIZE_HIGH / 3, "Game Start!");
    outtextxy((WINDOW_SIZE_WIDTH + BOARD_SIZE_WIDTH) / 2.3, WINDOW_SIZE_HIGH / 3 + SIZE*2, "按 P 暫停");
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
    if (sk.pos[0].x >= WINDOW_SIZE_WIDTH)  sk.pos[0].x = 0;
    if (sk.pos[0].y >= WINDOW_SIZE_HIGH)   sk.pos[0].y = 0;

    // 自撞
    for (int i = sk.n-1; i > 0; i--)
    {
        if (sk.pos[0].x == sk.pos[i].x && sk.pos[0].y == sk.pos[i].y)
        {
            cleardevice();
            setcolor(RED);
            outtextxy((WINDOW_SIZE_WIDTH + BOARD_SIZE_WIDTH) / 2.3, WINDOW_SIZE_HIGH / 3, "Game Over!");
            outtextxy((WINDOW_SIZE_WIDTH + BOARD_SIZE_WIDTH) / 2.3, WINDOW_SIZE_HIGH / 3 + SIZE*2, "在另一個小黑窗中，輸入任意鍵重新開始");
            system("pause");
            delay(1000);
            initGame();
        }
    }
}