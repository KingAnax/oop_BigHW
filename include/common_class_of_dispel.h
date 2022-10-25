//2151613 计科 毛宇录
#pragma once

#include <iostream>
#include <iomanip>
#include <conio.h>
#include <windows.h>
#include <string.h>

using namespace std;

#define BDI_VALUE_END -1
#define BDI_VALUE_BLANK 0

#define UP_TO_DOWN 1
#define DOWN_TO_UP 2
#define LEFT_TO_RIGHT 3
#define RIGHT_TO_LEFT 4

struct block_display_info {
	const int value;
	const char* content;
	bool highlight;
	int color_fg;
	int color_bg;
	char left_top[3];
	char right_top[3];
	char left_bottom[3];
	char right_bottom[3];
	char row[3];
	char col[3];
};

struct frame_display_info {
	char left_top[3];
	char right_top[3];
	char left_bottom[3];
	char right_bottom[3];
	char row[3];
	char col[3];
	char left_separator[3];
	char right_separator[3];
	char top_separator[3];
	char bottom_separator[3];
	char mid_separator[3];
};

struct game_info {
	int is_separate;
	int is_rower;
	int is_column;
	int color_bg_frame;
	int color_fg_frame;
	int color_bg_board;
	int color_fg_board;
	int color_bg_board_highlight;
	int color_fg_board_highlight;
	int row_value;
	int col_value;
	int row;
	int col;
	int last_line;
	int block_height;
	int block_width;
	int delay_time_board;
	int delay_time_frame;
	int delay_time_block;
	int delay_time_move;
	int col_max;
};


//共有
void end();
void mov_array(int* num, int row, int col, int mode, const int col_max);
void init_array(int* num, int row, int col, int col_max, int number_count);

//命令行
void confirm_press_enter(const char* msg);
void show_color_blank_command_line(int* num, int row, int column, const int col_max, const char* msg);
void tepan(char px, char py, int* num, int* result, const int col_max);
int panduan(char px, char py, int* num, const int col_max);
int is_end(int row, int column, int* num, const int col_max, const char* msg);
void boundary_command_line(int* num, int row, int column, const int col_max, const block_display_info* bdi, const char* msg);
void show_color_command_line(int* num, int* num_signed, int row, int column, const int col_max, const char* msg);
void xy(char* px, char* py, int row, int column, int* num, int col_max);
void tepan(int i, int* num, int* num_signed, int* result, int col_max);
void sign_command_line(int i, int row, int* num, int* num_signed, int row_max, int col_max);
int confirm_command_line(const char* msg);
void putin(int* row, int* column, int* target, int row_min, int row_max, int col_min, int col_max, int target_min, int target_max);

//伪图形
void find_not_blank(const int row, const int col, int* num, int& row_no, int& col_no, game_info* gi);
void mov_pattern(const int row, const int col, int* num, const int mode, const game_info* const gi, const block_display_info* const bdi, const frame_display_info* const fdi);
int read_mouse_keyboard(int& MAction, int& MRow, int& MCol, int& KeyCode1, int& KeyCode2, int* num, const game_info* gi, const block_display_info* const bdi);
void draw_block(int row, int col, int value, const game_info* gi, const block_display_info* bdi);
void init_board(int row, int col, int is_separate, int is_rower, int is_column, int block_height, int block_width, int color_fg_frame, int color_bg_frame, int color_fg_board, int color_bg_board, int color_fg_board_highlight, int color_bg_board_highlight, int delay_time_frame, int delay_time_block, int delay_time_move, const int col_max, game_info* gi);
void bottom_statue(const char* msg1, const char* msg2, const game_info* gi);
void top_statue(const char* msg1, const char* msg2, const game_info* gi);
void confirm_click(char ch);
void draw_board(int row, int col, int col_max, int* num, const game_info* gi, const frame_display_info* fdi, const block_display_info* bdi);
void move_block(const int row_no, const int col_no, const int bdi_value, const game_info* gi, const block_display_info* const bdi, const frame_display_info* const fdi, const int direction, const int distance);