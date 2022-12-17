/* 2151613 ë��¼ �ƿ� */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <string>
//�ɸ�����Ҫ�ټ���������Ҫ��ͷ�ļ�
#include "../include/class_aat.h"
using namespace std;

#define parameter_count 3
#define parameter_count 3
#define name_size       8
#define info_size       8

/* ���������������������Ҳ���Խ��Զ��庯����������cpp�� */
int check_ip(const string def)
{
	string def_ip = ".";
	(def_ip += def) += ".";
	int dot_num = 0;
	int str_len = def_ip.size();
	int value = 0;
	for (int i = 0; i < str_len; ++i) {
		if (def_ip[i] == '.') {
			if (i && def_ip[i - 1] == '.') //���������
				return -1;
			++dot_num;
			if (dot_num > 5) //�㳬��5����
				return -1;
			if (value >= 256) //����value
				return -1;
			value = 0;
		}
		else if (def_ip[i] >= '0' && def_ip[i] <= '9')
			(value *= 10) += (def_ip[i] - '0');
		else
			return -1;
	}
	if (dot_num != 5)
		return -1;
	return 0;
}
/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int main(int argc, char* argv[])
{
	args_analyse_tools args[] = {
		args_analyse_tools("--l",      ST_EXTARGS_TYPE::int_with_default, 1, 64, 32, 64000),
		args_analyse_tools("--n",      ST_EXTARGS_TYPE::int_with_default, 1, 4, 1, 1024),
		args_analyse_tools("--t",      ST_EXTARGS_TYPE::boolean,   0, false),
		args_analyse_tools()
	};
	if (argc == 1) { //usage
		args_analyse_print(args);
		return -1;
	}
	int ret = check_ip(*(argv + argc - 1)); //�ȼ��IP��ַ
	if (ret < 0) {
		cout << "IP��ַ����" << endl;
		return -1;
	}
	int need_fixed_args = 1;
	int cur_argc;
	if ((cur_argc = args_analyse_process(argc, argv, args, need_fixed_args)) < 0)
		return -1;
	cout << "�������ͨ��" << endl;
	cout << args[0].get_name() << " ������" << args[0].get_int() << endl;
	cout << args[1].get_name() << " ������" << args[1].get_int() << endl;
	cout << args[2].get_name() << " ������" << args[2].existed() << endl;
	cout << "IP��ַ��" << *(argv + argc - 1) << endl;
	return 0;
}

