/* 2151613 ë��¼ �ƿ� */
#include <iostream>
#include <cmath>
#include "../include/cmd_hdc_tools.h"

using namespace std;

//������Ϊ���౦��

//ͷ��
static void head(const int point_x, const int point_y)
{
	//�Ȼ�������
	hdc_set_pencolor(255, 251, 52);
	hdc_rectangle(point_x - 200, point_y - 250, 300, 300, 0, 1, 2);
	hdc_set_pencolor(0, 0, 0);
	hdc_rectangle(point_x - 200, point_y - 250, 300, 300, 0, 0, 2);

}

//�۾�
static void eyes(const int point_x, const int point_y)
{
	//�Ȼ���������Բ
	{
		//���
		{
			hdc_set_pencolor(255, 255, 255);
			hdc_ellipse(point_x - 100, point_y - 135, 50, 45, 10, 1, 2);
			//���
			hdc_set_pencolor(0, 0, 0);
			hdc_ellipse(point_x - 100, point_y - 135, 50, 45, 10, 0, 2);
		}

		//�ұ�
		{
			hdc_set_pencolor(255, 255, 255);
			hdc_ellipse(point_x - 5, point_y - 135, 50, 45, -10, 1, 2);
			//���
			hdc_set_pencolor(0, 0, 0);
			hdc_ellipse(point_x - 5, point_y - 135, 50, 45, -10, 0, 2);
		}
	}

	//�ڲ�������ͬ��Բ
	{
		//��Բ
		{
			hdc_set_pencolor(120, 190, 212);
			hdc_circle(point_x - 78, point_y - 135, 16, 1, 2);
			hdc_circle(point_x - 27, point_y - 135, 16, 1, 2);

			//������
			hdc_set_pencolor(0, 0, 0);
			hdc_circle(point_x - 78, point_y - 135, 16, 0, 2);
			hdc_circle(point_x - 27, point_y - 135, 16, 0, 2);
		}
		
		//��Բ
		{
			hdc_set_pencolor(0, 4, 35);
			hdc_circle(point_x - 78, point_y - 135, 5, 1, 2);
			hdc_circle(point_x - 27, point_y - 135, 5, 1, 2);
		}
	}
	
}

//���
static void tie(const int point_x, const int point_y)
{
	hdc_set_pencolor(255, 3, 11);

	//�����������������ƴ��
	hdc_triangle(point_x - 50, point_y + 105, point_x - 50, point_y + 40, point_x - 70, point_y + 90, 1, 2);
	hdc_triangle(point_x - 50, point_y + 105, point_x - 50, point_y + 40, point_x - 30, point_y + 90, 1, 2);
	hdc_set_pencolor(0, 0, 0);
	hdc_triangle(point_x - 50, point_y + 105, point_x - 50, point_y + 40, point_x - 70, point_y + 90, 0, 2);
	hdc_triangle(point_x - 50, point_y + 105, point_x - 50, point_y + 40, point_x - 30, point_y + 90, 0, 2);
	hdc_set_pencolor(255, 3, 11);
	hdc_line(point_x - 50, point_y + 55, point_x - 50, point_y + 104, 2);

	//�������������
	hdc_set_pencolor(255, 3, 11);
	hdc_triangle(point_x - 65, point_y + 40, point_x - 35, point_y + 40, point_x - 50, point_y + 55, 1, 2);
	hdc_set_pencolor(0, 0, 0);
	hdc_triangle(point_x - 65, point_y + 40, point_x - 35, point_y + 40, point_x - 50, point_y + 55, 0, 2);

}

//�·�
static void clothes(const int point_x, const int point_y)
{
	//���岿������������ƴ��

	//��ɫ����
	{
		hdc_set_pencolor(203, 136, 24);
		//�Ȼ����
		hdc_rectangle(point_x - 130, point_y + 140, 45, 12, 0, 1, 2);
		hdc_rectangle(point_x - 10, point_y + 140, 45, 12, 0, 1, 2);
		hdc_set_pencolor(0, 0, 0);
		hdc_rectangle(point_x - 130, point_y + 140, 45, 12, 0, 0, 2);
		hdc_rectangle(point_x - 10, point_y + 140, 45, 12, 0, 0, 2);

		//�ٻ��·�
		hdc_set_pencolor(203, 136, 24);
		hdc_rectangle(point_x - 200, point_y + 80, 300, 60, 0, 1, 2);
		hdc_set_pencolor(0, 0, 0);
		hdc_rectangle(point_x - 200, point_y + 80, 300, 60, 0, 0, 2);
	}

	//��ɫ����
	hdc_set_pencolor(255, 255, 255);
	hdc_rectangle(point_x - 200, point_y + 40, 300, 40, 0, 1, 2);
	hdc_set_pencolor(0, 0, 0);
	hdc_rectangle(point_x - 200, point_y + 40, 300, 40, 0, 0, 2);

	tie(point_x, point_y);

	//����
	hdc_set_pencolor(4, 0, 0);
	hdc_rectangle(point_x - 180, point_y + 90, 40, 10, 0, 1, 2);
	hdc_rectangle(point_x - 120, point_y + 90, 40, 10, 0, 1, 2);
	hdc_rectangle(point_x - 20, point_y + 90, 40, 10, 0, 1, 2);
	hdc_rectangle(point_x + 40, point_y + 90, 40, 10, 0, 1, 2);
}

//��������
static void sleeve(const int point_x, const int point_y)
{
	//��
	hdc_set_pencolor(255, 255, 255);
	hdc_rectangle(point_x - 200, point_y, 40, 50, 30, 1, 2);
	hdc_set_pencolor(0, 0, 0);
	hdc_rectangle(point_x - 200, point_y, 40, 50, 30, 0, 2);

	//��
	hdc_set_pencolor(255, 255, 255);
	hdc_rectangle(point_x + 68, point_y + 15, 40, 50, -30, 1, 2);
	hdc_set_pencolor(0, 0, 0);
	hdc_rectangle(point_x + 68, point_y + 15, 40, 50, -30, 0, 2);
}

//����
static void nose(const int point_x, const int point_y)
{
	//�����ҷֳ���������,ÿ����Բ������

	//��һ����
	hdc_set_pencolor(255, 251, 52);
	hdc_sector(point_x - 50, point_y - 110, 13, 220, 300, 1, 2);
	hdc_set_pencolor(0, 0, 0);
	hdc_arc(point_x - 50, point_y - 110, 13, 220, 300, 2);

	//�ڶ�����
	hdc_set_pencolor(255, 251, 52);
	hdc_sector(point_x - 52, point_y - 112, 11, 300, 75, 1, 2);
	hdc_set_pencolor(0, 0, 0);
	hdc_arc(point_x - 52, point_y - 112, 11, 300, 75, 2);

	//��������
	hdc_set_pencolor(255, 251, 52);
	hdc_sector(point_x - 61, point_y - 110, 21, 78, 145, 1, 2);
	hdc_set_pencolor(0, 0, 0);
	hdc_arc(point_x - 61, point_y - 110, 21, 78, 145, 2);

}

//���
static void mouth(const int point_x, const int point_y)
{
	//��Բ��
	hdc_set_pencolor(0, 0, 0);
	hdc_arc(point_x - 50, point_y - 200, 150, 130, 228, 2);

	//������ֱ��
	//��
	hdc_line(point_x - 167, point_y - 100, point_x - 155, point_y - 108);
	//��
	hdc_line(point_x + 68, point_y - 103, point_x + 56, point_y - 108);

}

//����
static void sock(const int point_x, const int point_y)
{
	//�Ȼ�������ɫ�ĳ����κ�������
	hdc_set_pencolor(255, 255, 255);
	hdc_rectangle(point_x - 115, point_y + 152, 15, 90, 0, 1, 2);
	hdc_triangle(point_x - 115, point_y + 232, point_x - 115, point_y + 242, point_x - 125, point_y + 242, 1, 2);
	hdc_rectangle(point_x + 5, point_y + 152, 15, 90, 0, 1, 2);
	hdc_triangle(point_x + 20, point_y + 232, point_x + 20, point_y + 242, point_x + 30, point_y + 242, 1, 2);

	hdc_set_pencolor(0, 0, 0);
	hdc_rectangle(point_x - 115, point_y + 152, 15, 90, 0, 0, 2);
	hdc_triangle(point_x - 115, point_y + 232, point_x - 115, point_y + 242, point_x - 125, point_y + 242, 0, 2);
	hdc_rectangle(point_x + 5, point_y + 152, 15, 90, 0, 0, 2);
	hdc_triangle(point_x + 20, point_y + 232, point_x + 20, point_y + 242, point_x + 30, point_y + 242, 0, 2);

	hdc_set_pencolor(255, 255, 255);
	hdc_line(point_x - 115, point_y + 233, point_x - 115, point_y + 241);
	hdc_line(point_x + 20, point_y + 233, point_x + 20, point_y + 241);

	//������
	hdc_set_pencolor(152, 145, 36);
	hdc_rectangle(point_x - 115, point_y + 190, 15, 8, 0, 1, 2);
	hdc_rectangle(point_x + 5, point_y + 190, 15, 8, 0, 1, 2);
	hdc_set_pencolor(84, 54, 23);
	hdc_rectangle(point_x - 115, point_y + 210, 15, 3, 0, 1, 2);
	hdc_rectangle(point_x + 5, point_y + 210, 15, 3, 0, 1, 2);
}

//���ϵİߵ�
static void pot(const int point_x, const int point_y)
{
	hdc_set_pencolor(172, 169, 5);
	//��һ
	hdc_ellipse(point_x - 160, point_y - 215, 20, 10, -60, 1, 2);
	//���
	hdc_ellipse(point_x - 178, point_y - 165, 12, 6, -60, 1, 2);
	//����
	hdc_ellipse(point_x - 155, point_y - 50, 12, 6, -60, 1, 2);
	//����
	hdc_ellipse(point_x - 150, point_y, 20, 15, -30, 1, 2);
	//��һ
	hdc_ellipse(point_x + 80, point_y - 210, 12, 5, -60, 1, 2);
	//�Ҷ�
	hdc_ellipse(point_x + 58, point_y - 50, 20, 12, -65, 1, 2);
	//����
	hdc_ellipse(point_x + 58, point_y + 12, 8, 4, -55, 1, 2);

}

//ѥ��
static void boots(const int point_x, const int point_y)
{
	hdc_set_pencolor(0, 0, 0);
	//ѥ������������
	hdc_rectangle(point_x - 125, point_y + 237, 25, 15, 0, 1, 2);

	hdc_rectangle(point_x + 5, point_y + 237, 25, 15, 0, 1, 2);
	//ѥ�м��������κͳ�����
	hdc_triangle(point_x - 125, point_y + 242, point_x - 125, point_y + 237, point_x - 135, point_y + 242, 1, 2);
	hdc_rectangle(point_x - 135, point_y + 242, 10, 10, 0, 1, 2);

	hdc_triangle(point_x + 5, point_y + 242, point_x + 5, point_y + 237, point_x + 15, point_y + 242, 1, 2);
	hdc_rectangle(point_x + 15, point_y + 242, 10, 10, 0, 1, 2);
	//ѥͷ������Բ
	hdc_ellipse(point_x - 142, point_y + 240, 20, 13, 0, 1, 2);

	hdc_ellipse(point_x + 47, point_y + 240, 20, 13, 0, 1, 2);
	//����
	hdc_rectangle(point_x - 140, point_y + 247, 10, 5, 0, 1, 2);

	hdc_rectangle(point_x + 30, point_y + 247, 10, 5, 0, 1, 2);
}

//����
static void dimple(const int point_x, const int point_y)
{
	//���Ȼ�Բ��
	hdc_set_pencolor(220, 22, 1);
	//��
	hdc_arc(point_x - 160, point_y - 105, 19, 230, 70, 2);
	//��
	hdc_arc(point_x + 60, point_y - 105, 19, 270, 150, 2);

	//�㼸��
	hdc_point(point_x - 173, point_y - 112, 5);
	hdc_point(point_x - 160, point_y - 120, 5);
	hdc_point(point_x - 164, point_y - 108, 5);

	hdc_point(point_x + 55, point_y - 117, 5);
	hdc_point(point_x + 70, point_y - 115, 5);
	hdc_point(point_x + 60, point_y - 110, 5);

}

//��
static void hands(const int point_x, const int point_y)
{
	//��
	{
		//��Բ������
		hdc_set_pencolor(255, 251, 52);
		hdc_ellipse(point_x - 205, point_y + 162, 12, 17, -20, 1, 2);
		hdc_set_pencolor(0, 0, 0);
		hdc_ellipse(point_x - 205, point_y + 162, 12, 17, -20, 0, 2);

		//�ֱ�
		hdc_set_pencolor(255, 251, 52);
		hdc_rectangle(point_x - 212, point_y + 40, 12, 107, 0, 1, 2);
		hdc_set_pencolor(0, 0, 0);
		hdc_rectangle(point_x - 212, point_y + 40, 12, 107, 0, 0, 2);
		hdc_set_pencolor(255, 251, 52);
		hdc_line(point_x - 212, point_y + 147, point_x - 200, point_y + 147, 2);

		//��ָ��
		hdc_set_pencolor(0, 0, 0);
		hdc_line(point_x - 206, point_y + 165, point_x - 200, point_y + 178, 2);
		hdc_arc(point_x - 206, point_y + 160, 6, 45, 200, 2);
		hdc_line(point_x - 206, point_y + 165, point_x - 210, point_y + 153, 2);
		hdc_line(point_x - 200, point_y + 163, point_x - 195, point_y + 175, 2);
	}
	//��
	{
		//��Բ������
		hdc_set_pencolor(255, 251, 52);
		hdc_ellipse(point_x + 106, point_y + 162, 12, 17, 20, 1, 2);
		hdc_set_pencolor(0, 0, 0);
		hdc_ellipse(point_x + 106, point_y + 162, 12, 17, 20, 0, 2);

		//�ֱ�
		hdc_set_pencolor(255, 251, 52);
		hdc_rectangle(point_x + 100, point_y + 40, 12, 107, 0, 1, 2);
		hdc_set_pencolor(0, 0, 0);
		hdc_rectangle(point_x + 100, point_y + 40, 12, 107, 0, 0, 2);
		hdc_set_pencolor(255, 251, 52);
		hdc_line(point_x + 100 , point_y + 147, point_x + 112, point_y + 147, 2);

		//��ָ��
		hdc_set_pencolor(0, 0, 0);
		hdc_line(point_x + 108, point_y + 165, point_x + 104, point_y + 178, 2);
		hdc_arc(point_x + 108 , point_y + 160, 6, 160, 315, 2);
		hdc_line(point_x + 108, point_y + 165, point_x + 112, point_y + 153, 2);
		hdc_line(point_x + 98, point_y + 178, point_x + 104, point_y + 161, 2);
	}

}



void hdc_draw_cartoon_2151613(const int base_x, const int base_y)
{
	hdc_cls();

	//����ͼ��˳�����������˳��
	hands(base_x, base_y);
	sleeve(base_x, base_y);
	head(base_x, base_y);
	eyes(base_x, base_y);
	clothes(base_x, base_y);
	mouth(base_x, base_y);
	dimple(base_x, base_y);
	sock(base_x, base_y);
	boots(base_x, base_y);
	pot(base_x, base_y);
	nose(base_x, base_y);
}
