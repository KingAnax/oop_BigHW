/*2151613 毛宇录 计科*/
#include "../include/common_file_opr.h"

int file_size(ifstream &fin)
{
    int cur = (int)fin.tellg();
    int l, r;
    fin.seekg(0, ios::beg);
    l = (int)fin.tellg();
    fin.seekg(0, ios::end);
    r = (int)fin.tellg();
    fin.seekg(0, cur);
    return r - l;
}

static double get_float()
{
    int x, y;
    cout << " 请输入跳转位置百分比，最多取两位小数：";
    cct_getxy(x, y);
    double value;
    cin >> value;
    while (cin.fail() || value < 0 || value > 100) {
        cin.clear();
        cin.ignore(65536, '\n');
        cct_gotoxy(x, y);
        cout << "                 ";
        cct_gotoxy(x, y);
        cin >> value;
    }
    value = ((double)((int)(value * 100))) / 10000;
    return value;
}

int tp(int file_size)
{
    double value = get_float();
    int pos = (int)(value * file_size);
    return pos;
}