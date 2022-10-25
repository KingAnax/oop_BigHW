/* 2151613 ë��¼ �ƿ� */

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
		cout << "\n������!��Ϸ����" << endl;
	else
		cout << "\n��ϲʤ��!��Ϸ����" << endl;
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

	//��¼ʱ��
	clock_t startTime, endTime;
	//��ʱ��ʼ
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
		cout << "\n������!��Ϸ����" << endl;
	else
		cout << "\n��ϲʤ��!��Ϸ����" << endl;

	endTime = clock();//��ʱ����
	cout << "��ʱ��" << (double)(endTime - startTime) / CLOCKS_PER_SEC << "��\n";

	end_with_enter();
}