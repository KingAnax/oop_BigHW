/*2151613 计科 毛宇录*/
#include "90-01-b2.h"

void print_map_picture(int row, int column, int* num)
{
	cout << setiosflags(ios::right) << "\n";
	cout << setw(7) << "0";
	for (int c = 1; c < column; c++)
		cout << setw(8) << c;
	cout << "\n" << setw(2) << "";
	cct_setcolor(15, 0);
	cout << "┏";
	for (int i = 1; i <= column - 1; i++) {
		for (int a = 1; a <= 3; a++)
			cout << "━";
		cout << "┳";
	}
	for (int a = 1; a <= 3; a++) {
		cout << "━";
	}
	cout << "┓" << endl;
	for (int r = 0; r < row; r++) {
		for (int i = 0; i < 3; i++) {
			cct_setcolor(0, 7);
			if (i == 1)
				cout << (char)(r + 'A') << " ";
			else
				cout << "  ";
			cct_setcolor(15, 0);
			cout << "┃";
			for (int c = 0; c < column; c++) {
				int color;
				color = *(num + r * column_max + c) % 10;
				if (color == 0)
					color = 10;
				cct_setcolor(color, 0);
				if (i == 0)
					cout << "┏━┓";
				else if (i == 1)
					cout << "┃" << setw(2) << resetiosflags(ios::right) << setiosflags(ios::left) << *(num + r * column_max + c) << "┃";
				else
					cout << "┗━┛";
				cct_setcolor(15, 0);
				cout << "┃";
			}
			cout << endl;
		}
		if (r == row - 1)
			break;
		int x, y;
		cct_getxy(x, y);
		cct_gotoxy(x + 2, y);
		cout << "┣";
		for (int a = 0; a < column - 1; a++) {
			for (int a = 1; a <= 3; a++) {
				cout << "━";
			}
			cout << "╋";
		}
		for (int a = 1; a <= 3; a++) {
			cout << "━";
		}
		cout << "┫\n";
	}
	cct_setcolor(0, 7);
	cout << "  ";
	cct_setcolor(15, 0);
	cout << "┗";
	for (int i = 1; i <= column - 1; i++) {
		for (int a = 1; a <= 3; a++) {
			cout << "━";
		}
		cout << "┻";
	}
	for (int a = 1; a <= 3; a++) {
		cout << "━";
	}
	cout << "┛" << endl;
	cct_setcolor(0, 7);
	cout << resetiosflags(ios::left);
	return;
}

void score_sum(int* total_score, int* num, int* num_new, int target)
{
	int score = 0, count = 0;
	for (int p = 0; p < column_max * column_min; p++) {
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

int newdata_picture(int x, int y, int row, int* num, int* num_new, int* stage, int mode = 0) //生成新数据
{
	cct_gotoxy(x, y + 3 + 4 * row);
	cout << setw(64) << "";
	cct_gotoxy(x, y + 4 + 4 * row);
	cout << setw(64) << "";
	cct_gotoxy(x, y + 3 + 4 * row);
	int MX = 0, MY = 0, MAction = 0, keycode1 = 0, keycode2 = 0; //响应
	cct_enable_mouse();
	cct_setcursor(3);
	if (!mode) {
		cout << "下落0完成，回车键/单击左键填充新值";
		while ((keycode1 != '\r') && (MAction != 2)) {
			cct_read_keyboard_and_mouse(MX, MY, MAction, keycode1, keycode2);
			if (keycode1 == 'q' || keycode1 == 'Q' || MAction == 8)
				return 1;
		}
	}
	cct_disable_mouse();
	for (int p = 0; p < column_max * row_max; p++) {
		if (*(num + p) > *stage)
			*stage = *(num + p);
	}
	for (int p = 0; p < column_max * row_max; p++) {
		if (*(num_new + p))
			*(num + p) = chance_number(*stage);
	}
	for (int p = 0; p < column_max * row_max; p++) {
		if (*(num_new + p)) {
			putin_color(p / column_max, p % column_max, num, 1);
			*(num_new + p) = 0;
		}
	}
	return 0;
}

void combine_picture(int row, int column, int i, int* num, int* num_new)
{
	for (int p = 0; p < column_max * row_max; p++) {  //循环合并
		if (*(num_new + p) && (p != i))
			*(num + p) = 0;
	}
	*(num + i) += 1;
	putin_color(i / column_max, i % column_max, num, 1);
	for (int r = 0; r < row; r++) {
		for (int c = 0; c < column; c++) {
			if (!*(num + r * column_max + c))
				putin_color(r, c, num, 3);
		}
	}
	Sleep(800);
	return;
}

void combine_picture_2(int row, int column, int i, int* num, int* num_new)
{
	cct_setcursor(3);
	*(num + i) += 1;
	for (int p = 0; p < column_max * row_max; p++) {  //循环合并
		if (*(num_new + p) && (p != i))
			*(num + p) = 0;
	}
	putin_color(i / column_max, i % column_max, num, 0);
	*(num_new + i) = 0;
	for (int r = 0; r < row; r++) {
		for (int c = 0; c < column; c++) {
			if (*(num_new + r * column_max + c) > 0)
				putin_color(r, c, num, 3);
		}
	}
	Sleep(500);
	return;
}

void fall_gif(int i, int* num)
{
	int color, r = i / column_max, c = i % column_max;
	color = *(num + (r - 1) * column_max + c) % 10;
	if (color == 0)
		color = 10;
	cct_showstr(4 + 8 * c, 6 + 4 * (r - 1), "┗━┛", color, 0);
	cct_setcolor(color, 0);
	cct_gotoxy(4 + 8 * c, 5 + 4 * (r - 1));
	cout << "┃" << setw(2) << *(num + (r - 1) * column_max + c) << "┃";
	cct_showstr(4 + 8 * c, 4 + 4 * (r - 1), "┏━┓", color, 0);
	cct_showch(4 + 8 * c, 3 + 4 * (r - 1), ' ', 15, 15, 6);
	Sleep(8);
	cct_showstr(4 + 8 * c, 7 + 4 * (r - 1), "┗━┛", color, 0);
	cct_setcolor(color, 0);
	cct_gotoxy(4 + 8 * c, 6 + 4 * (r - 1));
	cout << "┃" << setw(2) << *(num + (r - 1) * column_max + c) << "┃";
	cct_showstr(4 + 8 * c, 5 + 4 * (r - 1), "┏━┓", color, 0);
	cct_showch(4 + 8 * c, 4 + 4 * (r - 1), ' ', 15, 15, 6);
	Sleep(8);
	cct_showstr(4 + 8 * c, 8 + 4 * (r - 1), "┗━┛", color, 0);
	cct_setcolor(color, 0);
	cct_gotoxy(4 + 8 * c, 7 + 4 * (r - 1));
	cout << "┃" << setw(2) << *(num + (r - 1) * column_max + c) << "┃";
	cct_showstr(4 + 8 * c, 6 + 4 * (r - 1), "┏━┓", color, 0);
	cct_showch(4 + 8 * c, 5 + 4 * (r - 1), ' ', 15, 15, 6);
	Sleep(8);
	cct_showstr(4 + 8 * c, 9 + 4 * (r - 1), "┗━┛", color, 0);
	cct_setcolor(color, 0);
	cct_gotoxy(4 + 8 * c, 8 + 4 * (r - 1));
	cout << "┃" << setw(2) << *(num + (r - 1) * column_max + c) << "┃";
	cct_showstr(4 + 8 * c, 7 + 4 * (r - 1), "┏━┓", color, 0);
	cct_showch(4 + 8 * c, 6 + 4 * (r - 1), ' ', 15, 15, 6);
	cct_showstr(4 + 8 * c, 6 + 4 * (r - 1), "━━━", 15, 0);
	Sleep(8);
	cct_setcolor(0, 7);
	return;
}

int fall_picture(int row, int column, int* num, int* num_new, int mode) //冒泡法排序并下落
{
	cct_gotoxy(0, 3 + 4 * row);
	cout << setw(64) << "";
	cct_gotoxy(0, 4 + 4 * row);
	cout << setw(64) << "";
	cct_gotoxy(0, 3 + 4 * row);
	int MX = 0, MY = 0, MAction = 0, keycode1 = 0, keycode2 = 0; //响应
	cct_setcursor(3);
	cct_enable_mouse();
	if (!mode) {
		cout << "合成完成，回车键/单击左键下落0";
		while ((keycode1 != '\r') && (MAction != 2)) {
			cct_read_keyboard_and_mouse(MX, MY, MAction, keycode1, keycode2);
			if (keycode1 == 'q' || keycode1 == 'Q' || MAction == 8)
				return 1;
		}
	}
	cct_disable_mouse();
	for (int p = (row - 1) * column_max; p <= (row - 1) * column_max + column - 1; p++) {
		for (int a = row - 1; a >= 0; a--) {
			int i = p;
			while (i >= column_max) {
				while ((!*(num + i)) && (*(num + i - column_max) > 0) && (i <= p)) {
					fall_gif(i, num);
					*(num + i) = *(num + i - column_max); //数组交换
					*(num + i - column_max) = 0;
					*(num_new + i) = 0;
					*(num_new + i - column_max) = 1;
					i += column_max;
				}
				i -= column_max;
			}
		}
	}
	return 0;
}

void find3(int i, int row, int* num, int* num_new) //找相同并用白色显示
{
	if (i < column_max) {                 //首行
		if ((*(num + i + column_max) == *(num + i)) && (!*(num_new + i + column_max))) {
			*(num_new + i + column_max) = 1;
			putin_color(i / column_max + 1, i % column_max, num, 0);
			find3(i + column_max, row, num, num_new);
		}
		tepan_new_recursion2(i, row, num, num_new);
	}
	else if (i >= column_max * (row - 1)) {  //尾行
		if ((*(num + i - column_max) == *(num + i)) && (!*(num_new + i - column_max))) {
			*(num_new + i - column_max) = 1;
			putin_color(i / column_max - 1, i % column_max, num, 0);
			find3(i - column_max, row, num, num_new);
		}
		tepan_new_recursion2(i, row, num, num_new);
	}
	else {                          //中间部分
		if ((*(num + i + column_max) == *(num + i)) && (!*(num_new + i + column_max))) {
			*(num_new + i + column_max) = 1;
			putin_color(i / column_max + 1, i % column_max, num, 0);
			find3(i + column_max, row, num, num_new);
		}
		if ((*(num + i - column_max) == *(num + i)) && (!*(num_new + i - column_max))) {
			*(num_new + i - column_max) = 1;
			putin_color(i / column_max - 1, i % column_max, num, 0);
			find3(i - column_max, row, num, num_new);
		}
		tepan_new_recursion2(i, row, num, num_new);
	}
	return;
}

void putin_color(int r, int c, int* num, int mode)
{
	int color;
	if (*(num + r * column_max + c) < 0)
		return;
	color = *(num + r * column_max + c) % 10;
	if (color == 0)
		color = 10;
	if (!mode) {
		if (color < 7)
			cct_setcolor(color, 7); //调色
		else
			cct_setcolor(color + 2, 7);
	}
	else if (mode == 1) {
		if (color < 7)
			cct_setcolor(color, 0); //调色
		else
			cct_setcolor(color + 2, 0);
	}
	else if (mode == 2) {
		if (color < 7)
			cct_setcolor(color, 15); //调色
		else
			cct_setcolor(color + 2, 15);
	}
	if (mode != 3) {
		cct_gotoxy(4 + 8 * c, 3 + 4 * r);  //标识选中的块
		cout << "┏━┓";
		cct_gotoxy(4 + 8 * c, 4 + 4 * r);
		cout << "┃" << setw(2) << setiosflags(ios::left) << *(num + r * column_max + c) << "┃";
		cct_gotoxy(4 + 8 * c, 5 + 4 * r);
		cout << "┗━┛";
	}
	else {
		cct_showch(4 + 8 * c, 3 + 4 * r, ' ', 15, 15, 6);
		cct_showch(4 + 8 * c, 4 + 4 * r, ' ', 15, 15, 6);
		cct_showch(4 + 8 * c, 5 + 4 * r, ' ', 15, 15, 6);//标识选中的块
	}
	cct_setcolor(0, 7);
	return;
}

void print_board(int row, int column, int* num, int mode = 0)
{
	cct_cls();
	cct_setconsoleborder(column * 8 + 5, 7 + 4 * row);
	cout << setiosflags(ios::right) << "\n";
	cout << setw(7) << "0";
	for (int c = 1; c < column; c++)
		cout << setw(8) << c;
	cout << "\n" << setw(2) << "";
	cct_setcolor(15, 0);
	cout << "┏";
	for (int i = 1; i <= column - 1; i++) {
		for (int a = 1; a <= 3; a++)
			cout << "━";
		cout << "┳";
		if (!mode)
			Sleep(10);
	}
	for (int a = 1; a <= 3; a++) {
		cout << "━";
		if (!mode)
			Sleep(10);
	}
	cout << "┓" << endl;
	for (int r = 0; r < row; r++) {
		for (int i = 0; i < 3; i++) {
			cct_setcolor(0, 7);
			if (i == 1)
				cout << setw(2) << resetiosflags(ios::right) << setiosflags(ios::left) << static_cast<char>(r + 'A');
			else
				cout << setw(2) << "";
			cct_setcolor(15, 0);
			cout << "┃";
			for (int a = 0; a < column; a++) {
				for (int b = 0; b < 6; b++) {
					cout << " ";
					if (!mode)
						Sleep(5);
				}
				cout << "┃";
			}
			cout << endl;
		}
		if (r == row - 1)
			break;
		int x, y;
		cct_getxy(x, y);
		cct_gotoxy(x + 2, y);
		cout << "┣";
		for (int a = 0; a < column - 1; a++) {
			for (int a = 1; a <= 3; a++) {
				cout << "━";
				if (!mode)
					Sleep(10);
			}
			cout << "╋";
			if (!mode)
				Sleep(10);
		}
		for (int a = 1; a <= 3; a++) {
			cout << "━";
			if (!mode)
				Sleep(10);
		}
		cout << "┫\n";
	}
	cct_setcolor(0, 7);
	cout << "  ";
	cct_setcolor(15, 0);
	cout << "┗";
	for (int i = 1; i <= column - 1; i++) {
		for (int a = 1; a <= 3; a++) {
			cout << "━";
			if (!mode)
				Sleep(10);
		}
		cout << "┻";
		if (!mode)
			Sleep(10);
	}
	for (int a = 1; a <= 3; a++) {
		cout << "━";
		if (!mode)
			Sleep(10);
	}
	cout << "┛" << endl;
	for (int r = 0; r < row; r++) {
		for (int i = 0; i < 3; i++) {
			for (int c = 0; c < column; c++) {
				cct_gotoxy(4 + 8 * c, r * 4 + i + 3);
				int color;
				color = *(num + r * column_max + c) % 10;
				if (color == 0)
					color = 10;
				cct_setcolor(color, 0);
				if (i == 0)
					cout << "┏━┓";
				else if (i == 1)
					cout << "┃" << setw(2) << *(num + r * column_max + c) << "┃";
				else
					cout << "┗━┛";
			}
		}
	}
	cct_setcolor(0, 7);
	cct_gotoxy(0, 0);
	cout << "屏幕当前设置为：" << 7 + 4 * row << "行" << column * 8 + 5 << "列\n ";
	cct_gotoxy(0, 3 + 4 * row);
	return;
}

int error(int MX, int MY, int row, int column)
{
	int result = 0;
	if (MY <= 2 || MY >= 2 + 4 * row || (MY - 2) % 4 == 0)
		result++;
	if (MX <= 2 || (MX - 2) % 8 == 0 || (MX - 2) % 8 == 1 || MX >= 8 * column + 3)
		result++;
	return result;
}

int mouse_keyboard(int row, int column, int* num, int mode, int* i, int* num_new = NULL)
{
	cct_enable_mouse();
	cct_gotoxy(0, 3 + 4 * row);
	if (!mode)
		cout << "箭头键/鼠标移动，回车键/单击左键选择并结束";
	else if (mode == 1)
		cct_showstr(0, 3 + 4 * row, "箭头键/鼠标移动，回车键/单击左键选择,Q/单击右键结束");
	cct_setcursor(3);
	int panduan1 = 2, a = 0, p, b = 0;
	int r = *i / column_max, c = *i % column_max;
	int MX = 0, MY = 0, MAction = 0, keycode1 = 0, keycode2 = 0; //响应
	int r_old = 0, c_old = 0, MAction_old = 0, keycode1_old = 0, keycode2_old = 0; //镜像
	while (1) {
		while ((keycode1 != '\r') && (MAction != 2)) {
			if ((!a) && (!b))
				putin_color(r, c, num, 0);
			else if (!a)
				putin_color(r, c, num, 2);
			a = 0;
			p = cct_read_keyboard_and_mouse(MX, MY, MAction, keycode1, keycode2);
			if (!b) {
				for (int r1 = 0; r1 < row; r1++) {
					for (int c1 = 0; c1 < column; c1++) {
						putin_color(r1, c1, num, 1);
					}
				}
			}
			if (keycode1 == 'q' || keycode1 == 'Q' || MAction == 8) {
				cct_gotoxy(0, 3 + 4 * row);
				return 1;
			}
			if (b) {
				if (b == 1) {
					if (MAction == 2 || keycode1 == '\r') {
						cct_gotoxy(0, 3 + 4 * row);
						return 0;
					}
				}
				if (c != c_old || r != r_old || keycode1 == 224 || error(MX, MY, row, column)) {
					b = 0;
					cct_gotoxy(0, 3 + 4 * row);
					cout << setw(64) << "";
					cct_gotoxy(0, 4 + 4 * row);
					cout << setw(64) << "";
					cct_gotoxy(0, 3 + 4 * row);
					for (int r1 = 0; r1 < row; r1++) {
						for (int c1 = 0; c1 < column; c1++) {
							putin_color(r1, c1, num, 1);
						}
					}
				}
			}
			if (!b) {
				if (p) {
					if (panduan1 != p) {
						cct_gotoxy(0, 3 + 4 * row);
						cout << setw(64) << "";
						cct_gotoxy(0, 4 + 4 * row);
						cout << setw(64) << "";
					}
					cct_gotoxy(0, 3 + 4 * row);
					if (keycode1 == 224) {
						if (keycode2 == 72) {
							if (r == 0)
								r = row - 1;
							else
								r--;
						}
						else if (keycode2 == 80)
							r = (r + 1) % row;
						else if (keycode2 == 75) {
							if (c == 0)
								c = column - 1;
							else
								c--;
						}
						else
							c = (c + 1) % column;
					}
					cout << "[当前键盘]" << (char)(c + '0') << "列 " << (char)(r + 'A') << "行";
				}
				else {
					if (panduan1 != p) {
						cct_gotoxy(0, 3 + 4 * row);
						cout << setw(64) << "";
						cct_gotoxy(0, 4 + 4 * row);
						cout << setw(64) << "";
					}
					cct_gotoxy(0, 3 + 4 * row);
					cout << "[当前鼠标] ";
					if (error(MX, MY, row, column)) {
						cout << "位置非法";
						a = 1;
					}
					else {
						c = (MX - 3) / 8, r = (MY - 3) / 4;
						cout << (char)(c + '0') << "列 " << (char)(r + 'A') << "行";
					}
				}
				c_old = c; r_old = r;
			}
			panduan1 = p;
			if (error(MX, MY, row, column))
				MAction = 0;
		}
		if (!b) {
			cct_gotoxy(0, 3 + 4 * row);
			cout << setw(64) << "";
			cct_gotoxy(0, 4 + 4 * row);
			cout << setw(64) << "";
			cct_gotoxy(0, 3 + 4 * row);
		}
		if (!mode) {
			cout << "选中了 " << (char)(r + 'A') << "行 " << (char)(c + '0') << "列";
			cct_disable_mouse();
			cct_setcursor(2);
			return 0;
		}
		*i = r * column_max + c;
		if (!b) {
			if (panduan(r + 'A', c + '0', num, column_max)) {
				cout << "箭头键/鼠标移动取消当前选择，回车键/单机左键合成";
				for (int r1 = 0; r1 < row; r1++) {
					for (int c1 = 0; c1 < column; c1++) {
						*(num_new + r1 * column_max + c1) = 0;
					}
				}
				putin_color(r, c, num, 2);
				find3(*i, row, num, num_new);
				MAction = 0, keycode1 = 0, keycode2 = 0, b = 1;
			}
			else {
				cct_showstr(0, 3 + 4 * row, "周围无相同值,箭头键/鼠标移动,回车键/单击左键选择,Q/单击右键结束");
				MAction = 0, keycode1 = 0, keycode2 = 0, b = 2;
			}
		}
		else if (b == 2) {
			MAction = 0, keycode1 = 0, keycode2 = 0, b = 2;
		}
	}
	cct_disable_mouse();
	cct_setcursor(2);
	return 0;
}

void mode5(void)
{
	int row, column;  //行列
	putin(&row, &column, NULL, row_min, row_max, column_min, column_max, target_min, target_max);  //输入
	int num[row_max][column_max] = { 0 }; //建立数组
	init_array(&num[0][0], row, column, column_max, start);  //初始化内部数组
	cct_cls();
	cct_setconsoleborder(column * 6 + 7, 8 + 3 * row);
	cout << setiosflags(ios::right) << "\n ";
	for (int c = 0; c < column; c++)
		cout << setw(6) << c;
	cout << "\n" << setw(2) << "";
	cct_setcolor(15, 0);
	cout << "┏";
	for (int i = 1; i <= 3 * column; i++) {
		cout << "━";
		Sleep(10);
	}
	cout << "┓" << endl;
	for (int r = 0; r < row; r++) {
		for (int i = 0; i < 3; i++) {
			cct_setcolor(0, 7);
			if (i == 1)
				cout << setw(2) << resetiosflags(ios::right) << setiosflags(ios::left) << static_cast<char>(r + 'A');
			else
				cout << setw(2) << "";
			cct_setcolor(15, 0);
			cout << "┃";
			for (int a = 0; a < 6 * column; a++) {
				cout << " ";
				Sleep(5);
			}
			cout << "┃";
			cout << endl;
		}
	}
	cct_setcolor(0, 7);
	cout << "  ";
	cct_setcolor(15, 0);
	cout << "┗";
	for (int i = 1; i <= 3 * column; i++) {
		cout << "━";
		Sleep(10);
	}
	cout << "┛" << endl;
	for (int r = 0; r < row; r++) {
		for (int i = 0; i < 3; i++) {
			cct_gotoxy(4, r * 3 + i + 3);
			for (int c = 0; c < column; c++) {
				if (num[r][c] < 7)
					cct_setcolor(num[r][c], 0);
				else if (num[r][c] < 13)
					cct_setcolor(num[r][c] + 2, 0);
				else
					cct_setcolor(num[r][c] + 3, 0);
				if (i == 0)
					cout << "┏━┓";
				else if (i == 1)
					cout << "┃" << setw(2) << num[r][c] << "┃";
				else
					cout << "┗━┛";
			}
		}
	}
	cct_setcolor(0, 7);
	cct_gotoxy(0, 0);
	cout << "屏幕当前设置为：" << 8 + 3 * row << "行" << column * 6 + 7 << "列\n ";
	cct_gotoxy(0, 3 + 3 * row);
	return;
}

void mode6(void)
{
	int row, column;  //行列
	putin(&row, &column, NULL, row_min, row_max, column_min, column_max, target_min, target_max);  //输入
	int num[row_max][column_max] = { 0 }; //建立数组
	init_array(&num[0][0], row, column, column_max, start); //初始化内部数组
	print_board(row, column, &num[0][0]);
	return;
}

void mode7(void)
{
	int row, column;  //行列
	int i = 0;
	putin(&row, &column, NULL, row_min, row_max, column_min, column_max, target_min, target_max);  //输入
	int num[row_max][column_max] = { 0 }; //建立数组
	init_array(&num[0][0], row, column, column_max, start);  //初始化内部数组
	print_board(row, column, &num[0][0], 1);
	mouse_keyboard(row, column, &num[0][0], 0, &i);
	return;
}

void mode8(void)
{
	int row, column, i = 0;  //行列和坐标
	int target, score = 0, stage = 3;
	putin(&row, &column, &target, row_min, row_max, column_min, column_max, target_min, target_max); //输入
	int num[row_max][column_max] = { 0 }; //建立数组
	int num_new[row_max][column_max] = { 0 }; //建立仿像数组
	init_array(&num[0][0], row, column, column_max, start);  //初始化内部数组
	print_board(row, column, &num[0][0], 1);
	if (mouse_keyboard(row, column, &num[0][0], 1, &i, &num_new[0][0]))
		return;
	putin_color(i / column_max, i % column_max, &num[0][0], 1);
	combine_picture(row, column, i, &num[0][0], &num_new[0][0]);
	cct_gotoxy(0, 0);
	score_sum(&score, &num[0][0], &num_new[0][0], target);
	if (fall_picture(row, column, &num[0][0], &num_new[0][0]))
		return;
	newdata_picture(0, 0, row, &num[0][0], &num_new[0][0], &stage);
	cct_gotoxy(0, 3 + 4 * row);
	cout << setw(64) << "";
	cct_gotoxy(0, 4 + 4 * row);
	cout << setw(64) << "";
	cct_gotoxy(0, 3 + 4 * row);
	cout << "本次合成结束，按C/单击左键继续新一次的合成";
	int MX = 0, MY = 0, MAction = 0, keycode1 = 0, keycode2 = 0; //响应
	cct_setcursor(3);
	cct_enable_mouse();
	while ((keycode1 != 'c') && (MAction != 2) && (keycode1 != 'C')) {
		cct_read_keyboard_and_mouse(MX, MY, MAction, keycode1, keycode2);
		if (keycode1 == 'q' || keycode1 == 'Q' || MAction == 8)
			return;
	}
	return;
}

void mode9()
{
	int row, column, i = 0;  //行列和坐标
	int target, score = 0, stage = 3;
	putin(&row, &column, &target, row_min, row_max, column_min, column_max, target_min, target_max);  //输入
	int num[row_max][column_max] = { 0 }; //建立数组
	int num_new[row_max][column_max] = { 0 }; //建立仿像数组
	init_array(&num[0][0], row, column, column_max, start);  //初始化内部数组
	print_board(row, column, &num[0][0], 1);
	while (1) {
		if (mouse_keyboard(row, column, &num[0][0], 1, &i, &num_new[0][0]))
			return;
		putin_color(i / column_max, i % column_max, &num[0][0], 1);
		combine_picture(row, column, i, &num[0][0], &num_new[0][0]);
		cct_gotoxy(0, 0);
		score_sum(&score, &num[0][0], &num_new[0][0], target);
		if (fall_picture(row, column, &num[0][0], &num_new[0][0], 1))
			return;
		if (newdata_picture(0, 0, row, &num[0][0], &num_new[0][0], &stage, 1))
			return;
		cct_gotoxy(0, 3 + 4 * row);
		cout << setw(64) << "";
		cct_gotoxy(0, 4 + 4 * row);
		cout << setw(64) << "";
		cct_gotoxy(0, 3 + 4 * row);
		if (stage == target) {
			cout << "达到合成目标" << target << ",按鼠标左键/回车键继续" << endl;
			target++;
			cct_enable_mouse();
			int MX = 0, MY = 0, MAction = 0, keycode1 = 0, keycode2 = 0; //响应
			while ((keycode1 != '\r') && (MAction != 2)) {
				cct_read_keyboard_and_mouse(MX, MY, MAction, keycode1, keycode2);
			}
		}
		if (!is_end(row, column, &num[0][0], column_max, "无可消除项，结束"))
			return;
	}
	return;
}