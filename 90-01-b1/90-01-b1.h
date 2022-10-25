/*2151613 ¼Æ¿Æ Ã«ÓîÂ¼*/
#pragma once

#include "../include/cmd_console_tools.h"
#include <conio.h>
#include <iostream>
#include <iomanip>
#include <windows.h>
using namespace std;

void hanoi_main(int n, char src, char tmp, char dst, char mode);
void mode6(int flour, char src, char dst);
void speedtest();
void lie(char mode);
void hang();
void chushi(int flour, char qishi);
int hanoi_shuru(int* flour, char* qishi, char* zhongjian, char* mubiao, char ch);
void choose_mode(char mode, int n = 0, char src = '\0', char dst = '\0', char tmp = '\0');