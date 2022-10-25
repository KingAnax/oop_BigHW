//2151613 计科 毛宇录

#include "90-02-b1.h"

const char* msg1 = "\n\n当前数组(不同色标识)：                       \n";
const char* msg2 = "\n\n相同值归并后的数组(不同色标识)：             \n";
const char* msg3 = "\n\n下落后的数组：                               \n";

const block_display_info bdi_num[7] = {
	{0, NULL, 1},
	{1, NULL, 0},
	{2, NULL, 0},
	{3, NULL, 0},
	{4, NULL, 0},
	{5, NULL, 0},
	{-1, NULL, NULL},
};

const block_display_info bdi_num_signed[3] = {
	{0, NULL, 0},
	{1, "*\0", 0},
	{-1, NULL, NULL},
};


void pfA()
{
	int row, col;  //行列
	char px, py;  //坐标
	putin(&row, &col, NULL, row_min, row_max, col_min, col_max, NULL, NULL);  //输入
	int num[row_max][col_max] = { 0 }; //建立数组
	int num_signed[row_max][col_max] = { 0 }; //建立仿像数组
	init_array(&num[0][0], row, col, col_max, number_count);  //初始化内部数组 
	boundary_command_line(&num[0][0], row, col, col_max, bdi_num, "\n当前数组：\n");  //打印界面
	xy(&px, &py, row, col, &num[0][0], col_max);  //输入坐标
	sign_command_line((px - 'A') * col_max + py - '0', row, &num[0][0], &num_signed[0][0], row_max, col_max);//找相同
	show_color_command_line(&num[0][0], &num_signed[0][0], row, col, col_max, msg1);  //打印彩色数组
	end();
}

void pfB()
{
	int row, col;  //行列
	char px, py;  //坐标
	int score = 0;
	putin(&row, &col, NULL, row_min, row_max, col_min, col_max, NULL, NULL);  //输入
	int num[row_max][col_max] = { 0 }; //建立数组
	int num_signed[row_max][col_max] = { 0 }; //建立仿像数组
	init_array(&num[0][0], row, col, col_max, number_count);  //初始化内部数组 
	boundary_command_line(&num[0][0], row, col, col_max, bdi_num, "\n当前数组：\n");  //打印界面
	xy(&px, &py, row, col, &num[0][0], col_max);  //输入坐标
	sign_command_line((px - 'A') * col_max + py - '0', row, &num[0][0], &num_signed[0][0], row_max, col_max);//找相同
	boundary_command_line(&num_signed[0][0], row, col, col_max, bdi_num_signed, "\n查找结果数组：\n");  //打印界面
	show_color_command_line(&num[0][0], &num_signed[0][0], row, col, col_max, msg1);  //打印彩色数组
	int val;//接收返回值
	char buf[80] = {};//存储字符串
	sprintf_s(buf, "%s%c%c%s", "请确认是否把", px, py, "及周围的相同值消除(Y/N/Q)：");
	val = confirm_command_line(buf);
	switch (val) {
		case 0:
			eliminate(&num[0][0], &num_signed[0][0]);//数值消除
			show_color_command_line(&num[0][0], &num_signed[0][0], row, col, col_max, msg2);  //打印彩色数组
			cout << "\n本次得分：" << score_count(&score, &num_signed[0][0]);
			cout << " 总得分：" << score << endl;//计分
			confirm_press_enter("\n\n按回车键进行数组下落操作...");
			mov_array(&num[0][0], row, col, UP_TO_DOWN, col_max); //下落
			mov_array(&num[0][0], row, col, RIGHT_TO_LEFT, col_max); //左移
			show_color_command_line(&num[0][0], &num_signed[0][0], row, col, col_max, msg3);  //打印彩色数组
			break;
		case 1:
			break;
		case 2:
			break;
	}
	end();
}

void pfC()
{
	int row, col;  //行列
	char px, py;  //坐标
	int score = 0;
	putin(&row, &col, NULL, row_min, row_max, col_min, col_max, NULL, NULL);  //输入
	int num[row_max][col_max] = { 0 }; //建立数组
	int num_signed[row_max][col_max] = { 0 }; //建立仿像数组
	int val;//接收返回值
	char buf[80] = {};//存储字符串
	init_array(&num[0][0], row, col, col_max, number_count);  //初始化内部数组 
	while (1) {
		boundary_command_line(&num[0][0], row, col, col_max, bdi_num, "\n当前数组：\n");  //打印界面
		xy(&px, &py, row, col, &num[0][0], col_max);  //输入坐标
		sign_command_line((px - 'A') * col_max + py - '0', row, &num[0][0], &num_signed[0][0], row_max, col_max);//找相同
		boundary_command_line(&num_signed[0][0], row, col, col_max, bdi_num_signed, "\n查找结果数组：\n");  //打印界面
		show_color_command_line(&num[0][0], &num_signed[0][0], row, col, col_max, msg1);  //打印彩色数组
		sprintf_s(buf, "%s%c%c%s", "请确认是否把", px, py, "及周围的相同值消除(Y/N/Q)：");
		val = confirm_command_line(buf);
		if (val == 0) {
			eliminate(&num[0][0], &num_signed[0][0]);//数值消除
			show_color_command_line(&num[0][0], &num_signed[0][0], row, col, col_max, msg2);  //打印彩色数组
			cout << "\n本次得分：" << score_count(&score, &num_signed[0][0]);
			cout << " 总得分：" << score << endl;//计分
			confirm_press_enter("\n\n按回车键进行数组下落操作...");
			mov_array(&num[0][0], row, col, UP_TO_DOWN, col_max); //下落
			mov_array(&num[0][0], row, col, RIGHT_TO_LEFT, col_max); //左移
			show_color_blank_command_line(&num[0][0], row, col, col_max, msg3);  //打印彩色数组
			reset_num_signed(&num_signed[0][0]);
		}
		else if (val == 1)
			continue;
		else if (val == 2)
			break;
		if (!is_end(row, col, &num[0][0], col_max, "\n\n无可消除项游戏结束\n")) {
			cout << "剩余消除项" << remain_block_num(&num[0][0]) << " ";
			cout << "奖励得分：" << score_end(&score, &num[0][0], row, col);
			cout << " 总得分：" << score << endl;
			break;
		}
		confirm_press_enter("\n本次消除结束，按回车键继续新一次的消除...\n");
	}
	end();
}