//2151613 �ƿ� ë��¼

#include "90-02-b1.h"

const char* msg1 = "\n\n��ǰ����(��ͬɫ��ʶ)��                       \n";
const char* msg2 = "\n\n��ֵͬ�鲢�������(��ͬɫ��ʶ)��             \n";
const char* msg3 = "\n\n���������飺                               \n";

const block_display_info bdi_num[7] = {
	{0, NULL, 1},
	{1, NULL, 0},
	{2, NULL, 0},
	{3, NULL, 0},
	{4, NULL, 0},
	{5, NULL, 0},
	{-1, NULL, NULL},
};

const block_display_info bdi_num_signed[3] = {
	{0, NULL, 0},
	{1, "*\0", 0},
	{-1, NULL, NULL},
};


void pfA()
{
	int row, col;  //����
	char px, py;  //����
	putin(&row, &col, NULL, row_min, row_max, col_min, col_max, NULL, NULL);  //����
	int num[row_max][col_max] = { 0 }; //��������
	int num_signed[row_max][col_max] = { 0 }; //������������
	init_array(&num[0][0], row, col, col_max, number_count);  //��ʼ���ڲ����� 
	boundary_command_line(&num[0][0], row, col, col_max, bdi_num, "\n��ǰ���飺\n");  //��ӡ����
	xy(&px, &py, row, col, &num[0][0], col_max);  //��������
	sign_command_line((px - 'A') * col_max + py - '0', row, &num[0][0], &num_signed[0][0], row_max, col_max);//����ͬ
	show_color_command_line(&num[0][0], &num_signed[0][0], row, col, col_max, msg1);  //��ӡ��ɫ����
	end();
}

void pfB()
{
	int row, col;  //����
	char px, py;  //����
	int score = 0;
	putin(&row, &col, NULL, row_min, row_max, col_min, col_max, NULL, NULL);  //����
	int num[row_max][col_max] = { 0 }; //��������
	int num_signed[row_max][col_max] = { 0 }; //������������
	init_array(&num[0][0], row, col, col_max, number_count);  //��ʼ���ڲ����� 
	boundary_command_line(&num[0][0], row, col, col_max, bdi_num, "\n��ǰ���飺\n");  //��ӡ����
	xy(&px, &py, row, col, &num[0][0], col_max);  //��������
	sign_command_line((px - 'A') * col_max + py - '0', row, &num[0][0], &num_signed[0][0], row_max, col_max);//����ͬ
	boundary_command_line(&num_signed[0][0], row, col, col_max, bdi_num_signed, "\n���ҽ�����飺\n");  //��ӡ����
	show_color_command_line(&num[0][0], &num_signed[0][0], row, col, col_max, msg1);  //��ӡ��ɫ����
	int val;//���շ���ֵ
	char buf[80] = {};//�洢�ַ���
	sprintf_s(buf, "%s%c%c%s", "��ȷ���Ƿ��", px, py, "����Χ����ֵͬ����(Y/N/Q)��");
	val = confirm_command_line(buf);
	switch (val) {
		case 0:
			eliminate(&num[0][0], &num_signed[0][0]);//��ֵ����
			show_color_command_line(&num[0][0], &num_signed[0][0], row, col, col_max, msg2);  //��ӡ��ɫ����
			cout << "\n���ε÷֣�" << score_count(&score, &num_signed[0][0]);
			cout << " �ܵ÷֣�" << score << endl;//�Ʒ�
			confirm_press_enter("\n\n���س������������������...");
			mov_array(&num[0][0], row, col, UP_TO_DOWN, col_max); //����
			mov_array(&num[0][0], row, col, RIGHT_TO_LEFT, col_max); //����
			show_color_command_line(&num[0][0], &num_signed[0][0], row, col, col_max, msg3);  //��ӡ��ɫ����
			break;
		case 1:
			break;
		case 2:
			break;
	}
	end();
}

void pfC()
{
	int row, col;  //����
	char px, py;  //����
	int score = 0;
	putin(&row, &col, NULL, row_min, row_max, col_min, col_max, NULL, NULL);  //����
	int num[row_max][col_max] = { 0 }; //��������
	int num_signed[row_max][col_max] = { 0 }; //������������
	int val;//���շ���ֵ
	char buf[80] = {};//�洢�ַ���
	init_array(&num[0][0], row, col, col_max, number_count);  //��ʼ���ڲ����� 
	while (1) {
		boundary_command_line(&num[0][0], row, col, col_max, bdi_num, "\n��ǰ���飺\n");  //��ӡ����
		xy(&px, &py, row, col, &num[0][0], col_max);  //��������
		sign_command_line((px - 'A') * col_max + py - '0', row, &num[0][0], &num_signed[0][0], row_max, col_max);//����ͬ
		boundary_command_line(&num_signed[0][0], row, col, col_max, bdi_num_signed, "\n���ҽ�����飺\n");  //��ӡ����
		show_color_command_line(&num[0][0], &num_signed[0][0], row, col, col_max, msg1);  //��ӡ��ɫ����
		sprintf_s(buf, "%s%c%c%s", "��ȷ���Ƿ��", px, py, "����Χ����ֵͬ����(Y/N/Q)��");
		val = confirm_command_line(buf);
		if (val == 0) {
			eliminate(&num[0][0], &num_signed[0][0]);//��ֵ����
			show_color_command_line(&num[0][0], &num_signed[0][0], row, col, col_max, msg2);  //��ӡ��ɫ����
			cout << "\n���ε÷֣�" << score_count(&score, &num_signed[0][0]);
			cout << " �ܵ÷֣�" << score << endl;//�Ʒ�
			confirm_press_enter("\n\n���س������������������...");
			mov_array(&num[0][0], row, col, UP_TO_DOWN, col_max); //����
			mov_array(&num[0][0], row, col, RIGHT_TO_LEFT, col_max); //����
			show_color_blank_command_line(&num[0][0], row, col, col_max, msg3);  //��ӡ��ɫ����
			reset_num_signed(&num_signed[0][0]);
		}
		else if (val == 1)
			continue;
		else if (val == 2)
			break;
		if (!is_end(row, col, &num[0][0], col_max, "\n\n�޿���������Ϸ����\n")) {
			cout << "ʣ��������" << remain_block_num(&num[0][0]) << " ";
			cout << "�����÷֣�" << score_end(&score, &num[0][0], row, col);
			cout << " �ܵ÷֣�" << score << endl;
			break;
		}
		confirm_press_enter("\n�����������������س���������һ�ε�����...\n");
	}
	end();
}