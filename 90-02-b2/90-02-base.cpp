/* 2151613 毛宇录 计科 */

#include "90-02-b2.h"

void pf1()
{
	int rank;
	int mine[row_max][col_max];
	int mine_open[row_max][col_max];

	cct_cls();
	game_info_input(rank);
	init_array(mine, mine_open, rank);
	cct_cls();
	show_innner_array_command_line(mine, rank, 1);
	end_with_enter();
}

void pf2()
{
	int rank;
	int mine[row_max][col_max];
	int mine_open[row_max][col_max];

	cct_cls();
	game_info_input(rank);
	cct_cls();
	show_innner_array_command_line(mine, rank);
	char px, py;
	get_rc_command_line(px, py, rank);
	init_array(mine, mine_open, rank, px, py);
	uncover(mine, mine_open, px, py, rank);
	show_open_array_command_line(mine, mine_open, rank);
	end_with_enter();
}

void pf3()
{
	int rank;
	int ret = 0;
	int mine[row_max][col_max];
	int mine_open[row_max][col_max];

	cct_cls();
	game_info_input(rank);
	cct_cls();
	show_innner_array_command_line(mine, rank);
	int count = 0;
	while (1) {
		char px, py;
		if (get_rc_command_line(px, py, rank))
			break;
		if(!count)
			init_array(mine, mine_open, rank, px, py);
		ret = uncover(mine, mine_open, px, py, rank);
		show_open_array_command_line(mine, mine_open, rank);
		if (ret)
			break;
		if(check_end(mine_open,rank))
			break;
		++count;
	}
	if (ret)
		cout << "\n你输了!游戏结束" << endl;
	else
		cout << "\n恭喜胜利!游戏结束" << endl;
	end_with_enter();
}

void pf4()
{
	int rank;
	int ret = 0;
	int mine[row_max][col_max];
	int mine_open[row_max][col_max];

	cct_cls();
	game_info_input(rank);
	cct_cls();
	show_innner_array_command_line(mine, rank);
	int count = 0;

	//记录时间
	clock_t startTime, endTime;
	//计时开始
	startTime = clock();

	while (1) {
		char px, py;
		if (get_rc_command_line(px, py, rank))
			break;
		if (!count)
			init_array(mine, mine_open, rank, px, py);
		ret = uncover(mine, mine_open, px, py, rank);
		show_open_array_command_line(mine, mine_open, rank);
		if (ret)
			break;
		if (check_end(mine_open, rank))
			break;
		++count;
	}
	if (ret)
		cout << "\n你输了!游戏结束" << endl;
	else
		cout << "\n恭喜胜利!游戏结束" << endl;

	endTime = clock();//计时结束
	cout << "用时：" << (double)(endTime - startTime) / CLOCKS_PER_SEC << "秒\n";

	end_with_enter();
}