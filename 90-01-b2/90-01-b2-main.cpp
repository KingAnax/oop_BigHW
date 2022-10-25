/*2151613 计科 毛宇录*/

#include "90-01-b2.h"
#include "../include/common_input.h"
#include "../include/common_class_of_dispel.h"

const char* menu_item[] = {
		"1.命令行找出可合成项并标识（非递归）\n",
		"2.命令行找出可合成项并标识（递归）\n",
		"3.命令行完成一次合成（分步骤显示）\n",
		"4.命令行完整版（分步骤显示）\n",
		"5.伪图形界面显示初始数组（无分隔线）\n",
		"6.伪图形界面显示初始数组（有分隔线）\n",
		"7.伪图形界面下用箭头键/鼠标选择当前色块\n",
		"8.伪图形界面完成一次合成（分步骤）\n",
		"9.伪图形界面完整版(支持鼠标)\n",
		"0.退出\n",
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
		end();  //结束
		cct_setcolor(0, 7);
	}
	cout << "\n请按任意键继续. . . ";
	char ch = _getch();
	return 0;
}
