//2151613 ¼Æ¿Æ Ã«ÓîÂ¼
#pragma once

#include <iostream>
#include <ctime>
#include "../include/cmd_console_tools.h"
#include "../include/common_input.h"
#include "../include/common_class_of_dispel.h"

using namespace std;

#define row_min 8
#define row_max 10
#define col_min 8
#define col_max 10
#define number_count 5

void pfA();
void pfB();
void pfC();
void pfD();
void pfE();
void pfF();
void pfG();
int remain_block_num(int* num);
void reset_num_signed(int* num_signed);
void eliminate(int* num, int* num_signed);
int score_count(int* score, int* num_signed);
int score_end(int* score, int* num, int row, int col);