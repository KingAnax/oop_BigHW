/*2151613 ë��¼ �ƿ�*/
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

//���ֲ��ֳߴ�
#define page_height 16
#define page_width  70

//����һ����Ϣ
struct line_info {
	string content = "";
	int line_first_pos = 0;
};

//��Ϊ�Ķ�������
struct page {
	bool is_first = true;
	bool is_end = false;
	int start_pos = 0;
	int end_pos = 0;
	int show_format = 0; //0���Զ�������1�ǲ���
	int start_no = 0;
	int line_num = page_height;
	line_info myline[page_height + 1]; //��0��ʼ�����һ�м�¼֮ǰ��Ϣ
};

void show_page(page& mypage, ifstream& fin);
int read_sav(const char* sav_name, string file_name);
void write_sav(int pos, const char* sav_name, string file_name);
void draw_frame();
void info_line(int pos, string file_name, int size);
void clear_status_line(int y);
void addition_line();
void read_page(page& mypage, ifstream& fin);
void roll_down_single(page& mypage, ifstream& fin);
void roll_down_page(page& mypage, ifstream& fin);
void roll_up_single(page& mypage, ifstream& fin);
void roll_up_page(page& mypage, ifstream& fin);
void goto_line(page& mypage, ifstream& fin, int size, int pos = -2);
void change_format(page& mypage, ifstream& fin);