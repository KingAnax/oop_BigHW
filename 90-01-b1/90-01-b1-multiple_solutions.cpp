/*2151613 �ƿ� ë��¼*/

#include "90-01-b1.h"

/* ----------------------------------------------------------------------------------

     ���ļ����ܣ�
    1����ű� hanoi_main.cpp �и��ݲ˵�����ֵ���õĸ��˵����Ӧ��ִ�к���

     ���ļ�Ҫ��
    1�����������ⲿȫ�ֱ�����const��#define�������Ʒ�Χ�ڣ�
    2�������徲̬ȫ�ֱ�����������Ҫ��������Ҫ�����ĵ���ʾ��ȫ�ֱ�����ʹ��׼���ǣ����á����á��ܲ��þ������ã�
    3����̬�ֲ����������������ƣ���ʹ��׼��Ҳ�ǣ����á����á��ܲ��þ�������
    4���������ϵͳͷ�ļ����Զ���ͷ�ļ��������ռ��

   ----------------------------------------------------------------------------------- */


   /***************************************************************************
     �������ƣ�
     ��    �ܣ�
     ���������
     �� �� ֵ��
     ˵    ����
   ***************************************************************************/

int num = 0;//��¼����
int speed;//��ʱ
int Array[3][10] = { 0 };//�����̱��
int number[3] = { 0 };//����������

void speedtest(void)//��ʱ
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

void lie(char mode)//��ӡ��������
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

void hang(void) //��ӡ��������
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

void vary(char src, char dst) //����任
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

int hanoi_shuru(int* flour, char* qishi, char* zhongjian, char* mubiao, char ch)//�������
{
    cout << "�����뺺ŵ���Ĳ���(1-10)��\n";
    cin >> *flour;
    while (*flour < 1 || *flour > 10 || cin.fail())
    {
        cin.clear();
        cin.ignore(65536, '\n');
        cout << "�����뺺ŵ���Ĳ���(1-10)��\n";
        cin >> *flour;
    }
    cin.ignore(65536, '\n');
    cout << "��������ʼ��(A-C)��\n";
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
        cout << "��������ʼ��(A-C)��\n";
        cin >> *qishi;
        if (*qishi == 'a')
            *qishi = 'A';
        if (*qishi == 'b')
            *qishi = 'B';
        if (*qishi == 'c')
            *qishi = 'C';
    }
    cin.ignore(65536, '\n');
    cout << "������Ŀ����(A-C)��\n";
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
            cout << "Ŀ����(" << *mubiao << ")��������ʼ��(" << *qishi << ")��ͬ\n";
        cout << "������Ŀ����(A-C)��\n";
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
        cout << "�������ƶ��ٶ�(0-5: 0-���س�������ʾ 1-��ʱ� 5-��ʱ���)" << endl;
        cin >> speed;
        while (speed < 0 || speed > 5 || cin.fail())
        {
            cin.clear();
            cin.ignore(65536, '\n');
            cout << "�������ƶ��ٶ�(0-5: 0-���س�������ʾ 1-��ʱ� 5-��ʱ���)\n";
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

void mode1(char src, char dst, int n)//ģʽ1
{
    cout << n << "# " << src << "---->" << dst << endl;
}

void mode2(char src, char dst, int n)//ģʽ2
{
    num++;
    cout << "��" << setw(4) << num << " ��" << "(" << setw(2) << n << "#: " << src << "-->" << dst << ")" << endl;
}

void mode3(char src, char dst, int n)//ģʽ3
{
    num++;
    cout << "��" << setw(4) << num << " ��" << "(" << setw(2) << n << "#: " << src << "-->" << dst << ")";
    vary(src, dst);
    hang();
}

void mode4(char src, char dst, int n)//ģʽ4
{
    num++;
    cct_gotoxy(0, 17);
    cout << "��" << setw(4) << num << " ��" << "(" << setw(2) << n << "#: " << src << "-->" << dst << ")   ";
    lie('4');
    vary(src, dst);
    cct_gotoxy(22, 17);
    hang();
    lie('4');
    speedtest();
    cct_gotoxy(0, 18);
}

void mode5(void)//ģʽ5
{
    cct_cls();
    zhuzi();
}

void mode6(int flour, char src, char dst)//ģʽ6
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

void mode7(int flour, char src, char dst, char tmp)//ģʽ7  �����ӵ�����6�����ٸú����ڣ�
{
    speed = 2;
    num++;
    if (num > 1)
        return;
    yidong(flour, src, dst, Array, number);
}

void mode8(char src, char dst, int n)//ģʽ8  �����ӵ�����6�����ٸú����ڣ�
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
    cout << "��" << setw(4) << num << " ��" << "(" << setw(2) << n << "#: " << src << "-->" << dst << ")   ";
    lie('8');
    vary(src, dst);
    cct_gotoxy(22, 32);
    hang();
    lie('8');
    yidong(n, src, dst, Array8, number8);
    speedtest();
    cct_gotoxy(0, 33);
}

void mode9(char src, char dst, int n)//ģʽ9  �����ӵ�����6�����ӵ��ƶ�������ģʽ8��
{
    cct_cls();
    cout << "�� " << src << " �ƶ��� " << dst << " ,�� " << n << " ��";
    cct_gotoxy(0, 32);
    cout << "��ʼ:" << setw(17) << "";
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
        cout << "�������ƶ�������(������ʽ��AC=A���˵������ƶ���C��Q=�˳�) ��";
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
            cout << "��Ϸ����!!!!!" << endl;
            return;
        }
        if ((sum == 2) && (letter[0] >= 'A') && (letter[1] >= 'A') && (letter[0] <= 'C') && (letter[1] <= 'C') && (letter[1] != letter[0]))
        {
            if (number[letter[0] - 'A'] == 0)
            {
                cct_gotoxy(0, 35);
                cout << "Դ��Ϊ��!";
                Sleep(1250);
                cct_gotoxy(0, 35);
                cout << setw(25) << "";
            }
            else if ((number[letter[1] - 'A'] != 0))
            {
                if (Array[letter[0] - 'A'][number[letter[0] - 'A'] - 1] > Array[letter[1] - 'A'][number[letter[1] - 'A'] - 1])
                {
                    cct_gotoxy(0, 35);
                    cout << "����ѹС�̣��Ƿ��ƶ�!";
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
                cout << "��Ϸ����!!!!!" << endl;
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

void choose_mode(char mode, int n, char src, char dst, char tmp)//ѡ��ģʽ
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

void hanoi_main(int n, char src, char tmp, char dst, char mode)//�ݹ麯��
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

void chushi(int flour, char qishi)//��ʼ������
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

