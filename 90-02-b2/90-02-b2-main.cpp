/* 2151613 ë��¼ �ƿ� */

#include "90-02-b2.h"

const char* menu_item[] = {
	"1.ѡ��ģʽ����ʾ�ڲ�����\n",
	"2.����һ��λ�ã���ʾ������\n",
	"3.�ڲ����������\n",
	"4.�ڲ����������棨��ǡ�����ʱ�䣩\n",
	"5.������ܣ���ʾ�ڲ�����\n",
	"6.������λ�úͺϷ��ԣ��Լ�������\n",
	"7.�����һ�Σ���ʾ������\n",
	"8.����������Ϸ��֧���Ҽ���ǣ��ж���Ϸ����\n",
	"9.������Ϸ�������������ո񡢽�����ʾʱ��\n",
	"0.�˳���Ϸ\n",
	NULL
};
const char* choice = "1234567890";

int main()
{
	srand((unsigned)time(NULL));
	while (1) {
		cct_cls();
		cct_setconsoleborder(85, 47);
		char sel = menu(menu_item, choice);
		switch (sel) {
			case '1':
				pf1();
				break;
			case '2':
				pf2();
				break;
			case '3':
				pf3();
				break;
			case '4':
				pf4();
				break;
			case '5':
				pf5();
				break;
			case '6':
				pf6();
				break;
			case '7':
				pf7();
				break;
			case '8':
				pf8();
				break;
			case '9':
				pf9();
				break;
		}
		if (sel == '0')
			break;
	}
	return 0;
}