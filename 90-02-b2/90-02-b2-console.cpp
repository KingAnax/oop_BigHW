/* 2151613 毛宇录 计科 */

#include "90-02-b2.h"

void pf5()
{
	int rank;
	int mine[row_max][col_max];
	int mine_open[row_max][col_max];

	cct_cls();
	game_info_input(rank);

	CONSOLE_GRAPHICS_INFO MyCGI;                            //声明一个CGI变量
	gmw_init(&MyCGI);                                       //做一个初始化
	gmw_set_rowcol(&MyCGI, rank_info[rank - 1].row, rank_info[rank - 1].col); //游戏区域设置
	gmw_set_color(&MyCGI, COLOR_BLACK, COLOR_WHITE);		//修改窗口颜色并级联修改游戏区域、上下状态栏
	gmw_set_font(&MyCGI, "新宋体", 16, 0);				    //TrueType字体（新宋体）宽度不需要，可任意设置
	gmw_set_frame_style(&MyCGI, 4, 2, true);				//每个色块区域宽度2列*高度2列，要分隔线
	gmw_set_frame_default_linetype(&MyCGI, 1);			    //设置框架线型为预置值1
	gmw_set_frame_color(&MyCGI, COLOR_HWHITE, COLOR_BLACK); //设置框架颜色
	gmw_set_rowno_switch(&MyCGI, true);					    //显示行号
	gmw_set_colno_switch(&MyCGI, true);					    //显示列标
	gmw_set_block_border_switch(&MyCGI, false);			    //设置色块不需要小边框
	gmw_set_status_line_switch(&MyCGI, TOP_STATUS_LINE);	//开启上状态栏
	gmw_set_status_line_switch(&MyCGI, LOWER_STATUS_LINE);	//开启下状态栏

	cct_setcursor(CURSOR_INVISIBLE);                        //设置光标不可见

	init_array(mine, mine_open, rank);

	gmw_draw_frame(&MyCGI);

	for (int i = 0; i < rank_info[rank - 1].row; ++i)
		for (int j = 0; j < rank_info[rank - 1].col; ++j)
			draw_block(&MyCGI, mine[i][j], i, j, 0);

	end_with_enter();
}

void pf6()
{
	int rank;
	int mine[row_max][col_max];
	int mine_open[row_max][col_max];

	cct_cls();
	game_info_input(rank);

	CONSOLE_GRAPHICS_INFO MyCGI;                            //声明一个CGI变量
	gmw_init(&MyCGI);                                       //做一个初始化
	gmw_set_rowcol(&MyCGI, rank_info[rank - 1].row, rank_info[rank - 1].col); //游戏区域设置
	gmw_set_color(&MyCGI, COLOR_BLACK, COLOR_WHITE);		//修改窗口颜色并级联修改游戏区域、上下状态栏
	gmw_set_font(&MyCGI, "新宋体", 16, 0);				    //TrueType字体（新宋体）宽度不需要，可任意设置
	gmw_set_frame_style(&MyCGI, 4, 2, true);				//每个色块区域宽度2列*高度2列，要分隔线
	gmw_set_frame_default_linetype(&MyCGI, 1);			    //设置框架线型为预置值1
	gmw_set_frame_color(&MyCGI, COLOR_HWHITE, COLOR_BLACK); //设置框架颜色
	gmw_set_rowno_switch(&MyCGI, true);					    //显示行号
	gmw_set_colno_switch(&MyCGI, true);					    //显示列标
	gmw_set_block_border_switch(&MyCGI, false);			    //设置色块不需要小边框
	gmw_set_status_line_switch(&MyCGI, TOP_STATUS_LINE);	//开启上状态栏
	gmw_set_status_line_switch(&MyCGI, LOWER_STATUS_LINE);	//开启下状态栏

	cct_setcursor(CURSOR_INVISIBLE);                        //设置光标不可见

	init_array(mine, mine_open, rank);

	gmw_draw_frame(&MyCGI);

	for (int i = 0; i < rank_info[rank - 1].row; ++i)
		for (int j = 0; j < rank_info[rank - 1].col; ++j)
			draw_block(&MyCGI, mine[i][j], i, j, 0);


	int MAction, MRow, MCol, KeyCode1, KeyCode2;
	int ret;

	while (1) {
		ret = gmw_read_keyboard_and_mouse(&MyCGI, MAction, MRow, MCol, KeyCode1, KeyCode2);
		if (ret == CCT_MOUSE_EVENT) {
			if (MAction == MOUSE_LEFT_BUTTON_CLICK)
				break;
		}
	}

	end_with_enter();
}

void pf7()
{
	int rank;
	int mine[row_max][col_max];
	int mine_open[row_max][col_max];

	cct_cls();
	game_info_input(rank);

	CONSOLE_GRAPHICS_INFO MyCGI;                            //声明一个CGI变量
	gmw_init(&MyCGI);                                       //做一个初始化
	gmw_set_rowcol(&MyCGI, rank_info[rank - 1].row, rank_info[rank - 1].col); //游戏区域设置
	gmw_set_color(&MyCGI, COLOR_BLACK, COLOR_WHITE);		//修改窗口颜色并级联修改游戏区域、上下状态栏
	gmw_set_font(&MyCGI, "新宋体", 16, 0);				    //TrueType字体（新宋体）宽度不需要，可任意设置
	gmw_set_frame_style(&MyCGI, 4, 2, true);				//每个色块区域宽度2列*高度2列，要分隔线
	gmw_set_frame_default_linetype(&MyCGI, 1);			    //设置框架线型为预置值1
	gmw_set_frame_color(&MyCGI, COLOR_HWHITE, COLOR_BLACK); //设置框架颜色
	gmw_set_rowno_switch(&MyCGI, true);					    //显示行号
	gmw_set_colno_switch(&MyCGI, true);					    //显示列标
	gmw_set_block_border_switch(&MyCGI, false);			    //设置色块不需要小边框
	gmw_set_status_line_switch(&MyCGI, TOP_STATUS_LINE);	//开启上状态栏
	gmw_set_status_line_switch(&MyCGI, LOWER_STATUS_LINE);	//开启下状态栏

	cct_setcursor(CURSOR_INVISIBLE);                        //设置光标不可见

	gmw_draw_frame(&MyCGI);

	for (int i = 0; i < rank_info[rank - 1].row; ++i)
		for (int j = 0; j < rank_info[rank - 1].col; ++j)
			draw_block(&MyCGI, mine[i][j], i, j, 1);


	int MAction, MRow, MCol, KeyCode1, KeyCode2;
	int ret;

	while (1) {
		ret = gmw_read_keyboard_and_mouse(&MyCGI, MAction, MRow, MCol, KeyCode1, KeyCode2);
		if (ret == CCT_MOUSE_EVENT) {
			if (MAction == MOUSE_LEFT_BUTTON_CLICK)
				break;
		}
	}

	char px, py;
	px = MRow + 'A';
	if (MCol < 9)
		py = MCol + '1';
	else
		py = MCol - 9 + 'a';

	init_array(mine, mine_open, rank, px, py);

	ret = uncover(mine, mine_open, px, py, rank);

	for (int i = 0; i < rank_info[rank - 1].row; ++i)
		for (int j = 0; j < rank_info[rank - 1].col; ++j)
			if(mine_open[i][j])
				draw_block(&MyCGI, mine[i][j], i, j, 0);

	cct_gotoxy(MyCGI.SLI.lower_start_x, MyCGI.SLI.lower_start_y);

	end_with_enter();
}

void pf8()
{
	int rank;
	int mine[row_max][col_max];
	int mine_open[row_max][col_max];
	int mine_sign[row_max][col_max];

	cct_cls();
	game_info_input(rank);

	for (int i = 0; i < rank_info[rank - 1].row; ++i)
		for (int j = 0; j < rank_info[rank - 1].col; ++j)
			mine_sign[i][j] = 0;

	CONSOLE_GRAPHICS_INFO MyCGI;                            //声明一个CGI变量
	gmw_init(&MyCGI);                                       //做一个初始化
	gmw_set_rowcol(&MyCGI, rank_info[rank - 1].row, rank_info[rank - 1].col); //游戏区域设置
	gmw_set_color(&MyCGI, COLOR_BLACK, COLOR_WHITE);		//修改窗口颜色并级联修改游戏区域、上下状态栏
	gmw_set_font(&MyCGI, "新宋体", 16, 0);				    //TrueType字体（新宋体）宽度不需要，可任意设置
	gmw_set_frame_style(&MyCGI, 4, 2, true);				//每个色块区域宽度2列*高度2列，要分隔线
	gmw_set_frame_default_linetype(&MyCGI, 1);			    //设置框架线型为预置值1
	gmw_set_frame_color(&MyCGI, COLOR_HWHITE, COLOR_BLACK); //设置框架颜色
	gmw_set_rowno_switch(&MyCGI, true);					    //显示行号
	gmw_set_colno_switch(&MyCGI, true);					    //显示列标
	gmw_set_block_border_switch(&MyCGI, false);			    //设置色块不需要小边框
	gmw_set_status_line_switch(&MyCGI, TOP_STATUS_LINE);	//开启上状态栏
	gmw_set_status_line_switch(&MyCGI, LOWER_STATUS_LINE);	//开启下状态栏

	cct_setcursor(CURSOR_INVISIBLE);                        //设置光标不可见

	gmw_draw_frame(&MyCGI);

	for (int i = 0; i < rank_info[rank - 1].row; ++i)
		for (int j = 0; j < rank_info[rank - 1].col; ++j)
			draw_block(&MyCGI, mine[i][j], i, j, 1);

	gmw_status_line(&MyCGI, TOP_STATUS_LINE, "ESC退出");

	int MAction, MRow, MCol, KeyCode1, KeyCode2;
	int ret;
	int count = 0;
	int flag_quit = 0;

	while (1) {
		while (1) {
			ret = read_keyboard_and_mouse(&MyCGI, MAction, MRow, MCol, KeyCode1, KeyCode2);
			if (ret == CCT_MOUSE_EVENT) {
				if (MAction == MOUSE_LEFT_BUTTON_CLICK)
					break;
				else if (MAction == MOUSE_RIGHT_BUTTON_CLICK) {
					ret = sign_mine(mine_sign, mine_open, MRow, MCol);
					if (ret) {
						if(mine_sign[MRow][MCol] == 1)
							draw_block(&MyCGI, mine[MRow][MCol], MRow, MCol, 2);
						else
							draw_block(&MyCGI, mine[MRow][MCol], MRow, MCol, 1);
					}
				}
			}
			else {
				if (KeyCode1 == 27) {
					flag_quit = 1;
					break;
				}
			}
		}

		if (flag_quit)
			break;

		char px, py;
		px = MRow + 'A';
		if (MCol < 9)
			py = MCol + '1';
		else
			py = MCol - 9 + 'a';

		if(!count)
			init_array(mine, mine_open, rank, px, py);

		if (!mine_sign[MRow][MCol]) {
			ret = uncover(mine, mine_open, px, py, rank);

			for (int i = 0; i < rank_info[rank - 1].row; ++i)
				for (int j = 0; j < rank_info[rank - 1].col; ++j)
					if (mine_open[i][j])
						draw_block(&MyCGI, mine[i][j], i, j, 0);
		}

		if (ret)
			break;
		if (check_end(mine, mine_open, mine_sign, rank))
			break;

		++count;
	}

	if (ret)
		gmw_status_line(&MyCGI, LOWER_STATUS_LINE, "\n你输了!游戏结束");
	else if(!flag_quit)
		gmw_status_line(&MyCGI, LOWER_STATUS_LINE, "\n恭喜胜利!游戏结束");

	cct_gotoxy(MyCGI.SLI.lower_start_x, MyCGI.SLI.lower_start_y);
	end_with_enter();
}

void pf9()
{
	int rank;
	int mine[row_max][col_max];
	int mine_open[row_max][col_max];
	int mine_sign[row_max][col_max];

	cct_cls();
	game_info_input(rank);

	for (int i = 0; i < rank_info[rank - 1].row; ++i)
		for (int j = 0; j < rank_info[rank - 1].col; ++j)
			mine_sign[i][j] = 0;

	CONSOLE_GRAPHICS_INFO MyCGI;                            //声明一个CGI变量
	gmw_init(&MyCGI);                                       //做一个初始化
	gmw_set_rowcol(&MyCGI, rank_info[rank - 1].row, rank_info[rank - 1].col); //游戏区域设置
	gmw_set_color(&MyCGI, COLOR_BLACK, COLOR_WHITE);		//修改窗口颜色并级联修改游戏区域、上下状态栏
	gmw_set_font(&MyCGI, "新宋体", 16, 0);				    //TrueType字体（新宋体）宽度不需要，可任意设置
	gmw_set_frame_style(&MyCGI, 4, 2, true);				//每个色块区域宽度2列*高度2列，要分隔线
	gmw_set_frame_default_linetype(&MyCGI, 1);			    //设置框架线型为预置值1
	gmw_set_frame_color(&MyCGI, COLOR_HWHITE, COLOR_BLACK); //设置框架颜色
	gmw_set_rowno_switch(&MyCGI, true);					    //显示行号
	gmw_set_colno_switch(&MyCGI, true);					    //显示列标
	gmw_set_block_border_switch(&MyCGI, false);			    //设置色块不需要小边框
	gmw_set_status_line_switch(&MyCGI, TOP_STATUS_LINE);	//开启上状态栏
	gmw_set_status_line_switch(&MyCGI, LOWER_STATUS_LINE);	//开启下状态栏

	cct_setcursor(CURSOR_INVISIBLE);                        //设置光标不可见

	gmw_draw_frame(&MyCGI);

	for (int i = 0; i < rank_info[rank - 1].row; ++i)
		for (int j = 0; j < rank_info[rank - 1].col; ++j)
			draw_block(&MyCGI, mine[i][j], i, j, 1);

	gmw_status_line(&MyCGI, TOP_STATUS_LINE, "等待游戏开始,ESC退出,空格显示时间");

	int MAction, MRow, MCol, KeyCode1, KeyCode2;
	int ret;
	int count = 0;
	int flag_quit = 0;

	//记录时间
	clock_t startTime = 0, endTime = 0;

	int sign_count = 0;

	while (1) {
		while (1) {
			ret = read_keyboard_and_mouse(&MyCGI, MAction, MRow, MCol, KeyCode1, KeyCode2);
			if (ret == CCT_MOUSE_EVENT) {
				if (MAction == MOUSE_LEFT_BUTTON_CLICK)
					break;
				else if (MAction == MOUSE_RIGHT_BUTTON_CLICK) {
					if (count) {
						if (mine_sign[MRow][MCol])
							--sign_count;
						else
							++sign_count;
						if (sign_mine(mine_sign, mine_open, MRow, MCol)) {
							if (mine_sign[MRow][MCol] == 1)
								draw_block(&MyCGI, mine[MRow][MCol], MRow, MCol, 2);
							else
								draw_block(&MyCGI, mine[MRow][MCol], MRow, MCol, 1);
						}
						break;
					}
					else
						continue;
				}
			}
			else {
				if (KeyCode1 == 27) {
					flag_quit = 1;
					break;
				}
				else if (KeyCode1 == ' ') {
					if (count) {
						int curTime = clock();
						char buf[80];
						sprintf_s(buf, "%s%lf%s", "当前用时:", (double)(curTime - startTime) / CLOCKS_PER_SEC, "秒, ");
						gmw_status_line(&MyCGI, TOP_STATUS_LINE, "ESC退出,空格显示时间", buf);
					}
				}
			}
		}

		if (flag_quit)
			break;

		char px, py;
		px = MRow + 'A';
		if (MCol < 9)
			py = MCol + '1';
		else
			py = MCol - 9 + 'a';

		if (!count) {
			init_array(mine, mine_open, rank, px, py);
			//计时开始
			startTime = clock();
		}

		if (MAction != MOUSE_RIGHT_BUTTON_CLICK) {
			ret = uncover(mine, mine_open, px, py, rank);

			for (int i = 0; i < rank_info[rank - 1].row; ++i)
				for (int j = 0; j < rank_info[rank - 1].col; ++j)
					if (mine_open[i][j])
						draw_block(&MyCGI, mine[i][j], i, j, 0);
		}

		if (ret)
			break;
		if (check_end(mine, mine_open, mine_sign, rank))
			break;

		char buf[80];
		sprintf_s(buf, "%s%d%c", "剩余雷数:", rank_info[rank - 1].mine_num - sign_count, ',');
		gmw_status_line(&MyCGI, TOP_STATUS_LINE, "ESC退出,空格显示时间", buf);

		++count;
	}

	endTime = clock();//计时结束

	char buf[80];
	sprintf_s(buf, "%s%lf%s", "总用时:", (double)(endTime - startTime) / CLOCKS_PER_SEC, "秒, ");

	if (ret)
		gmw_status_line(&MyCGI, LOWER_STATUS_LINE, "\n你输了!游戏结束", buf);
	else if (!flag_quit)
		gmw_status_line(&MyCGI, LOWER_STATUS_LINE, "\n恭喜胜利!游戏结束", buf);

	cct_gotoxy(MyCGI.SLI.lower_start_x, MyCGI.SLI.lower_start_y);
	end_with_enter();
}