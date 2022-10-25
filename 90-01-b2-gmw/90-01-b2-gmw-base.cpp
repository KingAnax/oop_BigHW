/* 2151613 毛宇录 计科 */

#include "90-01-b2-gmw.h"

static void confirm_km(const CONSOLE_GRAPHICS_INFO* const MyCGI, bool &flag_sel, int &count, const int mrow, const int mcol, const int row, const int col, int (*num)[col_max], int (*num_sel)[col_max], int &score_total, int &target)
{
	char temp[80];
	if (!flag_sel) {
		count = find_equal(0, num[mrow][mcol], row, col, num, num_sel, mrow, mcol);
		if (count > 1) {
			flag_sel = TRUE;
			for (int i = 0; i < row_max; ++i)
				for (int j = 0; j < col_max; ++j)
					if (num_sel[i][j])
						gmw_draw_block(MyCGI, i, j, num[i][j], bdi_cat);
			gmw_draw_block(MyCGI, mrow, mcol, num[mrow][mcol], bdi_sel);
			sprintf(temp, "已选中%c行%d列", char('A' + mrow), mcol);
			gmw_status_line(MyCGI, LOWER_STATUS_LINE, NULL, NULL);
		}
		else
			gmw_status_line(MyCGI, LOWER_STATUS_LINE, NULL, "周围无相同项!");
	}
	else {
		flag_sel = FALSE;
		combine(MyCGI, row, col, mrow, mcol, num, num_sel);
		score(MyCGI, count, num[mrow][mcol] - 1, score_total, target);
		fall(MyCGI, num, row, col);
		fill_blank(MyCGI, num, row, col);
		int stage = init_num;
		for (int i = 0; i < row; ++i)
			for (int j = 0; j < col; ++j)
				if (num[i][j] > stage)
					stage = num[i][j];
		if (stage == target && is_end(num, row, col)) {
			sprintf(temp, "%s%d%s", "已达到合成目标", target, ",向更高目标进发");
			gmw_status_line(MyCGI, LOWER_STATUS_LINE, NULL, temp);
			confirm_enter();
			++target;
		}
	}
}

void pf9()
{
	int num[row_max][col_max] = {};
	int num_sel[row_max][col_max] = {};
	int row, col, target;

	cct_cls();
	init_game_info(row, col, target);                       //行列、目标输入

	CONSOLE_GRAPHICS_INFO MyCGI;                            //声明一个CGI变量
	gmw_init(&MyCGI);                                       //做一个初始化
	gmw_set_rowcol(&MyCGI, row, col);					    //游戏区域设置
	gmw_set_color(&MyCGI, COLOR_BLACK, COLOR_WHITE);		//修改窗口颜色并级联修改游戏区域、上下状态栏
	gmw_set_font(&MyCGI, "新宋体", 16, 0);				    //TrueType字体（新宋体）宽度不需要，可任意设置
	gmw_set_frame_style(&MyCGI, 6, 3, true);				//每个色块区域宽度6列*高度3列，要分隔线
	gmw_set_frame_default_linetype(&MyCGI, 2);			    //设置框架线型为预置值2（全部为单线）
	gmw_set_frame_color(&MyCGI, COLOR_HWHITE, COLOR_BLACK); //设置框架颜色
	gmw_set_rowno_switch(&MyCGI, true);					    //显示行号
	gmw_set_colno_switch(&MyCGI, true);					    //显示列标
	gmw_set_delay(&MyCGI, DELAY_OF_DRAW_FRAME, 5);		    //画边框的延时
	gmw_set_delay(&MyCGI, DELAY_OF_BLOCK_MOVED, 20);		//移动的延时
	gmw_set_block_border_switch(&MyCGI, true);			    //设置色块需要小边框
	gmw_set_status_line_switch(&MyCGI, TOP_STATUS_LINE);	//开启上状态栏
	gmw_set_status_line_switch(&MyCGI, LOWER_STATUS_LINE);	//开启下状态栏

	cct_setcursor(CURSOR_INVISIBLE);                        //设置光标不可见

	init_array(num, row, col);                              //初始化数组

	int maction, old_mrow = 0, old_mcol = 0, mrow = 0, mcol = 0;
	int keycode1, keycode2;
	int ret;
	bool flag_quit = FALSE;
	bool flag_sel = FALSE;
	bool flag_moved = FALSE;

	cct_cls();

	/* 显示初始化的框架 */
	gmw_draw_frame(&MyCGI);

	//画色块
	for (int i = 0; i < row; ++i)
		for (int j = 0; j < col; ++j)
			gmw_draw_block(&MyCGI, i, j, num[i][j], bdi_normal);

	char temp[80] = {};

	/* 上状态栏显示内容 */
	sprintf(temp, "屏幕当前设置为：%d行 %d列", MyCGI.lines, MyCGI.cols);
	gmw_status_line(&MyCGI, TOP_STATUS_LINE, temp);
	/* 下状态栏显示内容 */
	gmw_status_line(&MyCGI, LOWER_STATUS_LINE, "箭头键/鼠标移动，回车键/单击左键选择, Q/单击右键结束");

	gmw_draw_block(&MyCGI, mrow, mcol, num[mrow][mcol], bdi_cat);


	//鼠标键盘
	int count = 0;
	int score_total = 0;
	while (1) {
		flag_moved = FALSE;
		old_mrow = mrow;
		old_mcol = mcol;
		ret = read_keyboard_and_mouse(&MyCGI, maction, mrow, mcol, keycode1, keycode2, num, num_sel, row, col);
		if (ret == CCT_MOUSE_EVENT) {
			if (maction == MOUSE_ONLY_MOVED)
				flag_moved = TRUE;
			else if (maction == MOUSE_LEFT_BUTTON_CLICK) {
				confirm_km(&MyCGI, flag_sel, count, mrow, mcol, row, col, num, num_sel, score_total, target);
			}
			else if (maction == MOUSE_RIGHT_BUTTON_CLICK) {
				flag_quit = TRUE;
				break;
			}
		}
		else if (ret == CCT_KEYBOARD_EVENT) {
			switch (keycode1) {
				case 224:
					flag_moved = TRUE;
					break;
				case 'q':
					flag_quit = TRUE;
					break;
				case 'Q':
					flag_quit = TRUE;
					break;
				case '\r':
					confirm_km(&MyCGI, flag_sel, count, mrow, mcol, row, col, num, num_sel, score_total, target);
					break;
			}
		}
		if (is_end(num, row, col)) {
			flag_quit = TRUE;
			gmw_status_line(&MyCGI, LOWER_STATUS_LINE, "按q退出", "无可合并项，游戏结束，");
			confirm_q();
		}
		if (flag_quit)
			break;
		if (flag_moved) {
			gmw_draw_block(&MyCGI, old_mrow, old_mcol, num[old_mrow][old_mcol], bdi_normal);
			gmw_draw_block(&MyCGI, mrow, mcol, num[mrow][mcol], bdi_cat);
			flag_sel = 0;
		}
	}
	cct_setcursor(CURSOR_VISIBLE_NORMAL);
}