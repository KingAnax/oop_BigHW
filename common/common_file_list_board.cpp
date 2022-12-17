/*2151613 毛宇录 计科*/
#include "../include/common_file_list_board.h"

const int height = 13;
const int width = 16;

#define stat_normal 0
#define stat_cat    1

static int get_file_num(const char* to_search)
{
	int handle;
	int i = 0;
	struct _finddata_t fileinfo;
	handle = (int)_findfirst(to_search, &fileinfo);
	if (-1 == handle)
		return -1;
	i++;
	while (!_findnext(handle, &fileinfo))
		i++;
	_findclose(handle);
	return i;
}

static int find(string*& file, const char* to_search)
{
	int handle;
	int i = 0;
	struct _finddata_t fileinfo;
	handle = (int)_findfirst(to_search, &fileinfo);
	file[i++] = fileinfo.name;
	while (!_findnext(handle, &fileinfo))
		file[i++] = fileinfo.name;
	_findclose(handle);
	return 0;
}

static void sort_file(string*& file, int num)
{
	for (int i = 0; i < num - 1; ++i) {
		bool flag = false;
		for (int j = 0; j < num - 1 - i; ++j) {
			if (file[j] > file[j + 1]) {
				string temp;
				temp = file[j];
				file[j] = file[j + 1];
				file[j + 1] = temp;
				flag = true;
			}
		}
		if (flag == false)
			break;
	}
}

static void print_line(CONSOLE_GRAPHICS_INFO MyCGI, string file, const int pos, const int mode, const int suffix_len)
{
	int count = 0;
	int wid;
	for (wid = 0; wid < width && wid < (int)(file.length() - 4); ++wid) {
		if (file[wid] < 0)
			++count;
	}
	if (count % 2 && file[wid - 1] < 0)
		--wid;
	string temp = file.substr(0, wid);
	for (int extra_len = width - wid; extra_len > 0; --extra_len)
		temp += " ";
	cct_gotoxy(MyCGI.start_x + 2, MyCGI.start_y + 1 + pos);
	if (mode == stat_cat)
		cct_setcolor(7, 0);
	cout << temp;
	cct_setcolor();
}

int list_board(string& str, const char* path, const char* to_search, const int suffix_len)
{
	string* file;
	int num = get_file_num(to_search);
	if (num < 0) {
		cout << "在" << path << "下无法找到任何文件" << endl;
		return -1;
	}
	file = new(nothrow) string[num];
	find(file, to_search);
	sort_file(file, num);
	cct_setcursor(3);

	//start
	CONSOLE_GRAPHICS_INFO MyCGI;                            //声明一个CGI变量
	gmw_init(&MyCGI);                                       //做一个初始化
	gmw_set_rowcol(&MyCGI, height, 1);                      //区域设置
	gmw_set_color(&MyCGI, COLOR_BLACK, COLOR_WHITE);		//修改窗口颜色并级联修改区域、上下状态栏
	gmw_set_font(&MyCGI, "新宋体", 16, 0);				    //TrueType字体（新宋体）宽度不需要，可任意设置
	gmw_set_frame_style(&MyCGI, width, 1, false);			//每个色块区域宽度16列*高度1列，不要分隔线
	gmw_set_frame_default_linetype(&MyCGI, 1);			    //设置框架线型为预置值1
	gmw_set_frame_color(&MyCGI, COLOR_BLACK, COLOR_HWHITE); //设置框架颜色
	gmw_set_rowno_switch(&MyCGI, false);					//不显示行号
	gmw_set_colno_switch(&MyCGI, false);					//不显示列标
	gmw_set_block_border_switch(&MyCGI, false);			    //设置色块不需要小边框
	gmw_set_status_line_switch(&MyCGI, TOP_STATUS_LINE);	//开启上状态栏
	gmw_set_status_line_switch(&MyCGI, LOWER_STATUS_LINE);	//开启下状态栏
	gmw_set_ext_rowcol(&MyCGI, 3, 6, 21, 30);               //设置额外行列

	gmw_draw_frame(&MyCGI);
	gmw_status_line(&MyCGI, TOP_STATUS_LINE, " 请选择文件");

	int len = num < height ? num : height;

	print_line(MyCGI, file[0], 0, stat_cat, suffix_len);
	for (int i = 1; i < len; ++i)
		print_line(MyCGI, file[i], i, stat_normal, suffix_len);

	//choose + slid
	int MX = 0, MY = 0, MAction = 0, keycode1 = 0, keycode2 = 0; //响应
	int rear = 0; //选中的文件编号
	int p = 0;    //当前行数
	while (1) {
		cct_read_keyboard_and_mouse(MX, MY, MAction, keycode1, keycode2);
		if (keycode1 == 224) {
			if (keycode2 == 72) {//上箭头
				if (p > 0) {
					print_line(MyCGI, file[rear - 1], p - 1, stat_cat, suffix_len);
					print_line(MyCGI, file[rear], p, stat_normal, suffix_len);
					--rear;
					--p;
				}
				else if (rear > 0) {
					rear--;
					print_line(MyCGI, file[rear], 0, stat_cat, suffix_len);
					for (int i = 1; i < height; ++i)
						print_line(MyCGI, file[rear + i], i, stat_normal, suffix_len);
				}
			}
			else if (keycode2 == 80) {//下箭头
				if (p < height - 1) {
					print_line(MyCGI, file[rear + 1], p + 1, stat_cat, suffix_len);
					print_line(MyCGI, file[rear], p, stat_normal, suffix_len);
					++rear;
					++p;
				}
				else if (rear < num - 1) {
					rear++;
					print_line(MyCGI, file[rear], height - 1, stat_cat, suffix_len);
					for (int i = 1; i < height; ++i)
						print_line(MyCGI, file[rear - i], height - i - 1, stat_normal, suffix_len);
				}
			}
		}
		else if (keycode1 == 13)
			break;
	}
	cct_setcursor(2);
	str = file[rear];
	gmw_status_line(&MyCGI, LOWER_STATUS_LINE, "");
	cout << "\n选择了" << str << "文件" << endl;
	delete[]file;
	return rear;
}