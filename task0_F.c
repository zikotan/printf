#include "main.h"

/**
 * get_fl - it calculates active flags
 * @format: the formatted string
 * @i: it take a parameter
 * Return: flags
 */
int get_fl(const char *format, int *i)
{
	int last_i, j;
	int fl = 0;
	const char fl_ch[] = {'-', '+', '0', '#', ' ', '\0'};
	const int fl_ar[] = {MIN, PLUS, ZERO, HASH, SPACE, 0};

	for (last_i = *i + 1; format[last_i] != '\0'; last_i++)
	{
		for (j = 0; fl_ch[j] != '\0'; j++)
			if (format[last_i] == fl_ch[j])
			{
				fl |= fl_ar[j];
				break;
			}
		if (fl_ch[j] == 0)
			break;
	}
	*i = last_i - 1;

	return (fl);
}

