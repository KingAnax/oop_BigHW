//2151613 计科 毛宇录

#include "../include/common_class_of_dispel.h"
#include "../include/cmd_console_tools.h"

void xy(char* px, char* py, int row, int column, int* num, int col_max)//输入坐标
{
	int x, y;
	cout << "请以字母 + 数字形式[例：c2]输入矩阵坐标：" << setw(20) << "";
	cct_getxy(x, y);
	x -= 61;//移动光标到上句开始处
	cct_gotoxy(x + 41, y);

	char array[3] = { 0 };
	cin.clear();
	cin.getline(array, 3, '\n');

	*px = array[0];
	*py = array[1];

	if ((*px >= 'a') && (*px <= 'z'))//小写转大写
		*px -= 32;

	while (*px < 'A' || *px > 'A' + row - 1 || *py < '0' || *py > '0' + column - 1 || panduan(*px, *py, num, col_max) == 0) {
		if (*(num + (*px - 'A') * col_max + *py - '0') == 0) {
			cout << "输入的矩阵坐标位置为0（非法位置），请重新输入" << endl;
		}
		else if ((*px >= 'A') && (*px <= 'A' + row - 1) && (*py >= '0') && (*py <= '0' + column - 1)) {    //判断相邻有无
			cout << "输入为" << *px << "行" << *py << "列" << setw(10) << "" << endl;
			cout << "输入的矩阵坐标位置处无连续相同值，请重新输入\n";
		}
		else if (array[0] != '\0') {
			cct_gotoxy(x, y + 1);    //判断超范围
			cout << "输入错误，请重新输入.";
		}
		cct_gotoxy(x, y);
		cout << "请以字母 + 数字形式[例：c2]输入矩阵坐标：" << setw(20) << "";
		cct_gotoxy(x + 41, y);
		cin.clear();
		cin.getline(array, 3, '\n');
		*px = array[0];
		*py = array[1];
		if ((*px >= 'a') && (*px <= 'z'))//小写转大写
			*px -= 32;
	}

	cct_gotoxy(0, y + 1);
	cout << "输入为" << *px << "行" << *py << "列" << endl;

	return;
}

int confirm_command_line(const char* msg)
{
	int x, y;
	cct_getxy(x, y);
	cout << msg;
	char ch;
	ch = _getche();
	while ((ch != 'y') && (ch != 'Y') && (ch != 'n') && (ch != 'N') && (ch != 'q') && (ch != 'Q')) {
		cct_gotoxy(x, y);
		cout << msg;
		ch = _getche();
	}
	if (ch == 'q' || ch == 'Q')
		return 2;
	if (ch == 'n' || ch == 'N')
		return 1;
	return 0;
}

void init_array(int* num, int row, int col, int col_max, int number_count)
{
	srand((unsigned)time(NULL));

	for (int r = 0; r < row; r++) {
		for (int c = 0; c < col; c++)
			*(num + r * col_max + c) = rand() % number_count + 1;
	}
}

void tepan(char px, char py, int* num, int* result, const int col_max)//边界判断
{
	if (py == '0') {
		if (*(num + 1) == *(num) && *num != BDI_VALUE_BLANK)
			*result += 1;
	}
	else if (py == '0' + col_max - 1) {
		if (*(num - 1) == *(num) && *num != BDI_VALUE_BLANK)
			*result += 1;
	}
	else {
		if (*(num + 1) == *(num) && *num != BDI_VALUE_BLANK)
			*result += 1;
		if (*(num - 1) == *(num) && *num != BDI_VALUE_BLANK)
			*result += 1;
	}
	return;
}

void tepan(int i, int* num, int* num_signed, int* result, int col_max)//判断部分
{
	if (i % col_max == 0) {
		if ((*(num + i + 1) == *(num + i)) && (!*(num_signed + i + 1))) {
			*result += 1;
			*(num_signed + i + 1) = 1;
		}
	}
	else if ((i + 1) % col_max == 0) {
		if ((*(num - 1 + i) == *(num + i)) && (!*(num_signed + i - 1))) {
			*result += 1;
			*(num_signed + i - 1) = 1;
		}
	}
	else {
		if ((*(num + i + 1) == *(num + i)) && (!*(num_signed + i + 1))) {
			*result += 1;
			*(num_signed + i + 1) = 1;
		}
		if ((*(num - 1 + i) == *(num + i)) && (!*(num_signed + i - 1))) {
			*result += 1;
			*(num_signed + i - 1) = 1;
		}
	}
	return;
}

int panduan(char px, char py, int* num, const int col_max)//非递归，判断有无相邻位置相同数
{
	int result = 0;
	num += (px - 'A') * col_max + py - '0';
	if (px == 'A') {                 //首行
		if ((*(num + col_max) == *num) && (*num != BDI_VALUE_BLANK))
			result++;
		tepan(px, py, num, &result, col_max);
	}
	else if ((px == 'A' + col_max - 1) && (*num != BDI_VALUE_BLANK)) {  //尾行
		if (*(num - col_max) == *num)
			result++;
		tepan(px, py, num, &result, col_max);
	}
	else {                          //中间部分
		if ((*(num + col_max) == *num) && (*num != BDI_VALUE_BLANK))
			result++;
		if ((*(num - col_max) == *num) && (*num != BDI_VALUE_BLANK))
			result++;
		tepan(px, py, num, &result, col_max);
	}
	return result;
}

int is_end(int row, int column, int* num, const int col_max, const char* msg) //结束判断
{
	int result = 0;
	for (int p = 0; p < row * column; p++)
		result += panduan(p / column + 'A', p % column + '0', num, col_max);
	if (!result)
		cout << msg;
	return result;
}

void boundary_command_line(int* num, int row, int column, const int col_max, const block_display_info* bdi, const char* msg)//命令行打印界面
{
	cout << msg;
	cout << "  |";
	for (int c = 0; c < column; c++)
		cout << setw(3) << c;
	cout << "\n--+" << setw((int)(3 * (double)column + 1)) << setfill('-') << "";
	cout << setfill(' ');
	for (int r = 0; r < row; r++) {
		cout << "\n" << static_cast<char>('A' + r) << " |";
		for (int c = 0; c < column; c++) {
			int i = 0;
			while ((bdi + i)->value != -1) {
				if ((bdi + i)->value == *(num + r * col_max + c)) {
					if ((bdi + i)->content == NULL) {
						if ((bdi + i)->value < 10)
							cout << setw(2) << "";
						else
							cout << ' ';
						if ((bdi + i)->highlight)
							cct_setcolor(14, 0);
						cout << (bdi + i)->value;
						cct_setcolor(0, 7);
					}
					else {
						cout << setw(2) << "";
						if ((bdi + i)->highlight)
							cct_setcolor(14, 0);
						cout << (bdi + i)->content;
						cct_setcolor(0, 7);
					}
					break;
				}
				++i;
			}
			cct_setcolor(0, 7);
		}
	}
	cout << "\n\n";
	return;
}

void show_color_command_line(int* num, int* num_signed, int row, int column, const int col_max, const char* msg)//命令行不同色标识
{
	if (msg != NULL)
		cout << msg;
	cout << setw(3) << "|";
	for (int c = 0; c < column; c++)
		cout << setw(3) << c;
	cout << "\n--+-------------------------------";
	for (int r = 0; r < row; r++) {
		cout << "\n" << static_cast<char>('A' + r) << " |";
		for (int c = 0; c < column; c++) {
			if (!*(num_signed + r * col_max + c))
				cout << setw(3) << *(num + r * col_max + c);
			else {
				cout << setw(2) << "";
				cct_setcolor(14, 0);
				cout << *(num + r * col_max + c);
				cct_setcolor(0, 7);
			}
		}
	}
	cout << "\n\n";
	return;
}

void show_color_blank_command_line(int* num, int row, int column, const int col_max, const char* msg)//命令行不同色标识
{
	if (msg != NULL)
		cout << msg;
	cout << setw(3) << "|";
	for (int c = 0; c < column; c++)
		cout << setw(3) << c;
	cout << "\n--+-------------------------------";
	for (int r = 0; r < row; r++) {
		cout << "\n" << static_cast<char>('A' + r) << " |";
		for (int c = 0; c < column; c++) {
			if (*(num + r * col_max + c))
				cout << setw(3) << *(num + r * col_max + c);
			else {
				cout << setw(2) << "";
				cct_setcolor(14, 0);
				cout << *(num + r * col_max + c);
				cct_setcolor(0, 7);
			}
		}
	}
	cout << "\n\n";
	return;
}

void mov_array(int* num, int row, int col, int mode, const int col_max)
{
	if (mode == DOWN_TO_UP) {

	}
	else if (mode == UP_TO_DOWN) {
		for (int p = (row - 1) * col_max; p <= (row - 1) * col_max + col - 1; p++) {
			for (int a = row - 1; a >= 0; a--) {
				int i = p;
				int b = 0;      //判断是否排序结束
				while (i >= col_max) {
					if (*(num + i) == BDI_VALUE_BLANK) {
						*(num + i) = *(num + i - col_max);
						*(num + i - col_max) = BDI_VALUE_BLANK;
						b = 1;
					}
					i -= col_max;
				}
				if (!b)
					break;
			}
		}
	}
	else if (mode == RIGHT_TO_LEFT) {
		int blank = 0;
		for (int j = 0; j < col; ++j) {
			int i = 0;
			for (i; i < row; ++i) {
				if (*(num + i * col_max + j) != BDI_VALUE_BLANK)
					break;
			}
			if (i >= row)
				++blank;
			else if (blank > 0) {
				for (i = row - 1; i >= 0; --i) {
					*(num + i * col_max + j - blank) = *(num + i * col_max + j);
					*(num + i * col_max + j) = BDI_VALUE_BLANK;
				}
			}
		}
	}
	else if (mode == LEFT_TO_RIGHT) {

	}
}

void putin(int* row, int* column, int* target, int row_min, int row_max, int col_min, int col_max, int target_min, int target_max)//输入行数和列数
{
	cct_cls();
	cout << "请输入行数(" << row_min << "-" << row_max << ")：\n";
	cin >> *row;
	while (cin.fail() || *row < row_min || *row > row_max) {
		if (cin.fail()) {
			cin.clear();
			cin.ignore(65536, '\n');
		}
		cout << "请输入行数(" << row_min << "-" << row_max << ")：\n";
		cin >> *row;
	}
	cout << "请输入列数(" << col_min << "-" << col_max << ")：\n";
	cin >> *column;
	while (cin.fail() || *column < col_min || *column > col_max) {
		if (cin.fail()) {
			cin.clear();
			cin.ignore(65536, '\n');
		}
		cout << "请输入列数(" << col_min << "-" << col_max << ")：\n";
		cin >> *column;
	}
	if (target == NULL)
		return;
	cout << "请输入合成目标(" << target_min << "-" << target_max << ")：\n";
	cin >> *target;
	while (cin.fail() || *target < target_min || *target > target_max) {
		if (cin.fail()) {
			cin.clear();
			cin.ignore(65536, '\n');
		}
		cout << "请输入合成目标(" << target_min << "-" << target_max << ")：\n";
		cin >> *target;
	}
	return;
}

void sign_command_line(int i, int row, int* num, int* num_signed, int row_max, int col_max)   //非递归,找合并位置
{
	*(num_signed + i) = 1;
	int result = 0;
	while (1) {
		result = 0;
		for (int i = 0; i < col_max * row_max; i++) {
			if (*(num_signed + i) == 1) {           //找到有标记为相邻相同的位置
				if (i < col_max) {                 //首行
					if ((*(num + i + col_max) == *(num + i)) && (!*(num_signed + i + col_max))) {
						result++;
						*(num_signed + i + col_max) = 1;
					}
					tepan(i, num, num_signed, &result, col_max);
				}
				else if (i >= col_max * (row - 1)) {  //尾行
					if ((*(num + i - col_max) == *(num + i)) && (!*(num_signed + i - col_max))) {
						result++;
						*(num_signed + i - col_max) = 1;
					}
					tepan(i, num, num_signed, &result, col_max);
				}
				else {                          //中间部分
					if ((*(num + i + col_max) == *(num + i)) && (!*(num_signed + i + col_max))) {
						result++;
						*(num_signed + i + col_max) = 1;
					}
					if ((*(num + i - col_max) == *(num + i)) && (!*(num_signed + i - col_max))) {
						result++;
						*(num_signed + i - col_max) = 1;
					}
					tepan(i, num, num_signed, &result, col_max);
				}
			}
		}
		if (result == 0)
			break;
	}
	return;
}

void end()//结束每一小题
{
	cout << "\n";
	int x, y;
	cct_getxy(x, y);
	char ch;
	cout << "本小题结束，请输入End继续...        ";
	cct_gotoxy(x + 28, y);
	cin.clear();
	cin.ignore(1024, '\n');
	ch = getchar();
	while (1) {
		if (ch == 'e' || ch == 'E') {
			ch = getchar();
			if (ch == 'n' || ch == 'N') {
				ch = getchar();
				if (ch == 'd' || ch == 'D')
					break;
			}
		}
		cct_gotoxy(x, y + 1);
		cout << "输入错误，请重新输入";
		cct_gotoxy(x, y);
		cout << "本小题结束，请输入End继续...       ";
		cct_gotoxy(x + 28, y);
		ch = getchar();
	}
}

void confirm_press_enter(const char* msg)
{
	cout << msg;
	char ch;
	ch = _getche();
	while (ch != 13) {
		ch = _getche();
	}
}

void top_statue(const char* msg1, const char* msg2, const game_info* gi)  //上状态栏
{
	cct_showstr(0, 0, " ", gi->color_bg_board, gi->color_fg_board, gi->col);
	cct_gotoxy(0, 0);
	if (msg1 != NULL) {
		cct_setcolor(gi->color_bg_board_highlight, gi->color_fg_board_highlight);
		cout << msg1;
	}
	if (msg2 != NULL) {
		cct_setcolor(gi->color_bg_board, gi->color_fg_board);
		cout << msg2;
	}
}

void bottom_statue(const char* msg1, const char* msg2, const game_info* gi)  //下状态栏
{
	cct_showstr(0, gi->last_line, " ", gi->color_bg_board, gi->color_fg_board, gi->col);
	cct_gotoxy(0, gi->last_line);
	if (msg1 != NULL) {
		cct_showstr(0, gi->last_line, msg1, gi->color_bg_board_highlight, gi->color_fg_board_highlight);
	}
	if (msg2 != NULL) {
		cct_setcolor(gi->color_bg_board, gi->color_fg_board);
		cout << msg2;
	}
}

void draw_block(int row, int col, int value, const game_info* gi, const block_display_info* bdi) //画一个方块
{
	int color_fg_block = 0, color_bg_block = 0;

	char* content = NULL;

	int p = 0;
	while ((bdi + p)->value != -1) {
		if (value == (bdi + p)->value) {
			content = (char*)(bdi + p)->content;
			color_fg_block = (bdi + p)->color_fg;
			color_bg_block = (bdi + p)->color_bg;
			break;
		}
		++p;
	}

	int px = gi->is_rower + 3 + col * (gi->is_separate * 2 + gi->block_width);
	int py = gi->is_column + 2 + row * (gi->is_separate + gi->block_height);

	cct_setcolor(color_bg_block, color_fg_block);

	for (int i = 0; i < gi->block_height; ++i) {
		cct_gotoxy(px, py + i);
		if (i == 0) {
			cout << bdi->left_top;
			for (int i = 0; i < (gi->block_width - 4) / 2; ++i)
				cout << bdi->row;
			cout << bdi->right_top;
		}
		else if (i == gi->block_height - 1) {
			cout << bdi->left_bottom;
			for (int i = 0; i < (gi->block_width - 4) / 2; ++i)
				cout << bdi->row;
			cout << bdi->right_bottom;
		}
		else {
			cout << bdi->col;
			if (i == gi->block_height / 2)
				cout << setw(gi->block_width - 4) << content;
			else
				cout << setw(gi->block_width - 4) << "";
			cout << bdi->col;
		}
	}
	cout << '\n';
}

void init_board(int row, int col, int is_separate, int is_rower, int is_column, int block_height, int block_width,
	int color_fg_frame, int color_bg_frame,
	int color_fg_board, int color_bg_board, int color_fg_board_highlight, int color_bg_board_highlight, int delay_time_frame,
	int delay_time_block, int delay_time_move, const int col_max, game_info* gi)
{
	gi->row_value = row;
	gi->col_value = col;
	gi->is_separate = is_separate;
	gi->is_rower = is_rower;
	gi->is_column = is_column;
	gi->row = row * 3 + 7 + is_separate * (row - 1) + is_column;
	gi->col = 6 + col * 6 + 2 * is_separate * (col - 1) + is_rower;
	gi->color_bg_board = color_bg_board;
	gi->color_fg_board = color_fg_board;
	gi->color_bg_board_highlight = color_bg_board_highlight;
	gi->color_fg_board_highlight = color_fg_board_highlight;
	gi->color_bg_frame = color_bg_frame;
	gi->color_fg_frame = color_fg_frame;
	gi->last_line = 3 + row * 3 + (row - 1) * is_separate + is_column;
	gi->block_height = block_height;
	gi->block_width = block_width;
	gi->delay_time_move = delay_time_move;
	gi->delay_time_block = delay_time_block;
	gi->delay_time_frame = delay_time_frame;
	gi->col_max = col_max;
}

void draw_board(int row, int col, int col_max, int* num, const game_info* gi, const frame_display_info* fdi, const block_display_info* bdi)
{
	cct_cls();
	cct_setconsoleborder(gi->col, gi->row);

	int start_x = gi->is_rower + 1;
	int start_y = gi->is_column + 1;

	//首先把框架画出

	//画列标
	if (gi->is_column) {
		cct_gotoxy(start_x, 1);
		cct_setcolor(gi->color_bg_board, gi->color_fg_board);
		cout << setw(int(2 + gi->block_width / 2)) << "0";
		for (int c = 1; c < col; c++)
			cout << setw(gi->block_width + gi->is_separate * 2) << c;
	}

	//框架首行
	cct_gotoxy(start_x, start_y);
	cct_setcolor(gi->color_bg_frame, gi->color_fg_frame);
	cout << fdi->left_top;
	for (int c = 0; c < col; ++c) {
		for (int i = 0; i < gi->block_width / 2; ++i) {
			cout << fdi->row;
			Sleep(gi->delay_time_frame);
		}
		if (c != col - 1 && gi->is_separate)
			cout << fdi->top_separator;
	}
	cout << fdi->right_top;

	cout << resetiosflags(ios::right) << setiosflags(ios::left);

	//中间主体
	char rower = 'A';
	for (int r = 0; r < row; ++r) {
		for (int i = 0; i < gi->block_height; ++i) {
			++start_y;
			//画行标
			if (i == gi->block_height / 2 && gi->is_rower) {
				cct_setcolor(gi->color_bg_board, gi->color_fg_board);
				cct_gotoxy(0, start_y);
				cout << rower++;
			}

			cct_gotoxy(start_x, start_y);
			cct_setcolor(gi->color_bg_frame, gi->color_fg_frame);
			cout << fdi->col;

			//填充中间内容
			for (int c = 0; c < col; ++c) {
				for (int j = 0; j < gi->block_width; ++j) {
					cout << " ";
					Sleep(gi->delay_time_frame);
				}

				//框架的分割线
				cct_setcolor(gi->color_bg_frame, gi->color_fg_frame);
				if (c != col - 1 && gi->is_separate)
					cout << fdi->col;
			}

			cout << fdi->col;
		}

		//每一行方块下的框架分隔线
		if (r != row - 1 && gi->is_separate) {
			start_y += gi->is_separate;
			cct_gotoxy(start_x, start_y);
			cout << fdi->left_separator;
			for (int c = 0; c < col; ++c) {
				for (int i = 0; i < gi->block_width / 2; ++i) {
					cout << fdi->row;
					Sleep(gi->delay_time_frame);
				}
				Sleep(gi->delay_time_frame);
				if (c != col - 1 && gi->is_separate)
					cout << fdi->mid_separator;
			}
			cout << fdi->right_separator;
		}
	}

	//框架底行
	++start_y;
	cct_gotoxy(start_x, start_y);
	cout << fdi->left_bottom;
	for (int c = 0; c < col; ++c) {
		for (int i = 0; i < gi->block_width / 2; ++i)
			cout << fdi->row;
		Sleep(gi->delay_time_frame);
		if (c != col - 1 && gi->is_separate)
			cout << fdi->bottom_separator;
	}
	cout << fdi->right_bottom;
	cout << resetiosflags(ios::left) << setiosflags(ios::right) << '\n';
}

int read_mouse_keyboard(int& MAction, int& MRow, int& MCol, int& KeyCode1, int& KeyCode2, int* num, const game_info* gi, const  block_display_info* const bdi)
{
	cct_enable_mouse();

	int MX = 0, MY = 0;  //记录鼠标位置
	int type;            //事件类型
	int MRow_new = MRow, MCol_new = MCol;    //行列新值
	int sign = 0, old_sign = 0;
	int is_sel = 0;

	while (1) {
		type = cct_read_keyboard_and_mouse(MX, MY, MAction, KeyCode1, KeyCode2);
		if (type == CCT_KEYBOARD_EVENT) {
			switch (KeyCode1) {
				case 'Q':
					return -1;
				case 'q':
					return -1;
				case '\r':
					return 1;
				case 224:
					switch (KeyCode2) {
						case KB_ARROW_UP:
							do {
								--MRow;
								if (MRow < 0)
									MRow = gi->row_value - 1;
							} while (*(num + MRow * gi->col_max + MCol) == BDI_VALUE_BLANK);
							break;
						case KB_ARROW_DOWN:
							do {
								++MRow;
								if (MRow >= gi->row_value)
									MRow = 0;
							} while (*(num + MRow * gi->col_max + MCol) == BDI_VALUE_BLANK);
							break;
						case KB_ARROW_LEFT:
							do {
								--MCol;
								if (MCol < 0)
									MCol = gi->col_value - 1;
							} while (*(num + MRow * gi->col_max + MCol) == BDI_VALUE_BLANK);
							break;
						case KB_ARROW_RIGHT:
							do {
								++MCol;
								if (MCol >= gi->col_value)
									MCol = 0;
							} while (*(num + MRow * gi->col_max + MCol) == BDI_VALUE_BLANK);
							break;
					}
					char temp[256];
					sprintf_s(temp, "[当前键盘] %c行%d列  ", char('A' + MRow), MCol);
					bottom_statue(NULL, temp, gi);
					return 0;
			}
		}
		else {
			//判断鼠标位置是否合法
			old_sign = sign;
			sign = 0;
			if (MX < gi->is_rower + 3 || MX > gi->col - 4 || MY < gi->is_column + 2 || MY > gi->row - 6)
				sign = 1;
			if (gi->is_separate) {
				if ((MX - (gi->is_rower + 3)) % (gi->block_width + 2) >= gi->block_width)
					sign = 1;
				if ((MY - (gi->is_column + 2)) % (gi->block_height + 1) >= gi->block_height)
					sign = 1;
			}

			MCol_new = (MX - (gi->is_rower + 3)) / (gi->block_width + gi->is_separate * 2);
			MRow_new = (MY - (gi->is_column + 2)) / (gi->block_height + gi->is_separate);

			if (*(num + MRow_new * gi->col_max + MCol_new) == BDI_VALUE_BLANK)
				sign = 1;

			if (sign && !old_sign)
				bottom_statue(NULL, "[当前鼠标] 位置非法", gi);
			if (sign) {
				draw_block(MRow, MCol, *(num + MRow * gi->col_max + MCol), gi, bdi);
				continue;
			}

			switch (MAction) {
				case MOUSE_RIGHT_BUTTON_CLICK:
					return -1;
				case MOUSE_LEFT_BUTTON_CLICK:
					return 1;
				case MOUSE_ONLY_MOVED:
					if (MRow_new != MRow || MCol_new != MCol || old_sign) {
						char temp[256];
						sprintf_s(temp, "[当前鼠标] %c行%d列  ", char('A' + MRow_new), MCol_new);
						bottom_statue(NULL, temp, gi);
						MRow = MRow_new;
						MCol = MCol_new;
						return 0;
					}
			}
		}
	}
	return 0;
}

static void inner_draw_block_for_move(const int px, const int py, const int bdi_value, const game_info* gi, const block_display_info* const bdi)
{
	int color_fg_block = 0, color_bg_block = 0;

	char* content = NULL;

	int p = 0;
	while ((bdi + p)->value != -1) {
		if (bdi_value == (bdi + p)->value) {
			content = (char*)(bdi + p)->content;
			color_fg_block = (bdi + p)->color_fg;
			color_bg_block = (bdi + p)->color_bg;
			break;
		}
		++p;
	}

	cct_setcolor(color_bg_block, color_fg_block);

	for (int i = 0; i < gi->block_height; ++i) {
		cct_gotoxy(px, py + i);
		if (i == 0) {
			cout << bdi->left_top;
			for (int i = 0; i < (gi->block_width - 4) / 2; ++i)
				cout << bdi->row;
			cout << bdi->right_top;
		}
		else if (i == gi->block_height - 1) {
			cout << bdi->left_bottom;
			for (int i = 0; i < (gi->block_width - 4) / 2; ++i)
				cout << bdi->row;
			cout << bdi->right_bottom;
		}
		else {
			cout << bdi->col;
			if (i == gi->block_height / 2)
				cout << setw(int(gi->block_width - 4)) << content;
			else
				cout << setw(int(gi->block_width - 4)) << "";
			cout << bdi->col;
		}
	}
	cout << '\n';
}

void move_block(const int row_no, const int col_no, const int bdi_value, const game_info* gi, const block_display_info* const bdi, const frame_display_info* const fdi, const int direction, const int distance)
{
	//起始色块左上角位置
	int x = gi->is_rower + 3 + col_no * (gi->is_separate * 2 + gi->block_width);
	int y = gi->is_column + 2 + row_no * (gi->is_separate + gi->block_height);

	if (direction == UP_TO_DOWN) {
		for (int i = 0; i < distance * (gi->block_height + gi->is_separate); i++) {
			if ((i + 1) % (gi->block_height + gi->is_separate) == 0 && gi->is_separate) {
				for (int j = 0; j < gi->block_width / 2; j++)
					cct_showstr(x + j * 2, y, fdi->row, gi->color_bg_frame, gi->color_fg_frame);
			}
			else {
				for (int j = 0; j < gi->block_width / 2; j++)
					cct_showstr(x + j * 2, y, "  ", gi->color_bg_frame, gi->color_fg_frame);
			}
			y += 1;
			inner_draw_block_for_move(x, y, bdi_value, gi, bdi);
			Sleep(gi->delay_time_move);
		}
	}
	else if (direction == DOWN_TO_UP) {
	}
	else if (direction == LEFT_TO_RIGHT) {
	}
	else if (direction == RIGHT_TO_LEFT) {
		for (int i = 0; i < distance * (gi->block_width + gi->is_separate * 2); i++) {
			if ((i + 1) % (gi->block_width + gi->is_separate * 2) == 0 && gi->is_separate) {
				for (int j = 0; j < gi->block_height; j++)
					cct_showstr(x + gi->block_width - 1, y + j, fdi->col, gi->color_bg_frame, gi->color_fg_frame);
			}
			else {
				for (int j = 0; j < gi->block_height; j++)
					cct_showstr(x + gi->block_width - 1, y + j, " ", gi->color_bg_frame, gi->color_fg_frame);
			}
			x -= 1;
			inner_draw_block_for_move(x, y, bdi_value, gi, bdi);
			Sleep(gi->delay_time_move);
		}
	}
}

void confirm_click(char ch)
{
	int MAction, MX = 0, MY = 0, KeyCode1, KeyCode2;
	int type;
	while (1) {
		type = cct_read_keyboard_and_mouse(MX, MY, MAction, KeyCode1, KeyCode2);
		if (MAction == MOUSE_LEFT_BUTTON_CLICK || KeyCode1 == ch)
			break;
	}
}

void mov_pattern(const int row, const int col, int* num, const int mode, const game_info* const gi, const block_display_info* const bdi, const frame_display_info* const fdi)
{
	int blank = 0;
	switch (mode) {
		case UP_TO_DOWN:
			for (int j = 0; j < col; ++j) {
				blank = 0;
				int i = row - 1;
				for (i; i >= 0; --i) {
					if (*(num + i * gi->col_max + j) != BDI_VALUE_BLANK) {
						if (blank)
							move_block(i, j, *(num + i * gi->col_max + j), gi, bdi, fdi, UP_TO_DOWN, blank);
					}
					else
						++blank;
				}
			}
			break;
		case DOWN_TO_UP:
			break;
		case LEFT_TO_RIGHT:
			break;
		case RIGHT_TO_LEFT:
			for (int j = 0; j < col; ++j) {
				int i = 0;
				for (i; i < row; ++i) {
					if (*(num + i * gi->col_max + j) != BDI_VALUE_BLANK)
						break;
				}
				if (i >= row)
					++blank;
				else if (blank > 0) {
					for (i = row - 1; i >= 0; --i) {
						if (*(num + i * gi->col_max + j) == BDI_VALUE_BLANK)
							continue;
						move_block(i, j, *(num + i * gi->col_max + j), gi, bdi, fdi, RIGHT_TO_LEFT, blank);
					}
				}
			}
			break;
	}
}

void find_not_blank(const int row, const int col, int* num, int &row_no, int &col_no, game_info* gi)
{
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			if (*(num + i * gi->col_max + j) != BDI_VALUE_BLANK) {
				row_no = i;
				col_no = j;
				return;
			}
		}
	}
}