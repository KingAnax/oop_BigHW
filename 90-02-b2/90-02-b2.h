/* 2151613 毛宇录 计科 */
#pragma once

#include <iostream>
#include <string.h>
#include <ctime>
#include <conio.h>
#include "../include/cmd_console_tools.h"
#include "../include/common_input.h"
#include "../include/cmd_gmw_tools.h"

using namespace std;

struct sweep_mine_rank_info {
	int row;
	int col;
	int mine_num;
	char choice_row[40];
	char choice_col[40];
};

const sweep_mine_rank_info rank_info[3] = {
	{9,9,10,"ABCDEFGHI","123456789"},
	{16,16,40,"ABCDEFGHIJKLMNOP","123456789abcdefg"},
	{16,30,99,"ABCDEFGHIJKLMNOP","123456789abcdefghijklmnopqrstu"}
};

#define row_max 16
#define col_max 30
#define is_mine -1

//主函数
void pf1();
void pf2();
void pf3();
void pf4();
void pf5();
void pf6();
void pf7();
void pf8();
void pf9();

//共用工具函数
void game_info_input(int& rank);
void init_array(int(*p)[col_max], int(*p_open)[col_max], const int rank, const char px = -1, const char py = -1);
void end_with_enter();
int uncover(const int(*mine)[col_max], int(*mine_open)[col_max], const char px, const char py, const int rank);
int check_end(const int(*mine_open)[col_max], const int rank);
int sign_mine(int(*mine_sign)[col_max], const int(*mine_open)[col_max], const int r, const int c);

//命令行专用
int get_rc_command_line(char& px, char& py, const int rank);
void show_innner_array_command_line(int(*p)[col_max], const int rank, const int mode = 0);
void show_open_array_command_line(const int(*mine)[col_max], const int(*mine_open)[col_max], const int rank);

//伪图形专用
void draw_block(const CONSOLE_GRAPHICS_INFO* const pCGI, const int value, const int row_no, const int col_no, const int mode);
int check_end(const int(*mine)[col_max], const int(*mine_open)[col_max], const int(*mine_sign)[col_max], const int rank);
int read_keyboard_and_mouse(const CONSOLE_GRAPHICS_INFO* const pCGI, int& MAction, int& MRow, int& MCol, int& KeyCode1, int& KeyCode2, const bool update_lower_status_line = TRUE);