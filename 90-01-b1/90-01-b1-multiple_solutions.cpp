/*2151613 计科 毛宇录*/

#include "90-01-b1.h"

/* ----------------------------------------------------------------------------------

     本文件功能：
    1、存放被 hanoi_main.cpp 中根据菜单返回值调用的各菜单项对应的执行函数

     本文件要求：
    1、不允许定义外部全局变量（const及#define不在限制范围内）
    2、允许定义静态全局变量（具体需要的数量不要超过文档显示，全局变量的使用准则是：少用、慎用、能不用尽量不用）
    3、静态局部变量的数量不限制，但使用准则也是：少用、慎用、能不用尽量不用
    4、按需加入系统头文件、自定义头文件、命名空间等

   ----------------------------------------------------------------------------------- */


   /***************************************************************************
     函数名称：
     功    能：
     输入参数：
     返 回 值：
     说    明：
   ***************************************************************************/

int num = 0;//记录步数
int speed;//延时
int Array[3][10] = { 0 };//现有盘编号
int number[3] = { 0 };//现有盘数量

void speedtest(void)//延时
{
    if (speed == 0)
    {
        char a;
        a = _getch();
        if (a != '\r')
        {
            speedtest();
        }
    }
    else if (speed == 1)
    {
        Sleep(1000);
    }
    else if (speed == 2)
    {
        Sleep(500);
    }
    else if (speed == 3)
    {
        Sleep(100);
    }
    else if (speed == 4)
    {
        Sleep(20);
    }
    else if (speed == 5)
    {
        Sleep(1 / 30);
    }
}

void lie(char mode)//打印纵向数组
{
    int a;
    if ((mode != '8') && (mode != '9'))
        a = 11;
    else
        a = 26;
    for (int i = 1; i <= 10; i++)
    {
        cct_gotoxy(11, a);
        if (Array[0][i - 1] != 0)
        {
            cout << Array[0][i - 1];
            a -= 1;
        }
        else
        {
            cout << "  ";
            a -= 1;
        }
    }
    if ((mode != '8') && (mode != '9'))
        a = 11;
    else
        a = 26;
    for (int i = 1; i <= 10; i++)
    {
        cct_gotoxy(21, a);
        if (Array[1][i - 1] != 0)
        {
            cout << Array[1][i - 1];
            a -= 1;
        }
        else
        {
            cout << "  ";
            a -= 1;
        }
    }
    if ((mode != '8') && (mode != '9'))
        a = 11;
    else
        a = 26;
    for (int i = 1; i <= 10; i++)
    {
        cct_gotoxy(31, a);
        if (Array[2][i - 1] != 0)
        {
            cout << Array[2][i - 1];
            a -= 1;
        }
        else
        {
            cout << "  ";
            a -= 1;
        }
    }
    if ((mode != '8') && (mode != '9'))
        cct_gotoxy(0, 12);
    else
        cct_gotoxy(0, 27);
    cout << "         =========================\n           A         B         C" << endl;
}

void hang(void) //打印横向数组
{
    cout << " A:";
    for (int i = 1; i <= 10; i++)
    {
        if (Array[0][i - 1] != 0)
            cout << setw(2) << Array[0][i - 1];
        else
            cout << setw(2) << "";
    }
    cout << " B:";
    for (int i = 1; i <= 10; i++)
    {
        if (Array[1][i - 1] != 0)
            cout << setw(2) << Array[1][i - 1];
        else
            cout << setw(2) << "";
    }
    cout << " C:";
    for (int i = 1; i <= 10; i++)
    {
        if (Array[2][i - 1] != 0)
            cout << setw(2) << Array[2][i - 1];
        else
            cout << setw(2) << "";
    }
    cout << endl;
}

void vary(char src, char dst) //数组变换
{
    if ((src == 'A') && (dst == 'B'))
    {
        Array[1][number[1]++] = Array[0][number[0] - 1];
        Array[0][number[0]-- - 1] = 0;
    }
    if ((src == 'A') && (dst == 'C'))
    {
        Array[2][number[2]++] = Array[0][number[0] - 1];
        Array[0][number[0]-- - 1] = 0;
    }
    if ((src == 'B') && (dst == 'A'))
    {
        Array[0][number[0]++] = Array[1][number[1] - 1];
        Array[1][number[1]-- - 1] = 0;
    }
    if ((src == 'B') && (dst == 'C'))
    {
        Array[2][number[2]++] = Array[1][number[1] - 1];
        Array[1][number[1]-- - 1] = 0;
    }
    if ((src == 'C') && (dst == 'A'))
    {
        Array[0][number[0]++] = Array[2][number[2] - 1];
        Array[2][number[2]-- - 1] = 0;
    }
    if ((src == 'C') && (dst == 'B'))
    {
        Array[1][number[1]++] = Array[2][number[2] - 1];
        Array[2][number[2]-- - 1] = 0;
    }
}

int hanoi_shuru(int* flour, char* qishi, char* zhongjian, char* mubiao, char ch)//输入参数
{
    cout << "请输入汉诺塔的层数(1-10)：\n";
    cin >> *flour;
    while (*flour < 1 || *flour > 10 || cin.fail())
    {
        cin.clear();
        cin.ignore(65536, '\n');
        cout << "请输入汉诺塔的层数(1-10)：\n";
        cin >> *flour;
    }
    cin.ignore(65536, '\n');
    cout << "请输入起始柱(A-C)：\n";
    cin >> *qishi;
    if (*qishi == 'a')
        *qishi = 'A';
    if (*qishi == 'b')
        *qishi = 'B';
    if (*qishi == 'c')
        *qishi = 'C';
    while (*qishi < 'A' || *qishi > 'C' || cin.fail())
    {
        cin.clear();
        cin.ignore(65536, '\n');
        cout << "请输入起始柱(A-C)：\n";
        cin >> *qishi;
        if (*qishi == 'a')
            *qishi = 'A';
        if (*qishi == 'b')
            *qishi = 'B';
        if (*qishi == 'c')
            *qishi = 'C';
    }
    cin.ignore(65536, '\n');
    cout << "请输入目标柱(A-C)：\n";
    cin >> *mubiao;
    if (*mubiao == 'a')
        *mubiao = 'A';
    if (*mubiao == 'b')
        *mubiao = 'B';
    if (*mubiao == 'c')
        *mubiao = 'C';
    while (*mubiao < 'A' || *mubiao > 'C' || cin.fail() || *mubiao == *qishi)
    {
        cin.clear();
        cin.ignore(65536, '\n');
        if (*mubiao == *qishi)
            cout << "目标柱(" << *mubiao << ")不能与起始柱(" << *qishi << ")相同\n";
        cout << "请输入目标柱(A-C)：\n";
        cin >> *mubiao;
        if (*mubiao == 'a')
            *mubiao = 'A';
        if (*mubiao == 'b')
            *mubiao = 'B';
        if (*mubiao == 'c')
            *mubiao = 'C';
    }
    cin.ignore(65536, '\n');
    if ((*qishi == 'A') && (*mubiao == 'B'))
        *zhongjian = 'C';
    if ((*qishi == 'A') && (*mubiao == 'C'))
        *zhongjian = 'B';
    if ((*qishi == 'B') && (*mubiao == 'A'))
        *zhongjian = 'C';
    if ((*qishi == 'B') && (*mubiao == 'C'))
        *zhongjian = 'A';
    if ((*qishi == 'C') && (*mubiao == 'A'))
        *zhongjian = 'B';
    if ((*qishi == 'C') && (*mubiao == 'B'))
        *zhongjian = 'A';
    if (ch == '4' || ch == '8')
    {
        cout << "请输入移动速度(0-5: 0-按回车单步演示 1-延时最长 5-延时最短)" << endl;
        cin >> speed;
        while (speed < 0 || speed > 5 || cin.fail())
        {
            cin.clear();
            cin.ignore(65536, '\n');
            cout << "请输入移动速度(0-5: 0-按回车单步演示 1-延时最长 5-延时最短)\n";
            cin >> speed;
        }
        cin.ignore(65536, '\n');
    }
    return speed;
}

void zhuzi(void)
{
    cct_showch(1, 15, ' ', 14, 14, 23);
    cct_showch(34, 15, ' ', 14, 14, 23);
    cct_showch(67, 15, ' ', 14, 14, 23);
    for (int i = 1; i <= 12; i++)
    {
        cct_showch(12, 15 - i, ' ', 14, 14, 1);
        cct_showch(45, 15 - i, ' ', 14, 14, 1);
        cct_showch(78, 15 - i, ' ', 14, 14, 1);
        Sleep(200);
    }
}

void yidong(int flour, char src, char dst, int Array[][10], int number[])
{
    int bg_color, fg_color, y = 15 - number[src - 'A'];
    if (flour < 7)
    {
        bg_color = flour;
        fg_color = flour;
    }
    else
    {
        bg_color = flour + 2;
        fg_color = flour + 2;
    }
    for (; y > 1; y--)
    {
        cct_showch(12 - Array[src - 'A'][number[src - 'A'] - 1] + 33 * (src - 'A'), y, ' ', 0, 7, Array[src - 'A'][number[src - 'A'] - 1]);
        if (y != 2)
            cct_showch(12 + 33 * (src - 'A'), y, ' ', 14, 14, 1);
        else
            cct_showch(12 + 33 * (src - 'A'), y, ' ', 0, 7, 1);
        cct_showch(13 + 33 * (src - 'A'), y, ' ', 0, 7, Array[src - 'A'][number[src - 'A'] - 1]);
        cct_showch(12 - Array[src - 'A'][number[src - 'A'] - 1] + 33 * (src - 'A'), y - 1, ' ', bg_color, fg_color, Array[src - 'A'][number[src - 'A'] - 1] * 2 + 1);
        if (speed == 1)
            Sleep(500);
        else if (speed == 3)
            Sleep(25);
        else if (speed == 4)
            Sleep(5);
        else if (speed == 5)
            Sleep(1 / 30);
        else
            Sleep(100);
    }
    if (dst > src)
    {
        for (int i = 1; i <= (dst - src) * 33; i++)
        {
            cct_showch(11 - Array[src - 'A'][number[src - 'A'] - 1] + 33 * (src - 'A') + i, y, ' ', 0, 7, 1);
            cct_showch(12 + Array[src - 'A'][number[src - 'A'] - 1] + 33 * (src - 'A') + i, y, ' ', bg_color, fg_color, 1);
            if (speed == 1)
                Sleep(500);
            else if (speed == 3)
                Sleep(25);
            else if (speed == 4)
                Sleep(5);
            else if (speed == 5)
                Sleep(1 / 30);
            else
                Sleep(100);
        }
    }
    else
    {
        for (int i = 1; i <= (src - dst) * 33; i++)
        {
            cct_showch(13 + Array[src - 'A'][number[src - 'A'] - 1] + 33 * (src - 'A') - i, y, ' ', 0, 7, 1);
            cct_showch(12 - Array[src - 'A'][number[src - 'A'] - 1] + 33 * (src - 'A') - i, y, ' ', bg_color, fg_color, 1);
            if (speed == 1)
                Sleep(500);
            else if (speed == 3)
                Sleep(25);
            else if (speed == 4)
                Sleep(5);
            else if (speed == 5)
                Sleep(1 / 30);
            else
                Sleep(100);
        }
    }
    y = 2;
    cct_showch(12 - Array[src - 'A'][number[src - 'A'] - 1] + 33 * (dst - 'A'), 1, ' ', 0, 7, Array[src - 'A'][number[src - 'A'] - 1] * 2 + 1);
    for (; y < 14 - number[dst - 'A']; y++)
    {
        cct_showch(12 - Array[src - 'A'][number[src - 'A'] - 1] + 33 * (dst - 'A'), y, ' ', 0, 7, Array[src - 'A'][number[src - 'A'] - 1]);
        if (y != 2)
            cct_showch(12 + 33 * (dst - 'A'), y, ' ', 14, 14, 1);
        else
            cct_showch(12 + 33 * (dst - 'A'), y, ' ', 0, 7, 1);
        cct_showch(13 + 33 * (dst - 'A'), y, ' ', 0, 7, Array[src - 'A'][number[src - 'A'] - 1]);
        cct_showch(12 - Array[src - 'A'][number[src - 'A'] - 1] + 33 * (dst - 'A'), y + 1, ' ', bg_color, fg_color, Array[src - 'A'][number[src - 'A'] - 1] * 2 + 1);
        if (speed == 1)
            Sleep(500);
        else if (speed == 3)
            Sleep(25);
        else if (speed == 4)
            Sleep(5);
        else if (speed == 5)
            Sleep(1 / 30);
        else
            Sleep(100);
    }
    cct_setcolor(COLOR_BLACK, COLOR_WHITE);
}

void mode1(char src, char dst, int n)//模式1
{
    cout << n << "# " << src << "---->" << dst << endl;
}

void mode2(char src, char dst, int n)//模式2
{
    num++;
    cout << "第" << setw(4) << num << " 步" << "(" << setw(2) << n << "#: " << src << "-->" << dst << ")" << endl;
}

void mode3(char src, char dst, int n)//模式3
{
    num++;
    cout << "第" << setw(4) << num << " 步" << "(" << setw(2) << n << "#: " << src << "-->" << dst << ")";
    vary(src, dst);
    hang();
}

void mode4(char src, char dst, int n)//模式4
{
    num++;
    cct_gotoxy(0, 17);
    cout << "第" << setw(4) << num << " 步" << "(" << setw(2) << n << "#: " << src << "-->" << dst << ")   ";
    lie('4');
    vary(src, dst);
    cct_gotoxy(22, 17);
    hang();
    lie('4');
    speedtest();
    cct_gotoxy(0, 18);
}

void mode5(void)//模式5
{
    cct_cls();
    zhuzi();
}

void mode6(int flour, char src, char dst)//模式6
{
    zhuzi();
    if (flour < 7)
    {
        for (int i = 1; i <= flour; i++)
        {
            cct_showch(11 + 33 * (src - 'A') - flour + i, 15 - i, ' ', flour - i + 1, flour - i + 1, 2 * (flour - i + 1) + 1);
            Sleep(50);
        }
    }
    else
    {
        for (int i = 1; i <= flour; i++)
        {
            if (i < 5)
                cct_showch(11 + 33 * (src - 'A') - flour + i, 15 - i, ' ', flour + 3 - i, flour + 3 - i, 2 * (flour - i + 1) + 1);
            else
                cct_showch(11 + 33 * (src - 'A') - flour + i, 15 - i, ' ', flour - i + 1, flour - i + 1, 2 * (flour - i + 1) + 1);
            Sleep(50);
        }
    }
}

void mode7(int flour, char src, char dst, char tmp)//模式7  （柱子调用了6，不再该函数内）
{
    speed = 2;
    num++;
    if (num > 1)
        return;
    yidong(flour, src, dst, Array, number);
}

void mode8(char src, char dst, int n)//模式8  （柱子调用了6，不再该函数内）
{
    int number8[3], Array8[3][10];
    for (int i = 0; i < 3; i++)
    {
        number8[i] = number[i];
        for (int x = 0; x < 10; x++)
        {
            Array8[i][x] = Array[i][x];
        }
    }
    num++;
    cct_gotoxy(0, 32);
    cout << "第" << setw(4) << num << " 步" << "(" << setw(2) << n << "#: " << src << "-->" << dst << ")   ";
    lie('8');
    vary(src, dst);
    cct_gotoxy(22, 32);
    hang();
    lie('8');
    yidong(n, src, dst, Array8, number8);
    speedtest();
    cct_gotoxy(0, 33);
}

void mode9(char src, char dst, int n)//模式9  （柱子调用了6，盘子的移动调用了模式8）
{
    cct_cls();
    cout << "从 " << src << " 移动到 " << dst << " ,共 " << n << " 层";
    cct_gotoxy(0, 32);
    cout << "初始:" << setw(17) << "";
    hang();
    lie('9');
    mode6(n, src, dst);
    cct_setcolor(COLOR_BLACK, COLOR_WHITE);
    cct_setcursor(2);
    char ch;
    char letter[30];
    for (int i = 0; i < 30; i++)
    {
        letter[i] = '\0';
    }
    int sum = 0;
    while (1)
    {
        cct_gotoxy(0, 34);
        cout << "请输入移动的柱号(命令形式：AC=A顶端的盘子移动到C，Q=退出) ：";
        cout << setw(30) << "";
        cct_gotoxy(60, 34);
        ch = _getch();
        while (ch != '\r')
        {
            if ((ch != ' ') && (ch != '\b') && (ch > 26))
                cout << ch;
            if ((ch >= 'a') && (ch <= 'c'))
                ch -= 32;
            if ((ch != ' ') && (ch != '\b') && (ch > 26))
                letter[sum++] = ch;
            if (ch == -32)
                ch = _getch();
            ch = _getch();
            if (sum == 19)
                break;
        }
        if ((sum == 1) && (letter[0] == 'q' || letter[0] == 'Q'))
        {
            cct_gotoxy(0, 35);
            cout << "游戏结束!!!!!" << endl;
            return;
        }
        if ((sum == 2) && (letter[0] >= 'A') && (letter[1] >= 'A') && (letter[0] <= 'C') && (letter[1] <= 'C') && (letter[1] != letter[0]))
        {
            if (number[letter[0] - 'A'] == 0)
            {
                cct_gotoxy(0, 35);
                cout << "源柱为空!";
                Sleep(1250);
                cct_gotoxy(0, 35);
                cout << setw(25) << "";
            }
            else if ((number[letter[1] - 'A'] != 0))
            {
                if (Array[letter[0] - 'A'][number[letter[0] - 'A'] - 1] > Array[letter[1] - 'A'][number[letter[1] - 'A'] - 1])
                {
                    cct_gotoxy(0, 35);
                    cout << "大盘压小盘，非法移动!";
                    Sleep(1250);
                    cct_gotoxy(0, 35);
                    cout << setw(25) << "";
                }
                else
                {
                    speed = 5;
                    cct_setcursor(3);
                    mode8(letter[0], letter[1], Array[letter[0] - 'A'][number[letter[0] - 'A'] - 1]);
                    cct_setcolor(COLOR_BLACK, COLOR_WHITE);
                    cct_setcursor(2);
                }
            }
            else
            {
                speed = 5;
                cct_setcursor(3);
                mode8(letter[0], letter[1], Array[letter[0] - 'A'][number[letter[0] - 'A'] - 1]);
                cct_setcolor(COLOR_BLACK, COLOR_WHITE);
                cct_setcursor(2);
            }
            if (number[dst - 'A'] == n)
            {
                cct_gotoxy(0, 35);
                cout << "游戏结束!!!!!" << endl;
                return;
            }
        }
        sum = 0;
        for (int i = 0; i < 30; i++)
        {
            letter[i] = '\0';
        }
    }
}

void choose_mode(char mode, int n, char src, char dst, char tmp)//选择模式
{
    if (mode == '1')
        mode1(src, dst, n);
    else if (mode == '2')
        mode2(src, dst, n);
    else if (mode == '3')
        mode3(src, dst, n);
    else if (mode == '4')
        mode4(src, dst, n);
    else if (mode == '5')
        mode5();
    else if (mode == '6')
        mode6(n, src, dst);
    else if (mode == '7')
        mode7(n, src, dst, tmp);
    else if (mode == '8')
        mode8(src, dst, n);
    else if (mode == '9')
        mode9(src, dst, n);
}

void hanoi_main(int n, char src, char tmp, char dst, char mode)//递归函数
{
    if (n == 1)
        choose_mode(mode, n, src, dst);
    else
    {
        hanoi_main(n - 1, src, dst, tmp, mode);
        choose_mode(mode, n, src, dst);
        hanoi_main(n - 1, tmp, src, dst, mode);
    }
}

void chushi(int flour, char qishi)//初始化数组
{
    for (int i = 0; i < 10; i++)
    {
        Array[0][i] = 0;
        Array[1][i] = 0;
        Array[2][i] = 0;
    }
    number[0] = 0, number[1] = 0, number[2] = 0, num = 0;
    if (qishi == 'A')
    {
        for (int i = 1; i <= flour; i++)
        {
            Array[0][i - 1] = flour - i + 1;
        }
        number[0] = flour;
    }
    if (qishi == 'B')
    {
        for (int i = 1; i <= flour; i++)
        {
            Array[1][i - 1] = flour - i + 1;
        }
        number[1] = flour;
    }
    if (qishi == 'C')
    {
        for (int i = 1; i <= flour; i++)
        {
            Array[2][i - 1] = flour - i + 1;
        }
        number[2] = flour;
    }
}

