//2151613 �ƿ� ë��¼

#include "../include/common_input.h"

char menu(const char* content[], const char* choice, const int mode)
{
	char ret;//��Ϊ����ֵ

	//��ӡ�˵�
	int row_max = 0, i = 0;

	while (*(content + i)) {
		if (strlen(*(content + i)) > (unsigned)row_max)
			row_max = (int)strlen(*(content + i));
		++i;
	}

	i = 0;
	--row_max;

	cout << setfill('-')<<setw(row_max) << "" << endl;

	while (*(content + i)) {
		cout << *(content + i);
		++i;
	}

	cout << setfill('-') << setw(row_max) << "" << endl;
	cout << setfill(' ');
	cout << "[��ѡ��:] ";

	//�����ж�
	int flag = 0;
	while (!flag) {
		ret = _getch();
		if (strchr(choice, ret) != NULL)
			flag = 1;
		if (flag) {
			cout << ret << endl;
			Sleep(200);
		}
	}

	return ret;
}