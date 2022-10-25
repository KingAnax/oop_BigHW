/* 2151613 毛宇录 计科 */

#include "90-01-b2-gmw.h"

void init_game_info(int &row, int &col, int& target)
{
	cout << "请输入行数(" << row_min << "-" << row_max << ")：\n";
	cin >> row;
	while (cin.fail() || row < row_min || row > row_max) {
		if (cin.fail()) {
			cin.clear();
			cin.ignore(65536, '\n');
		}
		cout << "请输入行数(" << row_min << "-" << row_max << ")：\n";
		cin >> row;
	}
	cout << "请输入列数(" << col_min << "-" << col_max << ")：\n";
	cin >> col;
	while (cin.fail() || col < col_min || col > col_max) {
		if (cin.fail()) {
			cin.clear();
			cin.ignore(65536, '\n');
		}
		cout << "请输入列数(" << col_min << "-" << col_max << ")：\n";
		cin >> col;
	}
	if (target == NULL)
		return;
	cout << "请输入合成目标(" << target_min << "-" << target_max << ")：\n";
	cin >> target;
	while (cin.fail() || target < target_min || target > target_max) {
		if (cin.fail()) {
			cin.clear();
			cin.ignore(65536, '\n');
		}
		cout << "请输入合成目标(" << target_min << "-" << target_max << ")：\n";
		cin >> target;
	}
	return;
}

void init_array(int (*num)[col_max], const int row, const int col)
{
	for (int i = 0; i < row; ++i)
		for (int j = 0; j < col; ++j)
			*(*(num + i) + j) = rand() % init_num + 1;
}

int chance_number(const int stage)  //根据概率生成数字
{
	int result;
	if (stage == 3)
		result = rand() % 3 + 1;
	else if (stage == 4)
		result = (rand() % 10) / 3 + 1;
	else if (stage == 5) {
		result = rand() % 100;
		if (result < 75)
			result = result / 25 + 1;
		else
			result = result / 90 + 4;
	}
	else if (stage == 6) {
		result = rand() % 20;
		if (result < 16)
			result = result / 4 + 1;
		else
			result = result / 19 + 5;
	}
	else
	{
		result = rand() % 20;
		if (result < 16)
			result = result * (stage - 3) / 16 + 1;
		else if (result < 18)
			result = stage - 2;
		else
			result = stage - 1 + result / 19;
	}
	return result;
}

int read_keyboard_and_mouse(const CONSOLE_GRAPHICS_INFO* const pCGI, int& MAction, int& MRow, int& MCol, int& KeyCode1, int& KeyCode2, int (*num)[col_max], int(*num_sel)[col_max], const int row, const int col)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;

	cct_enable_mouse();

	int MX = 0, MY = 0;  //记录鼠标位置
	int type;            //事件类型
	int MRow_new = MRow, MCol_new = MCol;    //行列新值
	int sign = 0, old_sign = 0;
	char temp[256];

	while (1) {
		type = cct_read_keyboard_and_mouse(MX, MY, MAction, KeyCode1, KeyCode2);
		if (type == CCT_KEYBOARD_EVENT) {
			switch (KeyCode1) {
				case 'Q':
					return CCT_KEYBOARD_EVENT;
				case 'q':
					return CCT_KEYBOARD_EVENT;
				case '\r':
					return CCT_KEYBOARD_EVENT;
				case 224:
					for (int i = 0; i < row; ++i)
						for (int j = 0; j < col; ++j)
							if (num_sel[i][j]) {
								gmw_draw_block(pCGI, i, j, num[i][j], bdi_normal);
								num_sel[i][j] = 0;
							}
					switch (KeyCode2) {
						case KB_ARROW_UP:
							--MRow;
							if (MRow < 0)
								MRow = row - 1;
							break;
						case KB_ARROW_DOWN:
							++MRow;
							if (MRow >= row)
								MRow = 0;
							break;
						case KB_ARROW_LEFT:
							--MCol;
							if (MCol < 0)
								MCol = col - 1;
							break;
						case KB_ARROW_RIGHT:
							++MCol;
							if (MCol >= col)
								MCol = 0;
							break;
					}
					sprintf(temp, "[当前键盘] %c行%d列  ", char('A' + MRow), MCol);
					gmw_status_line(pCGI, LOWER_STATUS_LINE, temp);
					gmw_draw_block(pCGI, MRow, MCol, *(*(num + MRow) + MCol), bdi_normal);
					return CCT_KEYBOARD_EVENT;
			}
		}
		else {
			//判断右键
			if (MAction == MOUSE_RIGHT_BUTTON_CLICK) {
				MRow = MRow_new;
				MCol = MCol_new;
				return CCT_MOUSE_EVENT;
			}
			old_sign = sign;
			//判断鼠标位置是否合法
			sign = 0;
			if (MX < pCGI->start_x + pCGI->draw_frame_with_row_no * 2 + 2)
				sign = 1;
			if (MX >= pCGI->start_x + pCGI->draw_frame_with_row_no * 2 + pCGI->CFI.bwidth - 2)
				sign = 1;
			if (MY < pCGI->start_y + pCGI->draw_frame_with_col_no + 1)
				sign = 1;
			if (MY >= pCGI->start_y + pCGI->draw_frame_with_col_no + pCGI->CFI.bhigh - 1)
				sign = 1;
			if (pCGI->CFI.separator) {
				if ((MX - pCGI->start_x - pCGI->draw_frame_with_row_no * 2 - 2) % (pCGI->CFI.block_width + 2) >= pCGI->CFI.block_width)
					sign = 1;
				if ((MY - pCGI->start_y - pCGI->draw_frame_with_col_no - 1) % (pCGI->CFI.block_high + 1) >= pCGI->CFI.block_high)
					sign = 1;
			}

			//判断左键
			if (MAction == MOUSE_LEFT_BUTTON_CLICK) {
				if (sign)
					gmw_status_line(pCGI, LOWER_STATUS_LINE, "[当前光标] 位置非法");
				else {
					return CCT_MOUSE_EVENT;
				}
			}

			//剩下鼠标移动
			if (sign) {
				if (!old_sign) {
					gmw_status_line(pCGI, LOWER_STATUS_LINE, "[当前光标] 位置非法");
					gmw_draw_block(pCGI, MRow, MCol, *(*(num + MRow) + MCol), bdi_normal);
					for (int i = 0; i < row; ++i)
						for (int j = 0; j < col; ++j)
							if (num_sel[i][j]) {
								gmw_draw_block(pCGI, i, j, num[i][j], bdi_normal);
								num_sel[i][j] = 0;
							}
				}
			}
			else {
				MCol_new = (MX - pCGI->start_x - pCGI->draw_frame_with_row_no * 2 - 2) / (pCGI->CFI.block_width + pCGI->CFI.separator * 2);
				MRow_new = (MY - pCGI->start_y - pCGI->draw_frame_with_col_no - 1) / (pCGI->CFI.block_high + pCGI->CFI.separator);
				if (MRow_new != MRow || MCol_new != MCol || old_sign) {
					sprintf(temp, "[当前光标] %c行%d列", char('A' + MRow_new), MCol_new);
					gmw_status_line(pCGI, LOWER_STATUS_LINE, temp);
					MRow = MRow_new;
					MCol = MCol_new;
					return CCT_MOUSE_EVENT;
				}
			}
		}
	}

	return CCT_MOUSE_EVENT;
}

int find_equal(int count, const int bdi_value, const int row, const int col, const int (*num)[col_max], int (*num_sel)[col_max], const int mrow, const int mcol)
{
	//以递归方式查找
	if (mrow < 0 || mrow >= row || mcol < 0 || mcol >= col) //超出边界返回
		return count;
	if (num_sel[mrow][mcol] == 1) //已标记过则返回
		return count;
	if (num[mrow][mcol] == bdi_value) {
		++count;
		num_sel[mrow][mcol] = 1;
		count += find_equal(0, bdi_value, row, col, num, num_sel, mrow - 1, mcol); //向上
		count += find_equal(0, bdi_value, row, col, num, num_sel, mrow + 1, mcol); //向下
		count += find_equal(0, bdi_value, row, col, num, num_sel, mrow, mcol - 1); //向左
		count += find_equal(0, bdi_value, row, col, num, num_sel, mrow, mcol + 1); //向右
	}
	return count;
}

void combine(const CONSOLE_GRAPHICS_INFO* const MyCGI, const int row, const int col, int mrow, int mcol, int (*num)[col_max], int (*num_sel)[col_max])
{
	for (int i = 0; i < row; ++i)
		for (int j = 0; j < col; ++j)
			if (num_sel[i][j] && (i != mrow || j != mcol))
				num[i][j] = BDI_VALUE_BLANK;
	++num[mrow][mcol];
	for (int i = 0; i < row; ++i)
		for (int j = 0; j < col; ++j)
			if (num_sel[i][j]) {
				num_sel[i][j] = 0;
				gmw_draw_block(MyCGI, i, j, num[i][j], bdi_normal);
			}
	Sleep(200);
}

void score(const CONSOLE_GRAPHICS_INFO* const MyCGI, const int count, const int value ,int &score_total, const int target)
{
	int score_cur = count * value * 3;
	score_total += score_cur;
	char buf[80] = {};
	sprintf(buf, "%s%d%s%d%s%d", "本次得分:", score_cur, " 总分:", score_total, " 合成目标:", target);
	gmw_status_line(MyCGI, TOP_STATUS_LINE, buf);
}

void fall(const CONSOLE_GRAPHICS_INFO* const MyCGI, int (*num)[col_max], const int row, const int col)
{
	int blank;
	for (int j = 0; j < col; ++j) {
		blank = 0;
		int i = row - 1;
		for (i; i >= 0; --i) {
			if (num[i][j] != BDI_VALUE_BLANK) {
				if (blank) {
					gmw_move_block(MyCGI, i, j, num[i][j], BDI_VALUE_BLANK, bdi_normal, UP_TO_DOWN, blank);
					num[i + blank][j] = num[i][j];
					num[i][j] = 0;
				}
			}
			else
				++blank;
		}
	}
}

void fill_blank(const CONSOLE_GRAPHICS_INFO* const MyCGI, int(*num)[col_max], const int row, const int col)
{
	int stage = init_num;
	for (int i = 0; i < row; ++i)
		for (int j = 0; j < col; ++j)
			if (num[i][j] > stage)
				stage = num[i][j];
	for (int i = 0; i < row; ++i)
		for (int j = 0; j < col; ++j)
			if (num[i][j] == BDI_VALUE_BLANK) {
				num[i][j] = chance_number(stage);
				gmw_draw_block(MyCGI, i, j, num[i][j], bdi_normal);
			}
}

int is_end(int(*num)[col_max], const int row, const int col)
{
	int num_pick[row_max][col_max];
	for (int i = 0; i < row; ++i)
		for (int j = 0; j < col; ++j)
			if (find_equal(0, num[i][j], row, col, num, num_pick, i, j) > 1)
				return 0;
	return 1;
}

void confirm_q()
{
	char ch  = _getch();
	while (ch != 'q' && ch != 'Q')
		ch = _getch();
}

void confirm_enter()
{
	int MX, MY, MAction, keycode1, keycode2;
	while (1) {
		int ret = cct_read_keyboard_and_mouse(MX, MY, MAction, keycode1, keycode2);
		if (ret == CCT_MOUSE_EVENT) {
			if (MAction == MOUSE_LEFT_BUTTON_CLICK)
				break;
		}
		else {
			if (keycode1 == '\r')
				break;
		}
	}
}