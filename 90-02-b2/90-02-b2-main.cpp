/* 2151613 毛宇录 计科 */

#include "90-02-b2.h"

const char* menu_item[] = {
	"1.选择模式，显示内部数组\n",
	"2.输入一个位置，显示打开区域\n",
	"3.内部数组基础版\n",
	"4.内部数组完整版（标记、运行时间）\n",
	"5.画出框架，显示内部数据\n",
	"6.检测鼠标位置和合法性，以及左键点击\n",
	"7.鼠标点击一次，显示打开区域\n",
	"8.允许连续游戏，支持右键标记，判断游戏结束\n",
	"9.完整游戏，标明雷数，空格、结束显示时间\n",
	"0.退出游戏\n",
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