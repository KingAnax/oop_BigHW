/* 2151613 ë��¼ �ƿ� */

#include "90-02-b2.h"

void game_info_input(int& rank)
{
	cout << "������ɨ����Ϸ�ĵȼ������֣�������\\�м�\\�߼���1\\2\\3��" << endl;
	char ch;
	ch = _getch();
	while (ch < '1' || ch > '3')
		ch = _getch();
	rank = ch - '0';
}

static void for_init_array(int(*p)[col_max], int(*p_open)[col_max], const int row, const int col, int mine_count, const int px, const int py)
{
	for (int i = 0; i < row; ++i)
		for (int j = 0; j < col; ++j) {
			p[i][j] = 0;
			p_open[i][j] = 0;
		}
	while (mine_count) {
		int r = rand() % row;
		int c = rand() % col;
		//��֤�����״�ѡ�е���Χ��֮ǰ���׵�
		if (*(*(p + r) + c) != is_mine && (r > px  + 1 || c > py + 1 || r < px - 1 || c < py - 1))
			*(*(p + r) + c) = is_mine;
		else
			continue;
		--mine_count;
	}
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			if (p[i][j] == is_mine) {
				//��
				if (i > 0 && p[i - 1][j] != is_mine)
					++p[i - 1][j];
				//��
				if (i < row - 1 && p[i + 1][j] != is_mine)
					++p[i + 1][j];
				//��
				if (j > 0 && p[i][j - 1] != is_mine)
					++p[i][j - 1];
				//��
				if (j < col - 1 && p[i][j + 1] != is_mine)
					++p[i][j + 1];
				//����
				if (i > 0 && j > 0 && p[i - 1][j - 1] != is_mine)
					++p[i - 1][j - 1];
				//����
				if (i > 0 && j < col - 1 && p[i - 1][j + 1] != is_mine)
					++p[i - 1][j + 1];
				//����
				if (i < row - 1 && j > 0 && p[i + 1][j - 1] != is_mine)
					++p[i + 1][j - 1];
				//����
				if (i < row - 1 && j < col - 1 && p[i + 1][j + 1] != is_mine)
					++p[i + 1][j + 1];
			}
		}
	}
}

void init_array(int(*p)[col_max], int(*p_open)[col_max], const int rank, const char px, const char py)
{
	int r = (px < 0 ? -1 : px - 'A');
	int c;
	if (py < 0)
		c = -1;
	else if (py <= '9')
		c = py - '1';
	else
		c = py - 'a' + 9;
	for_init_array(p, p_open, rank_info[rank -1].row, rank_info[rank - 1].col, rank_info[rank - 1].mine_num, r, c);
}

static void for_draw_command_line(const int col)
{
	//�б�
	cout << setw(2) << "" << '|';
	for (int i = 0; i < col; ++i) {
		if (i < 9)
			cout << setw(2) << resetiosflags(ios::right) << setiosflags(ios::left) << i + 1;
		else
			cout << setw(2) << resetiosflags(ios::right) << setiosflags(ios::left) << (char)('a' + i - 9);
	}
	//����
	cout << "\n" << setw(2) << setfill('-') << "" << '+';
	cout << setw(col * 2 - 1) << "" << endl;
	cout << setfill(' ');
}

void show_innner_array_command_line(int(*p)[col_max], const int rank, const int mode)
{
	cout << "�ڲ����飺" << endl;

	for_draw_command_line(rank_info[rank - 1].col);

	//ÿ��
	for (int i = 0; i < rank_info[rank - 1].row; ++i) {
		//�б�
		cout << setw(2) << resetiosflags(ios::right) << setiosflags(ios::left) << (char)('A' + i);
		cout << '|';
		//����
		switch (mode) {
			case 0:
				for (int j = 0; j < rank_info[rank - 1].col; ++j)
					cout << setw(2) << resetiosflags(ios::right) << setiosflags(ios::left) << 'X';
				break;
			case 1:
				for (int j = 0; j < rank_info[rank - 1].col; ++j)
					cout << setw(2) << resetiosflags(ios::right) << setiosflags(ios::left) << (char)(p[i][j] >= 0 ? p[i][j] + '0' : '*');
				break;
		}
		cout << endl;
	}
	cout << resetiosflags(ios::left) << setiosflags(ios::right);
}

void end_with_enter()
{
	cout << "\n\n���س�������...";
	char ch;
	ch = _getch();
	while (ch != '\r')
		ch = _getch();
}

int get_rc_command_line(char& px, char& py, const int rank)
{
	char choice_row[40] = "\0", choice_col[40] = "\0";
	strcpy_s(choice_row, rank_info[rank - 1].choice_row);
	strcpy_s(choice_col, rank_info[rank - 1].choice_col);
	cout << "\n\n�����ݺ����꣨��Gf��A1����q�˳�����";
	px = _getch();
	while (strchr(choice_row, px) == NULL && px != 'q')
		px = _getch();
	cout << px;
	if (px == 'q')
		return 1;
	py = _getch();
	while (strchr(choice_col, py) == NULL && py != 'q')
		py = _getch();
	cout << py;
	return 0;
}

static void for_uncover(const int(*mine)[col_max], int(*mine_open)[col_max], const int r, const int c, const int rank)
{
	//Խ�緵��
	if (r < 0 || r >= rank_info[rank - 1].row || c < 0 || c >= rank_info[rank - 1].col)
		return;
	//�ѱ�ǹ��򷵻�
	if (mine_open[r][c] > 0)
		return;
	//���׷���
	if (mine[r][c] == is_mine)
		return;

	*(*(mine_open + r) + c) = 1;

	//��������0���־ͽ�����
	if (*(*(mine + r) + c) > 0)
		return;

	//����
	for_uncover(mine, mine_open, r - 1, c, rank);
	//����
	for_uncover(mine, mine_open, r + 1, c, rank);
	//����
	for_uncover(mine, mine_open, r, c - 1, rank);
	//����
	for_uncover(mine, mine_open, r, c + 1, rank);
}

int uncover(const int(*mine)[col_max], int(*mine_open)[col_max], const char px, const char py, const int rank)
{
	int r = px - 'A';
	int c;
	if (py >= 'a')
		c = 9 + py - 'a';
	else
		c = py - '1';
	//�ݹ�
	//�ѱ�ǹ��򷵻�
	if (*(*(mine_open + r) + c) > 0)
		return 0;

	*(*(mine_open + r) + c) = 1;

	//���׽���
	if (*(*(mine + r) + c) == is_mine)
		return -1;

	//��������0���־ͽ�����
	if (*(*(mine + r) + c) > 0)
		return 0;

	//����
	for_uncover(mine, mine_open, r - 1, c, rank);
	//����
	for_uncover(mine, mine_open, r + 1, c, rank);
	//����
	for_uncover(mine, mine_open, r, c - 1, rank);
	//����
	for_uncover(mine, mine_open, r, c + 1, rank);
	return 0;
}

void show_open_array_command_line(const int(*mine)[col_max], const int(*mine_open)[col_max], const int rank)
{
	cout << "\n\n��ǰ���飺" << endl;

	for_draw_command_line(rank_info[rank - 1].col);

	//ÿ��
	for (int i = 0; i < rank_info[rank - 1].row; ++i) {
		//�б�
		cout << setw(2) << resetiosflags(ios::right) << setiosflags(ios::left) << (char)('A' + i);
		cout << '|';
		//����
		for (int j = 0; j < rank_info[rank - 1].col; ++j) {
			if(!mine_open[i][j]) //û�д�
				cout << setw(2) << resetiosflags(ios::right) << setiosflags(ios::left) << 'X';
			else { //����
				if (mine[i][j] >= 0) {
					cct_setcolor(14, (mine[i][j] + 1) % 7 - 1);
					cout << (char)(mine[i][j] + '0');
					cct_setcolor();
					cout << " ";
				}
				else {
					cct_setcolor(4, 0);
					cout << '*';
					cct_setcolor();
					cout << " ";
				}
			}
		}
		cout << endl;
	}
	cout << resetiosflags(ios::left) << setiosflags(ios::right);
}

int check_end(const int(*mine_open)[col_max], const int rank)
{
	int count = 0;
	for (int i = 0; i < rank_info[rank - 1].row; ++i)
		for (int j = 0; j < rank_info[rank - 1].col; ++j)
			if (mine_open[i][j] > 0)
				++count;
	if ((count + rank_info[rank - 1].mine_num) == rank_info[rank - 1].row * rank_info[rank - 1].col)
		return 1;
	else
		return 0;
}

int check_end(const int(*mine)[col_max], const int(*mine_open)[col_max], const int(*mine_sign)[col_max], const int rank)
{
	int count = 0;
	for (int i = 0; i < rank_info[rank - 1].row; ++i)
		for (int j = 0; j < rank_info[rank - 1].col; ++j)
			count += mine_open[i][j];

	if ((count + rank_info[rank - 1].mine_num) == rank_info[rank - 1].row * rank_info[rank - 1].col)
		return 1;

	int sign_right_count = 0;
	for (int i = 0; i < rank_info[rank - 1].row; ++i)
		for (int j = 0; j < rank_info[rank - 1].col; ++j)
			if (mine[i][j] == is_mine && mine_sign[i][j])
				++sign_right_count;

	if (sign_right_count == rank_info[rank - 1].mine_num)
		return 1;

	return 0;
}

void draw_block(const CONSOLE_GRAPHICS_INFO* const pCGI, const int value, const int row_no, const int col_no, const int mode)
{
	//��λ��ɫ�����Ͻ�
	int x = pCGI->start_x + pCGI->draw_frame_with_row_no * 2 + 2 + col_no * (pCGI->CFI.block_width + pCGI->CFI.separator * 2);
	int y = pCGI->start_y + pCGI->draw_frame_with_col_no + 1 + row_no * (pCGI->CFI.block_high + pCGI->CFI.separator);

	switch (mode) {
		case 0:
			cct_setcolor(7, value >= 0 ? (value + 6) % 7 + 1 : 0);
			break;
		case 1:
			cct_setcolor(6, 6);
			break;
		case 2:
			cct_setcolor(4, 0);
			break;
	}
	cct_gotoxy(x, y);
	cout << " ";
	cct_gotoxy(x, y + 1);
	cout << " "; 
	if (mode == 0) {
		if (value > 0)
			cout << value;
		else if (value < 0)
			cout << '*';
		else
			cout << ' ';
	}
	else if (mode == 1) {
		cout << ' ';
	}
	else if (mode == 2) {
		cout << '#';
	}
	cout << "  " << endl;

	cct_setcolor();
}

int sign_mine(int (*mine_sign)[col_max], const int (*mine_open)[col_max], const int r, const int c)
{
	if (mine_open[r][c])
		return 0;
	mine_sign[r][c] = 1 - mine_sign[r][c];
	return 1;
}

int read_keyboard_and_mouse(const CONSOLE_GRAPHICS_INFO* const pCGI, int& MAction, int& MRow, int& MCol, int& KeyCode1, int& KeyCode2, const bool update_lower_status_line)
{
	cct_enable_mouse();

	int MX = 0, MY = 0;  //��¼���λ��
	int type;            //�¼�����
	int MRow_new = MRow, MCol_new = MCol;    //������ֵ
	int sign = 0, old_sign = 0;

	while (1) {
		type = cct_read_keyboard_and_mouse(MX, MY, MAction, KeyCode1, KeyCode2);
		if (type == CCT_KEYBOARD_EVENT)
			return type;
		else {
			old_sign = sign;
			//�ж����λ���Ƿ�Ϸ�
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

			//�ж��Ҽ�
			if (MAction == MOUSE_RIGHT_BUTTON_CLICK) {
				if (!sign) {
					MRow = MRow_new;
					MCol = MCol_new;
					return CCT_MOUSE_EVENT;
				}
			}
			
			//�ж����
			if (MAction == MOUSE_LEFT_BUTTON_CLICK) {
				if (sign) {
					if (update_lower_status_line && !old_sign) {
						gmw_status_line(pCGI, LOWER_STATUS_LINE, "[��ǰ���] λ�÷Ƿ�");
					}
				}
				else {
					return CCT_MOUSE_EVENT;
				}
			}

			//ʣ������ƶ�
			if (sign) {
				if (update_lower_status_line && !old_sign) {
					gmw_status_line(pCGI, LOWER_STATUS_LINE, "[��ǰ���] λ�÷Ƿ�");
				}
			}
			else {
				MCol_new = (MX - pCGI->start_x - pCGI->draw_frame_with_row_no * 2 - 2) / (pCGI->CFI.block_width + pCGI->CFI.separator * 2);
				MRow_new = (MY - pCGI->start_y - pCGI->draw_frame_with_col_no - 1) / (pCGI->CFI.block_high + pCGI->CFI.separator);
				if (MRow_new != MRow || MCol_new != MCol || old_sign) {
					if (update_lower_status_line) {
						char temp[256];
						sprintf_s(temp, "[��ǰ���] %c��%d��", char('A' + MRow_new), MCol_new);
						gmw_status_line(pCGI, LOWER_STATUS_LINE, temp);
					}
					MRow = MRow_new;
					MCol = MCol_new;
					return CCT_MOUSE_EVENT;
				}
			}
		}
	}

	return CCT_MOUSE_EVENT; //�˾�ɸ�����Ҫ�޸�
}