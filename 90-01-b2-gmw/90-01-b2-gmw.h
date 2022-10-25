/* 2151613 毛宇录 计科 */
#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <ctime>
#include "../include/cmd_console_tools.h"
#include "../include/common_input.h"
#include "../include/cmd_gmw_tools.h"

using namespace std;

#define init_num 3
#define row_min 5
#define row_max 8
#define col_min 5
#define col_max 10
#define target_min 5
#define target_max 20

const BLOCK_DISPLAY_INFO bdi_normal[] = {
	{BDI_VALUE_BLANK, -1, -1, "  "},
	{1,  COLOR_BLUE, COLOR_BLACK, NULL},
	{2,  COLOR_GREEN, COLOR_BLACK, NULL},
	{3,  COLOR_CYAN, COLOR_BLACK, NULL},
	{4,  COLOR_RED, COLOR_BLACK, NULL},
	{5,  COLOR_PINK, COLOR_BLACK, NULL},
	{6,  COLOR_YELLOW, COLOR_BLACK, NULL},
	{7,  COLOR_HBLUE, COLOR_BLACK, NULL},
	{8,  COLOR_HGREEN, COLOR_BLACK, NULL},
	{9,  COLOR_HCYAN, COLOR_BLACK, NULL},
	{10,  COLOR_HRED, COLOR_BLACK, NULL},
	{11,  COLOR_HPINK, COLOR_BLACK, NULL},
	{12,  COLOR_HYELLOW, COLOR_BLACK, NULL},
	{13,  COLOR_BLUE, COLOR_BLACK, NULL},
	{14,  COLOR_GREEN, COLOR_BLACK, NULL},
	{15,  COLOR_CYAN, COLOR_BLACK, NULL},
	{16,  COLOR_RED, COLOR_BLACK, NULL},
	{17,  COLOR_PINK, COLOR_BLACK, NULL},
	{18,  COLOR_YELLOW, COLOR_BLACK, NULL},
	{19,  COLOR_HBLUE, COLOR_BLACK, NULL},
	{20,  COLOR_HGREEN, COLOR_BLACK, NULL},
	{BDI_VALUE_END, -1, -1, NULL}
};

const BLOCK_DISPLAY_INFO bdi_sel[] = {
	{BDI_VALUE_BLANK, -1, -1, "  "},
	{1,  COLOR_BLUE, COLOR_HWHITE, NULL},
	{2,  COLOR_GREEN, COLOR_HWHITE, NULL},
	{3,  COLOR_CYAN, COLOR_HWHITE, NULL},
	{4,  COLOR_RED, COLOR_HWHITE, NULL},
	{5,  COLOR_PINK, COLOR_HWHITE, NULL},
	{6,  COLOR_YELLOW, COLOR_HWHITE, NULL},
	{7,  COLOR_HBLUE, COLOR_HWHITE, NULL},
	{8,  COLOR_HGREEN, COLOR_HWHITE, NULL},
	{9,  COLOR_HCYAN, COLOR_HWHITE, NULL},
	{10,  COLOR_HRED, COLOR_HWHITE, NULL},
	{11,  COLOR_HPINK, COLOR_HWHITE, NULL},
	{12,  COLOR_HYELLOW, COLOR_HWHITE, NULL},
	{13,  COLOR_BLUE, COLOR_HWHITE, NULL},
	{14,  COLOR_GREEN, COLOR_HWHITE, NULL},
	{15,  COLOR_CYAN, COLOR_HWHITE, NULL},
	{16,  COLOR_RED, COLOR_HWHITE, NULL},
	{17,  COLOR_PINK, COLOR_HWHITE, NULL},
	{18,  COLOR_YELLOW, COLOR_HWHITE, NULL},
	{19,  COLOR_HBLUE, COLOR_HWHITE, NULL},
	{20,  COLOR_HGREEN, COLOR_HWHITE, NULL},
	{BDI_VALUE_END, -1, -1, NULL}
};

const BLOCK_DISPLAY_INFO bdi_cat[] = {
	{BDI_VALUE_BLANK, -1, -1, "  "},
	{1,  COLOR_BLUE, COLOR_WHITE, NULL},
	{2,  COLOR_GREEN, COLOR_WHITE, NULL},
	{3,  COLOR_CYAN, COLOR_WHITE, NULL},
	{4,  COLOR_RED, COLOR_WHITE, NULL},
	{5,  COLOR_PINK, COLOR_WHITE, NULL},
	{6,  COLOR_YELLOW, COLOR_WHITE, NULL},
	{7,  COLOR_HBLUE, COLOR_WHITE, NULL},
	{8,  COLOR_HGREEN, COLOR_WHITE, NULL},
	{9,  COLOR_HCYAN, COLOR_WHITE, NULL},
	{10,  COLOR_HRED, COLOR_WHITE, NULL},
	{11,  COLOR_HPINK, COLOR_WHITE, NULL},
	{12,  COLOR_HYELLOW, COLOR_WHITE, NULL},
	{13,  COLOR_BLUE, COLOR_WHITE, NULL},
	{14,  COLOR_GREEN, COLOR_WHITE, NULL},
	{15,  COLOR_CYAN, COLOR_WHITE, NULL},
	{16,  COLOR_RED, COLOR_WHITE, NULL},
	{17,  COLOR_PINK, COLOR_WHITE, NULL},
	{18,  COLOR_YELLOW, COLOR_WHITE, NULL},
	{19,  COLOR_HBLUE, COLOR_WHITE, NULL},
	{20,  COLOR_HGREEN, COLOR_WHITE, NULL},
	{BDI_VALUE_END, -1, -1, NULL}
};

//主函数
void pf9();

//工具函数
void confirm_q();
void confirm_enter();
int is_end(int(*num)[col_max], const int row, const int col);
int find_equal(int count, const int bdi_value, const int row, const int col, const int(*num)[col_max], int(*num_sel)[col_max], const int mrow, const int mcol);
void init_game_info(int& row, int& col, int& target);
void score(const CONSOLE_GRAPHICS_INFO* const MyCGI, const int count, const int value, int& score_total, const int target);
void init_array(int(*num)[col_max], const int row, const int col);
void fill_blank(const CONSOLE_GRAPHICS_INFO* const MyCGI, int(*num)[col_max], const int row, const int col);
void fall(const CONSOLE_GRAPHICS_INFO* const MyCGI, int(*num)[col_max], const int row, const int col);
void combine(const CONSOLE_GRAPHICS_INFO* const MyCGI, const int row, const int col, int mrow, int mcol, int(*num)[col_max], int(*num_sel)[col_max]);
int read_keyboard_and_mouse(const CONSOLE_GRAPHICS_INFO* const pCGI, int& MAction, int& MRow, int& MCol, int& KeyCode1, int& KeyCode2, int(*num)[col_max], int(*num_sel)[col_max], const int row, const int col);