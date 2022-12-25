/*2151613 毛宇录 计科*/
#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <cstring>
#include <Windows.h>
#include <sstream>
#include <fstream>
#include <conio.h>
#include "../include/cmd_gmw_tools.h"
#include "../include/cmd_console_tools.h"
#include "../include/common_file_list_board.h"
#include "../include/common_file_opr.h"
#include "../include/common_my_gmw_tools.h"

using namespace std;

//有字部分尺寸
#define page_height 16
#define page_width  72

//定义一行信息
struct line_info {
	string content = "";
	bool is_prv_CR = 0;     //是否为新行开始
	bool is_add_blank = 0;  //添加空格
	int line_first_pos = 0;
};

//作为阅读区界面
struct page {
	bool is_first = true;
	bool is_end = false;
	int start_pos = 0;
	int end_pos = 0;
	int show_format = 0; //0是自动缩进，1是不自动
	int start_no = 0;
	int line_num = page_height;
	line_info myline[page_height + 1]; //从0开始，最后一行记录之前信息
};

void show_page(page& mypage, ifstream& fin);
int read_sav(const char* sav_name, string file_name);
void write_sav(int pos, const char* sav_name, string file_name);
void draw_frame();
void info_line(int pos, string file_name, int size);
void clear_status_line(int y);
void addition_line();
void read_page_down(page& mypage, ifstream& fin);
void roll_down_single(page& mypage, ifstream& fin);
void roll_down_page(page& mypage, ifstream& fin);
void roll_up_single(page& mypage, ifstream& fin);
void roll_up_page(page& mypage, ifstream& fin);
void goto_line(page& mypage, ifstream& fin, int size, int pos = -1);
void change_format(page& mypage, ifstream& fin);