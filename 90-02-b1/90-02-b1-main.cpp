//2151613 �ƿ� ë��¼

#include "90-02-b1.h"

const char* menu_item[] = {
	"A.�����з�ʽ�ҳ����������ʶ\n",
	"B.���������һ������\n",
	"C.���������һ�أ��ֲ�����ʾ��\n",
	"D.αͼ�ν����������ѡ��һ��ɫ�飨�޷ָ��ߣ�\n",
	"E.αͼ�ν����������ѡ��һ��ɫ�飨�зָ��ߣ�\n",
	"F.αͼ�ν��������һ�κϳɣ��ֲ��裩\n",
	"G.αͼ�ν���������\n",
	"Q.�˳�\n",
	NULL
};

const char* choice = "abcdefgqABCDEFGQ";

int main()
{
	while (1) {
		cct_cls();
		cct_setconsoleborder(85, 47);
		char sel = menu(menu_item, choice);
		switch (sel) {
			case 'a':
				pfA();
				break;
			case 'b':
				pfB();
				break;
			case 'c':
				pfC();
				break;
			case 'd':
				pfD();
				break;
			case 'e':
				pfE();
				break;
			case 'f':
				pfF();
				break;
			case 'g':
				pfG();
				break;
			case 'q':
				break;
			case 'A':
				pfA();
				break;
			case 'B':
				pfB();
				break;
			case 'C':
				pfC();
				break;
			case 'D':
				pfD();
				break;
			case 'E':
				pfE();
				break;
			case 'F':
				pfF();
				break;
			case 'G':
				pfG();
				break;
			case 'Q':
				break;
		}
		if (sel == 'q' || sel == 'Q')
			break;
	}
	return 0;
}
