/* 2151613 ë��¼ �ƿ� */

#include "90-02-b2.h"

void pf5()
{
	int rank;
	int mine[row_max][col_max];
	int mine_open[row_max][col_max];

	cct_cls();
	game_info_input(rank);

	CONSOLE_GRAPHICS_INFO MyCGI;                            //����һ��CGI����
	gmw_init(&MyCGI);                                       //��һ����ʼ��
	gmw_set_rowcol(&MyCGI, rank_info[rank - 1].row, rank_info[rank - 1].col); //��Ϸ��������
	gmw_set_color(&MyCGI, COLOR_BLACK, COLOR_WHITE);		//�޸Ĵ�����ɫ�������޸���Ϸ��������״̬��
	gmw_set_font(&MyCGI, "������", 16, 0);				    //TrueType���壨�����壩��Ȳ���Ҫ������������
	gmw_set_frame_style(&MyCGI, 4, 2, true);				//ÿ��ɫ��������2��*�߶�2�У�Ҫ�ָ���
	gmw_set_frame_default_linetype(&MyCGI, 1);			    //���ÿ������ΪԤ��ֵ1
	gmw_set_frame_color(&MyCGI, COLOR_HWHITE, COLOR_BLACK); //���ÿ����ɫ
	gmw_set_rowno_switch(&MyCGI, true);					    //��ʾ�к�
	gmw_set_colno_switch(&MyCGI, true);					    //��ʾ�б�
	gmw_set_block_border_switch(&MyCGI, false);			    //����ɫ�鲻��ҪС�߿�
	gmw_set_status_line_switch(&MyCGI, TOP_STATUS_LINE);	//������״̬��
	gmw_set_status_line_switch(&MyCGI, LOWER_STATUS_LINE);	//������״̬��

	cct_setcursor(CURSOR_INVISIBLE);                        //���ù�겻�ɼ�

	init_array(mine, mine_open, rank);

	gmw_draw_frame(&MyCGI);

	for (int i = 0; i < rank_info[rank - 1].row; ++i)
		for (int j = 0; j < rank_info[rank - 1].col; ++j)
			draw_block(&MyCGI, mine[i][j], i, j, 0);

	end_with_enter();
}

void pf6()
{
	int rank;
	int mine[row_max][col_max];
	int mine_open[row_max][col_max];

	cct_cls();
	game_info_input(rank);

	CONSOLE_GRAPHICS_INFO MyCGI;                            //����һ��CGI����
	gmw_init(&MyCGI);                                       //��һ����ʼ��
	gmw_set_rowcol(&MyCGI, rank_info[rank - 1].row, rank_info[rank - 1].col); //��Ϸ��������
	gmw_set_color(&MyCGI, COLOR_BLACK, COLOR_WHITE);		//�޸Ĵ�����ɫ�������޸���Ϸ��������״̬��
	gmw_set_font(&MyCGI, "������", 16, 0);				    //TrueType���壨�����壩��Ȳ���Ҫ������������
	gmw_set_frame_style(&MyCGI, 4, 2, true);				//ÿ��ɫ��������2��*�߶�2�У�Ҫ�ָ���
	gmw_set_frame_default_linetype(&MyCGI, 1);			    //���ÿ������ΪԤ��ֵ1
	gmw_set_frame_color(&MyCGI, COLOR_HWHITE, COLOR_BLACK); //���ÿ����ɫ
	gmw_set_rowno_switch(&MyCGI, true);					    //��ʾ�к�
	gmw_set_colno_switch(&MyCGI, true);					    //��ʾ�б�
	gmw_set_block_border_switch(&MyCGI, false);			    //����ɫ�鲻��ҪС�߿�
	gmw_set_status_line_switch(&MyCGI, TOP_STATUS_LINE);	//������״̬��
	gmw_set_status_line_switch(&MyCGI, LOWER_STATUS_LINE);	//������״̬��

	cct_setcursor(CURSOR_INVISIBLE);                        //���ù�겻�ɼ�

	init_array(mine, mine_open, rank);

	gmw_draw_frame(&MyCGI);

	for (int i = 0; i < rank_info[rank - 1].row; ++i)
		for (int j = 0; j < rank_info[rank - 1].col; ++j)
			draw_block(&MyCGI, mine[i][j], i, j, 0);


	int MAction, MRow, MCol, KeyCode1, KeyCode2;
	int ret;

	while (1) {
		ret = gmw_read_keyboard_and_mouse(&MyCGI, MAction, MRow, MCol, KeyCode1, KeyCode2);
		if (ret == CCT_MOUSE_EVENT) {
			if (MAction == MOUSE_LEFT_BUTTON_CLICK)
				break;
		}
	}

	end_with_enter();
}

void pf7()
{
	int rank;
	int mine[row_max][col_max];
	int mine_open[row_max][col_max];

	cct_cls();
	game_info_input(rank);

	CONSOLE_GRAPHICS_INFO MyCGI;                            //����һ��CGI����
	gmw_init(&MyCGI);                                       //��һ����ʼ��
	gmw_set_rowcol(&MyCGI, rank_info[rank - 1].row, rank_info[rank - 1].col); //��Ϸ��������
	gmw_set_color(&MyCGI, COLOR_BLACK, COLOR_WHITE);		//�޸Ĵ�����ɫ�������޸���Ϸ��������״̬��
	gmw_set_font(&MyCGI, "������", 16, 0);				    //TrueType���壨�����壩��Ȳ���Ҫ������������
	gmw_set_frame_style(&MyCGI, 4, 2, true);				//ÿ��ɫ��������2��*�߶�2�У�Ҫ�ָ���
	gmw_set_frame_default_linetype(&MyCGI, 1);			    //���ÿ������ΪԤ��ֵ1
	gmw_set_frame_color(&MyCGI, COLOR_HWHITE, COLOR_BLACK); //���ÿ����ɫ
	gmw_set_rowno_switch(&MyCGI, true);					    //��ʾ�к�
	gmw_set_colno_switch(&MyCGI, true);					    //��ʾ�б�
	gmw_set_block_border_switch(&MyCGI, false);			    //����ɫ�鲻��ҪС�߿�
	gmw_set_status_line_switch(&MyCGI, TOP_STATUS_LINE);	//������״̬��
	gmw_set_status_line_switch(&MyCGI, LOWER_STATUS_LINE);	//������״̬��

	cct_setcursor(CURSOR_INVISIBLE);                        //���ù�겻�ɼ�

	gmw_draw_frame(&MyCGI);

	for (int i = 0; i < rank_info[rank - 1].row; ++i)
		for (int j = 0; j < rank_info[rank - 1].col; ++j)
			draw_block(&MyCGI, mine[i][j], i, j, 1);


	int MAction, MRow, MCol, KeyCode1, KeyCode2;
	int ret;

	while (1) {
		ret = gmw_read_keyboard_and_mouse(&MyCGI, MAction, MRow, MCol, KeyCode1, KeyCode2);
		if (ret == CCT_MOUSE_EVENT) {
			if (MAction == MOUSE_LEFT_BUTTON_CLICK)
				break;
		}
	}

	char px, py;
	px = MRow + 'A';
	if (MCol < 9)
		py = MCol + '1';
	else
		py = MCol - 9 + 'a';

	init_array(mine, mine_open, rank, px, py);

	ret = uncover(mine, mine_open, px, py, rank);

	for (int i = 0; i < rank_info[rank - 1].row; ++i)
		for (int j = 0; j < rank_info[rank - 1].col; ++j)
			if(mine_open[i][j])
				draw_block(&MyCGI, mine[i][j], i, j, 0);

	cct_gotoxy(MyCGI.SLI.lower_start_x, MyCGI.SLI.lower_start_y);

	end_with_enter();
}

void pf8()
{
	int rank;
	int mine[row_max][col_max];
	int mine_open[row_max][col_max];
	int mine_sign[row_max][col_max];

	cct_cls();
	game_info_input(rank);

	for (int i = 0; i < rank_info[rank - 1].row; ++i)
		for (int j = 0; j < rank_info[rank - 1].col; ++j)
			mine_sign[i][j] = 0;

	CONSOLE_GRAPHICS_INFO MyCGI;                            //����һ��CGI����
	gmw_init(&MyCGI);                                       //��һ����ʼ��
	gmw_set_rowcol(&MyCGI, rank_info[rank - 1].row, rank_info[rank - 1].col); //��Ϸ��������
	gmw_set_color(&MyCGI, COLOR_BLACK, COLOR_WHITE);		//�޸Ĵ�����ɫ�������޸���Ϸ��������״̬��
	gmw_set_font(&MyCGI, "������", 16, 0);				    //TrueType���壨�����壩��Ȳ���Ҫ������������
	gmw_set_frame_style(&MyCGI, 4, 2, true);				//ÿ��ɫ��������2��*�߶�2�У�Ҫ�ָ���
	gmw_set_frame_default_linetype(&MyCGI, 1);			    //���ÿ������ΪԤ��ֵ1
	gmw_set_frame_color(&MyCGI, COLOR_HWHITE, COLOR_BLACK); //���ÿ����ɫ
	gmw_set_rowno_switch(&MyCGI, true);					    //��ʾ�к�
	gmw_set_colno_switch(&MyCGI, true);					    //��ʾ�б�
	gmw_set_block_border_switch(&MyCGI, false);			    //����ɫ�鲻��ҪС�߿�
	gmw_set_status_line_switch(&MyCGI, TOP_STATUS_LINE);	//������״̬��
	gmw_set_status_line_switch(&MyCGI, LOWER_STATUS_LINE);	//������״̬��

	cct_setcursor(CURSOR_INVISIBLE);                        //���ù�겻�ɼ�

	gmw_draw_frame(&MyCGI);

	for (int i = 0; i < rank_info[rank - 1].row; ++i)
		for (int j = 0; j < rank_info[rank - 1].col; ++j)
			draw_block(&MyCGI, mine[i][j], i, j, 1);

	gmw_status_line(&MyCGI, TOP_STATUS_LINE, "ESC�˳�");

	int MAction, MRow, MCol, KeyCode1, KeyCode2;
	int ret;
	int count = 0;
	int flag_quit = 0;

	while (1) {
		while (1) {
			ret = read_keyboard_and_mouse(&MyCGI, MAction, MRow, MCol, KeyCode1, KeyCode2);
			if (ret == CCT_MOUSE_EVENT) {
				if (MAction == MOUSE_LEFT_BUTTON_CLICK)
					break;
				else if (MAction == MOUSE_RIGHT_BUTTON_CLICK) {
					ret = sign_mine(mine_sign, mine_open, MRow, MCol);
					if (ret) {
						if(mine_sign[MRow][MCol] == 1)
							draw_block(&MyCGI, mine[MRow][MCol], MRow, MCol, 2);
						else
							draw_block(&MyCGI, mine[MRow][MCol], MRow, MCol, 1);
					}
				}
			}
			else {
				if (KeyCode1 == 27) {
					flag_quit = 1;
					break;
				}
			}
		}

		if (flag_quit)
			break;

		char px, py;
		px = MRow + 'A';
		if (MCol < 9)
			py = MCol + '1';
		else
			py = MCol - 9 + 'a';

		if(!count)
			init_array(mine, mine_open, rank, px, py);

		if (!mine_sign[MRow][MCol]) {
			ret = uncover(mine, mine_open, px, py, rank);

			for (int i = 0; i < rank_info[rank - 1].row; ++i)
				for (int j = 0; j < rank_info[rank - 1].col; ++j)
					if (mine_open[i][j])
						draw_block(&MyCGI, mine[i][j], i, j, 0);
		}

		if (ret)
			break;
		if (check_end(mine, mine_open, mine_sign, rank))
			break;

		++count;
	}

	if (ret)
		gmw_status_line(&MyCGI, LOWER_STATUS_LINE, "\n������!��Ϸ����");
	else if(!flag_quit)
		gmw_status_line(&MyCGI, LOWER_STATUS_LINE, "\n��ϲʤ��!��Ϸ����");

	cct_gotoxy(MyCGI.SLI.lower_start_x, MyCGI.SLI.lower_start_y);
	end_with_enter();
}

void pf9()
{
	int rank;
	int mine[row_max][col_max];
	int mine_open[row_max][col_max];
	int mine_sign[row_max][col_max];

	cct_cls();
	game_info_input(rank);

	for (int i = 0; i < rank_info[rank - 1].row; ++i)
		for (int j = 0; j < rank_info[rank - 1].col; ++j)
			mine_sign[i][j] = 0;

	CONSOLE_GRAPHICS_INFO MyCGI;                            //����һ��CGI����
	gmw_init(&MyCGI);                                       //��һ����ʼ��
	gmw_set_rowcol(&MyCGI, rank_info[rank - 1].row, rank_info[rank - 1].col); //��Ϸ��������
	gmw_set_color(&MyCGI, COLOR_BLACK, COLOR_WHITE);		//�޸Ĵ�����ɫ�������޸���Ϸ��������״̬��
	gmw_set_font(&MyCGI, "������", 16, 0);				    //TrueType���壨�����壩��Ȳ���Ҫ������������
	gmw_set_frame_style(&MyCGI, 4, 2, true);				//ÿ��ɫ��������2��*�߶�2�У�Ҫ�ָ���
	gmw_set_frame_default_linetype(&MyCGI, 1);			    //���ÿ������ΪԤ��ֵ1
	gmw_set_frame_color(&MyCGI, COLOR_HWHITE, COLOR_BLACK); //���ÿ����ɫ
	gmw_set_rowno_switch(&MyCGI, true);					    //��ʾ�к�
	gmw_set_colno_switch(&MyCGI, true);					    //��ʾ�б�
	gmw_set_block_border_switch(&MyCGI, false);			    //����ɫ�鲻��ҪС�߿�
	gmw_set_status_line_switch(&MyCGI, TOP_STATUS_LINE);	//������״̬��
	gmw_set_status_line_switch(&MyCGI, LOWER_STATUS_LINE);	//������״̬��

	cct_setcursor(CURSOR_INVISIBLE);                        //���ù�겻�ɼ�

	gmw_draw_frame(&MyCGI);

	for (int i = 0; i < rank_info[rank - 1].row; ++i)
		for (int j = 0; j < rank_info[rank - 1].col; ++j)
			draw_block(&MyCGI, mine[i][j], i, j, 1);

	gmw_status_line(&MyCGI, TOP_STATUS_LINE, "�ȴ���Ϸ��ʼ,ESC�˳�,�ո���ʾʱ��");

	int MAction, MRow, MCol, KeyCode1, KeyCode2;
	int ret;
	int count = 0;
	int flag_quit = 0;

	//��¼ʱ��
	clock_t startTime = 0, endTime = 0;

	int sign_count = 0;

	while (1) {
		while (1) {
			ret = read_keyboard_and_mouse(&MyCGI, MAction, MRow, MCol, KeyCode1, KeyCode2);
			if (ret == CCT_MOUSE_EVENT) {
				if (MAction == MOUSE_LEFT_BUTTON_CLICK)
					break;
				else if (MAction == MOUSE_RIGHT_BUTTON_CLICK) {
					if (count) {
						if (mine_sign[MRow][MCol])
							--sign_count;
						else
							++sign_count;
						if (sign_mine(mine_sign, mine_open, MRow, MCol)) {
							if (mine_sign[MRow][MCol] == 1)
								draw_block(&MyCGI, mine[MRow][MCol], MRow, MCol, 2);
							else
								draw_block(&MyCGI, mine[MRow][MCol], MRow, MCol, 1);
						}
						break;
					}
					else
						continue;
				}
			}
			else {
				if (KeyCode1 == 27) {
					flag_quit = 1;
					break;
				}
				else if (KeyCode1 == ' ') {
					if (count) {
						int curTime = clock();
						char buf[80];
						sprintf_s(buf, "%s%lf%s", "��ǰ��ʱ:", (double)(curTime - startTime) / CLOCKS_PER_SEC, "��, ");
						gmw_status_line(&MyCGI, TOP_STATUS_LINE, "ESC�˳�,�ո���ʾʱ��", buf);
					}
				}
			}
		}

		if (flag_quit)
			break;

		char px, py;
		px = MRow + 'A';
		if (MCol < 9)
			py = MCol + '1';
		else
			py = MCol - 9 + 'a';

		if (!count) {
			init_array(mine, mine_open, rank, px, py);
			//��ʱ��ʼ
			startTime = clock();
		}

		if (MAction != MOUSE_RIGHT_BUTTON_CLICK) {
			ret = uncover(mine, mine_open, px, py, rank);

			for (int i = 0; i < rank_info[rank - 1].row; ++i)
				for (int j = 0; j < rank_info[rank - 1].col; ++j)
					if (mine_open[i][j])
						draw_block(&MyCGI, mine[i][j], i, j, 0);
		}

		if (ret)
			break;
		if (check_end(mine, mine_open, mine_sign, rank))
			break;

		char buf[80];
		sprintf_s(buf, "%s%d%c", "ʣ������:", rank_info[rank - 1].mine_num - sign_count, ',');
		gmw_status_line(&MyCGI, TOP_STATUS_LINE, "ESC�˳�,�ո���ʾʱ��", buf);

		++count;
	}

	endTime = clock();//��ʱ����

	char buf[80];
	sprintf_s(buf, "%s%lf%s", "����ʱ:", (double)(endTime - startTime) / CLOCKS_PER_SEC, "��, ");

	if (ret)
		gmw_status_line(&MyCGI, LOWER_STATUS_LINE, "\n������!��Ϸ����", buf);
	else if (!flag_quit)
		gmw_status_line(&MyCGI, LOWER_STATUS_LINE, "\n��ϲʤ��!��Ϸ����", buf);

	cct_gotoxy(MyCGI.SLI.lower_start_x, MyCGI.SLI.lower_start_y);
	end_with_enter();
}