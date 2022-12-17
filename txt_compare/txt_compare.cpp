/* 2151613 毛宇录 计科 */
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

/* 允许添加需要的内容 */
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
			cout << "文件[" << file_name << "]的第(" << f.line_no << ")行不符合要求，超过最大长度[" << line_max_len << "]." << endl;
			return -1;
		}
		f.line_buf[count] = '\0';
		ch_before = ch;
	}
	f.len = count;
	if (!count)
		f.is_empty = 1;
	f.right = count - 1;
	//处理右空白
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
				msg << "第[" << p1 - f1.line_buf << "]个字符开始有差异：";
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
				msg << "文件1已结束/文件2仍有内容：";
			msg << "文件2的尾部有多余字符：";
		}
		for (; *p2; ++p2)
			tag_dif[p2 - f1.line_buf] = '1';
		return -1;
	}
	if (*p1 && !*p2 || f1.type != eof && f2.type == eof) {
		if (!flag_first) {
			if (f2.type == eof)
				msg << "文件1仍有内容/文件2已结束：";
			msg << "文件1的尾部有多余字符：";
		}
		for (; *p1; ++p1)
			tag_dif[p1 - f1.line_buf] = '1';
		return -2;
	}
	return 0;
}

void hint(int count)
{
	cout << "在指定检查条件下共" << count << "行有差异." << endl;
	cout << "阅读提示：" << endl;
	cout << "        1、空行用<EMPTY>标出" << endl;
	cout << "        2、文件结束用<EOF>标出" << endl;
	cout << "        3、两行相同列位置的差异字符用亮色标出" << endl;
	cout << "        4、每行中的CR/LF/VT/BS/BEL用X标出(方便看清隐含字符)" << endl;
	cout << "        5、每行尾的多余的字符用亮色标出，CR/LF/VT/BS/BEL用亮色X标出(方便看清隐含字符)" << endl;
	cout << "        6、每行最后用<CR>标出(方便看清隐含字符)" << endl;
	cout << "        7、中文因为编码问题，差异位置可能报在后半个汉字上，但整个汉字都亮色标出" << endl;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
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

	msg << setw(wkey) << ' ' << "必选项：" << endl;
	msg << setw(wopt) << ' ' << "--file1 name1              : 指定要比较的第1个文件名（必选）" << endl;
	msg << setw(wopt) << ' ' << "--file2 name2              : 指定要比较的第2个文件名（必选）" << endl;
	msg << endl;

	msg << setw(wkey) << ' ' << "可选项：" << endl;
	msg << setw(wopt) << ' ' << "--trim none/left/right/all     : 指定每行的空格/tab的忽略方式（无此项则默认为none）" << endl;
	msg << setw(wopt) << ' ' << "\tnone   : 每行均严格匹配" << endl;
	msg << setw(wopt) << ' ' << "\tleft   : 每行均忽略头部空格" << endl;
	msg << setw(wopt) << ' ' << "\tright  : 每行均忽略尾部空格" << endl;
	msg << setw(wopt) << ' ' << "\tall    : 每行均忽略头尾空格" << endl;
	msg << setw(wopt) << ' ' << "--lineoffset n                 : 指定文件错位的行数（无此项则n为0）" << endl;
	msg << setw(wopt) << ' ' << "\t取值[-100..100]，负数表示忽略file1的前n行，正数表示忽略file2的前n行" << endl;
	msg << setw(wopt) << ' ' << "--ignore_blank                 : 忽略文件中--trim后的所有空行(无此项则不忽略)" << endl;
	msg << setw(wopt) << ' ' << "--CR_CRLF_not_equal            : 不忽略Windows/Linux文件的换行符差异(无此项则忽略差异)" << endl;
	msg << setw(wopt) << ' ' << "--max_diff m                   : 指定文件错位的行数（无此项则m为0）" << endl;
	msg << setw(wopt) << ' ' << "\t取值[0..100]，表示满m个不同行则结束运行，不再进行后续的比较" << endl;
	msg << setw(wopt) << ' ' << "--max_line x                   : 指定文件比较的最大行数（无此项则x为0）" << endl;
	msg << setw(wopt) << ' ' << "\t取值[0..10000]，表示比较x行后则结束运行，不再进行后续的比较" << endl;
	msg << setw(wopt) << ' ' << "--display none/normal/detailed : 指定显示的信息（无此项则默认为none）" << endl;
	msg << setw(wopt) << ' ' << "\tnone   : 仅一行匹配与否的提示" << endl;
	msg << setw(wopt) << ' ' << "\tnormal : 每个差异行给出差异信息" << endl;
	msg << setw(wopt) << ' ' << "\tright  : 每个差异行给出更详细的差异信息" << endl;
	msg << endl;

	msg << "e.g.   " << procname << " --file1 my.txt --file2 std.txt" << endl;
	msg << setw(wopt) << ' ' << " : 比较my.txt和std.txt，全部匹配，仅一行输出" << endl;
	msg << "       " << procname << " --file1 my.txt --file2 std.txt --trim all" << endl;
	msg << setw(wopt) << ' ' << " : 比较my.txt和std.txt，每行均去除头尾空格，仅一行输出" << endl;
	msg << "       " << procname << " --file1 my.txt --file2 std.txt --lineoffset -2" << endl;
	msg << setw(wopt) << ' ' << " : 比较my.txt和std.txt，忽略my.txt的前2行(即my.txt的第3行与std.txt的第1行进行比较，每行严格匹配)，仅一行输出" << endl;
	msg << "       " << procname << " --file1 my.txt --file2 std.txt --trim left --lineoffset 3" << endl;
	msg << setw(wopt) << ' ' << " : 比较my.txt和std.txt，忽略std.txt的前3行(即my.txt的第1行与std.txt的第4行进行比较)，每行去除头部空格，仅一行输出" << endl;
	msg << "       " << procname << " --file1 my.txt --file2 std.txt --ignore_blank" << endl;
	msg << setw(wopt) << ' ' << " : 比较my.txt和std.txt，忽略文件中的所有空行，仅一行输出" << endl;
	msg << "       " << procname << " --file1 my.txt --file2 std.txt --ignore_blank --trim right" << endl;
	msg << setw(wopt) << ' ' << " : 比较my.txt和std.txt，忽略文件中去除头尾空格后的所有空行，仅一行输出" << endl;
	msg << "       " << procname << " --file1 my.txt --file2 std.txt --max_diff 3" << endl;
	msg << setw(wopt) << ' ' << " : 比较my.txt和std.txt，全部匹配，有3行不匹配后结束运行，仅一行输出" << endl;
	msg << "       " << procname << " --file1 my.txt --file2 std.txt --max_line 7" << endl;
	msg << setw(wopt) << ' ' << " : 比较my.txt和std.txt，全部匹配，仅比较前7行，仅一行输出" << endl;
	msg << "       " << procname << " --file1 my.txt --file2 std.txt --CR_CRLF_not_queal" << endl;
	msg << setw(wopt) << ' ' << " : 比较my.txt和std.txt，全部匹配，不忽略Windows/Linux的文件差异，仅一行输出" << endl;
	msg << "       " << procname << " --file1 my.txt --file2 std.txt --display normal" << endl;
	msg << setw(wopt) << ' ' << " : 比较my.txt和std.txt，全部匹配，不匹配的行显示信息" << endl;
	msg << "       " << procname << " --file1 my.txt --file2 std.txt --display detailed" << endl;
	msg << setw(wopt) << ' ' << " : 比较my.txt和std.txt，全部匹配，不匹配的行显示详细信息" << endl;
	msg << endl;
	cout << msg.str() << endl;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int main(int argc, char** argv)
{
	/* 因为引入了 lib_aat_tools.lib，此处先检查大小是否符合要求 */
	if (sizeof(args_analyse_tools) != 200) {
		cout << "class args_analyse_tools 不是200字节，如果使用 lib_aat_tools.lib 中的函数则可能出错" << endl;
		return -1;
	}

	/* 指定去除空格的方式 */
	const string TrimType[] = { "none",	"left",	"right",	"all", "" };
	/* 指定信息的显示方式 */
	const string DisplayType[] = { "none",	"normal",	"detailed", "" };
	args_analyse_tools args[] = {
		args_analyse_tools("--help",				ST_EXTARGS_TYPE::boolean, 0, false),		//显示帮助信息
		args_analyse_tools("--debug",				ST_EXTARGS_TYPE::boolean, 0, false),		//显示调试信息（不要求与demo完全相同）
		args_analyse_tools("--file1",				ST_EXTARGS_TYPE::str, 1, string("")),		//用于比较的文件名1
		args_analyse_tools("--file2",				ST_EXTARGS_TYPE::str, 1, string("")),		//用于比较的文件名2
		args_analyse_tools("--trim",				ST_EXTARGS_TYPE::str_with_set_error, 1, 0, TrimType),		//空格的比较方式
		args_analyse_tools("--lineoffset",		ST_EXTARGS_TYPE::int_with_default,   1, 0, -100, 100),		//指定左右文件的行差
		args_analyse_tools("--ignore_blank",		ST_EXTARGS_TYPE::boolean, 0, false),							//忽略空行
		args_analyse_tools("--CR_CRLF_not_equal",	ST_EXTARGS_TYPE::boolean, 0, false),							//
		args_analyse_tools("--max_diff",			ST_EXTARGS_TYPE::int_with_default,   1, 0, 0, 100),			//比较的最大错误数，超出则停止
		args_analyse_tools("--max_line",			ST_EXTARGS_TYPE::int_with_default,   1, 0, 0, 10000),			//比较的函数
		args_analyse_tools("--display",			ST_EXTARGS_TYPE::str_with_set_error, 1, 0, DisplayType),		//显示差异的方式
		args_analyse_tools()  //最后一个，用于结束
	};
	int cur_argc, ret = 0;

	//最后一个参数0，表示除选项参数外，没有其它参数
	if ((cur_argc = args_analyse_process(argc, argv, args, 0)) < 0) {
		//错误信息在函数中已打印
		args_analyse_print(args);
		usage(argv[0]);
		return -1;
	}

	/* 后续代码 */
	//先判断有无必须参数
	if (!args[file1].existed() || !args[file2].existed()) {
		usage(*argv);
		cout << "必须指定参数[--file1和--file2]" << endl;
		return -1;
	}

	/*打开文件*/
	line_state f1, f2;
	f1.fin.open(args[file1].get_string(), ios::binary);
	if (!f1.fin.is_open()) {
		cout << "第1个文件[" << args[file1].get_string() << "]无法打开." << endl;
		return -1;
	}
	f2.fin.open(args[file2].get_string(), ios::binary);
	if (!f2.fin.is_open()) {
		cout << "第2个文件[" << args[file2].get_string() << "]无法打开." << endl;
		return -1;
	}

	/*根据参数初始化*/
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
	//检查冲突
	if (flag_LF && trim_value >= 2) {
		usage(*argv);
		cout << "参数[--CR_CRLF_not_equal]不能和[--trim right/all]同时存在." << endl;
		return -1;
	}

	if (display_value > 0) {
		cout << "比较结果输出：" << endl;
		cout << "====================================================================================================" << endl;
	}

	/*开始每行比较*/
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
		msg << "第[" << f1.line_no << " / " << f2.line_no << "]行 - ";
		int ret = check_line(f1, f2, msg, tag_dif);

		if (ret) {
			++cnt_diff;
			if (display_value <= 0) {
				cout << "文件不同." << endl;
				break;
			}
			cout << msg.str() << endl;
			if (display_value == 2) //画标尺
				surveyor(f1, f2);
			cout << "文件1 : ";
			draw_line(f1, f2, tag_dif); //画不同
			cout << "文件2 : ";
			draw_line(f2, f1, tag_dif); //画不同
			if (display_value == 2) {//hex
				cout << "文件1(HEX) : " << endl;
				print_hex(f1.line_buf);
				if (!f1.len){
					if (f1.type == eof)
						cout << "<EOF>" << endl;
					else if (f1.is_empty)
						cout << "<EMPTY>" << endl;
				}
				cout << "文件2(HEX) : " << endl;
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

	/*没有不同*/
	if (!cnt_diff) {
		if (display_value <= 0)
			cout << "文件相同." << endl;
		else
			cout << "在指定检查条件下完全一致." << endl;
		if (display_value > 0) {
			cout << "====================================================================================================" << endl;
		}
	}

	//有不同
	if (cnt_diff && display_value > 0) {
		hint(cnt_diff);
		cout << "====================================================================================================" << endl;
	}

	return 0;
}

/* 测试文件准备
	1.txt ：正常文件
	2.txt ：在1.txt的基础上，某些行前面无空格
	3.txt ：在1.txt的基础上，某些行后面无空格
	4.txt ：在1.txt的基础上，最后一行没有回车
	5.txt ：在1.txt的基础上，多一些空行
	6.txt ：在1.txt的基础上，多一些空行，其中某些行有空格和tab
	7.txt ：和1.txt完全相同
	8.txt ：是1.txt的Linux格式版

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

rem 不相同的例子
txt_compare --file1 1.txt --file2 2.txt
txt_compare --file1 1.txt --file2 2.txt --trim right
txt_compare --file1 1.txt --file2 5.txt
txt_compare --file1 1.txt --file2 5.txt --trim right
txt_compare --file1 1.txt --file2 6.txt
txt_compare --file1 1.txt --file2 6.txt --ignore_blank
txt_compare --file1 1.txt --file2 8.txt --CR_CRLF_not_equal

*/