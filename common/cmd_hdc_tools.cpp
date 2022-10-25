/*2151613 ë��¼ �ƿ�*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include "../include/cmd_hdc_tools.h"
using namespace std;

#if !HDC_SERIES_BY_TEACHER	//δ���������²Ŵ���������

/* ���������Ҫ��ͷ�ļ� */

extern "C" WINBASEAPI HWND WINAPI GetConsoleWindow(); //VS�д˴����в����ߣ���Ӱ������ʹ��

/* �Ѷ���ľ�̬ȫ�ֱ��� */
static HWND hWnd = GetConsoleWindow();
static HDC hdc = NULL;
static const double PI = 3.14159;
static int _BgColor_, _FgColor_, _Width_, _High;
static int _Delay_ms;

/* �����ʶ�ʹ�þ�̬ȫ�ֱ�����������static�����ⲿ���ɼ� */

/* �˴���������Զ��庯����������static�����ⲿ���ɼ� */

/* ��������˼�����������������ʵ�֣���Ҫ�Ķ� */
/***************************************************************************
  �������ƣ�
  ��    �ܣ���ʼ��
  ���������const int bgcolor������ɫ
            const int fgcolor��ǰ��ɫ
			const int width  ����Ļ��ȣ�����
			const int high   ����Ļ�߶ȣ�����
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void hdc_init(const int bgcolor, const int fgcolor, const int width, const int high)
{
	/* ���ͷţ���ֹ��release���ٴ�init��hdc_release�����룩 */
	hdc_release();

	/* ����init����һ����̬ȫ������¼������hdc_cls()���õ� */
	_BgColor_ = bgcolor;
	_FgColor_ = fgcolor;
	_Width_ = width;
	_High = high;

	hdc = GetDC(hWnd);

	cct_setcursor(CURSOR_INVISIBLE);
	cct_setcolor(bgcolor, fgcolor);
	cct_setfontsize("��������", 16);
	cct_setconsoleborder(width / 8 + !!(width % 8), high / 16 + !!(high % 16)); //������Ŀ�ȼ��߶�ת��Ϊ�ض��������������!!�ĺ��壺�������8/16�ı��������ж�+1
	cct_cls();
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ��ͷŻ�ͼ��Դ
  ���������
  �� �� ֵ��
  ˵    ����������
***************************************************************************/
void hdc_release()
{
	if (hdc) {
		ReleaseDC(hWnd, hdc);
		hdc = NULL;
		cct_setcursor(CURSOR_VISIBLE_NORMAL);
	}
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void hdc_set_delay(int ms)
{
	if (ms > 0)
		_Delay_ms = ms;
	else
		_Delay_ms = 0;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ����û�����ɫ������RGBֵ
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void hdc_set_pencolor(const int RGB_value)
{
	SelectObject(hdc, GetStockObject(DC_PEN));
	SetDCPenColor(hdc, RGB_value);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ����û�����ɫ������RGB��ɫ��ֵ0-255
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void hdc_set_pencolor(const unsigned char red, const unsigned char green, const unsigned char blue)
{
	hdc_set_pencolor(RGB(red, green, blue));
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ������Ļ�����е�ͼ��
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void hdc_cls()
{
    /* ����һ��Ҫ��һ����ɫ��ʼ������������ص㣬�ҵ�����㷽����ͬѧ����֪ͨ�� */
	hdc_init(_BgColor_, (_FgColor_  + 1) % 16, _Width_, _High);

	hdc_init(_BgColor_, _FgColor_, _Width_, _High);

	/* ���ֻ���������demoʱ�������hdc_cls()���һ������ȱ�ߵ����������ʱ����
	   ������ֻ������л������⣬���ߴ���ʱֵ */
	Sleep(30);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���(x,y)λ�ô���ָ����ɫ����һ�����ص�
  ���������const int x��x���꣬���Ͻ�Ϊ(0,0)
            const int y��y���꣬���Ͻ�Ϊ(0,0)
  �� �� ֵ��
  ˵    ������ɫֱ���õ�ǰ�趨�������ڵ��ô�ָ��
***************************************************************************/
static inline void hdc_base_point(const int x, const int y)
{
	MoveToEx(hdc, x - 1, y - 1, NULL);
	LineTo(hdc, x, y);
	if (_Delay_ms > 0)
		Sleep(_Delay_ms);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���(x1,y1)-(x2,y2)֮�仭��һ�����ص������
  ���������const int x1�����x���꣬���Ͻ�Ϊ(0,0)
			const int y1�����y���꣬���Ͻ�Ϊ(0,0)
			const int x2���յ�y���꣬���Ͻ�Ϊ(0,0)
			const int y2���յ�y���꣬���Ͻ�Ϊ(0,0)
  �� �� ֵ��
  ˵    ������ɫֱ���õ�ǰ�趨
***************************************************************************/
static inline void hdc_base_line(const int x1, const int y1, const int x2, const int y2)
{
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);
	if (_Delay_ms > 0)
		Sleep(_Delay_ms);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���(x,y)λ�ô���ָ����ɫ��һ��ָ����ϸ�ĵ�(�û�ʵ��Բ��ģ��)
  ���������const int x			��x���꣬���Ͻ�Ϊ(0,0)
            const int y			��y���꣬���Ͻ�Ϊ(0,0)
			const int thickness	����Ĵ�ϸ������λ1�����޲���(�����ᵼ�²���ȫ���)����ȱʡֵ��
			const int RGB_value	�������ɫ����ȱʡֵ��
  �� �� ֵ��
  ˵    �����Ľ�����Ч��
***************************************************************************/
void hdc_point(const int x, const int y, const int thickness, const int RGB_value)
{
	int tn = thickness;
	if (tn < 1)
		tn = 1;		//��������
	/* ������ֱ�������ޣ����ǵ����޳���һ����Сʱ��������Բ����λ��δʵ�� */

	const int tn_end = (tn <= 1) ? 1 : tn / 2;

	int angle, level;
	int old_x1 = INT_MAX, old_y1 = INT_MAX, x1, y1;
	int count = 0;

	if (RGB_value != INVALID_RGB)
		hdc_set_pencolor(RGB_value);

	int value;
	if (thickness <= 3)
		value = 360;
	else if (thickness <= 5)
		value = 45;
	else if (thickness <= 10)
		value = 5;
	else
		value = 1;

	/* �û�Բ�ķ�ʽģ��ֵ� */
	for (level = 1; level <= tn_end; level++) {
		for (angle = 0; angle <= 360; angle += value) {
			/* ע�⣬ϵͳ�������ᣬ0����Բ�����·� */
			x1 = x + (int)(level * sin(angle * PI / 180));
			y1 = y - (int)(level * cos(angle * PI / 180));

			/* ���뾶��Сʱ���Ƕȱ仯��������int�͵�x1/y1�仯����˼��ж���䣬�����ظ���ͬһ���ص� */
			if (x1 != old_x1 || y1 != old_y1) {
				old_x1 = x1;
				old_y1 = y1;
				hdc_base_point(x1, y1);
				++count;
		}
	}
}
#if 0
	/* �ſ���ע�ͣ����Կ���һ���ֵ����˼������ص���� */
	cct_gotoxy(0, 41);
	printf("count=%d           ", count);
	getchar();
#endif
}

/* -------------------------------------------------------------------------
	�������к�����ʵ�֣���������������׼�Ķ�
	1������Ҫ����ϵͳ�������й�ͼ�β����ĺ���
	2�����к�����ʵ�ֶ�����hdc_base_point/hdc_base_line���������
	3����һ�룬�ǲ������к�������Ҫ����������ʵ�ֹ��̣�Ӧ����ʵ����Щ������
	4�������ʵ������ӵĲ���
	5��ϵͳ�ĽǶ��뺯�������еĽǶȺ������180��
   ------------------------------------------------------------------------- */

/***************************************************************************
  �������ƣ�
  ��    �ܣ����߶�
  ���������const int x1		������x
            const int y1		������y
			const int x2		���յ��x
			const int y2		���յ��y
			const int thickness	���߶εĴ�ϸ����ȱʡֵ��
			const int RGB_value	���߶ε���ɫ����ȱʡֵ��
  �� �� ֵ��
  ˵    ���������������û���hdc_point����ϣ��ٶ�����
                  Ҳ������hdc_base_point/hdc_base_line����ϣ��ٶȿ죩
***************************************************************************/
void hdc_line(const int x1, const int y1, const int x2, const int y2, const int thickness, const int RGB_value)
{
	int th = thickness;
	if (th < 1)
		th = 1;

	if (RGB_value != INVALID_RGB)
		hdc_set_pencolor(RGB_value);

	for (int level = 0; level < th; level++)
		if (y1 != y2) {
			hdc_base_line(x1 - th / 2 + level, y1, x2 - th / 2 + level, y2);
		}
	for (int level = 0; level < th; level++)
		if (x1 != x2) {
			hdc_base_line(x1, y1 - th / 2 + level, x2, y2 - th / 2 + level);
		}
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�������������꣬��һ��������
  ���������const int x1		����1�����x
            const int y1		����1�����y
			const int x2		����2�����x
			const int y2		����2�����y
			const int x3		����3�����x
			const int y3		����3�����y
			bool filled			���Ƿ���Ҫ��䣨��ȱʡֵ��
			const int thickness	���ߵĴ�ϸ����ȱʡֵ��
			const int RGB_value	����ɫ����ȱʡֵ��
  �� �� ֵ��
  ˵    �������ж������Ƿ��ߣ�������ߣ�����һ��ֱ�߼���
***************************************************************************/
void hdc_triangle(const int x1, const int y1, const int x2, const int y2, const int x3, const int y3, bool filled, const int thickness, const int RGB_value)
{
	hdc_line(x1, y1, x2, y2, thickness, RGB_value);
	hdc_line(x1, y1, x3, y3, thickness, RGB_value);
	hdc_line(x3, y3, x2, y2, thickness, RGB_value);

	if (filled) {
		int y_high = y1, x_high = x1;
		int y_middle = y2, x_middle = x2;
		int y_low = y3, x_low = x3;

		//����
		if (y_high > y_middle) {
			y_high = y_high + y_middle;
			y_middle = y_high - y_middle;
			y_high = y_high - y_middle;
			x_high = x_high + x_middle;
			x_middle = x_high - x_middle;
			x_high = x_high - x_middle;
		}
		if (y_high > y_low) {
			y_high = y_high + y_low;
			y_low = y_high - y_low;
			y_high = y_high - y_low;
			x_high = x_high + x_low;
			x_low = x_high - x_low;
			x_high = x_high - x_low;
		}
		if (y_middle > y_low) {
			y_low = y_low + y_middle;
			y_middle = y_low - y_middle;
			y_low = y_low - y_middle;
			x_low = x_low + x_middle;
			x_middle = x_low - x_middle;
			x_low = x_low - x_middle;
		}

		for (int i = 1; i <= y_middle - y_high; i++) {
			int y = y_high + i;
			int x_high_to_low = (x_high * (y_low - y) + x_low * i) / (y_low - y_high);
			int x_high_to_middle = (x_high * (y_middle - y) + x_middle * i) / (y_middle - y_high);
			if (x_high == x_middle) {
				hdc_line(x_high_to_low, y, x_high, y, 2, RGB_value);
			}
			else if (x_high == x_low) {
				hdc_line(x_high_to_middle, y, x_high, y, 2, RGB_value);
			}
			else {
				hdc_line(x_high_to_low, y, x_high_to_middle, y, 2, RGB_value);
			}
		}

		for (int i = 1; i <= y_low - y_middle; i++) {
			int y = y_middle + i;
			int x_high_to_low = (x_high * (y_low - y) + x_low * (y - y_high)) / (y_low - y_high);
			int x_low_to_middle = (x_middle * (y_low - y) + x_low * i) / (y_low - y_middle);
			if (x_high == x_low) {
				hdc_line(x_low_to_middle, y, x_high, y, 2, RGB_value);
			}
			else if (x_middle == x_low) {
				hdc_line(x_high_to_low, y, x_middle, y, 2, RGB_value);
			}
			else {
				hdc_line(x_low_to_middle, y, x_high_to_low, y, 2, RGB_value);
			}
		}
	}
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ��������Ͻ����꼰��ȡ��߶ȣ�����һ��������
  ���������const int left_up_x			�����Ͻ�x
            const int left_up_y			�����Ͻ�y
			const int width				�����
			const int high				���߶�
			const int rotation_angles	�������Ͻ�Ϊ֧�㣬��x�����ת��ǣ�����תΪ����
			bool filled					���Ƿ���Ҫ��䣨��ȱʡֵ��
			const int thickness			���ߵĴ�ϸ����ȱʡֵ��
			const int RGB_value			����ɫ����ȱʡֵ��
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void hdc_rectangle(const int left_up_x, const int left_up_y, const int width, const int high, const int rotation_angles, const bool filled, const int thickness, const int RGB_value)
{
	int angle = rotation_angles;

	//ת������
	while (angle < 0)
		angle += 360;

	//����ʣ�¸���
	int right_up_x = (int)(left_up_x + width * cos(angle * PI / 180));
	int right_up_y = (int)(left_up_y + width * sin(angle * PI / 180));
	int left_down_x = (int)(left_up_x - high * sin(angle * PI / 180));
	int left_down_y = (int)(left_up_y + high * cos(angle * PI / 180));
	int right_down_x = (int)(left_up_x + width * cos(angle * PI / 180) - high * sin(angle * PI / 180));
	int right_down_y = (int)(left_up_y + high * cos(angle * PI / 180) + width * sin(angle * PI / 180));

	//������
	//�ϱ���
	hdc_line(left_up_x, left_up_y, right_up_x, right_up_y, thickness, RGB_value);
	//�����
	hdc_line(left_up_x, left_up_y, left_down_x, left_down_y, thickness, RGB_value);
	//�ұ���
	hdc_line(right_up_x, right_up_y, right_down_x, right_down_y, thickness, RGB_value);
	//�±���
	hdc_line(left_down_x, left_down_y, right_down_x, right_down_y, thickness, RGB_value);

	//�����
	if (filled) {
		for (int i = 1; i < high; i++) {
			//�����
			int x_left = (left_up_x * (high - i) + left_down_x * i) / high;
			int y_left = (left_up_y * (high - i) + left_down_y * i) / high;
			//���ұ�
			int x_right = (right_up_x * (high - i) + right_down_x * i) / high;
			int y_right = (right_up_y * (high - i) + right_down_y * i) / high;

			hdc_line(x_left, y_left, x_right, y_right, 2, RGB_value);
		}
	}
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ��������Ͻ����꼰�߳�������һ��������
  ���������const int left_up_x			�����Ͻ�x
			const int left_up_y			�����Ͻ�y
			const int length			���߳�
			const int rotation_angles	�������Ͻ�Ϊ֧�㣬��x�����ת��ǣ�����תΪ��������ȱʡֵ��
			const bool filled			���Ƿ���Ҫ��䣨��ȱʡֵ��
			const int thickness			���ߵĴ�ϸ����ȱʡֵ��
			const int RGB_value			����ɫ����ȱʡֵ��
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void hdc_square(const int left_up_x, const int left_up_y, const int length, const int rotation_angles, const bool filled, const int thickness, const int RGB_value)
{
	int angle = rotation_angles;

	//ת������
	while (angle < 0)
		angle += 360;

	//����ʣ�¸���
	int right_up_x = (int)(left_up_x + length * cos(angle * PI / 180));
	int right_up_y = (int)(left_up_y + length * sin(angle * PI / 180));
	int left_down_x = (int)(left_up_x - length * sin(angle * PI / 180));
	int left_down_y = (int)(left_up_y + length * cos(angle * PI / 180));
	int right_down_x = (int)(left_up_x + length * cos(angle * PI / 180) - length * sin(angle * PI / 180));
	int right_down_y = (int)(left_up_y + length * cos(angle * PI / 180) + length * sin(angle * PI / 180));

	//������
	//�ϱ���
	hdc_line(left_up_x, left_up_y, right_up_x, right_up_y, thickness, RGB_value);
	//�����
	hdc_line(left_up_x, left_up_y, left_down_x, left_down_y, thickness, RGB_value);
	//�ұ���
	hdc_line(right_up_x, right_up_y, right_down_x, right_down_y, thickness, RGB_value);
	//�±���
	hdc_line(left_down_x, left_down_y, right_down_x, right_down_y, thickness, RGB_value);

	//�����
	if (filled) {
		for (int i = 1; i < length; i++) {
			//�����
			int x_left = (left_up_x * (length - i) + left_down_x * i) / length;
			int y_left = (left_up_y * (length - i) + left_down_y * i) / length;
			//���ұ�
			int x_right = (right_up_x * (length - i) + right_down_x * i) / length;
			int y_right = (right_up_y * (length - i) + right_down_y * i) / length;

			hdc_line(x_left, y_left, x_right, y_right, 2, RGB_value);
		}
	}
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ����ո����Ĳ�����һ��Բ��
  ���������const int point_x		��Բ�ĵ�x
            const int point_y		��Բ�ĵ�y
			const int radius		���뾶
			const int angle_begin	����ʼ�Ƕȣ���Բ�����Ϸ�Ϊ0�㣬˳ʱ��Ϊ����ע�⣺��ϵͳ�������180��!!!������ȱʡֵ��
			const int angle_end		�������Ƕȣ�ͬ�ϣ�����ȱʡֵ��
			const int thickness		����ϸ����ȱʡֵ��
			const int RGB_value		����ɫ����ȱʡֵ��
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void hdc_arc(const int point_x, const int point_y, const int radius, const int angle_begin, const int angle_end, const int thickness, const int RGB_value)
{
	int angle_begin_new = angle_begin;
	int angle_end_new = angle_end;
	int angle;

	//ת������
	while (angle_begin_new < 0)
		angle_begin_new += 360;
	while (angle_end_new < 0)
		angle_end_new += 360;

	//ת����С�Ƚ�
	while (angle_begin_new >= 360)
		angle_begin_new -= 360;
	while (angle_end_new >= 360)
		angle_end_new -= 360;

	//�ж�Բ���ĳ���
	if (angle_begin_new >= angle_end_new)
		angle = angle_end_new - angle_begin_new + 360;
	else
		angle = angle_end_new - angle_begin_new;

	//���ò�������
	int precision;
	if (radius * thickness >= 1080)
		precision = 2;
	else
		precision = 1;

	//����
	for (int i = 0; i <= angle * PI * radius / 180; i += precision) {
		int x = point_x + (int)(radius * sin((double)(i) / radius + angle_begin_new * PI / 180));
		int y = point_y - (int)(radius * cos((double)(i) / radius + angle_begin_new * PI / 180));
		hdc_point(x, y, thickness, RGB_value);
	}
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ����ո����Ĳ�����һ������
  ���������const int point_x		��Բ�ĵ�x
			const int point_y		��Բ�ĵ�y
			const int radius		���뾶
			const int angle_begin	����ʼ�Ƕȣ���Բ�����Ϸ�Ϊ0�㣬˳ʱ��Ϊ����ע�⣺��ϵͳ�������180��!!!������ȱʡֵ��
			const int angle_end		�������Ƕȣ�ͬ�ϣ�����ȱʡֵ��
			const bool filled		���Ƿ���Ҫ��䣨��ȱʡֵ��
			const int thickness		����ϸ����ȱʡֵ��
			const int RGB_value		����ɫ����ȱʡֵ��
  ���������
  �� �� ֵ��
  ˵    ��������ʼ/�����ǶȲ�ֵΪ360�ı���ʱ������������
***************************************************************************/
void hdc_sector(const int point_x, const int point_y, const int radius, const int angle_begin, const int angle_end, const bool filled, const int thickness, const int RGB_value)
{
	int angle_begin_new = angle_begin;
	int angle_end_new = angle_end;
	int angle;

	//ת������
	while (angle_begin_new < 0)
		angle_begin_new += 360;
	while (angle_end_new < 0)
		angle_end_new += 360;

	//ת����С�Ƚ�
	while (angle_begin_new >= 360)
		angle_begin_new -= 360;
	while (angle_end_new >= 360)
		angle_end_new -= 360;

	//�ж�Բ���ĳ���
	if (angle_begin_new >= angle_end_new)
		angle = angle_end_new - angle_begin_new + 360;
	else
		angle = angle_end_new - angle_begin_new;

	//������(����еĻ�)
	if (angle != 360) {
		int x = point_x + (int)(radius * sin(angle_begin_new * PI / 180));
		int y = point_y - (int)(radius * cos(angle_begin_new * PI / 180));
		hdc_line(point_x, point_y, x, y, thickness, RGB_value);
		x = point_x + (int)(radius * sin(angle_end_new * PI / 180));
		y = point_y - (int)(radius * cos(angle_end_new * PI / 180));
		hdc_line(point_x, point_y, x, y, thickness, RGB_value);
	}

	//����

	//������Բ����ת������ʼ��,��ͳһͬ�뾶��ͬ����Բ���ϸ���λ��
	double angle_begin_double = 0;
	for (double i = 0; i < 2 * PI * radius; ++i) {
		if (i / radius * 180 / PI >= angle_begin_new) {
			angle_begin_double = i / radius * 180 / PI;
			break;
		}
	}

	//��ӡԲ������
	for (int i = 0; i <= angle * PI * radius / 180; ++i) {
		int x = point_x + (int)(radius * sin((double)(i) / radius + angle_begin_double * PI / 180));
		int y = point_y - (int)(radius * cos((double)(i) / radius + angle_begin_double * PI / 180));
		hdc_point(x, y, thickness, RGB_value);
	}

	//��ʵ��
	if (filled) {
		for (int i = 0; i <= angle * PI * radius / 180; ++i) {
			int x = point_x + (int)(radius * sin((double)(i) / radius + angle_begin_double * PI / 180));
			int y = point_y - (int)(radius * cos((double)(i) / radius + angle_begin_double * PI / 180));
			hdc_line(x, y, point_x, point_y, 2, RGB_value);
		}
	}
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ����ո����Ĳ�����һ��Բ
  ���������const int point_x		��Բ�ĵ�x
			const int point_y		��Բ�ĵ�y
			const int radius		���뾶
			const bool filled		���Ƿ���Ҫ��䣨��ȱʡֵ��
			const int thickness		����ϸ����ȱʡֵ��
			const int RGB_value		����ɫ����ȱʡֵ��
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void hdc_circle(const int point_x, const int point_y, const int radius, const bool filled, const int thickness, const int RGB_value)
{
	//���û�Բ������
	hdc_sector(point_x, point_y, radius, 0, 360, filled, thickness, RGB_value);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ����ո����Ĳ�����һ����Բ
  ���������const int point_x			��Բ�ĵ�x
			const int point_y			��Բ�ĵ�y
			const int radius_a			��ƽ����X��İ뾶
			const int radius_b			��ƽ����Y��İ뾶
			const int rotation_angles	����Բ��Ϊ֧�㣬��x�����ת��ǣ�����תΪ��������ȱʡֵ��
			const bool filled			���Ƿ���Ҫ��䣨��ȱʡֵ��
			const int thickness			����ϸ����ȱʡֵ��
			const int RGB_value			����ɫ����ȱʡֵ��
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void hdc_ellipse(const int point_x, const int point_y, const int radius_a, const int radius_b, const int rotation_angles, const bool filled, const int thickness, const int RGB_value)
{
	//�ó����뾶
	double radius_c = sqrt(fabs(radius_a * radius_a - radius_b * radius_b));
	//������ת��
	int angle = rotation_angles;

	//�ѽǶ�ת������
	while (angle < 0)
		angle += 360;
	//�ѽǶ�ת����Сֵ
	while (angle >= 360)
		angle -= 360;

	//ȡ���ֵ
	int radius_max = radius_a > radius_b ? radius_a : radius_b;
	double F_x_1 = point_x, F_y_1 = point_y;
	double F_x_2 = point_x, F_y_2 = point_y;

	//����a��b��С���������
	if (radius_a > radius_b) {
		//����������ת
		//��
		F_x_1 = point_x - radius_c * cos(angle * PI / 180);
		F_y_1 = point_y - radius_c * sin(angle * PI / 180);
		//��
		F_x_2 = point_x + radius_c * cos(angle * PI / 180);
		F_y_2 = point_y + radius_c * sin(angle * PI / 180);
	}
	else if (radius_a < radius_b) {
		//����������ת
		//��
		F_x_1 = point_x + radius_c * sin(angle * PI / 180);
		F_y_1 = point_y - radius_c * cos(angle * PI / 180);
		//��
		F_x_2 = point_x - radius_c * sin(angle * PI / 180);
		F_y_2 = point_y + radius_c * cos(angle * PI / 180);
	}
	else {
		hdc_circle(point_x, point_y, radius_a, filled, thickness, RGB_value);
		return;
	}

	//�ж������������ڵĵ㣬����Բ���򻭳�
	//ȡ���Ͻǵ������
	int left_top_x = point_x - radius_max;
	int left_top_y = point_y - radius_max;

	for (int j = 0; j < radius_max * 2 + 1; ++j) {
		for (int i = 0; i < radius_max * 2 + 1; ++i) {
			//��ǰ�������
			int x = i + left_top_x;
			int y = j + left_top_y;
			//������ľ���
			double l1 = sqrt(pow(x - F_x_1, 2) + pow(y - F_y_1, 2));
			double l2 = sqrt(pow(x - F_x_2, 2) + pow(y - F_y_2, 2));
			//�ж��Ƿ�����Բ��
			if (fabs(l1 + l2 - 2 * radius_max) < 1)
				hdc_point(x, y, thickness, RGB_value);
		}
	}

	//�����
	if (filled) {
		for (int j = 0; j < radius_max * 2 + 1; ++j) {
			//��ͬһ����������ҵĵ�
			int x_max = left_top_x;
			int x_min = left_top_x;
			int count = 0;
			for (int i = 0; i < radius_max * 2 + 1; ++i) {
				//��ǰ�������
				int x = i + left_top_x;
				int y = j + left_top_y;
				//������ľ���
				double l1 = sqrt(pow(x - F_x_1, 2) + pow(y - F_y_1, 2));
				double l2 = sqrt(pow(x - F_x_2, 2) + pow(y - F_y_2, 2));
				//�ж��Ƿ�����Բ��
				//�ҳ���������ҵĵ㣬���ߣ����Ч��
				if (fabs(l1 + l2 - 2 * radius_max) < 1) {
					count++;
					x_max = x;
					if (count == 1)
						x_min = x;
				}
			}
			hdc_line(x_min, j + left_top_y, x_max, j + left_top_y, 2, RGB_value);
		}
	}
}

#endif !HDC_SERIES_BY_TEACHER
