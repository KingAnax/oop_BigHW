/* 2151613 ë��¼ �ƿ� */

#include "90-01-b2-gmw.h"

const char* menu_item[] = {
	"9.αͼ�ν���������\n",
	"0.�˳�\n",
	NULL
};

const char* choice = "90";

int main()
{
	while (1) {
		cct_cls();
		cct_setconsoleborder(85, 47);
		char sel = menu(menu_item, choice);
		switch (sel) {
			case '9':
				pf9();
				break;
			case '0':
				break;
		}
		if (sel == '0')
			break;
	}
	return 0;
}