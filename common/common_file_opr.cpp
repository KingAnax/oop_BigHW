/*2151613 Ã«ÓîÂ¼ ¼Æ¿Æ*/
#include "90-02-b5.h"

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

int tp(ifstream &fin)
{
    return 0;
}