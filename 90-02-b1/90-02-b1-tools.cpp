//2151613 ¼Æ¿Æ Ã«ÓîÂ¼

#include "90-02-b1.h"

int score_count(int *score, int *num_signed)
{
	int count = 0;
	for (int i = 0; i < row_max * col_max; ++i) {
		if (*(num_signed + i) > 0)
			++count;
	}
	*score += count * count * 5;
	return count * count * 5;
}

int score_end(int* score, int* num, int row, int col)
{
	int count = 0;
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			if (*(num + i * col_max + j) > 0)
				++count;
		}
	}
	count >= 10 ? *score += 0 : *score += (10 - count) * 180;
	return ((10 - count) * 180 > 0 ? 0 : (10 - count) * 18);
}

void eliminate(int *num, int *num_signed)
{
	for (int i = 0; i < row_max * col_max; ++i) {
		if (*(num_signed + i) > 0)
			*(num + i) = 0;
	}
}

void reset_num_signed(int* num_signed) 
{
	for (int i = 0; i < row_max * col_max; ++i) {
		if (*(num_signed + i) > 0)
			*(num_signed + i) = 0;
	}
}

int remain_block_num(int* num)
{
	int count = 0;
	for (int i = 0; i < row_max * col_max; ++i) {
		if (*(num + i) > 0)
			++count;
	}
	return count;
}

