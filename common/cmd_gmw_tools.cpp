/* 2151613 ë��¼ �ƿ� */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <climits>
#include <conio.h>
#include <windows.h>
#include "../include/cmd_console_tools.h"
#include "../include/cmd_gmw_tools.h"
using namespace std;

/* --------------------------------------------------
		�˴����Ը�����Ҫ�ľ�̬ȫ�ֱ������������٣����û�У�����̬ȫ��ֻ������/�궨�壨�������ޣ���
   -------------------------------------------------- */


   /* --------------------------------------------------
		   �˴����Ը�����Ҫ���ڲ��������ߺ���
		   1�����������ޣ�����Ϊ gmw_inner_*
		   2����������
		   3��������static������ȷ��ֻ�ڱ�Դ�ļ���ʹ��
	  -------------------------------------------------- */
static int gmw_inner_draw_block_for_move(const CONSOLE_GRAPHICS_INFO* const pCGI, const int BX, const int BY, const int bdi_value_catchy, const BLOCK_DISPLAY_INFO* const bdi)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;

	//ѭ������
	for (int i = 0; (bdi + i)->value != BDI_VALUE_END; i++)
	{
		if (bdi_value_catchy == (bdi + i)->value) {
			//��λ��ɫ�����Ͻ�
			int x = BX;
			int y = BY;
			//ȡ��ɫ
			int bgcolor, fgcolor;
			bgcolor = (bdi + i)->bgcolor < 0 ? pCGI->CFI.bgcolor : (bdi + i)->bgcolor;
			fgcolor = (bdi + i)->fgcolor < 0 ? pCGI->CFI.fgcolor : (bdi + i)->fgcolor;

			if (pCGI->CBI.block_border == false) {  //����Ҫ�߿�
				for (int row = 0; row < pCGI->CFI.block_high; row++) {
					for (int col = 0; col < pCGI->CFI.block_width / 2; col++) {
						if (row == pCGI->CFI.block_high / 2 && col == pCGI->CFI.block_width / 4) {
							if ((bdi + i)->content == NULL) {
								cct_showint(x + col * 2, y + row, (bdi + i)->value, bgcolor, fgcolor);
								if ((bdi + i)->value < 10)
									cct_showch(x + col * 2 + 1, y + row, ' ', bgcolor, fgcolor);
							}
							else
								cct_showstr(x + col * 2, y + row, (bdi + i)->content, bgcolor, fgcolor);
						}
						else
							cct_showstr(x + col * 2, y + row, "  ", bgcolor, fgcolor);
					}
				}
			}
			else {                 //�б߿�
				for (int row = 0; row < pCGI->CFI.block_high; row++) {
					for (int col = 0; col < pCGI->CFI.block_width / 2; col++) {
						if (row == pCGI->CFI.block_high / 2 && col == pCGI->CFI.block_width / 4) {
							if ((bdi + i)->content == NULL) {
								cct_showint(x + col * 2, y + row, (bdi + i)->value, bgcolor, fgcolor);
								if ((bdi + i)->value < 10)
									cct_showch(x + col * 2 + 1, y + row, ' ', bgcolor, fgcolor);
							}
							else
								cct_showstr(x + col * 2, y + row, (bdi + i)->content, bgcolor, fgcolor);
						}
						else if ((bdi + i)->value == BDI_VALUE_BLANK)
							cct_showstr(x + col * 2, y + row, "  ", bgcolor, fgcolor);
						else if (row == 0) {
							if (col == 0)
								cct_showstr(x + col * 2, y + row, pCGI->CBI.top_left, bgcolor, fgcolor);
							else if (col == pCGI->CFI.block_width / 2 - 1)
								cct_showstr(x + col * 2, y + row, pCGI->CBI.top_right, bgcolor, fgcolor);
							else
								cct_showstr(x + col * 2, y + row, pCGI->CBI.h_normal, bgcolor, fgcolor);
						}
						else if (row == pCGI->CFI.block_high - 1) {
							if (col == 0)
								cct_showstr(x + col * 2, y + row, pCGI->CBI.lower_left, bgcolor, fgcolor);
							else if (col == pCGI->CFI.block_width / 2 - 1)
								cct_showstr(x + col * 2, y + row, pCGI->CBI.lower_right, bgcolor, fgcolor);
							else
								cct_showstr(x + col * 2, y + row, pCGI->CBI.h_normal, bgcolor, fgcolor);
						}
						else if (col == 0 || col == pCGI->CFI.block_width / 2 - 1)
							cct_showstr(x + col * 2, y + row, pCGI->CBI.v_normal, bgcolor, fgcolor);
						else
							cct_showstr(x + col * 2, y + row, "  ", bgcolor, fgcolor);
					}
				}
			}
			return 0;
		}
	}

	//������ֵ
	return -1; //�˾�ɸ�����Ҫ�޸�
}

/* -----------------------------------------------
		ʵ����������ĺ���������������׼����
   ----------------------------------------------- */
   /***************************************************************************
	 �������ƣ�
	 ��    �ܣ�������Ϸ����ܵ�������
	 ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
			   const int row						������(������Ϊ0���������ޣ���Ϊ��֤��ȷ��)
			   const int col						������(������Ϊ0���������ޣ���Ϊ��֤��ȷ��)
	 �� �� ֵ��
	 ˵    ����1��ָ��������Ϸ�ľ������������ֵ
			   2�����еı仯�ᵼ��CONSOLE_GRAPHICS_INFO�ṹ����������Աֵ�ı仯��Ҫ����
   ***************************************************************************/
int gmw_set_rowcol(CONSOLE_GRAPHICS_INFO* const pCGI, const int row, const int col)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;

	pCGI->row_num = row;
	pCGI->col_num = col;

	pCGI->lines = pCGI->extern_up_lines + pCGI->extern_down_lines + pCGI->draw_frame_with_col_no + pCGI->top_status_line + pCGI->lower_status_line + pCGI->CFI.bhigh + 4;
	pCGI->cols = pCGI->extern_left_cols + pCGI->extern_right_cols + pCGI->draw_frame_with_row_no * 2 + pCGI->CFI.bwidth + 1;

	pCGI->CFI.bhigh = pCGI->CFI.block_high * pCGI->row_num + pCGI->CFI.separator * (pCGI->row_num - 1) + 2;
	pCGI->CFI.bwidth = pCGI->CFI.block_width * pCGI->col_num + pCGI->CFI.separator * 2 * (pCGI->col_num - 1) + 4;

	pCGI->SLI.lower_start_y = pCGI->start_y + pCGI->CFI.bhigh + pCGI->draw_frame_with_col_no;

	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ������������ڣ�����Ϸ�������������ڵ�����cmd���ڣ�����ɫ
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
		   const int bg_color					��ǰ��ɫ��ȱʡCOLOR_BLACK��
		   const int fg_color					������ɫ��ȱʡCOLOR_WHITE��
		   const bool cascade					���Ƿ�����ȱʡΪtrue-������
  �� �� ֵ��
  ˵    ����1��cascade = trueʱ
				ͬ���޸���Ϸ���������ɫ
				ͬ���޸�����״̬���������ı��ı���ɫ��ǰ��ɫ����Ŀ�ı��ı���ɫ��ǰ��ɫ���䣩
			2���������ɫֵ���󼰳�ͻ����Ҫ��Ϊ��֤
				������ɫ��0-15
					ǰ��ɫ����ɫ��ֵһ�µ����޷���������
					ǰ��ɫ������״̬����Ŀǰ��ɫ�������޷�������Ŀ��ʾ
					...
***************************************************************************/
int gmw_set_color(CONSOLE_GRAPHICS_INFO* const pCGI, const int bgcolor, const int fgcolor, const bool cascade)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;

	pCGI->area_bgcolor = bgcolor;
	pCGI->area_fgcolor = fgcolor;
	cct_setcolor(bgcolor, fgcolor);

	if (cascade)
	{
		//��״̬��
		pCGI->SLI.top_normal_bgcolor = bgcolor;
		pCGI->SLI.top_normal_fgcolor = fgcolor;
		pCGI->SLI.top_catchy_bgcolor = bgcolor;
		//��״̬��
		pCGI->SLI.lower_normal_bgcolor = bgcolor;
		pCGI->SLI.lower_normal_fgcolor = fgcolor;
		pCGI->SLI.lower_catchy_bgcolor = bgcolor;
		//���
		pCGI->CFI.bgcolor = bgcolor;
		pCGI->CFI.fgcolor = fgcolor;
	}

	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ����ô��ڵ�����
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
		   const char *fontname					���������ƣ�ֻ����"Terminal"��"������"���֣������򷵻�-1�����ı����壩
		   const int fs_high					������߶ȣ�ȱʡ������Ϊ16�������������ƣ���Ϊ��֤��
		   const int fs_width					������߶ȣ�ȱʡ������Ϊ8�������������ƣ���Ϊ��֤��
  �� �� ֵ��
  ˵    ����1����cmd_console_tools�е�setfontsize���ƣ�Ŀǰֻ֧�֡��������塱�͡������塱
			2������������������ֱ�ӷ��أ�����ԭ�������ò���
***************************************************************************/
int gmw_set_font(CONSOLE_GRAPHICS_INFO* const pCGI, const char* fontname, const int fs_high, const int fs_width)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;

	int count = 0;
	if (strcmp(fontname, "��������") == 0)
		count++;
	if (strcmp(fontname, "Terminal") == 0)
		count++;
	if (strcmp(fontname, "������") == 0)
		count++;
	if (!count)
		return -1;
	strcpy(pCGI->CFT.font_type, fontname);
	pCGI->CFT.font_size_high = fs_high <= 0 ? 16 : fs_high;
	pCGI->CFT.font_size_width = fs_width <= 0 ? 8 : fs_width;

	cct_setfontsize(pCGI->CFT.font_type, pCGI->CFT.font_size_high, pCGI->CFT.font_size_width);

	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�������ʱ
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
		   const int type						����ʱ�����ͣ�ĿǰΪ3�֣�
		   const int delay_ms					����msΪ��λ����ʱ
			   ���߿����ʱ��0 ~ �������ޣ���Ϊ��֤��ȷ��<0����0��
			   ��ɫ�����ʱ��0 ~ �������ޣ���Ϊ��֤��ȷ��<0����0��
			   ɫ���ƶ�����ʱ��BLOCK_MOVED_DELAY_MS ~ �������ޣ���Ϊ��֤��ȷ�� <BLOCK_MOVED_DELAY_MS ���� BLOCK_MOVED_DELAY_MS��
  �� �� ֵ��
  ˵    ��
***************************************************************************/
int gmw_set_delay(CONSOLE_GRAPHICS_INFO* const pCGI, const int type, const int delay_ms)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;

	if (type == DELAY_OF_DRAW_FRAME)
		pCGI->delay_of_draw_frame = delay_ms < DRAW_FRAME_DELAY_MS ? DRAW_FRAME_DELAY_MS : delay_ms;
	else if (type == DELAY_OF_DRAW_BLOCK)
		pCGI->delay_of_draw_block = delay_ms < DRAW_BLOCK_DELAY_MS ? DRAW_BLOCK_DELAY_MS : delay_ms;
	else if (type == DELAY_OF_BLOCK_MOVED)
		pCGI->delay_of_block_moved = delay_ms < BLOCK_MOVED_DELAY_MS ? BLOCK_MOVED_DELAY_MS : delay_ms;

	return -1; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ���������������Ϸ����ܽṹ֮����Ҫ�����Ķ�������
  ��    �ܣ�CONSOLE_GRAPHICS_INFO *const pCGI	��
		   const int up_lines					���ϲ�������У�ȱʡ������Ϊ0���������ޣ���Ϊ��֤��
		   const int down_lines				���²�������У�ȱʡ������Ϊ0���������ޣ���Ϊ��֤��
		   const int left_cols					����߶�����У�ȱʡ������Ϊ0���������ޣ���Ϊ��֤��
		   const int right_cols				���ұ߶�����У�ȱʡ������Ϊ0���������ޣ���Ϊ��֤��
  �� �� ֵ��
  ˵    �����������еı仯�ᵼ��CONSOLE_GRAPHICS_INFO�ṹ����������Աֵ�ı仯��Ҫ����
***************************************************************************/
int gmw_set_ext_rowcol(CONSOLE_GRAPHICS_INFO* const pCGI, const int up_lines, const int down_lines, const int left_cols, const int right_cols)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;

	pCGI->extern_up_lines = up_lines;
	pCGI->extern_down_lines = down_lines;
	pCGI->extern_left_cols = left_cols;
	pCGI->extern_right_cols = right_cols;

	pCGI->start_x = pCGI->extern_left_cols;
	pCGI->start_y = pCGI->extern_up_lines + pCGI->top_status_line;

	pCGI->lines = pCGI->extern_up_lines + pCGI->extern_down_lines + pCGI->draw_frame_with_col_no + pCGI->top_status_line + pCGI->lower_status_line + pCGI->CFI.bhigh + 4;
	pCGI->cols = pCGI->extern_left_cols + pCGI->extern_right_cols + pCGI->draw_frame_with_row_no * 2 + pCGI->CFI.bwidth + 1;

	pCGI->CFI.bhigh = pCGI->CFI.block_high * pCGI->row_num + pCGI->CFI.separator * (pCGI->row_num - 1) + 2;
	pCGI->CFI.bwidth = pCGI->CFI.block_width * pCGI->col_num + pCGI->CFI.separator * 2 * (pCGI->col_num - 1) + 4;

	pCGI->SLI.lower_start_x = pCGI->start_x;
	pCGI->SLI.lower_start_y = pCGI->start_y + pCGI->CFI.bhigh + pCGI->draw_frame_with_col_no;

	pCGI->SLI.top_start_x = pCGI->start_x;
	pCGI->SLI.top_start_y = pCGI->start_y - 1;

	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���� CONSOLE_FRAME_TYPE �ṹ�е�11�����ͣ�ȱʡ4�֣�
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
			const int type						��1 - ȫ�� 2 - ȫ���� 3 - ��˫���� 4 - �ᵥ��˫
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int gmw_set_frame_default_linetype(CONSOLE_GRAPHICS_INFO* const pCGI, const int type)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;

	if (type == 1)
	{
		strcpy(pCGI->CFI.top_left, "�X");
		strcpy(pCGI->CFI.lower_left, "�^");
		strcpy(pCGI->CFI.top_right, "�[");
		strcpy(pCGI->CFI.lower_right, "�a");
		strcpy(pCGI->CFI.h_normal, "�T");
		strcpy(pCGI->CFI.v_normal, "�U");
		strcpy(pCGI->CFI.h_top_separator, "�j");
		strcpy(pCGI->CFI.h_lower_separator, "�m");
		strcpy(pCGI->CFI.v_left_separator, "�d");
		strcpy(pCGI->CFI.v_right_separator, "�g");
		strcpy(pCGI->CFI.mid_separator, "�p");
	}
	else if (type == 2)
	{
		strcpy(pCGI->CFI.top_left, "��");
		strcpy(pCGI->CFI.lower_left, "��");
		strcpy(pCGI->CFI.top_right, "��");
		strcpy(pCGI->CFI.lower_right, "��");
		strcpy(pCGI->CFI.h_normal, "��");
		strcpy(pCGI->CFI.v_normal, "��");
		strcpy(pCGI->CFI.h_top_separator, "��");
		strcpy(pCGI->CFI.h_lower_separator, "��");
		strcpy(pCGI->CFI.v_left_separator, "��");
		strcpy(pCGI->CFI.v_right_separator, "��");
		strcpy(pCGI->CFI.mid_separator, "��");
	}
	else if (type == 3)
	{
		strcpy(pCGI->CFI.top_left, "�V");
		strcpy(pCGI->CFI.lower_left, "�\");
		strcpy(pCGI->CFI.top_right, "�Y");
		strcpy(pCGI->CFI.lower_right, "�_");
		strcpy(pCGI->CFI.h_normal, "�T");
		strcpy(pCGI->CFI.v_normal, "��");
		strcpy(pCGI->CFI.h_top_separator, "�h");
		strcpy(pCGI->CFI.h_lower_separator, "�k");
		strcpy(pCGI->CFI.v_left_separator, "�b");
		strcpy(pCGI->CFI.v_right_separator, "�e");
		strcpy(pCGI->CFI.mid_separator, "�n");
	}
	else if (type == 4)
	{
		strcpy(pCGI->CFI.top_left, "�W");
		strcpy(pCGI->CFI.lower_left, "�]");
		strcpy(pCGI->CFI.top_right, "�Z");
		strcpy(pCGI->CFI.lower_right, "�`");
		strcpy(pCGI->CFI.h_normal, "��");
		strcpy(pCGI->CFI.v_normal, "�U");
		strcpy(pCGI->CFI.h_top_separator, "�i");
		strcpy(pCGI->CFI.h_lower_separator, "�l");
		strcpy(pCGI->CFI.v_left_separator, "�c");
		strcpy(pCGI->CFI.v_right_separator, "�f");
		strcpy(pCGI->CFI.mid_separator, "�o");
	}
	else
		return -1;

	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���� CONSOLE_FRAME_TYPE �ṹ�е�11������
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
			const char *...						����11�֣������.h���˴���
  �� �� ֵ��
  ˵    ����Լ��Ϊһ�������Ʊ��������ʹ���������ݣ���Ϊ��֤2�ֽ�
			1������2�ֽ���ֻȡǰ2�ֽ�
			2�������NULL���������ո����
			3�������1�ֽڣ���һ���ո������˶�������ʾ�ң������
***************************************************************************/
int gmw_set_frame_linetype(CONSOLE_GRAPHICS_INFO* const pCGI, const char* top_left, const char* lower_left, const char* top_right,
	const char* lower_right, const char* h_normal, const char* v_normal, const char* h_top_separator,
	const char* h_lower_separator, const char* v_left_separator, const char* v_right_separator, const char* mid_separator)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;

	if (top_left != NULL) {
		strcpy_s(pCGI->CFI.top_left, top_left);
		if (strlen(top_left) == 1)
			*(pCGI->CFI.top_left + 1) = ' ';
	}
	else
		strcpy(pCGI->CFI.top_left, "  ");

	if (lower_left != NULL) {
		strcpy_s(pCGI->CFI.lower_left, lower_left);
		if (strlen(top_left) == 1)
			*(pCGI->CFI.lower_left + 1) = ' ';
	}
	else
		strcpy(pCGI->CFI.lower_left, "  ");

	if (top_right != NULL) {
		strcpy_s(pCGI->CFI.top_right, top_right);
		if (strlen(top_right) == 1)
			*(pCGI->CFI.lower_right + 1) = ' ';
	}
	else
		strcpy(pCGI->CFI.top_right, "  ");

	if (lower_right != NULL) {
		strcpy_s(pCGI->CFI.lower_right, lower_right);
		if (strlen(lower_right) == 1)
			*(pCGI->CFI.lower_right + 1) = ' ';
	}
	else
		strcpy(pCGI->CFI.lower_right, "  ");

	if (h_normal != NULL) {
		strcpy_s(pCGI->CFI.h_normal, h_normal);
		if (strlen(h_normal) == 1)
			*(pCGI->CFI.h_normal + 1) = ' ';
	}
	else
		strcpy(pCGI->CFI.h_normal, "  ");

	if (v_normal != NULL) {
		strcpy_s(pCGI->CFI.v_normal, v_normal);
		if (strlen(v_normal) == 1)
			*(pCGI->CFI.v_normal + 1) = ' ';
	}
	else
		strcpy(pCGI->CFI.v_normal, "  ");

	if (h_top_separator != NULL) {
		strcpy_s(pCGI->CFI.h_top_separator, h_top_separator);
		if (strlen(h_top_separator) == 1)
			*(pCGI->CFI.h_top_separator + 1) = ' ';
	}
	else
		strcpy(pCGI->CFI.h_top_separator, "  ");

	if (h_lower_separator != NULL) {
		strcpy_s(pCGI->CFI.h_lower_separator, h_lower_separator);
		if (strlen(h_lower_separator) == 1)
			*(pCGI->CFI.h_lower_separator + 1) = ' ';
	}
	else
		strcpy(pCGI->CFI.h_lower_separator, "  ");

	if (v_left_separator != NULL) {
		strcpy_s(pCGI->CFI.v_left_separator, v_left_separator);
		if (strlen(v_left_separator) == 1)
			*(pCGI->CFI.v_left_separator + 1) = ' ';
	}
	else
		strcpy(pCGI->CFI.v_left_separator, "  ");

	if (v_right_separator != NULL) {
		strcpy_s(pCGI->CFI.v_right_separator, v_right_separator);
		if (strlen(v_right_separator) == 1)
			*(pCGI->CFI.v_right_separator + 1) = ' ';
	}
	else
		strcpy(pCGI->CFI.v_right_separator, "  ");

	if (mid_separator != NULL) {
		strcpy_s(pCGI->CFI.mid_separator, mid_separator);
		if (strlen(mid_separator) == 1)
			*(pCGI->CFI.mid_separator + 1) = ' ';
	}
	else
		strcpy(pCGI->CFI.mid_separator, "  ");
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���� CONSOLE_FRAME_TYPE �ṹ�е�ɫ��������С���Ƿ���Ҫ�ָ��ߵ�
  ������������������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
			const int block_width						����ȣ�����ȱʡ2����ΪԼ�������Ϊ�����Ʊ�����������������Ҫ+1��
			const int block_high						���߶ȣ�����ȱʡ1��
			const bool separator						���Ƿ���Ҫ�ָ��ߣ�ȱʡΪtrue����Ҫ�ָ��ߣ�
  �� �� ֵ��
  ˵    ������ܴ�С/�Ƿ���Ҫ�ָ��ߵȵı仯�ᵼ��CONSOLE_GRAPHICS_INFO�ṹ����������Աֵ�ı仯��Ҫ����
***************************************************************************/
int gmw_set_frame_style(CONSOLE_GRAPHICS_INFO* const pCGI, const int block_width, const int block_high, const bool separator)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;

	pCGI->CFI.separator = separator;

	if (block_width % 2 == 1)
		pCGI->CFI.block_width = block_width + 1;
	else if (block_width <= 0)
		pCGI->CFI.block_width = 2;
	else
		pCGI->CFI.block_width = block_width;
	pCGI->CFI.block_high = block_high <= 0 ? 1 : block_high;

	pCGI->CFI.bhigh = pCGI->CFI.block_high * pCGI->row_num + pCGI->CFI.separator * (pCGI->row_num - 1) + 2;
	pCGI->CFI.bwidth = pCGI->CFI.block_width * pCGI->col_num + pCGI->CFI.separator * 2 * (pCGI->col_num - 1) + 4;

	pCGI->lines = pCGI->extern_up_lines + pCGI->extern_down_lines + pCGI->draw_frame_with_col_no + pCGI->top_status_line + pCGI->lower_status_line + pCGI->CFI.bhigh + 4;
	pCGI->cols = pCGI->extern_left_cols + pCGI->extern_right_cols + pCGI->draw_frame_with_row_no * 2 + pCGI->CFI.bwidth + 1;

	pCGI->SLI.lower_start_y = pCGI->start_y + pCGI->CFI.bhigh + pCGI->draw_frame_with_col_no;

	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���� CONSOLE_BORDER_TYPE �ṹ�е���ɫ
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
			const int bg_color					������ɫ��ȱʡ -1��ʾ�ô��ڱ���ɫ��
			const int fg_color					��ǰ��ɫ��ȱʡ -1��ʾ�ô���ǰ��ɫ��
  �� �� ֵ��
  ˵    �����������ɫֵ���󼰳�ͻ����Ҫ��Ϊ��֤
				������ɫ��0-15��ǰ��ɫ����ɫ��ֵһ�µ����޷��������ݵ�
***************************************************************************/
int gmw_set_frame_color(CONSOLE_GRAPHICS_INFO* const pCGI, const int bgcolor, const int fgcolor)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;

	pCGI->CFI.bgcolor = bgcolor < 0 ? pCGI->area_bgcolor : bgcolor;
	pCGI->CFI.fgcolor = fgcolor < 0 ? pCGI->area_fgcolor : fgcolor;

	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���� CONSOLE_BLOCK_INFO �ṹ�е�6�����ͣ�ȱʡ4�֣�
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
			const int type						��1 - ȫ˫�� 2 - ȫ���� 3 - ��˫���� 4 - �ᵥ��˫
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int gmw_set_block_default_linetype(CONSOLE_GRAPHICS_INFO* const pCGI, const int type)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;

	if (type == 1)
	{
		strcpy(pCGI->CBI.top_left, "�X");
		strcpy(pCGI->CBI.lower_left, "�^");
		strcpy(pCGI->CBI.top_right, "�[");
		strcpy(pCGI->CBI.lower_right, "�a");
		strcpy(pCGI->CBI.h_normal, "�T");
		strcpy(pCGI->CBI.v_normal, "�U");
	}
	else if (type == 2)
	{
		strcpy(pCGI->CBI.top_left, "��");
		strcpy(pCGI->CBI.lower_left, "��");
		strcpy(pCGI->CBI.top_right, "��");
		strcpy(pCGI->CBI.lower_right, "��");
		strcpy(pCGI->CBI.h_normal, "��");
		strcpy(pCGI->CBI.v_normal, "��");
	}
	else if (type == 3)
	{
		strcpy(pCGI->CBI.top_left, "�V");
		strcpy(pCGI->CBI.lower_left, "�\");
		strcpy(pCGI->CBI.top_right, "�Y");
		strcpy(pCGI->CBI.lower_right, "�_");
		strcpy(pCGI->CBI.h_normal, "�T");
		strcpy(pCGI->CBI.v_normal, "��");
	}
	else if (type == 4)
	{
		strcpy(pCGI->CBI.top_left, "�W");
		strcpy(pCGI->CBI.lower_left, "�]");
		strcpy(pCGI->CBI.top_right, "�Z");
		strcpy(pCGI->CBI.lower_right, "�`");
		strcpy(pCGI->CBI.h_normal, "��");
		strcpy(pCGI->CBI.v_normal, "�U");
	}
	else
		return -1;

	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���� CONSOLE_BLOCK_INFO �ṹ�е�6������
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
		   const char *...					����6�֣������.h���˴���
  �� �� ֵ��
  ˵    ����Լ��Ϊһ�������Ʊ��������ʹ���������ݣ���Ϊ��֤2�ֽ�
			1������2�ֽ���ֻȡǰ2�ֽ�
			2�������NULL���������ո����
			3�������1�ֽڣ���һ���ո������˶�������ʾ�ң������
***************************************************************************/
int gmw_set_block_linetype(CONSOLE_GRAPHICS_INFO* const pCGI, const char* top_left, const char* lower_left, const char* top_right, const char* lower_right, const char* h_normal, const char* v_normal)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;

	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�����ÿ����Ϸɫ��(����)�Ƿ���ҪС�߿�
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
		   const bool on_off					��true - ��Ҫ flase - ����Ҫ��ȱʡfalse��
  �� �� ֵ��
  ˵    �����߿�Լ��Ϊ�����Ʊ����˫��
***************************************************************************/
int gmw_set_block_border_switch(CONSOLE_GRAPHICS_INFO* const pCGI, const bool on_off)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;

	pCGI->CBI.block_border = on_off;

	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ������Ƿ���ʾ����״̬��
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
			const int type						��״̬�����ͣ���/�£�
			const bool on_off					��true - ��Ҫ flase - ����Ҫ��ȱʡtrue��
  �� �� ֵ��
  ˵    ����1��״̬�������Լ�����£�
			   1.1����״̬��ֻ��һ�У������������Ϸ�����/�б�����棬Ϊ��������ʼһ�У�����������Ͻ����������״̬�������꣩
			   1.2����״̬��ֻ��һ�У������������·����ߵ�����
			   1.3��״̬���Ŀ��Ϊ�������ȣ������Ϣ������ض�
		   2�����еı仯�ᵼ��CONSOLE_GRAPHICS_INFO�ṹ����������Աֵ�ı仯��Ҫ����
***************************************************************************/
int gmw_set_status_line_switch(CONSOLE_GRAPHICS_INFO* const pCGI, const int type, const bool on_off)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;

	if (type == TOP_STATUS_LINE) {
		pCGI->top_status_line = on_off;
		pCGI->SLI.is_top_status_line = on_off;

		pCGI->start_y = pCGI->extern_up_lines + pCGI->top_status_line;

		pCGI->SLI.top_start_x = pCGI->start_x;
		pCGI->SLI.top_start_y = pCGI->start_y - 1;

		pCGI->SLI.lower_start_x = pCGI->start_x;
		pCGI->SLI.lower_start_y = pCGI->start_y + pCGI->CFI.bhigh + pCGI->draw_frame_with_col_no;

		pCGI->lines = pCGI->extern_up_lines + pCGI->extern_down_lines + pCGI->draw_frame_with_col_no + pCGI->top_status_line + pCGI->lower_status_line + pCGI->CFI.bhigh + 4;
	}
	else if (type == LOWER_STATUS_LINE) {
		pCGI->lower_status_line = on_off;
		pCGI->SLI.is_lower_status_line = on_off;
	}
	else
		return -1;

	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���������״̬������ɫ
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
			const int type						��״̬�����ͣ���/�£�
			const int normal_bgcolor			�������ı�����ɫ��ȱʡ -1��ʾʹ�ô��ڱ���ɫ��
			const int normal_fgcolor			�������ı�ǰ��ɫ��ȱʡ -1��ʾʹ�ô���ǰ��ɫ��
			const int catchy_bgcolor			����Ŀ�ı�����ɫ��ȱʡ -1��ʾʹ�ô��ڱ���ɫ��
			const int catchy_fgcolor			����Ŀ�ı�ǰ��ɫ��ȱʡ -1��ʾʹ������ɫ��
  ���������
  �� �� ֵ��
  ˵    �����������ɫֵ���󼰳�ͻ����Ҫ��Ϊ��֤
				������ɫ��0-15��ǰ��ɫ����ɫ��ֵһ�µ����޷��������ݵ�
***************************************************************************/
int gmw_set_status_line_color(CONSOLE_GRAPHICS_INFO* const pCGI, const int type, const int normal_bgcolor, const int normal_fgcolor, const int catchy_bgcolor, const int catchy_fgcolor)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;

	if (type == TOP_STATUS_LINE) {
		pCGI->SLI.top_normal_bgcolor = normal_bgcolor < 0 ? pCGI->area_bgcolor : normal_bgcolor;
		pCGI->SLI.top_catchy_bgcolor = catchy_bgcolor < 0 ? pCGI->area_bgcolor : catchy_bgcolor;
		pCGI->SLI.top_normal_fgcolor = normal_fgcolor < 0 ? pCGI->area_fgcolor : normal_fgcolor;
		pCGI->SLI.top_catchy_fgcolor = catchy_fgcolor < 0 ? 14 : catchy_fgcolor;
	}
	else if (type == LOWER_STATUS_LINE) {
		pCGI->SLI.lower_normal_bgcolor = normal_bgcolor < 0 ? pCGI->area_bgcolor : normal_bgcolor;
		pCGI->SLI.lower_catchy_bgcolor = catchy_bgcolor < 0 ? pCGI->area_bgcolor : catchy_bgcolor;
		pCGI->SLI.lower_normal_fgcolor = normal_fgcolor < 0 ? pCGI->area_fgcolor : normal_fgcolor;
		pCGI->SLI.lower_catchy_fgcolor = catchy_fgcolor < 0 ? 14 : catchy_fgcolor;
	}
	else
		return -1;

	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ������Ƿ���ʾ�к�
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
			const bool on_off					��true - ��ʾ flase - ����ʾ��ȱʡfalse��
  �� �� ֵ��
  ˵    ����1���к�Լ��Ϊ��ĸA��ʼ�������У��������26�����a��ʼ������52��ͳһΪ*��ʵ��Ӧ�ò����ܣ�
			2���Ƿ���ʾ�кŵı仯�ᵼ��CONSOLE_GRAPHICS_INFO�ṹ����������Աֵ�ı仯��Ҫ����
***************************************************************************/
int gmw_set_rowno_switch(CONSOLE_GRAPHICS_INFO* const pCGI, const bool on_off)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;

	pCGI->draw_frame_with_row_no = on_off;

	pCGI->lines = pCGI->extern_up_lines + pCGI->extern_down_lines + pCGI->draw_frame_with_col_no + pCGI->top_status_line + pCGI->lower_status_line + pCGI->CFI.bhigh + 4;
	pCGI->cols = pCGI->extern_left_cols + pCGI->extern_right_cols + pCGI->draw_frame_with_row_no * 2 + pCGI->CFI.bwidth + 1;
	pCGI->SLI.lower_start_y = pCGI->start_y + pCGI->CFI.bhigh + pCGI->draw_frame_with_col_no;

	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ������Ƿ���ʾ�б�
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
			const bool on_off					��true - ��ʾ flase - ����ʾ��ȱʡfalse��
  �� �� ֵ��
  ˵    ����1���б�Լ��Ϊ����0��ʼ�������У�����0-99������99ͳһΪ**��ʵ��Ӧ�ò����ܣ�
			2���Ƿ���ʾ�б�ı仯�ᵼ��CONSOLE_GRAPHICS_INFO�ṹ����������Աֵ�ı仯��Ҫ����
***************************************************************************/
int gmw_set_colno_switch(CONSOLE_GRAPHICS_INFO* const pCGI, const bool on_off)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;

	pCGI->draw_frame_with_col_no = on_off;

	pCGI->lines = pCGI->extern_up_lines + pCGI->extern_down_lines + pCGI->draw_frame_with_col_no + pCGI->top_status_line + pCGI->lower_status_line + pCGI->CFI.bhigh + 4;
	pCGI->cols = pCGI->extern_left_cols + pCGI->extern_right_cols + pCGI->draw_frame_with_row_no * 2 + pCGI->CFI.bwidth + 1;
	pCGI->SLI.lower_start_y = pCGI->start_y + pCGI->CFI.bhigh + pCGI->draw_frame_with_col_no;

	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���ӡ CONSOLE_GRAPHICS_INFO �ṹ���еĸ���Աֵ
  ���������
  �� �� ֵ��
  ˵    ����1�����������ã���ӡ��ʽ�Զ���
			2������������������δ���ù������Բ�ʵ��
***************************************************************************/
int gmw_print(const CONSOLE_GRAPHICS_INFO* const pCGI)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;

	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ��� CONSOLE_GRAPHICS_INFO �ṹ����ȱʡֵ���г�ʼ��
  ���������CONSOLE_GRAPHICS_INFO *const pCGI������ṹָ��
		   const int row					����Ϸ����ɫ��������ȱʡ10��
		   const int col					����Ϸ����ɫ��������ȱʡ10��
		   const int bgcolor				���������ڱ���ɫ��ȱʡ COLOR_BLACK��
		   const int fgcolor				���������ڱ���ɫ��ȱʡ COLOR_WHITE��
  �� �� ֵ��
  ˵    �������ڱ�����/ǰ���ף�����16*8�����������޶������У�����״̬�����У����к�/�б꣬�������Ϊ˫�ߣ�ɫ����2/�߶�1/��С�߿���ɫ��
***************************************************************************/
int gmw_init(CONSOLE_GRAPHICS_INFO* const pCGI, const int row, const int col, const int bgcolor, const int fgcolor)
{
	/* �����ñ�� */
	pCGI->inited = CGI_INITED;
	//��������
	pCGI->extern_down_lines = 0;
	pCGI->extern_left_cols = 0;
	pCGI->extern_right_cols = 0;
	pCGI->extern_up_lines = 0;
	//�кš��б�
	pCGI->draw_frame_with_col_no = false;
	pCGI->draw_frame_with_row_no = false;
	//��ܵ�������
	pCGI->row_num = row;
	pCGI->col_num = col;
	//ɫ��
	pCGI->CFI.separator = true;
	pCGI->CFI.block_high = 1;
	pCGI->CFI.block_width = 2;
	pCGI->CBI.block_border = false;
	pCGI->CFI.bhigh = pCGI->CFI.block_high * pCGI->row_num + pCGI->CFI.separator * (pCGI->row_num - 1) + 2;
	pCGI->CFI.bwidth = pCGI->CFI.block_width * pCGI->col_num + pCGI->CFI.separator * 2 * (pCGI->col_num - 1) + 4;
	//ɫ�����
	strcpy(pCGI->CBI.lower_right, "�a");
	strcpy(pCGI->CBI.lower_left, "�^");
	strcpy(pCGI->CBI.top_left, "�X");
	strcpy(pCGI->CBI.top_right, "�[");
	strcpy(pCGI->CBI.h_normal, "�T");
	strcpy(pCGI->CBI.v_normal, "�U");
	//ǰ���ͱ���ɫ
	pCGI->area_bgcolor = bgcolor;
	pCGI->area_fgcolor = fgcolor;
	cct_setcolor(bgcolor, fgcolor);
	//��ʱ
	pCGI->delay_of_draw_frame = DRAW_FRAME_DELAY_MS;
	pCGI->delay_of_draw_block = DRAW_BLOCK_DELAY_MS;
	pCGI->delay_of_block_moved = BLOCK_MOVED_DELAY_MS;
	//��ܽṹ
	pCGI->CFI.bgcolor = bgcolor;
	pCGI->CFI.fgcolor = fgcolor;
	strcpy(pCGI->CFI.top_left, "�X");
	strcpy(pCGI->CFI.lower_left, "�^");
	strcpy(pCGI->CFI.top_right, "�[");
	strcpy(pCGI->CFI.lower_right, "�a");
	strcpy(pCGI->CFI.h_normal, "�T");
	strcpy(pCGI->CFI.v_normal, "�U");
	strcpy(pCGI->CFI.h_top_separator, "�j");
	strcpy(pCGI->CFI.h_lower_separator, "�m");
	strcpy(pCGI->CFI.v_left_separator, "�d");
	strcpy(pCGI->CFI.v_right_separator, "�g");
	strcpy(pCGI->CFI.mid_separator, "�p");
	//������ֺ�
	strcpy(pCGI->CFT.font_type, "��������");
	pCGI->CFT.font_size_high = 16;
	pCGI->CFT.font_size_width = 8;
	cct_setfontsize("��������", 16, 8);
	//��״̬��
	pCGI->top_status_line = true;
	pCGI->SLI.is_top_status_line = true;

	pCGI->start_x = pCGI->extern_left_cols;
	pCGI->start_y = pCGI->extern_up_lines + pCGI->top_status_line;

	pCGI->SLI.top_start_x = pCGI->start_x;
	pCGI->SLI.top_start_y = pCGI->start_y - 1;
	pCGI->SLI.top_normal_bgcolor = bgcolor;
	pCGI->SLI.top_normal_fgcolor = fgcolor;
	pCGI->SLI.top_catchy_bgcolor = bgcolor;
	pCGI->SLI.top_catchy_fgcolor = 14;
	//��״̬��
	pCGI->lower_status_line = true;
	pCGI->SLI.is_lower_status_line = true;

	pCGI->SLI.lower_start_x = pCGI->start_x;
	pCGI->SLI.lower_start_y = pCGI->start_y + pCGI->CFI.bhigh + pCGI->draw_frame_with_col_no;

	pCGI->SLI.lower_normal_bgcolor = bgcolor;
	pCGI->SLI.lower_normal_fgcolor = fgcolor;
	pCGI->SLI.lower_catchy_bgcolor = bgcolor;
	pCGI->SLI.lower_catchy_fgcolor = 14;
	//��������ֵ
	pCGI->lines = pCGI->extern_up_lines + pCGI->extern_down_lines + pCGI->draw_frame_with_col_no + pCGI->top_status_line + pCGI->lower_status_line + pCGI->CFI.bhigh + 4;
	pCGI->cols = pCGI->extern_left_cols + pCGI->extern_right_cols + pCGI->draw_frame_with_row_no * 2 + pCGI->CFI.bwidth + 1;
	cct_setconsoleborder(pCGI->cols, pCGI->lines);
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�������Ϸ���
  ���������const CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
  �� �� ֵ��
  ˵    ��������ɲο�demo��Ч��
***************************************************************************/
int gmw_draw_frame(const CONSOLE_GRAPHICS_INFO* const pCGI)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;

	cct_setconsoleborder(pCGI->cols, pCGI->lines);

	int x = 0, y = 0;
	x = pCGI->start_x;
	y = pCGI->start_y;

	//���б껭�б�
	if (pCGI->draw_frame_with_col_no)
	{
		x += pCGI->draw_frame_with_row_no * 2 + 1 + pCGI->CFI.block_width / 2;
		for (int i = 0; i < pCGI->col_num; i++)
		{
			if (i <= 99)
				cct_showint(x, y, i, pCGI->area_bgcolor, pCGI->area_fgcolor);
			else
				cct_showstr(x, y, "**", pCGI->area_bgcolor, pCGI->area_fgcolor);
			x += pCGI->CFI.block_width + pCGI->CFI.separator * 2;
		}
		x = pCGI->start_x;
		y++;
	}

	//�����
	for (int row = 0; row < pCGI->row_num; row++) {
		x = pCGI->start_x + pCGI->draw_frame_with_row_no * 2;
		for (int col = 0; col < pCGI->col_num; col++) {
			if (col == 0) {
				if (row == 0) {
					cct_showstr(x, y, pCGI->CFI.top_left, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);
					x += 2;
				}
				else {
					if (pCGI->CFI.separator) {
						cct_showstr(x, y, pCGI->CFI.v_left_separator, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);
						x += 2;
					}
				}
			}
			else {
				if (pCGI->CFI.separator) {
					if (row == 0) {
						cct_showstr(x, y, pCGI->CFI.h_top_separator, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);
						x += 2;
					}
					else {
						cct_showstr(x, y, pCGI->CFI.mid_separator, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);
						x += 2;
					}
				}
			}
			//��ɫ���ȵĺ���
			for (int i = 0; i < pCGI->CFI.block_width / 2; i++)
			{
				if (row == 0 || pCGI->CFI.separator)
					cct_showstr(x, y, pCGI->CFI.h_normal, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);
				x += 2;
			}
			if (pCGI->CFI.separator)
				Sleep(pCGI->delay_of_draw_frame);
		}
		//�����һ��
		if (row == 0)
			cct_showstr(x, y, pCGI->CFI.top_right, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);
		else {
			if (pCGI->CFI.separator)
				cct_showstr(x, y, pCGI->CFI.v_right_separator, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);
		}
		//��ɫ��߶ȵ�����
		if (pCGI->CFI.separator || row == 0)
			y++;
		for (int i = 0; i < pCGI->CFI.block_high; i++) {
			if (i)
				y++;
			x = pCGI->start_x;
			//���б꣬����еĻ�
			int h = (pCGI->CFI.block_high + 1) / 2 - 1;
			if (h < 0)
				h = 0;
			if (i == h && pCGI->draw_frame_with_row_no)
			{
				if (row < 26)
					cct_showch(x, y, row + 'A', pCGI->area_bgcolor, pCGI->area_fgcolor);
				else if (row < 52)
					cct_showch(x, y, row - 26 + 'a', pCGI->area_bgcolor, pCGI->area_fgcolor);
				else
					cct_showch(x, y, '*', pCGI->area_bgcolor, pCGI->area_fgcolor);
			}
			//ɫ���ܺ�����
			x += pCGI->draw_frame_with_row_no * 2;
			for (int col = 0; col < pCGI->col_num; col++) {
				if (col == 0 || pCGI->CFI.separator) {
					cct_showstr(x, y, pCGI->CFI.v_normal, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);
					x += 2;
				}
				for (int i = 0; i < pCGI->CFI.block_width / 2; i++) {
					cct_showstr(x, y, "  ", pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);
					x += 2;
				}
				Sleep(pCGI->delay_of_draw_frame);
			}
			cct_showstr(x, y, pCGI->CFI.v_normal, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);
		}
		y++;
	}

	//�����һ��
	x = pCGI->start_x + pCGI->draw_frame_with_row_no * 2;
	y = pCGI->start_y + pCGI->CFI.bhigh - 1 + pCGI->draw_frame_with_col_no;
	for (int col = 0; col < pCGI->col_num; col++) {
		if (col == 0) {
			cct_showstr(x, y, pCGI->CFI.lower_left, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);
			x += 2;
		}
		else {
			if (pCGI->CFI.separator) {
				cct_showstr(x, y, pCGI->CFI.h_lower_separator, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);
				x += 2;
			}
		}
		for (int i = 0; i < pCGI->CFI.block_width / 2; i++)
		{
			cct_showstr(x, y, pCGI->CFI.h_normal, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);
			x += 2;
		}
		Sleep(pCGI->delay_of_draw_frame);
	}
	cct_showstr(x, y, pCGI->CFI.lower_right, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);

	cct_setcolor();

	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���״̬������ʾ��Ϣ
  ���������const CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
		   const int type							��ָ������/��״̬��
		   const char *msg						��������Ϣ
		   const char *catchy_msg					����Ҫ�ر��ע����Ϣ����������Ϣǰ��ʾ��
  �� �� ֵ��
  ˵    ����1���������޶�Ϊ����ܵĿ�ȣ����к��б�λ�ã����������ȥ
			2��������һ���ַ���ĳ���ֵ�ǰ������ᵼ�º������룬Ҫ����
***************************************************************************/
int gmw_status_line(const CONSOLE_GRAPHICS_INFO* const pCGI, const int type, const char* msg, const char* catchy_msg)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;

	int x, y;
	int value_catchy = 0, value_normal = 0;
	int len_catchy = 0, len_normal = 0;

	//��ȡ��Ϣ����
	if (catchy_msg == NULL)
		value_catchy = 0;
	else
		value_catchy = strlen(catchy_msg);
	if (msg == NULL)
		value_normal = 0;
	else
		value_normal = strlen(msg);

	if (value_catchy) {
		//��ֵ��̵�
		len_catchy = pCGI->CFI.bwidth + pCGI->draw_frame_with_row_no * 2 > value_catchy ? value_catchy : pCGI->CFI.bwidth + pCGI->draw_frame_with_row_no * 2;
		//��������ַ�
		int count = 0;
		for (int i = 0; i < len_catchy; i++) {
			if (*(catchy_msg + i) < 0)
				count++;
		}
		if (count % 2 == 1 && *(catchy_msg + len_catchy - 1) > 127)
			len_catchy--;
	}

	if (value_normal) {
		//��ֵ��̵�
		len_normal = pCGI->CFI.bwidth + pCGI->draw_frame_with_row_no * 2 - value_catchy > value_normal ? value_normal : pCGI->CFI.bwidth + pCGI->draw_frame_with_row_no * 2 - value_catchy;
		//��������ַ�
		int count = 0;
		for (int i = 0; i < len_normal; i++) {
			if (*(msg + i) < 0)
				count++;
		}
		if (count % 2 == 1 && *(msg + len_normal - 1) > 127)
			len_normal--;
	}

	if (type == LOWER_STATUS_LINE && pCGI->lower_status_line) { //��״̬��
		x = pCGI->SLI.lower_start_x;
		y = pCGI->SLI.lower_start_y;
		cct_showstr(x, y, " ", pCGI->SLI.lower_normal_bgcolor, pCGI->SLI.lower_normal_fgcolor, 1, pCGI->cols);
		cct_showstr(x, y, catchy_msg, pCGI->SLI.lower_catchy_bgcolor, pCGI->SLI.lower_catchy_fgcolor, 1, len_catchy);
		cct_getxy(x, y);
		cct_showstr(x, y, msg, pCGI->SLI.lower_normal_bgcolor, pCGI->SLI.lower_normal_fgcolor, 1, len_normal);
		cct_getxy(x, y);
		if (pCGI->CFI.bwidth + pCGI->draw_frame_with_row_no * 2 - len_catchy - len_normal > 0)
			cct_showch(x, y, ' ', pCGI->SLI.lower_normal_bgcolor, pCGI->SLI.lower_normal_fgcolor, pCGI->CFI.bwidth - len_catchy - len_normal);
	}
	else if (type == TOP_STATUS_LINE && pCGI->top_status_line) { //��״̬��
		x = pCGI->SLI.top_start_x;
		y = pCGI->SLI.top_start_y;
		cct_showstr(x, y, " ", pCGI->SLI.top_normal_bgcolor, pCGI->SLI.top_normal_fgcolor, 1, pCGI->cols);
		cct_showstr(x, y, catchy_msg, pCGI->SLI.top_catchy_bgcolor, pCGI->SLI.top_catchy_fgcolor, 1, len_catchy);
		cct_getxy(x, y);
		cct_showstr(x, y, msg, pCGI->SLI.top_normal_bgcolor, pCGI->SLI.top_normal_fgcolor, 1, len_normal);
		cct_getxy(x, y);
		if (pCGI->CFI.bwidth + pCGI->draw_frame_with_row_no * 2 - len_catchy - len_normal > 0)
			cct_showch(x, y, ' ', pCGI->SLI.top_normal_bgcolor, pCGI->SLI.top_normal_fgcolor, pCGI->CFI.bwidth - len_catchy - len_normal);
	}

	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���ʾĳһ��ɫ��(����Ϊ�ַ���������Ϊrow/col)
  ���������const CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
		   const int row_no						���кţ���0��ʼ����Ϊ��֤��ȷ�ԣ����򲻼�飩
		   const int col_no						���кţ���0��ʼ����Ϊ��֤��ȷ�ԣ����򲻼�飩
		   const int bdi_value_catchy						����Ҫ��ʾ��ֵ
		   const BLOCK_DISPLAY_INFO *const bdi		����Ÿ�ֵ��Ӧ����ʾ��Ϣ�Ľṹ������
  �� �� ֵ��
  ˵    ����1��BLOCK_DISPLAY_INFO �ĺ����ͷ�ļ����÷��ο���������
			2��bdi_value_catchyΪ BDI_value_catchy_BLANK ��ʾ�հ׿飬Ҫ���⴦��
***************************************************************************/
int gmw_draw_block(const CONSOLE_GRAPHICS_INFO* const pCGI, const int row_no, const int col_no, const int bdi_value_catchy, const BLOCK_DISPLAY_INFO* const bdi)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;

	//ѭ������
	for (int i = 0; (bdi + i)->value != BDI_VALUE_END; i++)
	{
		if (bdi_value_catchy == (bdi + i)->value) {
			//��λ��ɫ�����Ͻ�
			int x = pCGI->start_x + pCGI->draw_frame_with_row_no * 2 + 2 + col_no * (pCGI->CFI.block_width + pCGI->CFI.separator * 2);
			int y = pCGI->start_y + pCGI->draw_frame_with_col_no + 1 + row_no * (pCGI->CFI.block_high + pCGI->CFI.separator);
			//ȡ��ɫ
			int bgcolor, fgcolor;
			bgcolor = (bdi + i)->bgcolor < 0 ? pCGI->CFI.bgcolor : (bdi + i)->bgcolor;
			fgcolor = (bdi + i)->fgcolor < 0 ? pCGI->CFI.fgcolor : (bdi + i)->fgcolor;

			if (pCGI->CBI.block_border == false) {  //����Ҫ�߿�
				for (int row = 0; row < pCGI->CFI.block_high; row++) {
					for (int col = 0; col < pCGI->CFI.block_width / 2; col++) {
						if (row == pCGI->CFI.block_high / 2 && col == pCGI->CFI.block_width / 4) {
							if ((bdi + i)->value == BDI_VALUE_BLANK)
								cct_showstr(x + col * 2, y + row, "  ", bgcolor, fgcolor);
							else {
								if ((bdi + i)->content == NULL) {
									cct_showint(x + col * 2, y + row, (bdi + i)->value, bgcolor, fgcolor);
									if ((bdi + i)->value < 10)
										cct_showch(x + col * 2 + 1, y + row, ' ', bgcolor, fgcolor);
								}
								else
									cct_showstr(x + col * 2, y + row, (bdi + i)->content, bgcolor, fgcolor);
							}
						}
						else
							cct_showstr(x + col * 2, y + row, "  ", bgcolor, fgcolor);
						Sleep(pCGI->delay_of_draw_block);
					}
				}
			}
			else {                 //�б߿�
				for (int row = 0; row < pCGI->CFI.block_high; row++) {
					for (int col = 0; col < pCGI->CFI.block_width / 2; col++) {
						if (row == pCGI->CFI.block_high / 2 && col == pCGI->CFI.block_width / 4) {
							if ((bdi + i)->value == BDI_VALUE_BLANK)
								cct_showstr(x + col * 2, y + row, "  ", bgcolor, fgcolor);
							else {
								if ((bdi + i)->content == NULL) {
									cct_showint(x + col * 2, y + row, (bdi + i)->value, bgcolor, fgcolor);
									if ((bdi + i)->value < 10)
										cct_showch(x + col * 2 + 1, y + row, ' ', bgcolor, fgcolor);
								}
								else
									cct_showstr(x + col * 2, y + row, (bdi + i)->content, bgcolor, fgcolor);
							}
						}
						else if ((bdi + i)->value == BDI_VALUE_BLANK)
							cct_showstr(x + col * 2, y + row, "  ", bgcolor, fgcolor);
						else if (row == 0) {
							if (col == 0)
								cct_showstr(x + col * 2, y + row, pCGI->CBI.top_left, bgcolor, fgcolor);
							else if (col == pCGI->CFI.block_width / 2 - 1)
								cct_showstr(x + col * 2, y + row, pCGI->CBI.top_right, bgcolor, fgcolor);
							else
								cct_showstr(x + col * 2, y + row, pCGI->CBI.h_normal, bgcolor, fgcolor);
						}
						else if (row == pCGI->CFI.block_high - 1) {
							if (col == 0)
								cct_showstr(x + col * 2, y + row, pCGI->CBI.lower_left, bgcolor, fgcolor);
							else if (col == pCGI->CFI.block_width / 2 - 1)
								cct_showstr(x + col * 2, y + row, pCGI->CBI.lower_right, bgcolor, fgcolor);
							else
								cct_showstr(x + col * 2, y + row, pCGI->CBI.h_normal, bgcolor, fgcolor);
						}
						else if (col == 0 || col == pCGI->CFI.block_width / 2 - 1)
							cct_showstr(x + col * 2, y + row, pCGI->CBI.v_normal, bgcolor, fgcolor);
						else
							cct_showstr(x + col * 2, y + row, "  ", bgcolor, fgcolor);
						Sleep(pCGI->delay_of_draw_block);
					}
				}
			}
			return 0;
		}
	}

	//������ֵ,���ش���
	return -1; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ��ƶ�ĳһ��ɫ��
  ���������const CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
		   const int row_no						���кţ���0��ʼ����Ϊ��֤��ȷ�ԣ����򲻼�飩
		   const int col_no						���кţ���0��ʼ����Ϊ��֤��ȷ�ԣ����򲻼�飩
		   const int bdi_value_catchy						����Ҫ��ʾ��ֵ
		   const int blank_bdi_value_catchy				���ƶ����������ڶ���Ч����ʾʱ���ڱ�ʾ�հ׵�ֵ��һ��Ϊ0���˴���Ϊ�������룬�ǿ��ǵ����ܳ��ֵ����������
		   const BLOCK_DISPLAY_INFO *const bdi		�������ʾֵ/�հ�ֵ��Ӧ����ʾ��Ϣ�Ľṹ������
		   const int direction						���ƶ�����һ�����֣������cmd_gmw_tools.h
		   const int distance						���ƶ����루��1��ʼ����Ϊ��֤��ȷ�ԣ����򲻼�飩
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int gmw_move_block(const CONSOLE_GRAPHICS_INFO* const pCGI, const int row_no, const int col_no, const int bdi_value_catchy, const int blank_bdi_value_catchy, const BLOCK_DISPLAY_INFO* const bdi, const int direction, const int distance)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;

	//��ʼɫ�����Ͻ�λ��
	int x = pCGI->start_x + pCGI->draw_frame_with_row_no * 2 + 2 + col_no * (pCGI->CFI.block_width + pCGI->CFI.separator * 2);
	int y = pCGI->start_y + pCGI->draw_frame_with_col_no + 1 + row_no * (pCGI->CFI.block_high + pCGI->CFI.separator);
	//��ȡ�հ׿���ɫ
	int bgcolor = bdi->bgcolor < 0 ? pCGI->CFI.bgcolor : bdi->bgcolor;
	int fgcolor = bdi->fgcolor < 0 ? pCGI->CFI.fgcolor : bdi->fgcolor;

	if (direction == UP_TO_DOWN) {
		for (int i = 0; i < distance * (pCGI->CFI.block_width / 2 + pCGI->CFI.separator); i++) {
			if ((i + 1) % (pCGI->CFI.block_width / 2 + pCGI->CFI.separator) == 0 && pCGI->CFI.separator) {
				for (int j = 0; j < pCGI->CFI.block_width / 2; j++)
					cct_showstr(x + j * 2, y, pCGI->CFI.h_normal, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);
			}
			else {
				for (int j = 0; j < pCGI->CFI.block_width / 2; j++)
					cct_showstr(x + j * 2, y, "  ", bgcolor, fgcolor);
			}
			y += 1;
			gmw_inner_draw_block_for_move(pCGI, x, y, bdi_value_catchy, bdi);
			Sleep(pCGI->delay_of_block_moved);
		}
	}
	else if (direction == DOWN_TO_UP) {
		for (int i = 0; i < distance * (pCGI->CFI.block_width / 2 + pCGI->CFI.separator); i++) {
			if ((i + 1) % (pCGI->CFI.block_width / 2 + pCGI->CFI.separator) == 0 && pCGI->CFI.separator) {
				for (int j = 0; j < pCGI->CFI.block_width / 2; j++)
					cct_showstr(x + j * 2, y + pCGI->CFI.block_high - 1, pCGI->CFI.h_normal, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);
			}
			else {
				for (int j = 0; j < pCGI->CFI.block_width / 2; j++)
					cct_showstr(x + j * 2, y + pCGI->CFI.block_high - 1, "  ", bgcolor, fgcolor);
			}
			y -= 1;
			gmw_inner_draw_block_for_move(pCGI, x, y, bdi_value_catchy, bdi);
			Sleep(pCGI->delay_of_block_moved);
		}
	}
	else if (direction == LEFT_TO_RIGHT) {
		for (int i = 0; i < distance * (pCGI->CFI.block_width / 2 + pCGI->CFI.separator); i++) {
			if ((i + 1) % (pCGI->CFI.block_width / 2 + pCGI->CFI.separator) == 0 && pCGI->CFI.separator) {
				for (int j = 0; j < pCGI->CFI.block_high; j++)
					cct_showstr(x, y + j, pCGI->CFI.v_normal, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);
			}
			else {
				for (int j = 0; j < pCGI->CFI.block_high; j++)
					cct_showstr(x, y + j, "  ", bgcolor, fgcolor);
			}
			x += 2;
			gmw_inner_draw_block_for_move(pCGI, x, y, bdi_value_catchy, bdi);
			Sleep(pCGI->delay_of_block_moved);
		}
	}
	else if (direction == RIGHT_TO_LEFT) {
		for (int i = 0; i < distance * (pCGI->CFI.block_width / 2 + pCGI->CFI.separator); i++) {
			if ((i + 1) % (pCGI->CFI.block_width / 2 + pCGI->CFI.separator) == 0 && pCGI->CFI.separator) {
				for (int j = 0; j < pCGI->CFI.block_high; j++)
					cct_showstr(x + pCGI->CFI.block_width - 2, y + j, pCGI->CFI.v_normal, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);
			}
			else {
				for (int j = 0; j < pCGI->CFI.block_high; j++)
					cct_showstr(x + pCGI->CFI.block_width - 2, y + j, "  ", bgcolor, fgcolor);
			}
			x -= 2;
			gmw_inner_draw_block_for_move(pCGI, x, y, bdi_value_catchy, bdi);
			Sleep(pCGI->delay_of_block_moved);
		}
	}

	//��������
	return -1; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ������̻����
  ���������const CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
		   int &MAction							��������� CCT_MOUSE_EVENT�����ֵ��Ч��Ϊ MOUSE_ONLY_MOVED/MOUSE_LEFT_BUTTON_CLICK/MOUSE_RIGHT_BUTTON_CLICK ����֮һ
													   ������� CCT_KEYBOARD_EVENT�����ֵ��Ч
		   int &MRow								��������� CCT_MOUSE_EVENT �� MAction = MOUSE_ONLY_MOVED/MOUSE_LEFT_BUTTON_CLICK�����ֵ��Ч����ʾ���ѡ�����Ϸ������кţ���0��ʼ��
												  ���������ֵ��Ч�����������Чֵ���´��󣬲��Ǳ������Ĵ�!!!��
		   int &MCol								��������� CCT_MOUSE_EVENT �� MAction = MOUSE_ONLY_MOVED/MOUSE_LEFT_BUTTON_CLICK�����ֵ��Ч����ʾ���ѡ�����Ϸ������кţ���0��ʼ��
												  ���������ֵ��Ч�����������Чֵ���´��󣬲��Ǳ������Ĵ�!!!��
		   int &KeyCode1							��������� CCT_KEYBOARD_EVENT�����ֵ��Ч��Ϊ�����ļ��루���˫���룬��Ϊ��һ����
												  ���������ֵ��Ч�����������Чֵ���´��󣬲��Ǳ������Ĵ�!!!��
		   int &KeyCode2							��������� CCT_KEYBOARD_EVENT�����ֵ��Ч��Ϊ�����ļ��루���˫���룬��Ϊ�ڶ���������ǵ����룬��Ϊ0��
												  ���������ֵ��Ч�����������Чֵ���´��󣬲��Ǳ������Ĵ�!!!��
		   const bool update_lower_status_line		������ƶ�ʱ���Ƿ�Ҫ�ڱ���������ʾ"[��ǰ���] *��*��/λ�÷Ƿ�"����Ϣ��true=��ʾ��false=����ʾ��ȱʡΪtrue��
  �� �� ֵ����������Լ��
		   1�����������ƶ����õ���MRow/MCol�봫�����ͬ(���ָ��΢С���ƶ�)���򲻷��أ�������
							  �õ����зǷ�λ�ã��򲻷��أ����� update_lower_status_line ����������״̬����ʾ"[��ǰ���] λ�÷Ƿ�"
							  �õ���MRow/MCol�봫��Ĳ�ͬ(��������һ���仯)������ update_lower_status_line ����������״̬����ʾ"[��ǰ���] *��*��"���ٷ���MOUSE_ONLY_MOVED����Щ��Ϸ���غ�Ҫ����ɫ��Ĳ�ͬ��ɫ��ʾ��
		   2������ǰ������������ҵ�ǰ���ָ��ͣ��������Ϸ�����*��*���ϣ��򷵻� CCT_MOUSE_EVENT ��MAction Ϊ MOUSE_LEFT_BUTTON_CLICK, MRow Ϊ�кţ�MCol Ϊ�б�
								  �ҵ�ǰ���ָ��ͣ���ڷǷ����򣨷���Ϸ������Ϸ�����еķָ��ߣ����򲻷��أ����� update_lower_status_line ����������״̬����ʾ"[��ǰ���] λ�÷Ƿ�"
		   3������ǰ�������Ҽ������ж����ָ��ͣ�������Ƿ�Ϸ���ֱ�ӷ��� CCT_MOUSE_EVENT ��MAction Ϊ MOUSE_RIGHT_BUTTON_CLICK, MRow��MColȡ��ǰֵ����Ϊ�������ǵ��Ҽ������Ҫ���꣩
		   4��������¼����ϵ�ĳ������˫���밴��������ֱ�ӷ��� CCT_KEYBOARD_EVENT��KeyCode1/KeyCode2��Ϊ��Ӧ�ļ���ֵ
 ˵    ����ͨ������ cmd_console_tools.cpp �е� read_keyboard_and_mouse ����ʵ��
***************************************************************************/
int gmw_read_keyboard_and_mouse(const CONSOLE_GRAPHICS_INFO* const pCGI, int& MAction, int& MRow, int& MCol, int& KeyCode1, int& KeyCode2, const bool update_lower_status_line)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;

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
			//�ж��Ҽ�
			if (MAction == MOUSE_RIGHT_BUTTON_CLICK) {
				MRow = MRow_new;
				MCol = MCol_new;
				return CCT_MOUSE_EVENT;
			}
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
						sprintf(temp, "[��ǰ���] %c��%d��", char('A' + MRow_new), MCol_new);
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