/*2151613 毛宇录 计科*/
#include "90-02-b5.h"

int read_sav(const char* sav_name, string file_name)
{
	file_name = '[' + file_name + ']';
	int value = 0;
	ifstream fsav;
	fsav.open(sav_name, ios::in);
	if (fsav.fail())
		return 0;
	string temp;
	int pos;
	while (!fsav.eof()) {
		fsav >> temp >> pos;
		if (fsav.fail())
			return 0;
		if (temp == file_name) {
			value = pos;
			break;
		}
	}
	fsav.close();
	return value;
}

void write_sav(int start_pos, const char* sav_name, string file_name)
{
	file_name = '[' + file_name + ']';
	int pos = 0;
	string str;
	ifstream in;
	in.open(sav_name, ios::in);
	ofstream fsav_out;
	ostringstream temp;
	bool flag_is_exist = false;
	if (!in.fail()) {
		while (getline(in, str)) {
			if(str.length() > 0)
				temp << str << endl;
			if (str == file_name) {
				flag_is_exist = true;
				in >> pos;
				temp << start_pos << endl;
			}
		}
		in.close();
	}
	if(!flag_is_exist) {
		fsav_out.open(sav_name, ios::out | ios::app);
		fsav_out << file_name << endl;
		fsav_out << start_pos << endl;
		fsav_out << endl;
	}
	else {
		fsav_out.open(sav_name, ios::out | ios::trunc);
		fsav_out << temp.str();
	}
	fsav_out.close();
}

void clear_status_line(int y)
{
	cct_gotoxy(0, y);
	for (int i = 0; i < page_width + 4; ++i)
		cout << " ";
	cout << endl;
}

void info_line(int pos, string file_name, int size)
{
	clear_status_line(page_height + 2);
	file_name = file_name.substr(0, file_name.length() - 4);
	cct_gotoxy(0, page_height + 2);
	cout << " " << file_name << "   ";
	if (pos >= 0)
		cout << setprecision(2) << setiosflags(ios::fixed) << (double)(pos) / size * 100 << '%' << endl;
	else
		cout << "100.00%" << endl;
}

void addition_line()
{
	cct_gotoxy(0, page_height + 4);
	cout << setw(page_width + 4) << setfill('*') << "" << endl;
	cout << setfill(' ') << " 按键说明：";
	cout << "上下箭头键移动一行、";
	cout << "PgUp, PgDn移动一页" << endl;
	cout << " S键进度跳转、";
	cout << "N键返回菜单、";
	cout << "Q键退出程序、";
	cout << "F键转换模式" << endl;
}

void draw_frame()
{
	cct_cls();
	cct_setconsoleborder(page_width + 5, page_height + 9);
	//首行
	cout << "╔";
	for (int i = 0; i < page_width / 2; ++i)
		cout << "═";
	cout << "╗" << endl;
	//中间
	for (int i = 0; i < page_height; ++i) {
		cout << "║";
		for (int j = 0; j < page_width; ++j)
			cout << " ";
		cout << "║" << endl;
	}
	//尾行
	cout << "╚";
	for (int i = 0; i < page_width / 2; ++i)
		cout << "═";
	cout << "╝" << endl;
}

void read_page(page& mypage, ifstream& fin)
{
	int i;
	//从指定行号开始，目前不需要结束的行号
	for (i = mypage.start_no; i < page_height && !fin.eof(); ++i) {
		/*初始化*/
		mypage.myline[i].line_first_pos = (int)fin.tellg();
		mypage.myline[i].content = "";
		int line_length = page_width; //一行的上限长度
		int length = 0; //记录一行的长度
		int ch_count = 0; //记录中文字符
		bool is_read_CR = false; //记录是否读到换行
		/*处理前导空格*/
		if (mypage.show_format == 0) {
			if (fin.peek() != ' ' && fin.peek() != '\t' && fin.peek() != 0xA1 && fin.tellg() != 0) {
				fin.seekg(-1, ios::cur);
				if (fin.peek() == '\n') {
					line_length -= 4;
					for (int j = 0; j < 4; ++j)
						mypage.myline[i].content += (char)0xA1;
					fin.seekg(2, ios::cur);
				}
				else
					fin.seekg(1, ios::cur);
			}
		}
		/*开始读一行*/
		for (int j = 0; j < line_length; ++j) {
			char ch;
			fin.get(ch);
			//eof
			if (fin.eof())
				break;
			//\n
			if (ch == '\n') {
				is_read_CR = true;
				if (mypage.show_format == 1) {
					if (length == 0)
						break;
					if (fin.peek() != ' ' && fin.peek() != '\t' && fin.peek() != 0xA1) {
						--j;
						continue;
					}
					else
						break;
				}
				if(mypage.show_format == 0){
					break;
				}
			}
			is_read_CR = false;
			//加上字符
			mypage.myline[i].content += ch;
			++length;
			//判断中文字符
			if (ch < 0)
				++ch_count;
		}
		/*判断中文字符奇数*/
		if (ch_count % 2 && mypage.myline[i].content[length - 1] < 0) {
			mypage.myline[i].content[length - 1] = '\0';
			fin.seekg(-1, ios::cur);
		}
		/*删除行尾多余换行*/
		if (!is_read_CR) {
			if (fin.peek() == '\n')
				fin.seekg(2, ios::cur);
		}
	}
	/*更改下mypage信息*/
	mypage.line_num = i;
	mypage.end_pos = (int)fin.tellg();
	mypage.start_pos = mypage.myline[0].line_first_pos;
}

void show_page(page& mypage, ifstream& fin)
{
	for (int i = 0; i < page_height; ++i) {
		cct_gotoxy(2, i + 1);
		//记得要先清空当前行
		cout << setw(page_width) << "";
		if (i < mypage.line_num) {
			cct_gotoxy(2, i + 1);
			cout << mypage.myline[i].content << endl;
		}
	}
}

void roll_down_single(page& mypage, ifstream& fin)
{
	if (fin.eof())
		return;

	//先循环移动信息
	for (int i = 0; i < page_height - 1; ++i)
		mypage.myline[i] = mypage.myline[i + 1];

	//读一行
	mypage.start_no = page_height - 1;
	read_page(mypage, fin);
}

void roll_down_page(page& mypage, ifstream& fin)
{
	if (fin.eof())
		return;

	for (int i = 1; i < page_height; ++i)
		roll_down_single(mypage, fin);
}

void roll_up_single(page& mypage, ifstream& fin)
{
	goto_line(mypage, fin, -1, mypage.myline[page_height - 1].line_first_pos);
}

void roll_up_page(page& mypage, ifstream& fin)
{
	goto_line(mypage, fin, -1, mypage.myline[1].line_first_pos);
}

void goto_line(page& mypage, ifstream& fin, int size, int pos)
{
	int temp_pos;
	if (pos == -2) {
		cct_gotoxy(0, 3 + page_height);
		temp_pos = tp(size);
		clear_status_line(3 + page_height);
	}
	else
		temp_pos = pos;
	if (fin.eof())
		fin.clear();
	fin.seekg(0, ios::beg);
	//先读一页
	mypage.start_no = 0;
	read_page(mypage, fin);
	//然后循环读一行
	if (mypage.line_num >= page_height && mypage.end_pos != -1) {
		while (mypage.end_pos < temp_pos && !fin.eof())
			roll_down_single(mypage, fin);
	}
	//最后把显示界面读出来
	if (fin.eof())
		fin.clear();
	fin.seekg(mypage.start_pos, ios::beg);
	mypage.start_no = 0;
	read_page(mypage, fin);
}

void change_format(page& mypage, ifstream& fin)
{
	mypage.show_format = 1 - mypage.show_format;
	goto_line(mypage, fin, -1, mypage.end_pos);
}