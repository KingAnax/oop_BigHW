//2151613 计科 毛宇录

#include "90-02-b1.h"

const char* menu_item[] = {
	"A.命令行方式找出可消除项并标识\n",
	"B.命令行完成一次消除\n",
	"C.命令行完成一关（分步骤显示）\n",
	"D.伪图形界面下用鼠标选择一个色块（无分隔线）\n",
	"E.伪图形界面下用鼠标选择一个色块（有分隔线）\n",
	"F.伪图形界面下完成一次合成（分步骤）\n",
	"G.伪图形界面完整版\n",
	"Q.退出\n",
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
