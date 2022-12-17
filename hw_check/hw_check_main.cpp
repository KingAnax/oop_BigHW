/* 2151613 毛宇录 计科 */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <cstring>
using namespace std;

#include "hw_check.h"
#include "../include/class_aat.h"

struct student_info {
	char class_name[9];
	char no[8];
	char name[128];
	char file_1;
	char file_2;
	char stu_list[30][100] = { '\0' };
	char paoqi = '\0';
	char count = '\0';
	struct student_info* next;
};

static int check_debug(const char* p, ostringstream& msg)
{
	if (strlen(p) != 5) {
		msg << "参数[" << "--debug" << "]必须为5位0/1";
		return -1;
	}
	for (int i = 0; i < 5; ++i) {
		if (*(p + i) < '0' || *(p + i) > '1') {
			msg << "参数[" << "--debug" << "]的第[" << i + 1 << "]位不是0/1";
			return -1;
		}
	}
	return 0;
}

static int Read(const char* str, char* p, const int num)
{
	int i = 0;
	int count = 0;
	while (*(str + i) == ' ' || *(str + i) == '\t')
		++i;
	if (*(str + i) == '\0') {
		*p = '\0';
		return 0;
	}
	while (count < num - 1) {
		if (*(str + i) == ' ' || *(str + i) == '\t')
			break;
		if (*(str + i) == '*' && *(str + i + 1) == '/') {
			*p = '\0';
			return 1;
		}
		if (*(str + i) == '\0') {
			*p = '\0';
			return 1;
		}
		*p = *(str + i);
		++p;
		++count;
		++i;
	}
	*p = '\0';
	return 0;
}

static void rank_list(struct student_info* p)
{
	for (unsigned int i = 0; i < sizeof(p->stu_list) / sizeof(*p->stu_list) - 1; ++i) {
		for (unsigned int j = 0; j < sizeof(p->stu_list) / sizeof(*p->stu_list) - 1 - i; ++j) {
			if (strcmp(*(p->stu_list + j), *(p->stu_list + j + 1)) > 0 && strlen(*(p->stu_list + j + 1))) {
				char temp[100];
				strcpy(temp, *(p->stu_list + j));
				strcpy(*(p->stu_list + j), *(p->stu_list + j + 1));
				strcpy(*(p->stu_list + j + 1), temp);
			}
		}
	}
}

static void stu_rank(struct student_info* head, int sum)
{
	struct student_info* p = head;
	int check;
	struct student_info blank;

	//冒泡排序
	//先排课号在排学号
	for (int i = 0; i < sum - 1; ++i) {
		check = 0;
		p = head;
		int count = 0;
		while (count < sum - 1 - i) {
			if (strcmp(p->class_name, (p->next)->class_name) > 0) {
				strcpy(blank.class_name, p->class_name);
				strcpy(p->class_name, (p->next)->class_name);
				strcpy((p->next)->class_name, blank.class_name);

				strcpy(blank.no, p->no);
				strcpy(p->no, (p->next)->no);
				strcpy((p->next)->no, blank.no);

				strcpy(blank.name, p->name);
				strcpy(p->name, (p->next)->name);
				strcpy((p->next)->name, blank.name);

				blank.file_1 = p->file_1;
				p->file_1 = (p->next)->file_1;
				(p->next)->file_1 = blank.file_1;

				blank.file_2 = p->file_2;
				p->file_2 = (p->next)->file_2;
				(p->next)->file_2 = blank.file_2;

				check = 1;
			}
			else if (!strcmp(p->class_name, (p->next)->class_name) && strcmp(p->no, (p->next)->no) > 0) {
				strcpy(blank.class_name, p->class_name);
				strcpy(p->class_name, (p->next)->class_name);
				strcpy((p->next)->class_name, blank.class_name);

				strcpy(blank.no, p->no);
				strcpy(p->no, (p->next)->no);
				strcpy((p->next)->no, blank.no);

				strcpy(blank.name, p->name);
				strcpy(p->name, (p->next)->name);
				strcpy((p->next)->name, blank.name);

				blank.file_1 = p->file_1;
				p->file_1 = (p->next)->file_1;
				(p->next)->file_1 = blank.file_1;

				blank.file_2 = p->file_2;
				p->file_2 = (p->next)->file_2;
				(p->next)->file_2 = blank.file_2;

				check = 1;
			}
			p = p->next;
			count++;
		}
		if (check == 0)
			break;
	}
}

static int read_stulist(ostringstream& msg, char course_id[64], struct student_info*& head)
{
	char dat_name[64] = "./source/";
	strcpy(dat_name + 9, course_id);
	strcpy(dat_name + 9 + strlen(course_id), ".dat");
	dat_name[13 + strlen(course_id)] = '\0';

	fstream fin;
	fin.open(dat_name, ios::binary | ios::in);
	if (fin.fail()) {
		msg << "无法打开" << dat_name << endl;
		return -1;
	}

	char line[240];
	int line_num = 1;

	//首先把注释读完
	char ch = fin.peek();
	while (!fin.eof() && (ch == '#' || ch == '\n')) {
		if (ch == '#')
			msg << "\t--> 学生名单[" << dat_name << "]中的第[" << line_num << "]行为注释行，忽略" << endl;
		fin.getline(line, 240);
		fin.clear();
		ch = fin.peek();
		line_num++;
	}

	//接下来读取每一个学生信息
	struct student_info* p = NULL, * q = NULL;
	int count = 0;

	while (!fin.fail() && !fin.eof()) {
		char class_name_new[9];
		char no_new[9];
		fin >> class_name_new >> no_new;

		if (!*class_name_new || fin.eof())
			continue;

		if (count) {
			int check = 0;
			struct student_info* n;
			n = head;
			while (n != NULL) {
				if (!strcmp(no_new, n->no)) {
					check = 1;
					break;
				}
				n = n->next;
			}
			if (check) {
				msg << "\t--> 学生名单[" << dat_name << "]中的第[" << line_num << "]行学号[" << no_new << "]重复，忽略" << endl;
				fin.getline(line, 240);
				line_num++;
				continue;
			}
		}

		if (count)
			q = p;
		p = new(nothrow)student_info;
		if (p == NULL) {
			msg << "空间不足" << endl;
			return -1;
		}
		if (count == 0)
			head = p;
		else
			q->next = p;

		strcpy(p->no, no_new);
		strcpy(p->class_name, class_name_new);
		fin >> p->name >> p->file_1 >> p->file_2;

		p->next = NULL;
		count++;
		line_num++;
	}

	msg << "读取完成，共[" << line_num - 1 << "]行有内容，去重后学生总数[" << count << "]个" << endl;

	fin.close();
	return count;
}

static int print_stulist(ostringstream& msg, student_info* head, int sum)
{
	stu_rank(head, sum);
	msg << "序号\t课号\t学号\t姓名\t原始程序正确\t校验程序正确" << endl;
	struct student_info* p;
	p = head;
	int count = 1;
	while (p != NULL) {
		msg << count << '#' << '\t';
		msg << p->class_name << '\t';
		msg << p->no << '\t';
		msg << p->name << '\t';
		msg << p->file_1 << '\t';
		msg << p->file_2 << endl;
		count++;
		p = p->next;
	}
	return 0;
}

static int read_2nd_line(ostringstream& msg, const student_info* head, char* filename)
{
	msg << "序号\t课号\t学号\t姓名\t文件名\t分析结果" << endl;
	struct student_info* p;
	p = (student_info*)head;
	int count = 1;
	while (p != NULL) {
		char line[18];
		char file_dir[256];
		char file_own[256];

		sprintf(line, "%d%c", count, '#');
		strcpy(file_own, "./source");
		sprintf(file_dir, "%c%s%c%s", '/', p->class_name, '-', filename);
		strcat(file_own, file_dir);
		sprintf(file_dir, "%c%s%c%s%c%s", '/', p->no, '-', p->name, '-', filename);
		strcat(file_own, file_dir);
		msg << line << '\t';
		msg << p->class_name << '\t';
		msg << p->no << '\t';
		msg << p->name << '\t';
		msg << filename << '\t';

		fstream fin;
		fin.open(file_own, ios::binary | ios::in);
		if (fin.fail()) {
			msg << "未提交" << endl;
			count++;
			p->file_2 = 0;
			p = p->next;
			continue;
		}

		char sec_line[500];

		fin.getline(sec_line, 500, '\n');

		while (!*sec_line || (*sec_line == '\r' && !*(sec_line + 1)))
			fin.getline(sec_line, 500, '\n');

		//此时为第二行
		fin.getline(sec_line, 500, '\n');

		while (!*sec_line || (*sec_line == '\r' && !*(sec_line + 1)))
			fin.getline(sec_line, 500, '\n');

		int sec_line_len = (int)strlen(sec_line);

		if (sec_line[sec_line_len - 1] == '\r') {
			sec_line[sec_line_len - 1] = '\0';
			--sec_line_len;
		}

		if (sec_line_len > 256) {
			msg << "非空行超过了合理长度[256]字节." << endl;
			p = p->next;
			++count;
			continue;
		}

		int pk = 0;
		while (*(sec_line + pk) == ' ' || *(sec_line + pk) == '\t')
			++pk;
		if (pk) {
			char temp[256];
			strcpy(temp, sec_line + pk);
			strcpy(sec_line, temp);
			sec_line_len = strlen(sec_line);
		}

		int pos = sec_line_len - 1;
		while (*(sec_line + pos) == ' ' || *(sec_line + pos) == '\t')
			--pos;

		int cur_line = 0;

		if (*(sec_line) == '/' && *(sec_line + 1) == '/')
			cur_line = 1;
		else if (*(sec_line) == '/' && *(sec_line + 1) == '*' && *(sec_line + pos) == '/' && *(sec_line + pos - 1) == '*') {
			cur_line = 2;
			sec_line[pos - 1] = '\0';
			sec_line_len -= 2;
		}

		if (!cur_line) {
			msg << "第2行信息有错[不是//或/*开头，或者以/*开头但*/不在同一行]" << endl;
			fin.close();
			count++;
			p = p->next;
			continue;
		}

		int current = 0;

		int i = 2;
		int stu_no = 1;
		int current_no = 0;
		int flag = 0;
		while (1) {
			if (flag)
				break;
			while ((*(sec_line + i) == ' ' || *(sec_line + i) == '\t'))
				++i;
			if (i > sec_line_len - 1 || sec_line[i] == '\0')
				break;
			char no[64] = "";
			flag = Read(sec_line + i, no, no_max);

			i += strlen(no);
			while (*(sec_line + i) == ' ' || *(sec_line + i) == '\t')
				++i;

			char name[256] = "";
			if (!flag)
				flag = Read(sec_line + i, name, name_max);

			if (flag && !*no)
				break;

			if ((flag && !*name) || (*no && !*name)) {
				if (current)
					msg << "\t\t\t\t\t";
				msg << "第[" << stu_no - 1 << "]个学生后面的信息不全，忽略" << endl;
				++current;
				break;
			}

			i += strlen(name);

			//检查学号，姓名是否正确
			struct student_info* q = (student_info*)head;
			int is_exist = 0;
			int chongfu = 0;//自己学号重复
			int chongfu_2 = 0;//别人学号重复

			while (q != NULL) {
				if (strlen(no) != 7)
					break;
				if (!strcmp(p->no, no)) {
					chongfu = 1;
					break;
				}
				if (!strcmp(q->no, no) && !strcmp(q->name, name)) {
					int j = 0;
					while (**(p->stu_list + j)) {
						if (!strncmp(no, *(p->stu_list + j), 7))
							chongfu_2 = 1;
						++j;
					}
					if (chongfu_2)
						break;
					sprintf(*(p->stu_list + current_no), "%s%c%s", no, '\t', name);
					++current_no;
					is_exist = 1;
					break;
				}
				q = q->next;
			}
			if (!is_exist) {
				if (chongfu) {
					if (current)
						msg << "                                        ";
					msg << "第[" << stu_no << "]项写了自己，耍无赖么？" << endl;
					++current;
					break;
				}
				else if (chongfu_2) {
					if (current)
						msg << "\t\t\t\t\t";
					msg << "互验列表第[" << stu_no << "]项的学号[" << no << "]重复，忽略" << endl;
					++current;
				}
				else {
					if (current)
						msg << "\t\t\t\t\t";
					msg << "第[" << stu_no << "]项的学号[" << no << "]/姓名[" << name << "]不正确，忽略" << endl;
					++current;
				}
			}
			++stu_no;
		}

		//输出正确
		if (!current)
			msg << "ok" << endl;
		if (**p->stu_list) {
			rank_list(p);
			msg << "\t读到的正确互验者" << endl;
			int i = 0;
			while (**(p->stu_list + i)) {
				msg << '\t' << i + 1 << '\t' << *(p->stu_list + i) << endl;
				++i;
				p->count = i;
			}
		}

		fin.close();
		count++;
		p = p->next;
	}
	return 0;
}

static int print_2nd_line(ostringstream& msg, const student_info* head)
{
	msg << "序号	课号	学号	姓名" << endl;
	student_info* p = (student_info*)head;

	int count = 1;
	while (p != NULL) {
		msg << count << '#' << '\t';
		msg << p->class_name << '\t';
		msg << p->no << '\t';

		if (strlen(*p->stu_list)) {
			msg << p->name << endl;
			int i = 0;
			while (p != NULL && strlen(*(p->stu_list + i))) {
				int check = 0;
				msg << '\t';
				msg << '$' << i + 1 << '\t';
				msg << *(p->stu_list + i) << '\t';
				student_info* q = (student_info*)head;
				while (q != NULL) {
					if (!strncmp(q->no, *(p->stu_list + i), 7)) {
						int j = 0;
						while (strlen(*(q->stu_list + j))) {
							if (!strncmp(*(q->stu_list + j), p->no, 7))
								check = 1;
							++j;
						}
						break;
					}
					q = q->next;
				}
				if (check)
					msg << "ok" << endl;
				else {
					msg << "抛弃了你" << endl;
					if (p)
						++(p->paoqi);
				}
				++i;
			}
		}
		else
			msg << p->name << "\t无有效匹配项" << endl;

		if (p)
			p = p->next;

		++count;
	}
	return 0;
}

static int print_finalscore(ostringstream& msg, const student_info* head)
{
	msg << "序号	课号	学号	姓名	原始程序得分	检查程序原始分	检查程序扣分1	检查程序扣分2	检查程序总分" << endl;
	student_info* p = (student_info*)head;

	int count = 1;
	while (p != NULL) {
		msg << count << '#' << '\t';
		msg << p->class_name << '\t';
		msg << p->no << '\t';
		msg << p->name << '\t';

		int score_1, score_2;

		if (p->file_1 == '1') {
			score_1 = 100;
			msg << score_1 << '\t';
		}
		else {
			score_1 = 0;
			msg << score_1 << '\t';
		}

		if (p->file_2 == '1') {
			score_2 = 100;
			msg << score_2 << '\t';
		}
		else {
			score_2 = 0;
			msg << score_2 << '\t';
		}

		int error_1 = 0;
		int error_2 = 0;

		//判断是否被抛弃
		error_1 = (int)p->paoqi * 100 * -1;

		//先判断个数
		int n = 0;
		while (*(*p->stu_list + n))
			++n;
		if (p->count < 5)
			error_2 = (5 - p->count) * 20 * -1;

		//再判断对方有错


		msg << error_1 << '\t' << error_2 << '\t';
		msg << score_2 + error_1 + error_2 << endl;

		if (p)
			p = p->next;

		++count;
	}
	return 0;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：具体略，实际使用时，放入另一个cpp(例：hw_check_secondline.cpp)更合理
 ***************************************************************************/
int check_secondline(const string& cno, const string &stulist_fname, const string& filename, const string &debug)
{
	cout << "开始进行源程序文件次行检查..." << endl;//本次作业要求实现，本函数要改动
	ostringstream msg;

	int debug_p = 0;
	char debug_info[64] = { 0 };
	for (; debug[debug_p]; ++debug_p)
		debug_info[debug_p] = cno[debug_p];
	debug_info[debug_p] = '\0';

	if (check_debug(debug_info, msg) < 0) {
		cout << msg.str() << endl;
		return -1;
	}

	char course_id[9];
	for (int i = 0; cno[i]; ++i)
		course_id[i] = cno[i];
	course_id[8] = '\0';

	char file_name[256];
	int file_p = 0;
	for (; filename[file_p]; ++file_p)
		file_name[file_p] = filename[file_p];
	file_name[file_p] = '\0';

	/* 允许加入其它语句，但不能有cout */
	int ret = 0;

	//建立链表
	struct student_info* head = NULL;

	/* 读课号.dat */
	msg << "1.读取课号配置文件" << endl;
	ret = read_stulist(msg, course_id, head); //允许带返回值（也可以不要），参数自行约定，其中有一个是msg 
	/* 允许加入其它语句(也可以不要)，但不能有cout */
	if (debug[0] == 1)
		cout << msg.str() << endl;

	/* 允许加入其它语句，但不能有cout */

	msg.str(""); //清空msg中的信息
	msg << "2.按课号+学号排序的学生名单" << endl;
	ret = print_stulist(msg, head, ret); //允许带返回值（也可以不要），参数自行约定，其中有一个是msg 
	/* 允许加入其它语句(也可以不要)，但不能有cout */
	if (debug[1] == 1)
		cout << msg.str() << endl;

	/* 允许加入其它语句，但不能有cout */

	msg.str(""); //清空msg中的信息
	msg << "3.所有学生读取第2行的解析信息" << endl;
	ret = read_2nd_line(msg, head, file_name); //允许带返回值（也可以不要），参数自行约定，其中有一个是msg 
	/* 允许加入其它语句(也可以不要)，但不能有cout */
	if (debug[2] == 1)
		cout << msg.str() << endl;

	/* 允许加入其它语句，但不能有cout */

	/* 将双方进行信息匹配 */
	msg.str(""); //清空msg中的信息
	msg << "4.所有学生的第2行互验匹配结果" << endl;
	ret = print_2nd_line(msg, head); //允许带返回值（也可以不要），参数自行约定，其中有一个是msg 
	/* 允许加入其它语句(也可以不要)，但不能有cout */
	if (debug[3] == 1)
		cout << msg.str() << endl;

	/* 允许加入其它语句，但不能有cout */

	/* 再根据通过与否进行检查 */
	msg.str(""); //清空msg中的信息
	msg << "5.所有学生的第2行互验最终得分" << endl;
	ret = print_finalscore(msg, head); //允许带返回值（也可以不要），参数自行约定，其中有一个是msg 
	/* 允许加入其它语句(也可以不要)，但不能有cout */
	if (debug[4] == 1)
		cout << msg.str() << endl;

	/* 允许加入其它语句，但不能有cout */

	//释放
	struct student_info* p = NULL, * q = NULL;

	p = head;
	while (p) {
		q = p->next;
		delete[]p;
		p = q;
	}
	return 0;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：本次作业不要求实现，本函数不要改动
 ***************************************************************************/
int check_firstline(const string& cno, const string &stilist_fname, const string& filename)
{
	cout << "开始进行源程序文件首行检查..." << endl;
	return 0;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
 ***************************************************************************/
static void usage(const char* const procname, const int args_num)
{
	const int wkey = 7 + strlen(procname) + 1;
	const int wopt = 7 + strlen(procname) + 4;

	cout << endl;
	cout << "Usage: " << procname << " { --firstline | --secondline  }" << endl;
	cout << setw(wkey) << ' ' << "{ --cno xxx }" << endl;
	cout << setw(wkey) << ' ' << "{ --filename xxx/all }" << endl; //约定不允许实际文件名为all
	cout << setw(wkey) << ' ' << "{ --stulist_fname xxx }" << endl;
	cout << setw(wkey) << ' ' << "{ --debug 11111 }" << endl;
	cout << endl;

	cout << setw(wkey) << ' ' << "必选项：指定检查类型(多选一)" << endl;
	cout << setw(wopt) << ' ' << "--firstline     : 首行检查" << endl;
	cout << setw(wopt) << ' ' << "--secondline    : 次行检查" << endl;
	cout << setw(wkey) << ' ' << "必选项：" << endl;
	cout << setw(wopt) << ' ' << "--cno           : 课号" << endl;
	cout << setw(wopt) << ' ' << "--filename      : 文件名(all表示全部)" << endl;
	cout << setw(wopt) << ' ' << "--stulist_fname : 对应的学生列表文件名" << endl;
	cout << setw(wkey) << ' ' << "可选项：" << endl;
	cout << setw(wopt) << ' ' << "--debug         : Debug选项(仅适用于--secondline，默认11111)" << endl;
	cout << endl;

	cout << "e.g.   " << procname << " --firstline --cno 100692 --filename 3-b1.cpp --stulist_fname 100692.txt               : 检查100692课程的3-b1.cpp的首行" << endl;
	cout << "       " << procname << " --firstline --cno 100692 --filename all --stulist_fname 100692-firstline.txt          : 检查100692课程的全部文件的首行" << endl;
	cout << "       " << procname << " --secondline --cno 100742 --filename 15-b5.c --stulist_fname 10108001.dat               : 检查100742课程的15-b5.c的次行，输出全部信息" << endl;
	cout << "       " << procname << " --secondline --cno 100742 --filename 15-b5.c --stulist_fname 10108001.dat --debug 01001 : 检查100742课程的15-b5.c的次行，仅输出2、5项信息" << endl;
	cout << endl;

	if (args_num == 1) {
		cout << endl << endl << "请在cmd下加参数运行." << endl << endl;
		system("pause");
	}
}

/* enum的顺序要和args的排列顺序保持一致
   不用enum class 只是不想每次都做强制转换 */
enum OPT_ARGS { OPT_ARGS_HELP = 0, OPT_ARGS_FIRSTLINE, OPT_ARGS_SECONDLINE, OPT_ARGS_COURSEID, OPT_ARGS_FILENAME, OPT_ARGS_STULIST_FNAME, OPT_ARGS_DEBUG };

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int main(int argc, char** argv)
{
	args_analyse_tools args[] = {
		args_analyse_tools("--help", ST_EXTARGS_TYPE::boolean, 0, false),
		args_analyse_tools("--firstline", ST_EXTARGS_TYPE::boolean, 0, false),
		args_analyse_tools("--secondline", ST_EXTARGS_TYPE::boolean, 0, false),
		args_analyse_tools("--courseid", ST_EXTARGS_TYPE::str, 1, string("")),
		args_analyse_tools("--filename", ST_EXTARGS_TYPE::str, 1, string("")),
		args_analyse_tools("--stulist_fname", ST_EXTARGS_TYPE::str, 1, string("")),
		args_analyse_tools("--debug", ST_EXTARGS_TYPE::str, 1, string("11111")),
		args_analyse_tools()  //最后一个，用于结束
	};

	int cur_argc, ret = 0;

	//最后一个参数1，表示除选项参数外，还有其它参数
	if ((cur_argc = args_analyse_process(argc, argv, args, 0)) < 0) {
		//错误信息在函数中已打印
		return -1;
	}

	/* 需要自己实现 */
	args_analyse_print(args);

	/* 对help做特殊处理 */
	if (args[OPT_ARGS_HELP].existed()) {
		//只要有 --help，其它参数都忽略，显示帮助即可
		usage(argv[0], argc);
		return -1; //执行完成直接退出
	}

	/* 检查参数互斥性 */
	if (args[OPT_ARGS_FIRSTLINE].existed() + args[OPT_ARGS_SECONDLINE].existed() != 1) {
		usage(argv[0], argc);
		cout << "参数[" << args[OPT_ARGS_FIRSTLINE].get_name() << "|" << args[OPT_ARGS_SECONDLINE].get_name() << "]必须指定一个且只能指定一个" << endl;
		return -1;
	}

	/* 判断必选项是否存在 */
	if (args[OPT_ARGS_COURSEID].existed() == 0) {
		cout << "必须指定参数[" << args[OPT_ARGS_COURSEID].get_name() << "]" << endl;
		usage(argv[0], argc);
		return -1;
	}

	/* 判断必选项是否存在 */
	if (args[OPT_ARGS_FILENAME].existed() == 0) {
		cout << "必须指定参数[" << args[OPT_ARGS_FILENAME].get_name() << "]" << endl;
		usage(argv[0], argc);
		return -1;
	}

	/* 判断必选项是否存在 */
	if (args[OPT_ARGS_STULIST_FNAME].existed() == 0) {
		cout << "必须指定参数[" << args[OPT_ARGS_STULIST_FNAME].get_name() << "]" << endl;
		usage(argv[0], argc);
		return -1;
	}

	/* 判断 --firstline 和 --debug 是否冲突 */
	if (args[OPT_ARGS_FIRSTLINE].existed() + args[OPT_ARGS_DEBUG].existed() == 2) {
		cout << "参数[" << args[OPT_ARGS_FIRSTLINE].get_name() << "]不需要[" << args[OPT_ARGS_DEBUG].get_name() << "]" << endl;
		usage(argv[0], argc);
		return -1;
	}

	/* 判断 --secondline 和 --filename all 是否冲突 */
	if (args[OPT_ARGS_SECONDLINE].existed()) {
		if (args[OPT_ARGS_FILENAME].get_string() == "all") {
			cout << "参数[" << args[OPT_ARGS_SECONDLINE].get_name() << "]的[" << args[OPT_ARGS_SECONDLINE].get_name() << "]不能为all" << endl;
			usage(argv[0], argc);
			return -1;
		}
	}

	if (args[OPT_ARGS_FIRSTLINE].existed()) {
		/* 进行首行检查 */
		check_firstline(args[OPT_ARGS_COURSEID].get_string(), args[OPT_ARGS_STULIST_FNAME].get_string(), args[OPT_ARGS_FILENAME].get_string());
	}
	else if (args[OPT_ARGS_SECONDLINE].existed()) {
		/* 进行次行检查 */
		check_secondline(args[OPT_ARGS_COURSEID].get_string(), args[OPT_ARGS_STULIST_FNAME].get_string(), args[OPT_ARGS_FILENAME].get_string(), args[OPT_ARGS_DEBUG].get_string());
	}

	return 0;
}
