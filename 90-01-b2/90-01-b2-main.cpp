/*2151613 �ƿ� ë��¼*/

#include "90-01-b2.h"
#include "../include/common_input.h"
#include "../include/common_class_of_dispel.h"

const char* menu_item[] = {
		"1.�������ҳ��ɺϳ����ʶ���ǵݹ飩\n",
		"2.�������ҳ��ɺϳ����ʶ���ݹ飩\n",
		"3.���������һ�κϳɣ��ֲ�����ʾ��\n",
		"4.�����������棨�ֲ�����ʾ��\n",
		"5.αͼ�ν�����ʾ��ʼ���飨�޷ָ��ߣ�\n",
		"6.αͼ�ν�����ʾ��ʼ���飨�зָ��ߣ�\n",
		"7.αͼ�ν������ü�ͷ��/���ѡ��ǰɫ��\n",
		"8.αͼ�ν������һ�κϳɣ��ֲ��裩\n",
		"9.αͼ�ν���������(֧�����)\n",
		"0.�˳�\n",
		NULL
};

const char* choice = "0123456789";

int main()
{
	srand((unsigned)time(NULL));

	while (1) {
		cct_setconsoleborder(80, 40, 80, 999);
		char ch;
		cct_cls();
		ch = menu(menu_item, choice);
		if (ch == '0')
			break;
		if (ch == '1')
			mode1();
		if (ch == '2')
			mode2();
		if (ch == '3')
			mode3();
		if (ch == '4')
			mode4();
		if (ch == '5') {
			mode5();
			ch = getchar();
		}
		if (ch == '6') {
			mode6();
			ch = getchar();
		}
		if (ch == '7') {
			mode7();
			ch = getchar();
		}
		if (ch == '8') {
			mode8();
			ch = getchar();
		}
		if (ch == '9') {
			mode9();
			ch = getchar();
		}
		end();  //����
		cct_setcolor(0, 7);
	}
	cout << "\n�밴���������. . . ";
	char ch = _getch();
	return 0;
}
