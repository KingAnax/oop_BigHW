//2151613 �ƿ� ë��¼

#include "90-02-b1.h"

const block_display_info bdi_num[7] = {
	{0, "", 1, 15, 15, "�X", "�[","�^","�a","�T","�U"},
	{1, "��", 0, 0, 1, "�X", "�[","�^","�a","�T","�U"},
	{2, "��", 0, 0, 2, "�X", "�[","�^","�a","�T","�U"},
	{3, "��", 0, 0, 3, "�X", "�[","�^","�a","�T","�U"},
	{4, "��", 0, 0, 4, "�X", "�[","�^","�a","�T","�U"},
	{5, "��", 0, 0, 5, "�X", "�[","�^","�a","�T","�U"},
	{-1, NULL, NULL},
};

const block_display_info bdi_normal[7] = {
	{0, "", 1, 7, 7, "�X", "�[","�^","�a","�T","�U"},
	{1, "��", 0, 7, 1, "�X", "�[","�^","�a","�T","�U"},
	{2, "��", 0, 7, 2, "�X", "�[","�^","�a","�T","�U"},
	{3, "��", 0, 7, 3, "�X", "�[","�^","�a","�T","�U"},
	{4, "��", 0, 7, 4, "�X", "�[","�^","�a","�T","�U"},
	{5, "��", 0, 7, 5, "�X", "�[","�^","�a","�T","�U"},
	{-1, NULL, NULL},
};

const block_display_info bdi_sel[7] = {
	{0, "", 1, 15, 7, "�X", "�[","�^","�a","�T","�U"},
	{1, "��", 0, 15, 1, "�X", "�[","�^","�a","�T","�U"},
	{2, "��", 0, 15, 2, "�X", "�[","�^","�a","�T","�U"},
	{3, "��", 0, 15, 3, "�X", "�[","�^","�a","�T","�U"},
	{4, "��", 0, 15, 4, "�X", "�[","�^","�a","�T","�U"},
	{5, "��", 0, 15, 5, "�X", "�[","�^","�a","�T","�U"},
	{-1, NULL, NULL},
};

const frame_display_info fdi = {
	"�X", "�[","�^","�a","�T","�U","�d", "�g","�j","�m","�p"
};

void pfD()
{
	game_info g1 = {};
	game_info* gi = &g1;
	char buf[80] = {};
	int row, col;
	putin(&row, &col, NULL, row_min, row_max, col_min, col_max, NULL, NULL);
	int num[row_max][col_max] = { 0 };
	int num_signed[row_max][col_max] = { 0 };
	cct_setcursor(CURSOR_INVISIBLE);
	init_array(&num[0][0], row, col, col_max, number_count);
	init_board(row, col, 0, 1, 1, 3, 6, 0, 15, 7, 0, 14, 0, 1, 1, 0, col_max, gi);
	draw_board(row, col, col_max, &num[0][0], gi, &fdi, bdi_num);

	//���Ϸ���
	for (int i = 0; i < row; ++i)
		for (int j = 0; j < col; ++j)
			draw_block(i, j, num[i][j], gi, bdi_num);

	sprintf_s(buf, "%s%d%s%d%s", "��Ļ��ǰ����Ϊ��", gi->row, "��", gi->col, "��");
	top_statue(NULL, buf, gi);

	//������
	int MAction, MRow = 0, MCol = 0, KeyCode1, KeyCode2;
	int MRow_old = 0, MCol_old = 0;
	int type, flag = 0;
	draw_block(MRow, MCol, num[MRow][MCol], gi, bdi_normal);
	bottom_statue(NULL, "��ͷ��/����ƶ����س���/�������ѡ�񲢽���", gi);
	while (1) {
		MRow_old = MRow;
		MCol_old = MCol;
		type = read_mouse_keyboard(MAction, MRow, MCol, KeyCode1, KeyCode2, &num[0][0], gi, bdi_num);
		switch (type) {
			case -1:
				flag = 1;
				break;
			case 0:
				draw_block(MRow_old, MCol_old, num[MRow_old][MCol_old], gi, bdi_num);
				draw_block(MRow, MCol, num[MRow][MCol], gi, bdi_normal);
				break;
			case 1:
				char temp[256];
				sprintf_s(temp, "ѡ����%c��%d��", char('A' + MRow), MCol);
				bottom_statue(NULL, temp, gi);
				flag = 1;
				break;
		}
		if (flag)
			break;
	}
	cct_setcolor();
	cct_setcursor(CURSOR_VISIBLE_NORMAL);
	end();
}

void pfE()
{
	game_info g1 = {};
	game_info* gi = &g1;
	char buf[80] = {};
	int row, col;
	putin(&row, &col, NULL, row_min, row_max, col_min, col_max, NULL, NULL);
	int num[row_max][col_max] = { 0 };
	int num_signed[row_max][col_max] = { 0 };
	cct_setcursor(CURSOR_INVISIBLE);
	init_array(&num[0][0], row, col, col_max, number_count);
	init_board(row, col, 1, 1, 1, 3, 6, 0, 15, 7, 0, 14, 0, 1, 1, 0, col_max, gi);
	draw_board(row, col, col_max, &num[0][0], gi, &fdi, bdi_num);

	//���Ϸ���
	for (int i = 0; i < row; ++i)
		for (int j = 0; j < col; ++j)
			draw_block(i, j, num[i][j], gi, bdi_num);

	sprintf_s(buf, "%s%d%s%d%s", "��Ļ��ǰ����Ϊ��", gi->row, "��", gi->col, "��");
	top_statue(NULL, buf, gi);

	//������
	int MAction, MRow = 0, MCol = 0, KeyCode1, KeyCode2;
	int MRow_old = 0, MCol_old = 0;
	int type, flag = 0;
	draw_block(MRow, MCol, num[MRow][MCol], gi, bdi_normal);
	bottom_statue(NULL, "��ͷ��/����ƶ����س���/�������ѡ�񲢽���", gi);
	while (1) {
		MRow_old = MRow;
		MCol_old = MCol;
		type = read_mouse_keyboard(MAction, MRow, MCol, KeyCode1, KeyCode2, &num[0][0], gi, bdi_num);
		switch (type) {
			case -1:
				flag = 1;
				break;
			case 0:
				draw_block(MRow_old, MCol_old, num[MRow_old][MCol_old], gi, bdi_num);
				draw_block(MRow, MCol, num[MRow][MCol], gi, bdi_normal);
				break;
			case 1:
				char temp[256];
				sprintf_s(temp, "ѡ����%c��%d��", char('A' + MRow), MCol);
				bottom_statue(NULL, temp, gi);
				flag = 1;
				break;
		}
		if (flag)
			break;
	}
	cct_setcolor();
	cct_setcursor(CURSOR_VISIBLE_NORMAL);
	end();
}

void pfF()
{
	game_info g1 = {};
	game_info* gi = &g1;
	char buf[80] = {};
	int row, col;
	putin(&row, &col, NULL, row_min, row_max, col_min, col_max, NULL, NULL);
	int num[row_max][col_max] = { 0 };
	int num_signed[row_max][col_max] = { 0 };
	cct_setcursor(CURSOR_INVISIBLE);
	init_array(&num[0][0], row, col, col_max, number_count);
	init_board(row, col, 0, 1, 1, 3, 6, 0, 15, 7, 0, 14, 0, 1, 1, 50, col_max, gi);
	draw_board(row, col, col_max, &num[0][0], gi, &fdi, bdi_num);

	//���Ϸ���
	for (int i = 0; i < row; ++i)
		for (int j = 0; j < col; ++j)
			draw_block(i, j, num[i][j], gi, bdi_num);

	sprintf_s(buf, "%s%d%s%d%s", "��Ļ��ǰ����Ϊ��", gi->row, "��", gi->col, "��");
	top_statue(NULL, buf, gi);

	//������
	int MAction, MRow = 0, MCol = 0, KeyCode1, KeyCode2;
	int MRow_old = 0, MCol_old = 0;
	int type, flag_quit = 0, flag_sel = 0;
	draw_block(MRow, MCol, num[MRow][MCol], gi, bdi_normal);
	bottom_statue(NULL, "��ͷ��/����ƶ����س���/�������ѡ�񲢽���", gi);
	while (1) {
		MRow_old = MRow;
		MCol_old = MCol;
		type = read_mouse_keyboard(MAction, MRow, MCol, KeyCode1, KeyCode2, &num[0][0], gi, bdi_num);
		switch (type) {
			case -1:
				flag_quit = 1;
				break;
			case 0:
				if (flag_sel) {
					flag_sel = 0;
					for (int i = 0; i < row; ++i)
						for (int j = 0; j < col; ++j)
							if (num_signed[i][j]) {
								draw_block(i, j, num[i][j], gi, bdi_num);
								num_signed[i][j] = 0;
							}
				}
				else
					draw_block(MRow_old, MCol_old, num[MRow_old][MCol_old], gi, bdi_num);
				draw_block(MRow, MCol, num[MRow][MCol], gi, bdi_normal);
				break;
			case 1:
				if (!panduan(MRow + 'A', MCol + '0', &num[0][0], col_max))
					bottom_statue("��Χ����ֵͬ", NULL, gi);
				else if (flag_sel) {
					flag_quit = 1;
					flag_sel = 0;
					for (int i = 0; i < row; ++i) {
						for (int j = 0; j < col; ++j) {
							if (num_signed[i][j]) {
								draw_block(i, j, BDI_VALUE_BLANK, gi, bdi_num);
								num[i][j] = 0;
								num_signed[i][j] = 0;
							}
						}
					}
					bottom_statue(NULL, "�ϳ���ɣ��س���/�����������հ�ֵ", gi);
					confirm_click('\r');
					mov_pattern(row, col, &num[0][0], UP_TO_DOWN, gi, bdi_num, &fdi);
					mov_array(&num[0][0], row, col, UP_TO_DOWN, col_max);
					mov_pattern(row, col, &num[0][0], RIGHT_TO_LEFT, gi, bdi_num, &fdi);
					mov_array(&num[0][0], row, col, RIGHT_TO_LEFT, col_max);
				}
				else {
					flag_sel = 1;
					sign_command_line(MRow * col_max + MCol, row, &num[0][0], &num_signed[0][0], row_max, col_max);
					for(int i=0;i<row;++i)
						for(int j=0;j<col;++j)
							if(num_signed[i][j])
								draw_block(i, j, num[i][j], gi, bdi_normal);
					draw_block(MRow, MCol, num[MRow][MCol], gi, bdi_sel);
					bottom_statue(NULL, "�س�/��������ϳ�", gi);
				}
				break;
		}
		if (flag_quit)
			break;
	}
	cct_gotoxy(0, gi->last_line + 1);
	cct_setcolor();
	cct_setcursor(CURSOR_VISIBLE_NORMAL);
	end();
}

void pfG()
{
	game_info g1 = {};
	game_info* gi = &g1;
	char buf[80] = {};
	int row, col;
	putin(&row, &col, NULL, row_min, row_max, col_min, col_max, NULL, NULL);
	int num[row_max][col_max] = { 0 };
	int num_signed[row_max][col_max] = { 0 };
	int MAction, MRow = 0, MCol = 0, KeyCode1, KeyCode2;
	int MRow_old = 0, MCol_old = 0;
	int type, flag_quit = 0, flag_sel = 0;
	cct_setcursor(CURSOR_INVISIBLE);
	while (1) {
		init_array(&num[0][0], row, col, col_max, number_count);
		init_board(row, col, 1, 1, 1, 3, 6, 0, 15, 7, 0, 14, 0, 1, 1, 20, col_max, gi);
		draw_board(row, col, col_max, &num[0][0], gi, &fdi, bdi_num);
		//���Ϸ���
		for (int i = 0; i < row; ++i)
			for (int j = 0; j < col; ++j)
				draw_block(i, j, num[i][j], gi, bdi_num);
		sprintf_s(buf, "%s%d%s%d%s", "��Ļ��ǰ����Ϊ��", gi->row, "��", gi->col, "��");
		top_statue(NULL, buf, gi);
		//������
		draw_block(MRow, MCol, num[MRow][MCol], gi, bdi_normal);
		bottom_statue(NULL, "��ͷ��/����ƶ����س���/�������ѡ�񲢽���", gi);
		int score = 0, score_cur = 0;
		int flag_end = 0;
		while (1) {
			MRow_old = MRow;
			MCol_old = MCol;
			type = read_mouse_keyboard(MAction, MRow, MCol, KeyCode1, KeyCode2, &num[0][0], gi, bdi_num);
			if (type == -1)
				flag_quit = 1;
			else if (type == 0) {
				if (flag_sel) {
					flag_sel = 0;
					for (int i = 0; i < row; ++i)
						for (int j = 0; j < col; ++j)
							if (num_signed[i][j]) {
								draw_block(i, j, num[i][j], gi, bdi_num);
								num_signed[i][j] = 0;
							}
				}
				else
					draw_block(MRow_old, MCol_old, num[MRow_old][MCol_old], gi, bdi_num);
				draw_block(MRow, MCol, num[MRow][MCol], gi, bdi_normal);
			}
			else {
				if (!panduan(MRow + 'A', MCol + '0', &num[0][0], col_max))
					bottom_statue("��Χ����ֵͬ", NULL, gi);
				else if (flag_sel) {
					flag_sel = 0;
					score_cur = score_count(&score, &num_signed[0][0]);
					sprintf_s(buf, "%s%d%s%d", "���ε÷�:", score_cur, " �ܷ�:", score);
					top_statue(NULL, buf, gi);
					for (int i = 0; i < row; ++i) {
						for (int j = 0; j < col; ++j) {
							if (num_signed[i][j]) {
								draw_block(i, j, BDI_VALUE_BLANK, gi, bdi_num);
								num[i][j] = 0;
								num_signed[i][j] = 0;
							}
						}
					}
					//���������
					mov_pattern(row, col, &num[0][0], UP_TO_DOWN, gi, bdi_num, &fdi);
					mov_array(&num[0][0], row, col, UP_TO_DOWN, col_max);
					mov_pattern(row, col, &num[0][0], RIGHT_TO_LEFT, gi, bdi_num, &fdi);
					mov_array(&num[0][0], row, col, RIGHT_TO_LEFT, col_max);
					//�ж���Ϸ�Ƿ����
					if (!is_end(row, col, &num[0][0], col_max, "")) {
						flag_end = 1;
						int count = 0;
						for (int i = 0; i < row; ++i)
							for (int j = 0; j < col; ++j)
								if (num[i][j])
									++count;
						sprintf_s(buf, "%s%d%s", "ʣ��", count, "�����ǣ��޿���������ؽ���!");
						bottom_statue(buf, NULL, gi);
						score_cur = score_end(&score, &num[0][0], row, col);
						sprintf_s(buf, "%s%d%s%d", "�����÷�:", score_cur, " �ܷ�:", score);
						top_statue(NULL, buf, gi);
						confirm_click('\r');
					}
					else {
						//�Ҳ��ǿհ׵�ֵ
						if (num[MRow][MCol] == BDI_VALUE_BLANK)
							find_not_blank(row, col, &num[0][0], MRow, MCol, gi);
						//��ʾ������λ��
						if (num[MRow][MCol] != BDI_VALUE_BLANK) {
							draw_block(MRow, MCol, num[MRow][MCol], gi, bdi_normal);
							if (MAction != 0) {
								sprintf_s(buf, "[��ǰ���] %c��%d��  ", char('A' + MRow), MCol);
								bottom_statue(NULL, buf, gi);
							}
							else {
								sprintf_s(buf, "[��ǰ����] %c��%d��  ", char('A' + MRow), MCol);
								bottom_statue(NULL, buf, gi);
							}
						}
						else {
							bottom_statue(NULL, "��ǰλ�÷Ƿ�", gi);
							if (MAction == 0) {
								draw_block(MRow, MCol, num[MRow][MCol], gi, bdi_normal);
								sprintf_s(buf, "[��ǰ����] %c��%d��  ", char('A' + MRow), MCol);
								bottom_statue(NULL, buf, gi);
							}
						}
					}
				}
				else {
					flag_sel = 1;
					sign_command_line(MRow * col_max + MCol, row, &num[0][0], &num_signed[0][0], row_max, col_max);
					for (int i = 0; i < row; ++i)
						for (int j = 0; j < col; ++j)
							if (num_signed[i][j])
								draw_block(i, j, num[i][j], gi, bdi_normal);
					draw_block(MRow, MCol, num[MRow][MCol], gi, bdi_sel);
					bottom_statue(NULL, "�س�/��������ϳ�", gi);
				}
			}
			MAction = 0;
			if (flag_quit || flag_end)
				break;
		}
		if (flag_quit)
			break;
	}
	cct_setcolor();
	cct_setcursor(CURSOR_VISIBLE_NORMAL);
	end();
}