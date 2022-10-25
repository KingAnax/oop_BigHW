/* 2151613 ë��¼ �ƿ� */
#include <iostream>
#include <cmath>
#include <time.h>
#include "../include/cmd_hdc_tools.h"
#define Pi 3.1415926

using namespace std;

static void spiral(int point_x, int point_y, double a, double num, double precision, int thickness)
{
	int x, y;
	//����
	int x_old = 0, y_old = 0;
	for (double angle = precision; angle <= num ;angle += precision) {
		double angle_sqrt = sqrt(angle * Pi / 180);
		y = (int)(-a / angle_sqrt * cos(angle * Pi / 180) + point_y);
		x = (int)(-a / angle_sqrt * sin(angle * Pi / 180) + point_x);
		if (x_old != x || y_old != y) {
			hdc_set_pencolor(rand() % 256, rand() % 256, rand() % 256);
			hdc_point(x, y, thickness);
			y_old = y;
			x_old = x;
		}
	}
	//����
	for (double angle = precision; angle <= num; angle += precision) {
		double angle_sqrt = sqrt(angle * Pi / 180);
		y = (int)(a / angle_sqrt * cos(angle * Pi / 180) + point_y);
		x = (int)(a / angle_sqrt * sin(angle * Pi / 180) + point_x);
		if (x_old != x || y_old != y) {
			hdc_set_pencolor(rand() % 256, rand() % 256, rand() % 256);
			hdc_point(x, y, thickness);
			y_old = y;
			x_old = x;
		}
	}
	//����
	for (double angle = precision; angle <= num; angle += precision) {
		double angle_sqrt = sqrt(angle * Pi / 180);
		x = (int)(-a / angle_sqrt * cos(angle * Pi / 180) + point_x);
		y = (int)(-a / angle_sqrt * sin(angle * Pi / 180) + point_y);
		if (x_old != x || y_old != y) {
			hdc_set_pencolor(rand() % 256, rand() % 256, rand() % 256);
			hdc_point(x, y, thickness);
			y_old = y;
			x_old = x;
		}
	}
	//����
	for (double angle = precision; angle <= num; angle += precision) {
		double angle_sqrt = sqrt(angle * Pi / 180);
		x = (int)(a / angle_sqrt * cos(angle * Pi / 180) + point_x);
		y = (int)(a / angle_sqrt * sin(angle * Pi / 180) + point_y);
		if (x_old != x || y_old != y) {
			hdc_set_pencolor(rand() % 256, rand() % 256, rand() % 256);
			hdc_point(x, y, thickness);
			y_old = y;
			x_old = x;
		}
	}

	return;
}

void hdc_draw_Mathematical_curve_2151613()
{
	hdc_cls();
	srand((unsigned)time(NULL));
	spiral(400, 400, 80, 450, 0.05, 5);
	return;
}
