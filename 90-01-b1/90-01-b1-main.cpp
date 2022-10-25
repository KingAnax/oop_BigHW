/*2151613 �ƿ� ë��¼*/

#include "90-01-b1.h"
#include "../include/common_input.h"

const char* menu_item[] = {
        "1.������\n",
        "2.������(������¼)\n",
        "3.�ڲ�������ʾ(����)\n",
        "4.�ڲ�������ʾ(����+����)\n",
        "5.ͼ�ν�-Ԥ��-������Բ��\n",
        "6.ͼ�ν�-Ԥ��-����ʼ���ϻ�n������\n",
        "7.ͼ�ν�-Ԥ��-��һ���ƶ�\n",
        "8.ͼ�ν�-�Զ��ƶ��汾\n",
        "9.ͼ�ν�-��Ϸ��\n",
        "0.�˳�\n",
        NULL
};

const char* choice = "0123456789";

int main()
{
	/* demo������ִ�д˾䣬��cmd��������Ϊ40��x120�У����������120�У�����9000�У���cmd�����Ҳ���д�ֱ�����ˣ�*/
	cct_setconsoleborder(120, 40, 120, 9000);
    int speed = 0;
	char mode;

    mode = menu(menu_item, choice);

	while (mode != '0')
	{
		cout << "\n\n\n";
        int flour = 0;
        char qishi = '\0', mubiao = '\0', zhongjian = '\0';
        if (mode == '1' || mode == '2' || mode == '3' || mode == '4' || mode == '6' || mode == '7' || mode == '8' || mode == '9')
            speed = hanoi_shuru(&flour, &qishi, &zhongjian, &mubiao, mode);
        cct_setcursor(3);
        chushi(flour, qishi);
        if (mode == '1' || mode == '2' || mode == '3' || mode == '4' || mode == '8')
        {
            if (mode == '4' || mode == '8')
            {
                cct_cls();
                cout << "�� " << qishi << " �ƶ��� " << mubiao << "���� " << flour << " �㣬��ʱ����Ϊ " << speed;
                cct_gotoxy(0, 32);
                if(mode=='4')
                    cct_gotoxy(0, 17);
                cout << "��ʼ:" << setw(17) << "";
                hang();
                lie(mode);
                if(mode=='4')
                    speedtest();
            }
            if (mode == '8')
            {
                mode6(flour, qishi, mubiao);
                speedtest();
                cct_setcolor(COLOR_BLACK, COLOR_WHITE);
            }
            hanoi_main(flour, qishi, zhongjian, mubiao, mode);
        }
        else  if (mode == '5')
        {
            choose_mode(mode);
            cct_gotoxy(0, 18);
            cct_setcolor(COLOR_BLACK, COLOR_WHITE);
        }
        else if (mode == '6' || mode == '7')
        {
            cct_cls();
            cout << "�� " << qishi << " �ƶ��� " << mubiao << ", �� " << flour << " ��";
            if (mode == '6')
                choose_mode(mode, flour, qishi, mubiao, zhongjian);
            else
            {
                mode6(flour, qishi, mubiao);
                hanoi_main(flour, qishi, zhongjian, mubiao, mode);
            }
            cct_gotoxy(0, 18);
            cct_setcolor(COLOR_BLACK, COLOR_WHITE);
        }
        else if (mode == '9')
        {
            choose_mode(mode, flour, qishi, mubiao, zhongjian);
        }
        cct_setcursor(2);
		cout << "���س�������";
		mode = _getch();
		while (mode != '\r')
		{
			mode = _getch();
		}
		cct_cls();
		mode = menu(menu_item, choice);
	}
	return 0;
}
