/*2151613 毛宇录 计科*/
#include "../include/common_my_gmw_tools.h"

void my_read_keyboard(int& keycode1, int& keycode2)
{
	static const HANDLE __hin = GetStdHandle(STD_INPUT_HANDLE);		//取标准输入设备对应的句柄

	INPUT_RECORD InputRec;
	DWORD        res;

	while (1) {
		/* 从hin中读输入状态（包括鼠标、键盘等） */
		ReadConsoleInput(__hin, &InputRec, 1, &res);

		if (InputRec.EventType == KEY_EVENT) {
			keycode1 = 0x00;
			keycode2 = 0x00;
			if (InputRec.Event.KeyEvent.bKeyDown) { // 只在按下时判断，弹起时不判断
				switch (InputRec.Event.KeyEvent.wVirtualKeyCode) {
					case VK_UP:
						keycode1 = 0xe0;
						keycode2 = KB_ARROW_UP;		//模拟 _getch()方式返回的两个键码，分别是224（0xE0）和72（0x48）
						break;
					case VK_DOWN:
						keycode1 = 0xe0;
						keycode2 = KB_ARROW_DOWN;	//模拟 _getch()方式返回的两个键码，分别是224（0xE0）和80（0x50）
						break;
					case VK_LEFT:
						keycode1 = 0xe0;
						keycode2 = KB_ARROW_LEFT;	//模拟 _getch()方式返回的两个键码，分别是224（0xE0）和75（0x4B）
						break;
					case VK_RIGHT:
						keycode1 = 0xe0;
						keycode2 = KB_ARROW_RIGHT;	//模拟 _getch()方式返回的两个键码，分别是224（0xE0）和77（0x4D）
						break;
					case VK_PRIOR:
						keycode1 = 0xe0;
						keycode2 = KB_PAGE_UP;
						break;
					case VK_NEXT:
						keycode1 = 0xe0;
						keycode2 = KB_PAGE_DOWN;
						break;
					default:
						break;
				} //end of switch

				  /* 非箭头键直接返回ASCII形式（Fn、Insert、Delete等均未处理） */
				if (keycode1 == 0)
					keycode1 = InputRec.Event.KeyEvent.uChar.AsciiChar;

				return;
			} //end of if (KEYDOWN)
		} // end of if (键盘事件)
	}
}
