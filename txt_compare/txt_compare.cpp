/* 2151613 ë��¼ �ƿ� */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>
#include "../include/class_aat.h"
#include "../include/cmd_console_tools.h"
#include "txt_compare.h"
using namespace std;

#define line_max_len 1024

/* ���������Ҫ������ */
struct line_state {
	ifstream fin;
	char line_buf[line_max_len + 1];
	int line_no;
	int type;
	bool only_blank;
	bool is_empty;
	int left;
	int right;
	int len;
};

enum OPT_ARGS { help, debug, file1, file2, trim, lineoffset, ignore_blank, CR_CRLF_not_equal, max_diff, max_line, display };
enum class TRIM_VALUE { none, left, right, all };
enum class DISPLAY_VALUE { none, normal, detailed };
enum line_type { eof, CR, CR_LF };

static int read_line(line_state& f, const string file_name, const int trim_value, const bool flag_LF)
{
	++f.line_no;
	int count = 0;
	f.line_buf[0] = '\0';
	char ch_before = '\0';
	f.only_blank = true;
	f.left = 0;
	f.right = line_max_len;
	f.is_empty = 0;
	while (1) {
		char ch = f.fin.get();
		if (f.fin.eof()) {
			f.type = eof;
			break;
		}
		if (ch == '\n') {
			if (ch_before == '\r') {
				f.type = CR_LF;
				if (!flag_LF) {
					f.line_buf[count - 1] = '\0';
					--count;
				}
			}
			else
				f.type = CR;
			break;
		}
		if (ch != '\t' && ch != ' ')
			f.only_blank = false;
		if (f.only_blank == true && (trim_value == (int)TRIM_VALUE::left || trim_value == (int)TRIM_VALUE::all))
			f.left = count;
		f.line_buf[count] = ch;
		++count;
		if (count >= line_max_len) {
			cout << "�ļ�[" << file_name << "]�ĵ�(" << f.line_no << ")�в�����Ҫ�󣬳�����󳤶�[" << line_max_len << "]." << endl;
			return -1;
		}
		f.line_buf[count] = '\0';
		ch_before = ch;
	}
	f.len = count;
	if (!count)
		f.is_empty = 1;
	f.right = count - 1;
	//�����ҿհ�
	if (trim_value == (int)TRIM_VALUE::right || trim_value == (int)TRIM_VALUE::all) {
		for (int i = count - 1; i >= 0; --i) {
			if (f.line_buf[i] != '\t' && f.line_buf[i] != ' ')
				break;
			f.right = i;
		}
	}
	return 0;
}

static void surveyor(const line_state& f1, const line_state& f2)
{
	int len = 10;
	if (len < 10 * (f1.len / 10 + 1))
		len = 10 * (f1.len / 10 + 1);
	if (len < 10 * (f2.len / 10 + 1))
		len = 10 * (f2.len / 10 + 1);
	cout << "        ";
	cout << setfill('-') << setw(len) << "";
	cout << setfill(' ') << endl;
	cout << "        ";
	for (int i = 0; i < len / 10; ++i)
		cout << setw(10) << setiosflags(ios::left) << i % 10;
	cout << endl;
	cout << "        ";
	for (int i = 0; i < len / 10; ++i)
		cout << "0123456789";
	cout << endl;
	cout << "        ";
	cout << setfill('-') << setw(len) << "";
	cout << setfill(' ') << endl;
}

static void dec_to_hex_n(int num, char* hex_num)
{
	*hex_num = '0';
	if (num / 16 >= 10)
		*(hex_num) = num / 16 - 10 + 'a';
	else
		*(hex_num) = num / 16 + '0';
	if (num % 16 >= 10)
		*(hex_num + 1) = num % 16 - 10 + 'a';
	else
		*(hex_num + 1) = num % 16 + '0';
	return;
}

static void oct_to_hex(char* ch, int count)
{
	for (int i = 0; i < 8; i++)
		*(ch + i) = '0';
	for (int i = 7; i >= 0; i--)
	{
		if (count > 0)
		{
			if (count % 16 < 10)
				*(ch + i) = count % 16 + '0';
			else
				*(ch + i) = count % 16 - 10 + 'a';
			count /= 16;
		}
		else
			break;
	}
	return;
}

static void print_hex(const char* str)
{
	char hex_num[9] = { 0 };
	char array[17] = { 0 };
	unsigned char ch;
	int i = 0;
	while (1) {
		ch = *str;
		++str;
		if (!ch)
			break;
		if (i % 16 == 0) {
			oct_to_hex(hex_num, i);
			if (i != 0) {
				cout << "    ";
				for (int a = 0; a < 16; a++)
				{
					if ((array[a] >= 33) && (array[a] <= 126))
						cout << array[a];
					else
						cout << '.';
				}
				cout << endl;
			}
			cout << hex_num << " : ";
			for (int a = 0; a < 9; ++a)
				hex_num[a] = 0;
			for (int a = 0; a < 16; ++a)
				array[a] = 0;
		}
		array[i % 16] = ch;
		if ((i % 8 == 0) && (i % 16 != 0))
			cout << "- ";
		dec_to_hex_n(ch, hex_num);
		cout << setw(2) << hex_num << " ";
		for (int a = 0; a < 9; a++)
			hex_num[a] = '\0';
		i++;
	}
	if (i != 0) {
		if (i % 16 == 0)
			cout << "    ";
		else if (i % 16 > 8)
			cout << setw(((int)(4 + 3 * (16 - (double)(i % 16))))) << "";
		else
			cout << setw(((int)(6 + 3 * (16 - (double)(i % 16))))) << "";
		for (int a = 0; a < (i - 1) % 16 + 1; a++) {
			if ((array[a] >= 33) && (array[a] <= 126))
				cout << array[a];
			else
				cout << '.';
		}
		cout << endl;
	}
}

static void show(const char ch, const int mode)
{
	if (mode)
		cct_setcolor(14, 12);
	if (ch == 010 || ch == '\r' || ch == '\n' || ch == 11 || ch == 7)
		cout << "X";
	else
		cout << ch;
	cct_setcolor();
}

static void draw_line(const line_state& f1, const line_state& f2, char* tag_dif)
{
	if (f1.is_empty && f1.type != eof) {
		if (!f2.len && f2.type == eof)
			cct_setcolor(14, 12);
		cout << "<EMPTY>";
		cct_setcolor();
	}
	for (int i = 0; i < f1.len; ++i)
		show(*(f1.line_buf + i), tag_dif[i] - '0');

	if (f1.type == eof)
		cout << "<EOF>";
	else
		cout << "<CR>";
	cout << endl;
}

static int check_line(const line_state& f1, const line_state& f2, ostringstream& msg, char* tag_dif)
{
	int cnt_diff = 0;
	const char* p1 = f1.line_buf, * p2 = f2.line_buf;
	int cnt_CN_1 = 0;
	int cnt_CN_2 = 0;
	bool flag_first = 0;
	while (*p1 && *p2) {
		unsigned ch_1 = *p1, ch_2 = *p2;
		if (ch_1 > 255)
			++cnt_CN_1;
		else
			cnt_CN_1 = 0;
		if (ch_2 > 255)
			++cnt_CN_2;
		else
			cnt_CN_2 = 0;
		if (*p1 != *p2) {
			++cnt_diff;
			if (!flag_first)
				msg << "��[" << p1 - f1.line_buf << "]���ַ���ʼ�в��죺";
			tag_dif[p1 - f1.line_buf] = '1';
			if (ch_1 > 255 && cnt_CN_1 % 2 == 0)
				tag_dif[p1 - f1.line_buf - 1] = '1';
			if (ch_2 > 255 && cnt_CN_2 % 2 == 0)
				tag_dif[p1 - f1.line_buf - 1] = '1';
			flag_first = 1;
		}
		++p1;
		++p2;
	}
	if (!*p1 && *p2 || f1.type == eof && f2.type != eof) {
		if (!flag_first) {
			if (f1.type == eof)
				msg << "�ļ�1�ѽ���/�ļ�2�������ݣ�";
			msg << "�ļ�2��β���ж����ַ���";
		}
		for (; *p2; ++p2)
			tag_dif[p2 - f1.line_buf] = '1';
		return -1;
	}
	if (*p1 && !*p2 || f1.type != eof && f2.type == eof) {
		if (!flag_first) {
			if (f2.type == eof)
				msg << "�ļ�1��������/�ļ�2�ѽ�����";
			msg << "�ļ�1��β���ж����ַ���";
		}
		for (; *p1; ++p1)
			tag_dif[p1 - f1.line_buf] = '1';
		return -2;
	}
	return 0;
}

void hint(int count)
{
	cout << "��ָ����������¹�" << count << "���в���." << endl;
	cout << "�Ķ���ʾ��" << endl;
	cout << "        1��������<EMPTY>���" << endl;
	cout << "        2���ļ�������<EOF>���" << endl;
	cout << "        3��������ͬ��λ�õĲ����ַ�����ɫ���" << endl;
	cout << "        4��ÿ���е�CR/LF/VT/BS/BEL��X���(���㿴�������ַ�)" << endl;
	cout << "        5��ÿ��β�Ķ�����ַ�����ɫ�����CR/LF/VT/BS/BEL����ɫX���(���㿴�������ַ�)" << endl;
	cout << "        6��ÿ�������<CR>���(���㿴�������ַ�)" << endl;
	cout << "        7��������Ϊ�������⣬����λ�ÿ��ܱ��ں��������ϣ����������ֶ���ɫ���" << endl;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
 ***************************************************************************/
static void usage(const char* const procname)
{
	ostringstream msg;
	const int wkey = 7 + strlen(procname) + 1;
	const int wopt = 7 + strlen(procname) + 4;
	cout << endl;

	msg << procname << "-Ver1.0.0" << endl;
	msg << endl;

	msg << "Usage: " << procname << " --file1 xxx --file2 xxx [ --trim none/left/rigth/all | --lineoffset -100..100 | --ignore_blank | --max_diff 0..100 | --display none/normal/detailed ]" << endl;

	msg << setw(wkey) << ' ' << "��ѡ�" << endl;
	msg << setw(wopt) << ' ' << "--file1 name1              : ָ��Ҫ�Ƚϵĵ�1���ļ�������ѡ��" << endl;
	msg << setw(wopt) << ' ' << "--file2 name2              : ָ��Ҫ�Ƚϵĵ�2���ļ�������ѡ��" << endl;
	msg << endl;

	msg << setw(wkey) << ' ' << "��ѡ�" << endl;
	msg << setw(wopt) << ' ' << "--trim none/left/right/all     : ָ��ÿ�еĿո�/tab�ĺ��Է�ʽ���޴�����Ĭ��Ϊnone��" << endl;
	msg << setw(wopt) << ' ' << "\tnone   : ÿ�о��ϸ�ƥ��" << endl;
	msg << setw(wopt) << ' ' << "\tleft   : ÿ�о�����ͷ���ո�" << endl;
	msg << setw(wopt) << ' ' << "\tright  : ÿ�о�����β���ո�" << endl;
	msg << setw(wopt) << ' ' << "\tall    : ÿ�о�����ͷβ�ո�" << endl;
	msg << setw(wopt) << ' ' << "--lineoffset n                 : ָ���ļ���λ���������޴�����nΪ0��" << endl;
	msg << setw(wopt) << ' ' << "\tȡֵ[-100..100]��������ʾ����file1��ǰn�У�������ʾ����file2��ǰn��" << endl;
	msg << setw(wopt) << ' ' << "--ignore_blank                 : �����ļ���--trim������п���(�޴����򲻺���)" << endl;
	msg << setw(wopt) << ' ' << "--CR_CRLF_not_equal            : ������Windows/Linux�ļ��Ļ��з�����(�޴�������Բ���)" << endl;
	msg << setw(wopt) << ' ' << "--max_diff m                   : ָ���ļ���λ���������޴�����mΪ0��" << endl;
	msg << setw(wopt) << ' ' << "\tȡֵ[0..100]����ʾ��m����ͬ����������У����ٽ��к����ıȽ�" << endl;
	msg << setw(wopt) << ' ' << "--max_line x                   : ָ���ļ��Ƚϵ�����������޴�����xΪ0��" << endl;
	msg << setw(wopt) << ' ' << "\tȡֵ[0..10000]����ʾ�Ƚ�x�к���������У����ٽ��к����ıȽ�" << endl;
	msg << setw(wopt) << ' ' << "--display none/normal/detailed : ָ����ʾ����Ϣ���޴�����Ĭ��Ϊnone��" << endl;
	msg << setw(wopt) << ' ' << "\tnone   : ��һ��ƥ��������ʾ" << endl;
	msg << setw(wopt) << ' ' << "\tnormal : ÿ�������и���������Ϣ" << endl;
	msg << setw(wopt) << ' ' << "\tright  : ÿ�������и�������ϸ�Ĳ�����Ϣ" << endl;
	msg << endl;

	msg << "e.g.   " << procname << " --file1 my.txt --file2 std.txt" << endl;
	msg << setw(wopt) << ' ' << " : �Ƚ�my.txt��std.txt��ȫ��ƥ�䣬��һ�����" << endl;
	msg << "       " << procname << " --file1 my.txt --file2 std.txt --trim all" << endl;
	msg << setw(wopt) << ' ' << " : �Ƚ�my.txt��std.txt��ÿ�о�ȥ��ͷβ�ո񣬽�һ�����" << endl;
	msg << "       " << procname << " --file1 my.txt --file2 std.txt --lineoffset -2" << endl;
	msg << setw(wopt) << ' ' << " : �Ƚ�my.txt��std.txt������my.txt��ǰ2��(��my.txt�ĵ�3����std.txt�ĵ�1�н��бȽϣ�ÿ���ϸ�ƥ��)����һ�����" << endl;
	msg << "       " << procname << " --file1 my.txt --file2 std.txt --trim left --lineoffset 3" << endl;
	msg << setw(wopt) << ' ' << " : �Ƚ�my.txt��std.txt������std.txt��ǰ3��(��my.txt�ĵ�1����std.txt�ĵ�4�н��бȽ�)��ÿ��ȥ��ͷ���ո񣬽�һ�����" << endl;
	msg << "       " << procname << " --file1 my.txt --file2 std.txt --ignore_blank" << endl;
	msg << setw(wopt) << ' ' << " : �Ƚ�my.txt��std.txt�������ļ��е����п��У���һ�����" << endl;
	msg << "       " << procname << " --file1 my.txt --file2 std.txt --ignore_blank --trim right" << endl;
	msg << setw(wopt) << ' ' << " : �Ƚ�my.txt��std.txt�������ļ���ȥ��ͷβ�ո������п��У���һ�����" << endl;
	msg << "       " << procname << " --file1 my.txt --file2 std.txt --max_diff 3" << endl;
	msg << setw(wopt) << ' ' << " : �Ƚ�my.txt��std.txt��ȫ��ƥ�䣬��3�в�ƥ���������У���һ�����" << endl;
	msg << "       " << procname << " --file1 my.txt --file2 std.txt --max_line 7" << endl;
	msg << setw(wopt) << ' ' << " : �Ƚ�my.txt��std.txt��ȫ��ƥ�䣬���Ƚ�ǰ7�У���һ�����" << endl;
	msg << "       " << procname << " --file1 my.txt --file2 std.txt --CR_CRLF_not_queal" << endl;
	msg << setw(wopt) << ' ' << " : �Ƚ�my.txt��std.txt��ȫ��ƥ�䣬������Windows/Linux���ļ����죬��һ�����" << endl;
	msg << "       " << procname << " --file1 my.txt --file2 std.txt --display normal" << endl;
	msg << setw(wopt) << ' ' << " : �Ƚ�my.txt��std.txt��ȫ��ƥ�䣬��ƥ�������ʾ��Ϣ" << endl;
	msg << "       " << procname << " --file1 my.txt --file2 std.txt --display detailed" << endl;
	msg << setw(wopt) << ' ' << " : �Ƚ�my.txt��std.txt��ȫ��ƥ�䣬��ƥ�������ʾ��ϸ��Ϣ" << endl;
	msg << endl;
	cout << msg.str() << endl;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int main(int argc, char** argv)
{
	/* ��Ϊ������ lib_aat_tools.lib���˴��ȼ���С�Ƿ����Ҫ�� */
	if (sizeof(args_analyse_tools) != 200) {
		cout << "class args_analyse_tools ����200�ֽڣ����ʹ�� lib_aat_tools.lib �еĺ�������ܳ���" << endl;
		return -1;
	}

	/* ָ��ȥ���ո�ķ�ʽ */
	const string TrimType[] = { "none",	"left",	"right",	"all", "" };
	/* ָ����Ϣ����ʾ��ʽ */
	const string DisplayType[] = { "none",	"normal",	"detailed", "" };
	args_analyse_tools args[] = {
		args_analyse_tools("--help",				ST_EXTARGS_TYPE::boolean, 0, false),		//��ʾ������Ϣ
		args_analyse_tools("--debug",				ST_EXTARGS_TYPE::boolean, 0, false),		//��ʾ������Ϣ����Ҫ����demo��ȫ��ͬ��
		args_analyse_tools("--file1",				ST_EXTARGS_TYPE::str, 1, string("")),		//���ڱȽϵ��ļ���1
		args_analyse_tools("--file2",				ST_EXTARGS_TYPE::str, 1, string("")),		//���ڱȽϵ��ļ���2
		args_analyse_tools("--trim",				ST_EXTARGS_TYPE::str_with_set_error, 1, 0, TrimType),		//�ո�ıȽϷ�ʽ
		args_analyse_tools("--lineoffset",		ST_EXTARGS_TYPE::int_with_default,   1, 0, -100, 100),		//ָ�������ļ����в�
		args_analyse_tools("--ignore_blank",		ST_EXTARGS_TYPE::boolean, 0, false),							//���Կ���
		args_analyse_tools("--CR_CRLF_not_equal",	ST_EXTARGS_TYPE::boolean, 0, false),							//
		args_analyse_tools("--max_diff",			ST_EXTARGS_TYPE::int_with_default,   1, 0, 0, 100),			//�Ƚϵ�����������������ֹͣ
		args_analyse_tools("--max_line",			ST_EXTARGS_TYPE::int_with_default,   1, 0, 0, 10000),			//�Ƚϵĺ���
		args_analyse_tools("--display",			ST_EXTARGS_TYPE::str_with_set_error, 1, 0, DisplayType),		//��ʾ����ķ�ʽ
		args_analyse_tools()  //���һ�������ڽ���
	};
	int cur_argc, ret = 0;

	//���һ������0����ʾ��ѡ������⣬û����������
	if ((cur_argc = args_analyse_process(argc, argv, args, 0)) < 0) {
		//������Ϣ�ں������Ѵ�ӡ
		args_analyse_print(args);
		usage(argv[0]);
		return -1;
	}

	/* �������� */
	//���ж����ޱ������
	if (!args[file1].existed() || !args[file2].existed()) {
		usage(*argv);
		cout << "����ָ������[--file1��--file2]" << endl;
		return -1;
	}

	/*���ļ�*/
	line_state f1, f2;
	f1.fin.open(args[file1].get_string(), ios::binary);
	if (!f1.fin.is_open()) {
		cout << "��1���ļ�[" << args[file1].get_string() << "]�޷���." << endl;
		return -1;
	}
	f2.fin.open(args[file2].get_string(), ios::binary);
	if (!f2.fin.is_open()) {
		cout << "��2���ļ�[" << args[file2].get_string() << "]�޷���." << endl;
		return -1;
	}

	/*���ݲ�����ʼ��*/
	f1.line_no = 0;
	f2.line_no = 0;
	int cnt_diff = 0;
	int max_diff_cnt = 0, max_line_cnt = 0;
	bool flag_diff = false;
	int trim_value = -1, display_value = -1;
	bool flag_blank = false, flag_LF = false;
	//max_line
	if (args[max_line].existed()) {
		max_line_cnt = args[max_line].get_int();
	}
	//max_diff
	if (args[max_diff].existed()) {
		max_diff_cnt = args[max_diff].get_int();
	}
	//trim_value
	if (args[trim].existed()) {
		for (int i = 0;; ++i)
			if (args[trim].get_string() == TrimType[i]) {
				trim_value = i;
				break;
			}
	}
	//display_value
	if (args[display].existed()) {
		for (int i = 0;; ++i)
			if (args[display].get_string() == DisplayType[i]) {
				display_value = i;
				break;
			}
	}
	//ignore_blank
	if (args[ignore_blank].existed()) {
		flag_blank = true;
	}
	//CR_CRLF_not_equal
	if (args[CR_CRLF_not_equal].existed()) {
		flag_LF = true;
	}
	//lineoffset
	if (args[lineoffset].existed() && args[lineoffset].get_int()) {
		if (args[lineoffset].get_int() < 0) {//file1
			for (int i = 1; i <= -1 * args[lineoffset].get_int(); ++i) {
				if (read_line(f1, args[file1].get_name(), trim_value, flag_LF))
					return -1;
				if (f1.fin.eof())
					break;
			}
			f1.line_no += -1 * args[lineoffset].get_int();
		}
		else {//file2
			for (int i = 1; i <= args[lineoffset].get_int(); ++i) {
				if (read_line(f2, args[file2].get_name(), trim_value, flag_LF))
					return -1;
				if (f2.fin.eof())
					break;
			}
			f2.line_no += args[lineoffset].get_int();
		}
	}
	//����ͻ
	if (flag_LF && trim_value >= 2) {
		usage(*argv);
		cout << "����[--CR_CRLF_not_equal]���ܺ�[--trim right/all]ͬʱ����." << endl;
		return -1;
	}

	if (display_value > 0) {
		cout << "�ȽϽ�������" << endl;
		cout << "====================================================================================================" << endl;
	}

	/*��ʼÿ�бȽ�*/
	while (1) {
		if (read_line(f1, args[file1].get_name(), trim_value, flag_LF))
			return -1;
		if (read_line(f2, args[file2].get_name(), trim_value, flag_LF))
			return -1;
		if (flag_blank) {
			while ((!f1.line_buf[0] || f1.left >= f1.right) && !f1.fin.eof())
				if (read_line(f1, args[file1].get_name(), trim_value, flag_LF))
					return -1;
			while ((!f2.line_buf[0] || f2.left >= f2.right) && !f2.fin.eof())
				if (read_line(f2, args[file2].get_name(), trim_value, flag_LF))
					return -1;
		}

		ostringstream msg;
		char tag_dif[1025] = {};
		memset(tag_dif, '0', 1024);
		msg << "��[" << f1.line_no << " / " << f2.line_no << "]�� - ";
		int ret = check_line(f1, f2, msg, tag_dif);

		if (ret) {
			++cnt_diff;
			if (display_value <= 0) {
				cout << "�ļ���ͬ." << endl;
				break;
			}
			cout << msg.str() << endl;
			if (display_value == 2) //�����
				surveyor(f1, f2);
			cout << "�ļ�1 : ";
			draw_line(f1, f2, tag_dif); //����ͬ
			cout << "�ļ�2 : ";
			draw_line(f2, f1, tag_dif); //����ͬ
			if (display_value == 2) {//hex
				cout << "�ļ�1(HEX) : " << endl;
				print_hex(f1.line_buf);
				if (!f1.len){
					if (f1.type == eof)
						cout << "<EOF>" << endl;
					else if (f1.is_empty)
						cout << "<EMPTY>" << endl;
				}
				cout << "�ļ�2(HEX) : " << endl;
				print_hex(f2.line_buf);
				if (!f2.len) {
					if (f2.type == eof)
						cout << "<EOF>" << endl;
					else if (f2.is_empty)
						cout << "<EMPTY>" << endl;
				}
			}
			cout << endl;
		}
		if (f1.fin.eof() || f2.fin.eof())
			break;
	}

	if (display_value > 0) {
		cout << "====================================================================================================" << endl;
	}

	/*û�в�ͬ*/
	if (!cnt_diff) {
		if (display_value <= 0)
			cout << "�ļ���ͬ." << endl;
		else
			cout << "��ָ�������������ȫһ��." << endl;
		if (display_value > 0) {
			cout << "====================================================================================================" << endl;
		}
	}

	//�в�ͬ
	if (cnt_diff && display_value > 0) {
		hint(cnt_diff);
		cout << "====================================================================================================" << endl;
	}

	return 0;
}

/* �����ļ�׼��
	1.txt �������ļ�
	2.txt ����1.txt�Ļ����ϣ�ĳЩ��ǰ���޿ո�
	3.txt ����1.txt�Ļ����ϣ�ĳЩ�к����޿ո�
	4.txt ����1.txt�Ļ����ϣ����һ��û�лس�
	5.txt ����1.txt�Ļ����ϣ���һЩ����
	6.txt ����1.txt�Ļ����ϣ���һЩ���У�����ĳЩ���пո��tab
	7.txt ����1.txt��ȫ��ͬ
	8.txt ����1.txt��Linux��ʽ��

txt_compare --file1 1.txt --file2 2.txt --trim left
txt_compare --file1 1.txt --file2 2.txt --trim all
txt_compare --file1 2.txt --file2 3.txt --trim all
txt_compare --file1 1.txt --file2 4.txt --trim right --ignore_blank
txt_compare --file1 1.txt --file2 4.txt --trim all --ignore_blank
txt_compare --file1 2.txt --file2 4.txt --trim all --ignore_blank
txt_compare --file1 3.txt --file2 4.txt --trim right --ignore_blank
txt_compare --file1 3.txt --file2 4.txt --trim all --ignore_blank
txt_compare --file1 1.txt --file2 5.txt --trim right --ignore_blank
txt_compare --file1 1.txt --file2 6.txt --ignore_blank --trim right
txt_compare --file1 5.txt --file2 6.txt --ignore_blank --trim all
txt_compare --file1 1.txt --file2 7.txt
txt_compare --file1 1.txt --file2 8.txt

rem ����ͬ������
txt_compare --file1 1.txt --file2 2.txt
txt_compare --file1 1.txt --file2 2.txt --trim right
txt_compare --file1 1.txt --file2 5.txt
txt_compare --file1 1.txt --file2 5.txt --trim right
txt_compare --file1 1.txt --file2 6.txt
txt_compare --file1 1.txt --file2 6.txt --ignore_blank
txt_compare --file1 1.txt --file2 8.txt --CR_CRLF_not_equal

*/