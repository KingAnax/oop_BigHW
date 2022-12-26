/*2151613 ë��¼ �ƿ�*/
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
	cout << setfill(' ') << " ����˵����";
	cout << "���¼�ͷ���ƶ�һ�С�";
	cout << "PgUp, PgDn�ƶ�һҳ" << endl;
	cout << " S��������ת��";
	cout << "N�����ز˵���";
	cout << "Q���˳�����";
	cout << "F��ת��ģʽ" << endl;
}

void draw_frame()
{
	cct_cls();
	cct_setconsoleborder(page_width + 5, page_height + 9);
	//����
	cout << "�X";
	for (int i = 0; i < page_width / 2; ++i)
		cout << "�T";
	cout << "�[" << endl;
	//�м�
	for (int i = 0; i < page_height; ++i) {
		cout << "�U";
		for (int j = 0; j < page_width; ++j)
			cout << " ";
		cout << "�U" << endl;
	}
	//β��
	cout << "�^";
	for (int i = 0; i < page_width / 2; ++i)
		cout << "�T";
	cout << "�a" << endl;
}

void read_page(page& mypage, ifstream& fin)
{
	int i;
	//��ָ���кſ�ʼ��Ŀǰ����Ҫ�������к�
	for (i = mypage.start_no; i < page_height && !fin.eof(); ++i) {
		/*��ʼ��*/
		mypage.myline[i].line_first_pos = (int)fin.tellg();
		mypage.myline[i].content = "";
		int line_length = page_width; //һ�е����޳���
		int length = 0; //��¼һ�еĳ���
		int ch_count = 0; //��¼�����ַ�
		bool is_read_CR = false; //��¼�Ƿ��������
		/*����ǰ���ո�*/
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
		/*��ʼ��һ��*/
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
			//�����ַ�
			mypage.myline[i].content += ch;
			++length;
			//�ж������ַ�
			if (ch < 0)
				++ch_count;
		}
		/*�ж������ַ�����*/
		if (ch_count % 2 && mypage.myline[i].content[length - 1] < 0) {
			mypage.myline[i].content[length - 1] = '\0';
			fin.seekg(-1, ios::cur);
		}
		/*ɾ����β���໻��*/
		if (!is_read_CR) {
			if (fin.peek() == '\n')
				fin.seekg(2, ios::cur);
		}
	}
	/*������mypage��Ϣ*/
	mypage.line_num = i;
	mypage.end_pos = (int)fin.tellg();
	mypage.start_pos = mypage.myline[0].line_first_pos;
}

void show_page(page& mypage, ifstream& fin)
{
	for (int i = 0; i < page_height; ++i) {
		cct_gotoxy(2, i + 1);
		//�ǵ�Ҫ����յ�ǰ��
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

	//��ѭ���ƶ���Ϣ
	for (int i = 0; i < page_height - 1; ++i)
		mypage.myline[i] = mypage.myline[i + 1];

	//��һ��
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
	//�ȶ�һҳ
	mypage.start_no = 0;
	read_page(mypage, fin);
	//Ȼ��ѭ����һ��
	if (mypage.line_num >= page_height && mypage.end_pos != -1) {
		while (mypage.end_pos < temp_pos && !fin.eof())
			roll_down_single(mypage, fin);
	}
	//������ʾ���������
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