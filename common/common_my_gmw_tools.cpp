/*2151613 ë��¼ �ƿ�*/
#include "../include/common_my_gmw_tools.h"

void my_read_keyboard(int& keycode1, int& keycode2)
{
	static const HANDLE __hin = GetStdHandle(STD_INPUT_HANDLE);		//ȡ��׼�����豸��Ӧ�ľ��

	INPUT_RECORD InputRec;
	DWORD        res;

	while (1) {
		/* ��hin�ж�����״̬��������ꡢ���̵ȣ� */
		ReadConsoleInput(__hin, &InputRec, 1, &res);

		if (InputRec.EventType == KEY_EVENT) {
			keycode1 = 0x00;
			keycode2 = 0x00;
			if (InputRec.Event.KeyEvent.bKeyDown) { // ֻ�ڰ���ʱ�жϣ�����ʱ���ж�
				switch (InputRec.Event.KeyEvent.wVirtualKeyCode) {
					case VK_UP:
						keycode1 = 0xe0;
						keycode2 = KB_ARROW_UP;		//ģ�� _getch()��ʽ���ص��������룬�ֱ���224��0xE0����72��0x48��
						break;
					case VK_DOWN:
						keycode1 = 0xe0;
						keycode2 = KB_ARROW_DOWN;	//ģ�� _getch()��ʽ���ص��������룬�ֱ���224��0xE0����80��0x50��
						break;
					case VK_LEFT:
						keycode1 = 0xe0;
						keycode2 = KB_ARROW_LEFT;	//ģ�� _getch()��ʽ���ص��������룬�ֱ���224��0xE0����75��0x4B��
						break;
					case VK_RIGHT:
						keycode1 = 0xe0;
						keycode2 = KB_ARROW_RIGHT;	//ģ�� _getch()��ʽ���ص��������룬�ֱ���224��0xE0����77��0x4D��
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

				  /* �Ǽ�ͷ��ֱ�ӷ���ASCII��ʽ��Fn��Insert��Delete�Ⱦ�δ���� */
				if (keycode1 == 0)
					keycode1 = InputRec.Event.KeyEvent.uChar.AsciiChar;

				return;
			} //end of if (KEYDOWN)
		} // end of if (�����¼�)
	}
}
