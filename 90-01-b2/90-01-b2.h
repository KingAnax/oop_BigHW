/*2151613 ¼Æ¿Æ Ã«ÓîÂ¼*/
#pragma once

#include "../include/cmd_console_tools.h"
#include "../include/common_class_of_dispel.h"
#include <iostream>
#include <iomanip>
#include <conio.h>
#include <windows.h>
#include <ctime>

using namespace std;

#define start 3
#define row_min 5
#define row_max 8
#define column_min 5
#define column_max 10
#define target_min 5
#define target_max 20

void mode1(void);
void mode2(void);
void mode3(void);
void mode4(void);
void mode5(void);
void mode6(void);
void mode7(void);
void mode8(void);
void mode9(void);
void combine_picture_2(int row, int column, int i, int* num, int* num_new);
int fall_picture(int row, int column, int* num, int* num_new, int mode = 0);
void print_map_picture(int row, int column, int* num);
int chance_number(int stage = 3);
void find2(int i, int row, int* num, int* num_new);
void find3(int i, int row, int* num, int* num_new);
void putin_color(int r, int c, int* num, int mode);
void tepan_new_recursion(int i, int row, int* num, int* num_new);
void tepan_new_recursion2(int i, int row, int* num, int* num_new);
void new_data(int row, int column, int* num, int* num_new, int* stage);
void score_count(int* total_score, int* num, int* num_new, int target);