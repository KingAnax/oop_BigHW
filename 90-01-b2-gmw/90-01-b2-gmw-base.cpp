/* 2151613 ë��¼ �ƿ� */

#include "90-01-b2-gmw.h"

static void confirm_km(const CONSOLE_GRAPHICS_INFO* const MyCGI, bool &flag_sel, int &count, const int mrow, const int mcol, const int row, const int col, int (*num)[col_max], int (*num_sel)[col_max], int &score_total, int &target)
{
	char temp[80];
	if (!flag_sel) {
		count = find_equal(0, num[mrow][mcol], row, col, num, num_sel, mrow, mcol);
		if (count > 1) {
			flag_sel = TRUE;
			for (int i = 0; i < row_max; ++i)
				for (int j = 0; j < col_max; ++j)
					if (num_sel[i][j])
						gmw_draw_block(MyCGI, i, j, num[i][j], bdi_cat);
			gmw_draw_block(MyCGI, mrow, mcol, num[mrow][mcol], bdi_sel);
			sprintf(temp, "��ѡ��%c��%d��", char('A' + mrow), mcol);
			gmw_status_line(MyCGI, LOWER_STATUS_LINE, NULL, NULL);
		}
		else
			gmw_status_line(MyCGI, LOWER_STATUS_LINE, NULL, "��Χ����ͬ��!");
	}
	else {
		flag_sel = FALSE;
		combine(MyCGI, row, col, mrow, mcol, num, num_sel);
		score(MyCGI, count, num[mrow][mcol] - 1, score_total, target);
		fall(MyCGI, num, row, col);
		fill_blank(MyCGI, num, row, col);
		int stage = init_num;
		for (int i = 0; i < row; ++i)
			for (int j = 0; j < col; ++j)
				if (num[i][j] > stage)
					stage = num[i][j];
		if (stage == target && is_end(num, row, col)) {
			sprintf(temp, "%s%d%s", "�Ѵﵽ�ϳ�Ŀ��", target, ",�����Ŀ�����");
			gmw_status_line(MyCGI, LOWER_STATUS_LINE, NULL, temp);
			confirm_enter();
			++target;
		}
	}
}

void pf9()
{
	int num[row_max][col_max] = {};
	int num_sel[row_max][col_max] = {};
	int row, col, target;

	cct_cls();
	init_game_info(row, col, target);                       //���С�Ŀ������

	CONSOLE_GRAPHICS_INFO MyCGI;                            //����һ��CGI����
	gmw_init(&MyCGI);                                       //��һ����ʼ��
	gmw_set_rowcol(&MyCGI, row, col);					    //��Ϸ��������
	gmw_set_color(&MyCGI, COLOR_BLACK, COLOR_WHITE);		//�޸Ĵ�����ɫ�������޸���Ϸ��������״̬��
	gmw_set_font(&MyCGI, "������", 16, 0);				    //TrueType���壨�����壩��Ȳ���Ҫ������������
	gmw_set_frame_style(&MyCGI, 6, 3, true);				//ÿ��ɫ��������6��*�߶�3�У�Ҫ�ָ���
	gmw_set_frame_default_linetype(&MyCGI, 2);			    //���ÿ������ΪԤ��ֵ2��ȫ��Ϊ���ߣ�
	gmw_set_frame_color(&MyCGI, COLOR_HWHITE, COLOR_BLACK); //���ÿ����ɫ
	gmw_set_rowno_switch(&MyCGI, true);					    //��ʾ�к�
	gmw_set_colno_switch(&MyCGI, true);					    //��ʾ�б�
	gmw_set_delay(&MyCGI, DELAY_OF_DRAW_FRAME, 5);		    //���߿����ʱ
	gmw_set_delay(&MyCGI, DELAY_OF_BLOCK_MOVED, 20);		//�ƶ�����ʱ
	gmw_set_block_border_switch(&MyCGI, true);			    //����ɫ����ҪС�߿�
	gmw_set_status_line_switch(&MyCGI, TOP_STATUS_LINE);	//������״̬��
	gmw_set_status_line_switch(&MyCGI, LOWER_STATUS_LINE);	//������״̬��

	cct_setcursor(CURSOR_INVISIBLE);                        //���ù�겻�ɼ�

	init_array(num, row, col);                              //��ʼ������

	int maction, old_mrow = 0, old_mcol = 0, mrow = 0, mcol = 0;
	int keycode1, keycode2;
	int ret;
	bool flag_quit = FALSE;
	bool flag_sel = FALSE;
	bool flag_moved = FALSE;

	cct_cls();

	/* ��ʾ��ʼ���Ŀ�� */
	gmw_draw_frame(&MyCGI);

	//��ɫ��
	for (int i = 0; i < row; ++i)
		for (int j = 0; j < col; ++j)
			gmw_draw_block(&MyCGI, i, j, num[i][j], bdi_normal);

	char temp[80] = {};

	/* ��״̬����ʾ���� */
	sprintf(temp, "��Ļ��ǰ����Ϊ��%d�� %d��", MyCGI.lines, MyCGI.cols);
	gmw_status_line(&MyCGI, TOP_STATUS_LINE, temp);
	/* ��״̬����ʾ���� */
	gmw_status_line(&MyCGI, LOWER_STATUS_LINE, "��ͷ��/����ƶ����س���/�������ѡ��, Q/�����Ҽ�����");

	gmw_draw_block(&MyCGI, mrow, mcol, num[mrow][mcol], bdi_cat);


	//������
	int count = 0;
	int score_total = 0;
	while (1) {
		flag_moved = FALSE;
		old_mrow = mrow;
		old_mcol = mcol;
		ret = read_keyboard_and_mouse(&MyCGI, maction, mrow, mcol, keycode1, keycode2, num, num_sel, row, col);
		if (ret == CCT_MOUSE_EVENT) {
			if (maction == MOUSE_ONLY_MOVED)
				flag_moved = TRUE;
			else if (maction == MOUSE_LEFT_BUTTON_CLICK) {
				confirm_km(&MyCGI, flag_sel, count, mrow, mcol, row, col, num, num_sel, score_total, target);
			}
			else if (maction == MOUSE_RIGHT_BUTTON_CLICK) {
				flag_quit = TRUE;
				break;
			}
		}
		else if (ret == CCT_KEYBOARD_EVENT) {
			switch (keycode1) {
				case 224:
					flag_moved = TRUE;
					break;
				case 'q':
					flag_quit = TRUE;
					break;
				case 'Q':
					flag_quit = TRUE;
					break;
				case '\r':
					confirm_km(&MyCGI, flag_sel, count, mrow, mcol, row, col, num, num_sel, score_total, target);
					break;
			}
		}
		if (is_end(num, row, col)) {
			flag_quit = TRUE;
			gmw_status_line(&MyCGI, LOWER_STATUS_LINE, "��q�˳�", "�޿ɺϲ����Ϸ������");
			confirm_q();
		}
		if (flag_quit)
			break;
		if (flag_moved) {
			gmw_draw_block(&MyCGI, old_mrow, old_mcol, num[old_mrow][old_mcol], bdi_normal);
			gmw_draw_block(&MyCGI, mrow, mcol, num[mrow][mcol], bdi_cat);
			flag_sel = 0;
		}
	}
	cct_setcursor(CURSOR_VISIBLE_NORMAL);
}