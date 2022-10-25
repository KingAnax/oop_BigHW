/* 2151613 毛宇录 计科 */

#include "90-01-b2-gmw.h"

const char* menu_item[] = {
	"9.伪图形界面完整版\n",
	"0.退出\n",
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