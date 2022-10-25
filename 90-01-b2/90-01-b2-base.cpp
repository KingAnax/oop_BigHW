/*2151613 计科 毛宇录*/

#include "90-01-b2.h"

const char* msg1 = "\n\n当前数组(不同色标识)：                       \n";
const char* msg2 = "\n\n相同值归并后的数组(不同色标识)：         \n";
const char* msg3 = "\n\n除0后的数组(不同色标识)：                \n";
const char* msg4 = "\n\n新值填充后的数组(不同色标识)：           \n";

const block_display_info bdi_num[22] = {
	{0, NULL, 1},
	{1, NULL, 0},
	{2, NULL, 0},
	{3, NULL, 0},
	{4, NULL, 0},
	{5, NULL, 0},
	{6, NULL, 0},
	{7, NULL, 0},
	{8, NULL, 0},
	{9, NULL, 0},
	{10, NULL, 0},
	{11, NULL, 0},
	{12, NULL, 0},
	{13, NULL, 0},
	{14, NULL, 0},
	{15, NULL, 0},
	{16, NULL, 0},
	{17, NULL, 0},
	{18, NULL, 0},
	{19, NULL, 0},
	{20, NULL, 0},
	{-1, NULL, NULL},
};

const block_display_info bdi_num_signed[3] = {
	{0, NULL, 0},
	{1, "*\0", 0},
	{-1, NULL, NULL},
};

int combine(int i, int* num, int* num_new) //合并
{
	int x, y;
	cct_getxy(x, y);
	cout << "请确认是否把相邻的相同值合并到" << (char)(i / column_max + 'A') << (char)(i % column_max + '0') << "中(Y/N/Q)：";
	char ch;
	ch = _getche();
	while ((ch != 'y') && (ch != 'Y') && (ch != 'n') && (ch != 'N') && (ch != 'q') && (ch != 'Q')) {
		cct_gotoxy(x, y);
		cout << "请确认是否把相邻的相同值合并到" << (char)(i / column_max + 'A') << (char)(i % column_max + '0') << "中(Y/N/Q)：";
		ch = _getche();
	}
	if (ch == 'q' || ch == 'Q')
		return 2;
	if (ch == 'n' || ch == 'N')
		return 1;
	for (int p = 0; p < column_max * row_max; p++) {  //循环合并
		if (*(num_new + p) && (p != i))
			*(num + p) = 0;
	}
	*(num + i) += 1;
	return 0;
}

void score_count(int* total_score, int* num, int* num_new, int target) //记分
{
	int score = 0, count = 0;
	for (int p = 0; p < column_max * column_min; p++) { //查找合并项
		if (*(num_new + p)) {
			if (*(num + p)) {
				score = *(num + p) - 1;
				*(num_new + p) = 0;
			}
			count++;
		}
	}
	score = score * count * 3;
	*total_score += score;
	cout << "本次得分：" << score << " 总得分：" << *total_score << " 合成目标：" << target << endl;
	return;
}

void fall(int row, int column, int* num, int* num_new)
{
	cout << "\n按回车键进行数组下落除0操作...";
	char ch;
	ch = _getch();
	while (ch != '\r')
		ch = _getch();
	for (int p = (row - 1) * column_max; p <= (row - 1) * column_max + column - 1; p++) {
		for (int a = row - 1; a >= 0; a--) {
			int i = p;
			int b = 0;      //判断是否排序结束
			while (i >= column_max) {
				if (!*(num + i)) {
					*(num + i) = *(num + i - column_max);
					*(num + i - column_max) = 0;
					if (!*(num_new + i - column_max))
						*(num_new + i) = 0;
					*(num_new + i - column_max) = 1;
					b = 1;
				}
				i -= column_max;
			}
			if (!b)
				break;
		}
	}
	return;
}

void new_data(int row, int column, int* num, int* num_new, int* stage)
{
	cout << "\n按回车键进行新值填充...";
	char ch;
	ch = _getch();
	while (ch != '\r')
		ch = _getch();
	for (int p = 0; p < (row - 1) * column_max + column - 1; p++) {
		if (*(num + p) > *stage)
			*stage = *(num + p);
	}
	for (int p = 0; p < column_max * row_max; p++) {
		if (*(num_new + p))
			*(num + p) = chance_number(*stage);
	}
	return;
}

void find2(int i, int row, int* num, int* num_new)      //递归,找合并位置
{
	if (i < column_max) {                 //首void sign_command_line(int i, int row, int* num, int* num_new, int row_max, int col_max)行
		if ((*(num + i + column_max) == *(num + i)) && (!*(num_new + i + column_max))) {
			*(num_new + i + column_max) = 1;
			find2(i + column_max, row, num, num_new);
		}
		tepan_new_recursion(i, row, num, num_new);
	}
	else if (i >= column_max * (row - 1)) {  //尾行
		if ((*(num + i - column_max) == *(num + i)) && (!*(num_new + i - column_max))) {
			*(num_new + i - column_max) = 1;
			find2(i - column_max, row, num, num_new);
		}
		tepan_new_recursion(i, row, num, num_new);
	}
	else {                          //中间部分
		if ((*(num + i + column_max) == *(num + i)) && (!*(num_new + i + column_max))) {
			*(num_new + i + column_max) = 1;
			find2(i + column_max, row, num, num_new);
		}
		if ((*(num + i - column_max) == *(num + i)) && (!*(num_new + i - column_max))) {
			*(num_new + i - column_max) = 1;
			find2(i - column_max, row, num, num_new);
		}
		tepan_new_recursion(i, row, num, num_new);
	}
	return;
}

void mode1(void)
{
	int row, column;  //行列
	char px, py;  //坐标
	putin(&row, &column, NULL, row_min, row_max, column_min, column_max, target_min, target_max);  //输入
	int num[row_max][column_max] = { 0 }; //建立数组
	int num_new[row_max][column_max] = { 0 }; //建立仿像数组
	init_array(&num[0][0], row, column, column_max, start);  //初始化内部数组 
	boundary_command_line(&num[0][0], row, column, column_max, bdi_num, "\n\n当前数组：\n");  //打印界面
	xy(&px, &py, row, column, &num[0][0], column_max);  //输入坐标
	sign_command_line((px - 'A') * column_max + py - '0', row, &num[0][0], &num_new[0][0], row_max, column_max);  //找相同
	show_color_command_line(&num[0][0], &num_new[0][0], row, column, column_max, msg1);  //打印彩色数组
	return;
}

void mode2(void)
{
	int row, column;  //行列
	char px, py;  //坐标
	putin(&row, &column, NULL, row_min, row_max, column_min, column_max, target_min, target_max);  //输入
	int num[row_max][column_max] = { 0 }; //建立数组
	int num_new[row_max][column_max] = { 0 }; //建立仿像数组
	init_array(&num[0][0], row, column, column_max, start);  //初始化内部数组 
	boundary_command_line(&num[0][0], row, column, column_max, bdi_num, "\n\n当前数组：\n");  //打印界面
	xy(&px, &py, row, column, &num[0][0], column_max);  //输入坐标
	find2((px - 'A') * column_max + py - '0', row, &num[0][0], &num_new[0][0]);  //找相同
	show_color_command_line(&num[0][0], &num_new[0][0], row, column, column_max, msg1);  //打印彩色数组
	return;
}

void mode3(void)
{
	int row, column;  //行列
	char px, py;  //坐标
	int target, score = 0, stage = 3;
	putin(&row, &column, &target, row_min, row_max, column_min, column_max, target_min, target_max);  //输入
	int num[row_max][column_max] = { 0 }; //建立数组
	int num_new[row_max][column_max] = { 0 }; //建立仿像数组
	init_array(&num[0][0], row, column, column_max, start);  //初始化内部数组 
	boundary_command_line(&num[0][0], row, column, column_max, bdi_num, "\n\n当前数组：\n");  //打印界面
	xy(&px, &py, row, column, &num[0][0], column_max);  //输入坐标
	find2((px - 'A') * column_max + py - '0', row, &num[0][0], &num_new[0][0]);  //找相同
	show_color_command_line(&num[0][0], &num_new[0][0], row, column, column_max, msg1);  //打印数组,彩色
	if (combine((px - 'A') * column_max + py - '0', &num[0][0], &num_new[0][0])) //结合并判断是否要返回
		return;
	show_color_command_line(&num[0][0], &num_new[0][0], row, column, column_max, msg2); //打印数组,彩色
	score_count(&score, &num[0][0], &num_new[0][0], target); //积分
	fall(row, column, &num[0][0], &num_new[0][0]); //下落除0
	show_color_command_line(&num[0][0], &num_new[0][0], row, column, column_max, msg3); //打印数组,彩色
	new_data(row, column, &num[0][0], &num_new[0][0], &stage); //生成数字
	show_color_command_line(&num[0][0], &num_new[0][0], row, column, column_max, msg4); //打印数组,彩色
	if (!is_end(row, column, &num[0][0], column_max, "无可消除项，结束"))
		return;
	return;
}

void mode4(void)
{
	int row, column;  //行列
	char px, py;  //坐标
	int target, score = 0, stage = 3, panduan = 0;
	putin(&row, &column, &target, row_min, row_max, column_min, column_max, target_min, target_max);  //输入
	int num[row_max][column_max] = { 0 }; //建立数组
	int num_new[row_max][column_max] = { 0 }; //建立仿像数组
	init_array(&num[0][0], row, column, column_max, start);  //初始化内部数组 
	while (1) {
		for (int a = 0; a < row_max; a++) {     //初始化
			for (int b = 0; b < column_max; b++) {
				num_new[a][b] = 0;
			}
		}
		boundary_command_line(&num[0][0], row, column, column_max, bdi_num, "\n\n当前数组：\n");  //打印界面
		xy(&px, &py, row, column, &num[0][0], column_max);  //输入坐标
		find2((px - 'A') * column_max + py - '0', row, &num[0][0], &num_new[0][0]);  //找相同
		show_color_command_line(&num[0][0], &num_new[0][0], row, column, column_max, msg1);  //打印数组,彩色
		int result = combine((px - 'A') * column_max + py - '0', &num[0][0], &num_new[0][0]);
		while (result) {
			if (result == 2)
				return;
			else {
				boundary_command_line(&num[0][0], row, column, column_max, bdi_num, "\n\n当前数组：\n");  //打印界面
				xy(&px, &py, row, column, &num[0][0], column_max);  //输入坐标
				find2((px - 'A') * column_max + py - '0', row, &num[0][0], &num_new[0][0]);  //找相同
				show_color_command_line(&num[0][0], &num_new[0][0], row, column, column_max, msg1);  //打印数组,彩色
				result = combine((px - 'A') * column_max + py - '0', &num[0][0], &num_new[0][0]);
			}
		}
		show_color_command_line(&num[0][0], &num_new[0][0], row, column, column_max, msg2); //打印数组,彩色
		score_count(&score, &num[0][0], &num_new[0][0], target); //积分
		fall(row, column, &num[0][0], &num_new[0][0]); //下落除0
		show_color_command_line(&num[0][0], &num_new[0][0], row, column, column_max, msg3); //打印数组,彩色
		new_data(row, column, &num[0][0], &num_new[0][0], &stage); //生成数字
		show_color_command_line(&num[0][0], &num_new[0][0], row, column, column_max, msg4); //打印数组,彩色
		if (!is_end(row, column, &num[0][0], column_max, "无可消除项，结束"))
			return;
		cout << "\n本次合成结束，按回车键继续新一次的合成...";
		char ch;
		ch = _getch();
		while (ch != '\r')
			ch = _getch();
		if (stage == target)
			panduan++;
		if (panduan == 1) {
			cct_setcolor(14, 4);
			cout << "\n已经合成到" << target << endl;
			cct_setcolor(0, 7);
			cout << "按回车键继续向更高目标进发...\n";
			ch = _getch();
			while (ch != '\r')
				ch = _getch();
		}
	}
	return;
}