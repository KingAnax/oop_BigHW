/*2151613 计科 毛宇录*/

#include "90-01-b1.h"
#include "../include/common_input.h"

const char* menu_item[] = {
        "1.基本解\n",
        "2.基本解(步数记录)\n",
        "3.内部数组显示(横向)\n",
        "4.内部数组显示(纵向+横向)\n",
        "5.图形解-预备-画三个圆柱\n",
        "6.图形解-预备-在起始柱上画n个盘子\n",
        "7.图形解-预备-第一次移动\n",
        "8.图形解-自动移动版本\n",
        "9.图形解-游戏版\n",
        "0.退出\n",
        NULL
};

const char* choice = "0123456789";

int main()
{
	/* demo中首先执行此句，将cmd窗口设置为40行x120列（缓冲区宽度120列，行数9000行，即cmd窗口右侧带有垂直滚动杆）*/
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
                cout << "从 " << qishi << " 移动到 " << mubiao << "，共 " << flour << " 层，延时设置为 " << speed;
                cct_gotoxy(0, 32);
                if(mode=='4')
                    cct_gotoxy(0, 17);
                cout << "初始:" << setw(17) << "";
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
            cout << "从 " << qishi << " 移动到 " << mubiao << ", 共 " << flour << " 层";
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
		cout << "按回车键继续";
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
