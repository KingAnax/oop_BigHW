/* 2151613 毛宇录 计科 */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include "../include/class_aat.h"
//如有必要，可以加入其它头文件
using namespace std;

#if !ENABLE_LIB_AAT_TOOLS //不使用lib才有效

/* ---------------------------------------------------------------
	 允许加入其它需要static函数（内部工具用）
   ---------------------------------------------------------------- */

static int convert_ip(unsigned &ip_value, const string def)
{
	string def_ip = ".";
	(def_ip += def) += ".";
	int dot_num = 0;
	int str_len = def_ip.size();
	int value = 0;
	ip_value = 0;
	for (int i = 0; i < str_len; ++i) {
		if (def_ip[i] == '.') {
			if (i && def_ip[i - 1] == '.') //连续点错误
				return -1;
			++dot_num;
			if (dot_num > 5) //点超过5错误
				return -1;
			if (value >= 256) //处理value
				return -1;
			(ip_value *= 256) += value;
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

string ip_to_str(unsigned value)
{
	string ip = "";
	string str_temp = "";
	int int_temp;
	unsigned ipaddr = value;
	for (int i = 0; i < 4; ++i) {
		int_temp = ipaddr % 256;
		ipaddr /= 256;
		while (int_temp) {
			str_temp = char(int_temp % 10 + '0') + str_temp;
			int_temp /= 10;
		}
		ip = str_temp + ip;
		str_temp = "";
		if (i < 3)
			ip = '.' + ip;
	}
	return ip;
}

int is_arg(const char* const arg)
{
	if (strlen(arg) < 2 && *(arg) != '-')
		return -1;
	if (*arg != '-' || *(arg + 1) != '-')
		return -1;
	return 0;
}

int read(const char* str, int &num_value)
{
	int value = 0;
	int flag_neg = 1;
	if (*str == '-') {//先判断符号
		flag_neg = -1;
		++str;
	}
	while (*str) {
		if (*str < '0' || *str > '9')
			return -1;
		(value *= 10) += *str - '0';
		++str;
	}
	num_value = flag_neg * value;
	return 0;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：null
 ***************************************************************************/
args_analyse_tools::args_analyse_tools()
{
	args_name = "";
	extargs_type = ST_EXTARGS_TYPE::null;
	extargs_int_set = NULL;
	extargs_string_set = NULL;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：boolean
 ***************************************************************************/
args_analyse_tools::args_analyse_tools(const char* name, const ST_EXTARGS_TYPE type, const int ext_num, const bool def)
{
	args_name = name;
	extargs_type = type;
	extargs_num = ext_num;
	extargs_bool_default = def;
	args_existed = 0;
	extargs_int_set = NULL;
	extargs_string_set = NULL;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：int_with_default、int_with_error
 ***************************************************************************/
args_analyse_tools::args_analyse_tools(const char* name, const ST_EXTARGS_TYPE type, const int ext_num, const int def, const int _min, const int _max)
{
	args_name = name;
	extargs_type = type;
	extargs_num = ext_num;
	extargs_int_default = def;
	extargs_int_value = def;
	extargs_int_min = _min;
	extargs_int_max = _max;
	args_existed = 0;
	extargs_int_set = NULL;
	extargs_string_set = NULL;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：int_with_set_default、int_with_set_error
 ***************************************************************************/
args_analyse_tools::args_analyse_tools(const char* name, const enum ST_EXTARGS_TYPE type, const int ext_num, const int def_of_set_pos, const int* const set)
{
	args_name = name;
	extargs_type = type;
	extargs_num = ext_num;
	args_existed = 0;
	extargs_int_set = NULL;
	extargs_string_set = NULL;
	if (set != NULL) {
		int int_num = 0;
		while (*(set + int_num) != INVALID_INT_VALUE_OF_SET)
			++int_num;
		if (def_of_set_pos >= int_num)
			extargs_int_default = set[0];
		else
			extargs_int_default = set[def_of_set_pos];
		++int_num;
		extargs_int_set = new(nothrow) int[int_num];
		if(extargs_int_set != NULL)
			memcpy(extargs_int_set, set, sizeof(int) * int_num);
	}
	extargs_int_value = extargs_int_default;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：str、ipaddr_with_default、ipaddr_with_error
 ***************************************************************************/
args_analyse_tools::args_analyse_tools(const char* name, const ST_EXTARGS_TYPE type, const int ext_num, const string def)
{
	args_name = name;
	extargs_type = type;
	extargs_num = ext_num;
	args_existed = 0;
	if (type == ST_EXTARGS_TYPE::str) {
		extargs_string_default = def;
		extargs_string_value = def;
	}
	else if(type == ST_EXTARGS_TYPE::ipaddr_with_default){
		int ret;
		unsigned value;
		ret = convert_ip(value, def);
		if (!ret)
			extargs_ipaddr_default = value;
		extargs_ipaddr_value = extargs_ipaddr_default;
	}
	extargs_int_set = NULL;
	extargs_string_set = NULL;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：str_with_set_default、str_with_set_error
 ***************************************************************************/
args_analyse_tools::args_analyse_tools(const char* name, const ST_EXTARGS_TYPE type, const int ext_num, const int def_of_set_pos, const string* const set)
{
	args_name = name;
	extargs_type = type;
	extargs_num = ext_num;
	args_existed = 0;
	extargs_int_set = NULL;
	extargs_string_set = NULL;
	if (set != NULL) {
		int p = 0;
		while (set[p].size())
			++p;
		if(def_of_set_pos >= p)
			extargs_string_default = set[0];
		else
			extargs_string_default = set[def_of_set_pos];
		extargs_string_set = new(nothrow) string[p+1];
		if (extargs_string_set != NULL) {
			for (int i = 0; i < p; ++i)
				extargs_string_set[i] = set[i];
			extargs_string_set[p] = "";
		}
		extargs_string_value = extargs_string_default;
	}
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
 ***************************************************************************/
args_analyse_tools::~args_analyse_tools()
{
	if (extargs_int_set)
		delete[]extargs_int_set;
	if (extargs_string_set)
		delete[]extargs_string_set;
}

/* ---------------------------------------------------------------
	 允许AAT中自定义成员函数的实现（private）
   ---------------------------------------------------------------- */

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：已实现，不要动
 ***************************************************************************/
const string args_analyse_tools::get_name() const
{
	return args_name;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：加!!后，只能是0/1
			已实现，不要动
 ***************************************************************************/
const int args_analyse_tools::existed() const
{
	return !!args_existed;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：已实现，不要动
 ***************************************************************************/
const int args_analyse_tools::get_int() const
{
	return extargs_int_value;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：已实现，不要动
 ***************************************************************************/
const string args_analyse_tools::get_string() const
{
	return extargs_string_value;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：已实现，不要动
 ***************************************************************************/
const unsigned int args_analyse_tools::get_ipaddr() const
{
	return extargs_ipaddr_value;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：将 extargs_ipaddr_value 的值从 0x7f000001 转为 "127.0.0.1"
 ***************************************************************************/
const string args_analyse_tools::get_str_ipaddr() const
{
	string ip = ip_to_str(extargs_ipaddr_value);
	return ip;
}


/***************************************************************************
  函数名称：
  功    能：
  输入参数：follow_up_args：是否有后续参数
			./log_login --limit 10 --user root                    ：无后续参数，置0
			./ulimits_check --memory 256 --cpu 1 [./log_login ***]：有后续参数，置1
  返 回 值：
  说    明：友元函数
***************************************************************************/
int args_analyse_process(const int argc, const char* const *const argv, args_analyse_tools* const args, const int follow_up_args)
{
	int flag_null;
	for (int i = 1; i < argc - follow_up_args; ++i) {
		if (is_arg(*(argv + i)) < 0) {
			cout << "参数[" << *(argv + i) << "]格式非法" << endl;
			return -1;
		}
		flag_null = 1;
		for (int j = 0; args[j].extargs_type != ST_EXTARGS_TYPE::null; ++j) {
			if (*(argv + i) == args[j].args_name) { //匹配到
				flag_null = 0;
				if (args[j].args_existed) { //有重复
					cout << "参数[" << *(argv + i) << "]重复." << endl;
					return -1;
				}
				args[j].args_existed = 1;
				if (!args[j].extargs_num) //无需额外参数
					break;
				int flag_args_err = 0;
				if (i >= argc - 1 - follow_up_args || !is_arg(*(argv + i + 1))) { //缺少额外参数
					cout << "参数[" << *(argv + i) << "]的附加参数不足 ";
					flag_args_err = 1;
				}
				else { //存在额外参数
					int flag = 0, val = 0, ret;
					unsigned value = 0;
					switch (args[j].extargs_type) {
						case ST_EXTARGS_TYPE::boolean:
							break;
						case ST_EXTARGS_TYPE::int_with_default:
							ret = read(*(argv + i + 1), val);
							if (ret < 0) {
								cout << "参数[" << *(argv + i) << "]的附加参数不是整数. ";
								flag_args_err = 1;
							}
							else {
								if (val < args[j].extargs_int_min || val > args[j].extargs_int_max)
									args[j].extargs_int_value = args[j].extargs_int_default;
								else
									args[j].extargs_int_value = val;
							}
							break;
						case ST_EXTARGS_TYPE::int_with_error:
							ret = read(*(argv + i + 1), val);
							if (ret < 0) {
								cout << "参数[" << *(argv + i) << "]的附加参数不是整数. ";
								flag_args_err = 1;
							}
							else {
								if (val < args[j].extargs_int_min || val > args[j].extargs_int_max) {
									cout << "参数[" << *(argv + i) << "]的附加参数值(" << *(argv + i + 1) << ")非法. ";
									flag_args_err = 1;
								}
								else
									args[j].extargs_int_value = val;
							}
							break;
						case ST_EXTARGS_TYPE::int_with_set_default:
							ret = read(*(argv + i + 1), val);
							if (ret < 0) {
								cout << "参数[" << *(argv + i) << "]的附加参数不是整数. ";
								flag_args_err = 1;
							}
							else {
								for (int k = 0; *(args[j].extargs_int_set + k) != INVALID_INT_VALUE_OF_SET; ++k) {
									if (*(args[j].extargs_int_set + k) == val) {
										args[j].extargs_int_value = val;
										flag = 1;
										break;
									}
								}
								if (!flag)
									args[j].extargs_int_value = args[j].extargs_int_default;
							}
							break;
						case ST_EXTARGS_TYPE::int_with_set_error:
							ret = read(*(argv + i + 1), val);
							if (ret < 0) {
								cout << "参数[" << *(argv + i) << "]的附加参数不是整数. ";
								flag_args_err = 1;
							}
							else {
								for (int k = 0; *(args[j].extargs_int_set + k) != INVALID_INT_VALUE_OF_SET; ++k) {
									if (*(args[j].extargs_int_set + k) == val) {
										args[j].extargs_int_value = val;
										flag = 1;
										break;
									}
								}
								if (!flag) {
									cout << "参数[" << *(argv + i) << "]的附加参数值(" << *(argv + i + 1) << ")非法. ";
									flag_args_err = 1;
								}
							}
							break;
						case ST_EXTARGS_TYPE::str:
							if (**(argv + i + 1))
								args[j].extargs_string_value = *(argv + i + 1);
							else
								args[j].extargs_string_value = args[j].extargs_string_default;
							break;
						case ST_EXTARGS_TYPE::str_with_set_default:
							for (int k = 0; args[j].extargs_string_set[k].size(); ++k) {
								if (args[j].extargs_string_set[k] == *(argv + i + 1)) {
									args[j].extargs_string_value = *(argv + i + 1);
									flag = 1;
									break;
								}
							}
							if (!flag)
								args[j].extargs_string_value = args[j].extargs_string_default;
							break;
						case ST_EXTARGS_TYPE::str_with_set_error:
							for (int k = 0; args[j].extargs_string_set[k].size(); ++k) {
								if (args[j].extargs_string_set[k] == *(argv + i + 1)) {
									args[j].extargs_string_value = *(argv + i + 1);
									flag = 1;
									break;
								}
							}
							if (!flag) {
								cout << "参数[" << *(argv + i) << "]的附加参数值(" << *(argv + i + 1) << ")非法. ";
								flag_args_err = 1;
							}
							break;
						case ST_EXTARGS_TYPE::ipaddr_with_default:
							ret = convert_ip(value, *(argv + i + 1));
							if (ret < 0)
								args[j].extargs_ipaddr_value = args[j].extargs_ipaddr_default;
							else
								args[j].extargs_ipaddr_value = value;
							break;
						case ST_EXTARGS_TYPE::ipaddr_with_error:
							ret = convert_ip(value, *(argv + i + 1));
							if (ret < 0) {
								cout << "参数[" << *(argv + i) << "]的附加参数值(" << *(argv + i + 1) << ")非法. ";
								flag_args_err = 1;
							}
							else
								args[j].extargs_ipaddr_value = value;
							break;
					}
					++i;
				}//end 存在额外参数
				if (flag_args_err) {
					switch (args[j].extargs_type) {
						case ST_EXTARGS_TYPE::int_with_default:
							cout << "(类型:int, 范围[" << args[j].extargs_int_min << ".." << args[j].extargs_int_max << "] 缺省:" << args[j].extargs_int_default << ')' << endl;
							break;
						case ST_EXTARGS_TYPE::int_with_error:
							cout << "(类型:int, 范围[" << args[j].extargs_int_min << ".." << args[j].extargs_int_max << "])" << endl;
							break;
						case ST_EXTARGS_TYPE::int_with_set_default:
							cout << "(类型:int, 可取值[";
							for (int k = 0; *(args[j].extargs_int_set + k) != INVALID_INT_VALUE_OF_SET; ++k) {
								if (k)
									cout << '/';
								cout << *(args[j].extargs_int_set + k);
							}
							cout << "] 缺省:" << args[j].extargs_int_default << ')' << endl;
							break;
						case ST_EXTARGS_TYPE::int_with_set_error:
							cout << "(类型:int, 可取值[";
							for (int k = 0; *(args[j].extargs_int_set + k) != INVALID_INT_VALUE_OF_SET; ++k) {
								if (k)
									cout << '/';
								cout << *(args[j].extargs_int_set + k);
							}
							cout << "])" << endl;
							break;
						case ST_EXTARGS_TYPE::str:
							cout << "(类型:string";
							if (args[j].extargs_string_default.size())
								cout << " 缺省:" << args[j].extargs_string_default << ')' << endl;
							else
								cout << ')' << endl;
							break;
						case ST_EXTARGS_TYPE::str_with_set_default:
							cout << "(类型:string, 可取值[";
							for (int k = 0; args[j].extargs_string_set[k].size(); ++k) {
								if (k)
									cout << '/';
								cout << args[j].extargs_string_set[k];
							}
							cout << "] 缺省:" << args[j].extargs_string_default << ')' << endl;
							break;
						case ST_EXTARGS_TYPE::str_with_set_error:
							cout << "(类型:string, 可取值[";
							for (int k = 0; args[j].extargs_string_set[k].size(); ++k) {
								if (k)
									cout << '/';
								cout << args[j].extargs_string_set[k];
							}
							cout << "])" << endl;
							break;
						case ST_EXTARGS_TYPE::ipaddr_with_default:
							cout << "(类型:IP地址 缺省:" << ip_to_str(args[j].extargs_ipaddr_default) << ')' << endl;
							break;
						case ST_EXTARGS_TYPE::ipaddr_with_error:
							cout << "(类型:IP地址)" << endl;
							break;
					}
					return -1;
				}
				break;
			}//end 匹配到
		}
		if (flag_null) {
			cout << "参数[" << *(argv + i) << "]非法." << endl;
			return -1;
		}
	}
	return 0; //此句根据需要修改
}


/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：友元函数
***************************************************************************/
int args_analyse_print(const args_analyse_tools* const args)
{
	int width[6] = { 5,22,17,7,17,36 };
	for (int i = 0; args[i].extargs_type != ST_EXTARGS_TYPE::null; ++i) {
		if ((int)args[i].args_name.length() >= width[0])
			width[0] = args[i].args_name.size() + 1;
		if (args[i].extargs_type == ST_EXTARGS_TYPE::str || args[i].extargs_type == ST_EXTARGS_TYPE::str_with_set_default 
			|| args[i].extargs_type == ST_EXTARGS_TYPE::str_with_set_error) {
			if((int)args[i].extargs_string_default.length() >= width[2])
				width[2] = args[i].extargs_string_default.size() + 1;
			if ((int)args[i].extargs_string_value.length() >= width[4])
				width[4] = args[i].extargs_string_value.size() + 1;
		}
	}
	int width_total = 0;
	for (int i = 0; i < 6; ++i)
		width_total += width[i];
	cout << setw(width_total) << setfill('=') << "" << endl;
	cout << setfill(' ');
	cout << setiosflags(ios::left) << setw(width[0]) << "name" << setw(width[1]) << "type";
	cout << setw(width[2]) << "default" << setw(width[3]) << "exists";
	cout << setw(width[4]) << "value" << "range/set" << endl;
	cout << setw(width_total) << setfill('=') << "" << endl;
	cout << setfill(' ');
	for (int i = 0; args[i].extargs_type != ST_EXTARGS_TYPE::null; ++i) {
		cout << setw(width[0]) << args[i].args_name;
		switch (args[i].extargs_type) {
			case ST_EXTARGS_TYPE::boolean:
				cout << setw(width[1]) << "Bool";
				cout << setw(width[2]) << (args[i].extargs_bool_default ? "true" : "false");
				cout << setw(width[3]) << args[i].args_existed;
				if (args[i].args_existed)
					cout << setw(width[4]) << "true";
				else
					cout << setw(width[4]) << '/';
				cout << '/' << endl;
				break;
			case ST_EXTARGS_TYPE::int_with_default:
				cout << setw(width[1]) << "IntWithDefault";
				cout << setw(width[2]) << args[i].extargs_int_default;
				cout << setw(width[3]) << args[i].args_existed;
				if (args[i].args_existed)
					cout << setw(width[4]) << args[i].extargs_int_value;
				else
					cout << setw(width[4]) << '/';
				cout << '[' << args[i].extargs_int_min << ".." << args[i].extargs_int_max << ']' << endl;
				break;
			case ST_EXTARGS_TYPE::int_with_error:
				cout << setw(width[1]) << "IntWithError";
				cout << setw(width[2]) << '/';
				cout << setw(width[3]) << args[i].args_existed;
				if (args[i].args_existed)
					cout << setw(width[4]) << args[i].extargs_int_value;
				else
					cout << setw(width[4]) << '/';
				cout << '[' << args[i].extargs_int_min << ".." << args[i].extargs_int_max << ']' << endl;
				break;
			case ST_EXTARGS_TYPE::int_with_set_default:
				cout << setw(width[1]) << "IntSETWithDefault";
				cout << setw(width[2]) << args[i].extargs_int_default;
				cout << setw(width[3]) << args[i].args_existed;
				if (args[i].args_existed)
					cout << setw(width[4]) << args[i].extargs_int_value;
				else
					cout << setw(width[4]) << '/';
				for (int k = 0; args[i].extargs_int_set[k] != INVALID_INT_VALUE_OF_SET; ++k) {
					if (k)
						cout << '/';
					cout << args[i].extargs_int_set[k];
				}
				cout << endl;
				break;
			case ST_EXTARGS_TYPE::int_with_set_error:
				cout << setw(width[1]) << "IntSETWithError";
				cout << setw(width[2]) << '/';
				cout << setw(width[3]) << args[i].args_existed;
				if (args[i].args_existed)
					cout << setw(width[4]) << args[i].extargs_int_value;
				else
					cout << setw(width[4]) << '/';
				for (int k = 0; args[i].extargs_int_set[k] != INVALID_INT_VALUE_OF_SET; ++k) {
					if (k)
						cout << '/';
					cout << args[i].extargs_int_set[k];
				}
				cout << endl;
				break;
			case ST_EXTARGS_TYPE::str:
				cout << setw(width[1]) << "String";
				if (args[i].extargs_string_default.size())
					cout << setw(width[2]) << args[i].extargs_string_default;
				else
					cout << setw(width[2]) << '/';
				cout << setw(width[3]) << args[i].args_existed;
				if (args[i].args_existed)
					cout << setw(width[4]) << args[i].extargs_string_value;
				else
					cout << setw(width[4]) << '/';
				cout << '/' << endl;
				break;
			case ST_EXTARGS_TYPE::str_with_set_default:
				cout << setw(width[1]) << "StringSETWithDefault";
				cout << setw(width[2]) << args[i].extargs_string_default;
				cout << setw(width[3]) << args[i].args_existed;
				if (args[i].args_existed)
					cout << setw(width[4]) << args[i].extargs_string_value;
				else
					cout << setw(width[4]) << '/';
				for (int k = 0; args[i].extargs_string_set[k].size(); ++k) {
					if (k)
						cout << '/';
					cout << args[i].extargs_string_set[k];
				}
				cout << endl;
				break;
			case ST_EXTARGS_TYPE::str_with_set_error:
				cout << setw(width[1]) << "StringSETWithError";
				cout << setw(width[2]) << '/';
				cout << setw(width[3]) << args[i].args_existed;
				if (args[i].args_existed)
					cout << setw(width[4]) << args[i].extargs_string_value;
				else
					cout << setw(width[4]) << '/';
				for (int k = 0; args[i].extargs_string_set[k].size(); ++k) {
					if (k)
						cout << '/';
					cout << args[i].extargs_string_set[k];
				}
				cout << endl;
				break;
			case ST_EXTARGS_TYPE::ipaddr_with_default:
				cout << setw(width[1]) << "IPAddrWithDefault";
				cout << setw(width[2]) << ip_to_str(args[i].extargs_ipaddr_default);
				cout << setw(width[3]) << args[i].args_existed;
				if (args[i].args_existed)
					cout << setw(width[4]) << args[i].get_str_ipaddr();
				else
					cout << setw(width[4]) << '/';
				cout << '/' << endl;
				break;
			case ST_EXTARGS_TYPE::ipaddr_with_error:
				cout << setw(width[1]) << "IPAddrWithError";
				cout << setw(width[2]) << '/';
				cout << setw(width[3]) << args[i].args_existed;
				if (args[i].args_existed)
					cout << setw(width[4]) << args[i].get_str_ipaddr();
				else
					cout << setw(width[4]) << '/';
				cout << '/' << endl;
				break;
		}
	}
	cout << setw(width_total) << setfill('=') << "" << endl;
	cout << endl;
	return 0; //此句根据需要修改
}

#endif // !ENABLE_LIB_AAT_TOOLS
