/*2151613 毛宇录 计科*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include "../include/cmd_hdc_tools.h"
using namespace std;

#if !HDC_SERIES_BY_TEACHER	//未定义的情况下才打开条件编译

/* 允许添加需要的头文件 */

extern "C" WINBASEAPI HWND WINAPI GetConsoleWindow(); //VS中此处会有波浪线，不影响正常使用

/* 已定义的静态全局变量 */
static HWND hWnd = GetConsoleWindow();
static HDC hdc = NULL;
static const double PI = 3.14159;
static int _BgColor_, _FgColor_, _Width_, _High;
static int _Delay_ms;

/* 允许适度使用静态全局变量，但仅限static，即外部不可见 */

/* 此处允许添加自定义函数，但仅限static，即外部不可见 */

/* 下面给出了几个基本函数的完整实现，不要改动 */
/***************************************************************************
  函数名称：
  功    能：初始化
  输入参数：const int bgcolor：背景色
            const int fgcolor：前景色
			const int width  ：屏幕宽度（点阵）
			const int high   ：屏幕高度（点阵）
  返 回 值：
  说    明：
***************************************************************************/
void hdc_init(const int bgcolor, const int fgcolor, const int width, const int high)
{
	/* 先释放，防止不release而再次init（hdc_release可重入） */
	hdc_release();

	/* 窗口init后，用一个静态全局量记录，后续hdc_cls()会用到 */
	_BgColor_ = bgcolor;
	_FgColor_ = fgcolor;
	_Width_ = width;
	_High = high;

	hdc = GetDC(hWnd);

	cct_setcursor(CURSOR_INVISIBLE);
	cct_setcolor(bgcolor, fgcolor);
	cct_setfontsize("点阵字体", 16);
	cct_setconsoleborder(width / 8 + !!(width % 8), high / 16 + !!(high % 16)); //将点阵的宽度及高度转换为特定字体的行列数，!!的含义：如果不是8/16的倍数，行列多+1
	cct_cls();
}

/***************************************************************************
  函数名称：
  功    能：释放画图资源
  输入参数：
  返 回 值：
  说    明：可重入
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
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void hdc_set_delay(int ms)
{
	if (ms > 0)
		_Delay_ms = ms;
	else
		_Delay_ms = 0;
}

/***************************************************************************
  函数名称：
  功    能：设置画笔颜色，传入RGB值
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void hdc_set_pencolor(const int RGB_value)
{
	SelectObject(hdc, GetStockObject(DC_PEN));
	SetDCPenColor(hdc, RGB_value);
}

/***************************************************************************
  函数名称：
  功    能：设置画笔颜色，传入RGB三色，值0-255
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void hdc_set_pencolor(const unsigned char red, const unsigned char green, const unsigned char blue)
{
	hdc_set_pencolor(RGB(red, green, blue));
}

/***************************************************************************
  函数名称：
  功    能：清除屏幕上现有的图形
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void hdc_cls()
{
    /* 发现一定要换一种颜色初始化才能清除像素点，找到更简便方法的同学可以通知我 */
	hdc_init(_BgColor_, (_FgColor_  + 1) % 16, _Width_, _High);

	hdc_init(_BgColor_, _FgColor_, _Width_, _High);

	/* 部分机器上运行demo时，会出现hdc_cls()后第一根线有缺线的情况，加延时即可
	   如果部分机器运行还有问题，调高此延时值 */
	Sleep(30);
}

/***************************************************************************
  函数名称：
  功    能：在(x,y)位置处用指定颜色画出一个像素点
  输入参数：const int x：x坐标，左上角为(0,0)
            const int y：y坐标，左上角为(0,0)
  返 回 值：
  说    明：颜色直接用当前设定，可以在调用处指定
***************************************************************************/
static inline void hdc_base_point(const int x, const int y)
{
	MoveToEx(hdc, x - 1, y - 1, NULL);
	LineTo(hdc, x, y);
	if (_Delay_ms > 0)
		Sleep(_Delay_ms);
}

/***************************************************************************
  函数名称：
  功    能：在(x1,y1)-(x2,y2)之间画出一个像素点的连线
  输入参数：const int x1：起点x坐标，左上角为(0,0)
			const int y1：起点y坐标，左上角为(0,0)
			const int x2：终点y坐标，左上角为(0,0)
			const int y2：终点y坐标，左上角为(0,0)
  返 回 值：
  说    明：颜色直接用当前设定
***************************************************************************/
static inline void hdc_base_line(const int x1, const int y1, const int x2, const int y2)
{
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);
	if (_Delay_ms > 0)
		Sleep(_Delay_ms);
}

/***************************************************************************
  函数名称：
  功    能：在(x,y)位置处用指定颜色画一个指定粗细的点(用画实心圆来模拟)
  输入参数：const int x			：x坐标，左上角为(0,0)
            const int y			：y坐标，左上角为(0,0)
			const int thickness	：点的粗细，下限位1，上限不限(如过大会导致不完全填充)（有缺省值）
			const int RGB_value	：点的颜色（有缺省值）
  返 回 值：
  说    明：改进运行效率
***************************************************************************/
void hdc_point(const int x, const int y, const int thickness, const int RGB_value)
{
	int tn = thickness;
	if (tn < 1)
		tn = 1;		//处理下限
	/* 不卡点直径的上限，但是当上限超过一定大小时，画出的圆部分位置未实心 */

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

	/* 用画圆的方式模拟粗点 */
	for (level = 1; level <= tn_end; level++) {
		for (angle = 0; angle <= 360; angle += value) {
			/* 注意，系统的坐标轴，0°在圆的最下方 */
			x1 = x + (int)(level * sin(angle * PI / 180));
			y1 = y - (int)(level * cos(angle * PI / 180));

			/* 当半径很小时，角度变化不会引起int型的x1/y1变化，因此加判断语句，避免重复画同一像素点 */
			if (x1 != old_x1 || y1 != old_y1) {
				old_x1 = x1;
				old_y1 = y1;
				hdc_base_point(x1, y1);
				++count;
		}
	}
}
#if 0
	/* 放开此注释，可以看到一个粗点用了几个像素点组成 */
	cct_gotoxy(0, 41);
	printf("count=%d           ", count);
	getchar();
#endif
}

/* -------------------------------------------------------------------------
	给出下列函数的实现，函数名及参数表不准改动
	1、不需要调用系统的其他有关图形操作的函数
	2、下列函数的实现都基于hdc_base_point/hdc_base_line函数的组合
	3、想一想，是不是所有函数都需要给出独立的实现过程？应该先实现哪些函数？
	4、填充是实现中最复杂的部分
	5、系统的角度与函数参数中的角度含义相差180°
   ------------------------------------------------------------------------- */

/***************************************************************************
  函数名称：
  功    能：画线段
  输入参数：const int x1		：起点的x
            const int y1		：起点的y
			const int x2		：终点的x
			const int y2		：终点的y
			const int thickness	：线段的粗细（有缺省值）
			const int RGB_value	：线段的颜色（有缺省值）
  返 回 值：
  说    明：本函数可以用基于hdc_point的组合（速度慢）
                  也可以用hdc_base_point/hdc_base_line的组合（速度快）
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
  函数名称：
  功    能：给出三点的坐标，画一个三角形
  输入参数：const int x1		：第1个点的x
            const int y1		：第1个点的y
			const int x2		：第2个点的x
			const int y2		：第2个点的y
			const int x3		：第3个点的x
			const int y3		：第3个点的y
			bool filled			：是否需要填充（有缺省值）
			const int thickness	：边的粗细（有缺省值）
			const int RGB_value	：颜色（有缺省值）
  返 回 值：
  说    明：不判断三点是否共线，如果共线，划出一条直线即可
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

		//排序
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
  函数名称：
  功    能：给出左上角坐标及宽度、高度，画出一个长方形
  输入参数：const int left_up_x			：左上角x
            const int left_up_y			：左上角y
			const int width				：宽度
			const int high				：高度
			const int rotation_angles	：以左上角为支点，与x轴的旋转倾角（向下转为正）
			bool filled					：是否需要填充（有缺省值）
			const int thickness			：边的粗细（有缺省值）
			const int RGB_value			：颜色（有缺省值）
  返 回 值：
  说    明：
***************************************************************************/
void hdc_rectangle(const int left_up_x, const int left_up_y, const int width, const int high, const int rotation_angles, const bool filled, const int thickness, const int RGB_value)
{
	int angle = rotation_angles;

	//转成正数
	while (angle < 0)
		angle += 360;

	//定义剩下各点
	int right_up_x = (int)(left_up_x + width * cos(angle * PI / 180));
	int right_up_y = (int)(left_up_y + width * sin(angle * PI / 180));
	int left_down_x = (int)(left_up_x - high * sin(angle * PI / 180));
	int left_down_y = (int)(left_up_y + high * cos(angle * PI / 180));
	int right_down_x = (int)(left_up_x + width * cos(angle * PI / 180) - high * sin(angle * PI / 180));
	int right_down_y = (int)(left_up_y + high * cos(angle * PI / 180) + width * sin(angle * PI / 180));

	//画边线
	//上边线
	hdc_line(left_up_x, left_up_y, right_up_x, right_up_y, thickness, RGB_value);
	//左边线
	hdc_line(left_up_x, left_up_y, left_down_x, left_down_y, thickness, RGB_value);
	//右边线
	hdc_line(right_up_x, right_up_y, right_down_x, right_down_y, thickness, RGB_value);
	//下边线
	hdc_line(left_down_x, left_down_y, right_down_x, right_down_y, thickness, RGB_value);

	//画填充
	if (filled) {
		for (int i = 1; i < high; i++) {
			//对左边
			int x_left = (left_up_x * (high - i) + left_down_x * i) / high;
			int y_left = (left_up_y * (high - i) + left_down_y * i) / high;
			//对右边
			int x_right = (right_up_x * (high - i) + right_down_x * i) / high;
			int y_right = (right_up_y * (high - i) + right_down_y * i) / high;

			hdc_line(x_left, y_left, x_right, y_right, 2, RGB_value);
		}
	}
}

/***************************************************************************
  函数名称：
  功    能：给出左上角坐标及边长，画出一个长方形
  输入参数：const int left_up_x			：左上角x
			const int left_up_y			：左上角y
			const int length			：边长
			const int rotation_angles	：以左上角为支点，与x轴的旋转倾角（向下转为正）（有缺省值）
			const bool filled			：是否需要填充（有缺省值）
			const int thickness			：边的粗细（有缺省值）
			const int RGB_value			：颜色（有缺省值）
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void hdc_square(const int left_up_x, const int left_up_y, const int length, const int rotation_angles, const bool filled, const int thickness, const int RGB_value)
{
	int angle = rotation_angles;

	//转成正数
	while (angle < 0)
		angle += 360;

	//定义剩下各点
	int right_up_x = (int)(left_up_x + length * cos(angle * PI / 180));
	int right_up_y = (int)(left_up_y + length * sin(angle * PI / 180));
	int left_down_x = (int)(left_up_x - length * sin(angle * PI / 180));
	int left_down_y = (int)(left_up_y + length * cos(angle * PI / 180));
	int right_down_x = (int)(left_up_x + length * cos(angle * PI / 180) - length * sin(angle * PI / 180));
	int right_down_y = (int)(left_up_y + length * cos(angle * PI / 180) + length * sin(angle * PI / 180));

	//画边线
	//上边线
	hdc_line(left_up_x, left_up_y, right_up_x, right_up_y, thickness, RGB_value);
	//左边线
	hdc_line(left_up_x, left_up_y, left_down_x, left_down_y, thickness, RGB_value);
	//右边线
	hdc_line(right_up_x, right_up_y, right_down_x, right_down_y, thickness, RGB_value);
	//下边线
	hdc_line(left_down_x, left_down_y, right_down_x, right_down_y, thickness, RGB_value);

	//画填充
	if (filled) {
		for (int i = 1; i < length; i++) {
			//对左边
			int x_left = (left_up_x * (length - i) + left_down_x * i) / length;
			int y_left = (left_up_y * (length - i) + left_down_y * i) / length;
			//对右边
			int x_right = (right_up_x * (length - i) + right_down_x * i) / length;
			int y_right = (right_up_y * (length - i) + right_down_y * i) / length;

			hdc_line(x_left, y_left, x_right, y_right, 2, RGB_value);
		}
	}
}

/***************************************************************************
  函数名称：
  功    能：按照给出的参数画一段圆弧
  输入参数：const int point_x		：圆心的x
            const int point_y		：圆心的y
			const int radius		：半径
			const int angle_begin	：起始角度（以圆的最上方为0°，顺时针为正，注意：与系统坐标差了180°!!!）（有缺省值）
			const int angle_end		：结束角度（同上）（有缺省值）
			const int thickness		：粗细（有缺省值）
			const int RGB_value		：颜色（有缺省值）
  返 回 值：
  说    明：
***************************************************************************/
void hdc_arc(const int point_x, const int point_y, const int radius, const int angle_begin, const int angle_end, const int thickness, const int RGB_value)
{
	int angle_begin_new = angle_begin;
	int angle_end_new = angle_end;
	int angle;

	//转成正数
	while (angle_begin_new < 0)
		angle_begin_new += 360;
	while (angle_end_new < 0)
		angle_end_new += 360;

	//转成最小等角
	while (angle_begin_new >= 360)
		angle_begin_new -= 360;
	while (angle_end_new >= 360)
		angle_end_new -= 360;

	//判断圆弧的长度
	if (angle_begin_new >= angle_end_new)
		angle = angle_end_new - angle_begin_new + 360;
	else
		angle = angle_end_new - angle_begin_new;

	//设置采样精度
	int precision;
	if (radius * thickness >= 1080)
		precision = 2;
	else
		precision = 1;

	//画弧
	for (int i = 0; i <= angle * PI * radius / 180; i += precision) {
		int x = point_x + (int)(radius * sin((double)(i) / radius + angle_begin_new * PI / 180));
		int y = point_y - (int)(radius * cos((double)(i) / radius + angle_begin_new * PI / 180));
		hdc_point(x, y, thickness, RGB_value);
	}
}

/***************************************************************************
  函数名称：
  功    能：按照给出的参数画一个扇形
  输入参数：const int point_x		：圆心的x
			const int point_y		：圆心的y
			const int radius		：半径
			const int angle_begin	：起始角度（以圆的最上方为0°，顺时针为正，注意：与系统坐标差了180°!!!）（有缺省值）
			const int angle_end		：结束角度（同上）（有缺省值）
			const bool filled		：是否需要填充（有缺省值）
			const int thickness		：粗细（有缺省值）
			const int RGB_value		：颜色（有缺省值）
  输入参数：
  返 回 值：
  说    明：当起始/结束角度差值为360的倍数时，不画两条边
***************************************************************************/
void hdc_sector(const int point_x, const int point_y, const int radius, const int angle_begin, const int angle_end, const bool filled, const int thickness, const int RGB_value)
{
	int angle_begin_new = angle_begin;
	int angle_end_new = angle_end;
	int angle;

	//转成正数
	while (angle_begin_new < 0)
		angle_begin_new += 360;
	while (angle_end_new < 0)
		angle_end_new += 360;

	//转成最小等角
	while (angle_begin_new >= 360)
		angle_begin_new -= 360;
	while (angle_end_new >= 360)
		angle_end_new -= 360;

	//判断圆弧的长度
	if (angle_begin_new >= angle_end_new)
		angle = angle_end_new - angle_begin_new + 360;
	else
		angle = angle_end_new - angle_begin_new;

	//画两边(如果有的话)
	if (angle != 360) {
		int x = point_x + (int)(radius * sin(angle_begin_new * PI / 180));
		int y = point_y - (int)(radius * cos(angle_begin_new * PI / 180));
		hdc_line(point_x, point_y, x, y, thickness, RGB_value);
		x = point_x + (int)(radius * sin(angle_end_new * PI / 180));
		y = point_y - (int)(radius * cos(angle_end_new * PI / 180));
		hdc_line(point_x, point_y, x, y, thickness, RGB_value);
	}

	//画弧

	//设置以圆弧长转换的起始角,以统一同半径不同起点的圆弧上各点位置
	double angle_begin_double = 0;
	for (double i = 0; i < 2 * PI * radius; ++i) {
		if (i / radius * 180 / PI >= angle_begin_new) {
			angle_begin_double = i / radius * 180 / PI;
			break;
		}
	}

	//打印圆弧部分
	for (int i = 0; i <= angle * PI * radius / 180; ++i) {
		int x = point_x + (int)(radius * sin((double)(i) / radius + angle_begin_double * PI / 180));
		int y = point_y - (int)(radius * cos((double)(i) / radius + angle_begin_double * PI / 180));
		hdc_point(x, y, thickness, RGB_value);
	}

	//画实心
	if (filled) {
		for (int i = 0; i <= angle * PI * radius / 180; ++i) {
			int x = point_x + (int)(radius * sin((double)(i) / radius + angle_begin_double * PI / 180));
			int y = point_y - (int)(radius * cos((double)(i) / radius + angle_begin_double * PI / 180));
			hdc_line(x, y, point_x, point_y, 2, RGB_value);
		}
	}
}

/***************************************************************************
  函数名称：
  功    能：按照给出的参数画一个圆
  输入参数：const int point_x		：圆心的x
			const int point_y		：圆心的y
			const int radius		：半径
			const bool filled		：是否需要填充（有缺省值）
			const int thickness		：粗细（有缺省值）
			const int RGB_value		：颜色（有缺省值）
  返 回 值：
  说    明：
***************************************************************************/
void hdc_circle(const int point_x, const int point_y, const int radius, const bool filled, const int thickness, const int RGB_value)
{
	//调用画圆弧函数
	hdc_sector(point_x, point_y, radius, 0, 360, filled, thickness, RGB_value);
}

/***************************************************************************
  函数名称：
  功    能：按照给出的参数画一个椭圆
  输入参数：const int point_x			：圆心的x
			const int point_y			：圆心的y
			const int radius_a			：平行于X轴的半径
			const int radius_b			：平行于Y轴的半径
			const int rotation_angles	：以圆心为支点，与x轴的旋转倾角（向下转为正）（有缺省值）
			const bool filled			：是否需要填充（有缺省值）
			const int thickness			：粗细（有缺省值）
			const int RGB_value			：颜色（有缺省值）
  返 回 值：
  说    明：
***************************************************************************/
void hdc_ellipse(const int point_x, const int point_y, const int radius_a, const int radius_b, const int rotation_angles, const bool filled, const int thickness, const int RGB_value)
{
	//得出焦半径
	double radius_c = sqrt(fabs(radius_a * radius_a - radius_b * radius_b));
	//设置旋转角
	int angle = rotation_angles;

	//把角度转成正数
	while (angle < 0)
		angle += 360;
	//把角度转成最小值
	while (angle >= 360)
		angle -= 360;

	//取得最长值
	int radius_max = radius_a > radius_b ? radius_a : radius_b;
	double F_x_1 = point_x, F_y_1 = point_y;
	double F_x_2 = point_x, F_y_2 = point_y;

	//根据a、b大小分三种情况
	if (radius_a > radius_b) {
		//焦点坐标旋转
		//左
		F_x_1 = point_x - radius_c * cos(angle * PI / 180);
		F_y_1 = point_y - radius_c * sin(angle * PI / 180);
		//右
		F_x_2 = point_x + radius_c * cos(angle * PI / 180);
		F_y_2 = point_y + radius_c * sin(angle * PI / 180);
	}
	else if (radius_a < radius_b) {
		//焦点坐标旋转
		//上
		F_x_1 = point_x + radius_c * sin(angle * PI / 180);
		F_y_1 = point_y - radius_c * cos(angle * PI / 180);
		//下
		F_x_2 = point_x - radius_c * sin(angle * PI / 180);
		F_y_2 = point_y + radius_c * cos(angle * PI / 180);
	}
	else {
		hdc_circle(point_x, point_y, radius_a, filled, thickness, RGB_value);
		return;
	}

	//判断正方形区域内的点，在椭圆上则画出
	//取左上角点的坐标
	int left_top_x = point_x - radius_max;
	int left_top_y = point_y - radius_max;

	for (int j = 0; j < radius_max * 2 + 1; ++j) {
		for (int i = 0; i < radius_max * 2 + 1; ++i) {
			//当前点的坐标
			int x = i + left_top_x;
			int y = j + left_top_y;
			//到焦点的距离
			double l1 = sqrt(pow(x - F_x_1, 2) + pow(y - F_y_1, 2));
			double l2 = sqrt(pow(x - F_x_2, 2) + pow(y - F_y_2, 2));
			//判断是否在椭圆上
			if (fabs(l1 + l2 - 2 * radius_max) < 1)
				hdc_point(x, y, thickness, RGB_value);
		}
	}

	//画填充
	if (filled) {
		for (int j = 0; j < radius_max * 2 + 1; ++j) {
			//找同一行最左和最右的点
			int x_max = left_top_x;
			int x_min = left_top_x;
			int count = 0;
			for (int i = 0; i < radius_max * 2 + 1; ++i) {
				//当前点的坐标
				int x = i + left_top_x;
				int y = j + left_top_y;
				//到焦点的距离
				double l1 = sqrt(pow(x - F_x_1, 2) + pow(y - F_y_1, 2));
				double l2 = sqrt(pow(x - F_x_2, 2) + pow(y - F_y_2, 2));
				//判断是否在椭圆内
				//找出最左和最右的点，连线，提高效率
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
