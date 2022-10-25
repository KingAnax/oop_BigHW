/*2151613 计科 毛宇录*/
#include "90-01-b2.h"

int chance_number(int stage)  //根据概率生成数字
{
	int result;
	if (stage == 3)
		result = rand() % 3 + 1;
	else if (stage == 4)
		result = (rand() % 10) / 3 + 1;
	else if (stage == 5) {
		result = rand() % 100;
		if (result < 75)
			result = result / 25 + 1;
		else
			result = result / 90 + 4;
	}
	else if (stage == 6) {
		result = rand() % 20;
		if (result < 16)
			result = result / 4 + 1;
		else
			result = result / 19 + 5;
	}
	else
	{
		result = rand() % 20;
		if (result < 16)
			result = result * (stage - 3) / 16 + 1;
		else if (result < 18)
			result = stage - 2;
		else
			result = stage - 1 + result / 19;
	}
	return result;
}

void tepan_new_recursion(int i, int row, int* num, int* num_new)//判断部分
{
	if (i % column_max == 0) {
		if ((*(num + i + 1) == *(num + i)) && (!*(num_new + i + 1))) {
			*(num_new + i + 1) = 1;
			find2(i + 1, row, num, num_new);
		}
	}
	else if ((i + 1) % column_max == 0) {
		if ((*(num + i - 1) == *(num + i)) && (!*(num_new + i - 1))) {
			*(num_new + i - 1) = 1;
			find2(i - 1, row, num, num_new);
		}
	}
	else {
		if ((*(num + i + 1) == *(num + i)) && (!*(num_new + i + 1))) {
			*(num_new + i + 1) = 1;
			find2(i + 1, row, num, num_new);
		}
		if ((*(num + i - 1) == *(num + i)) && (!*(num_new + i - 1))) {
			*(num_new + i - 1) = 1;
			find2(i - 1, row, num, num_new);
		}
	}
	return;
}

void tepan_new_recursion2(int i, int row, int* num, int* num_new)//判断部分
{
	if (i % column_max == 0) {
		if ((*(num + i + 1) == *(num + i)) && (!*(num_new + i + 1))) {
			*(num_new + i + 1) = 1;
			putin_color((i + 1) / column_max, (i + 1) % column_max, num, 0);
			Sleep(30);
			find3(i + 1, row, num, num_new);
		}
	}
	else if ((i + 1) % column_max == 0) {
		if ((*(num + i - 1) == *(num + i)) && (!*(num_new + i - 1))) {
			*(num_new + i - 1) = 1;
			putin_color((i - 1) / column_max, (i - 1) % column_max, num, 0);
			find3(i - 1, row, num, num_new);
		}
	}
	else {
		if ((*(num + i + 1) == *(num + i)) && (!*(num_new + i + 1))) {
			*(num_new + i + 1) = 1;
			putin_color((i + 1) / column_max, (i + 1) % column_max, num, 0);
			find3(i + 1, row, num, num_new);
		}
		if ((*(num + i - 1) == *(num + i)) && (!*(num_new + i - 1))) {
			*(num_new + i - 1) = 1;
			putin_color((i - 1) / column_max, (i - 1) % column_max, num, 0);
			find3(i - 1, row, num, num_new);
		}
	}
	return;
}