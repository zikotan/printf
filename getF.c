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

/**
 * get_prec - it calculates the precision
 * @format: the formatted string
 * @i: the list of arguments to be printed
 * @list: list of arguments
 *
 * Return: the precision
 */
int get_prec(const char *format, int *i, va_list list)
{
	int this_i = *i + 1;
	int prec = -1;

	if (format[this_i] != '.')
		return (prec);
	prec = 0;
	for (this_i += 1; format[this_i] != '\0'; this_i++)
	{
		if (isdigit(format[this_i]))
		{
			prec *= 10;
			prec += format[this_i] - '0';
		}
		else if (format[this_i] == '*')
		{
			this_i++;
			prec = va_arg(list, int);
			break;
		}
		else
			break;
	}
	*i = this_i - 1;

	return (prec);
}

/**
 * get_wid - it calculates the width
 * @format: the formatted string
 * @i: the list of arguments to be printed
 * @list: list of arguments
 *
 * Return: the width
 */
int get_wid(const char *format, int *i, va_list list)
{
	int this_i;
	int wid = 0;

	for (this_i = *i + 1; format[this_i] != '\0'; this_i++)
	{
		if (isdigit(format[this_i]))
		{
			wid *= 10;
			wid += format[this_i] - '0';
		}
		else if (format[this_i] == '*')
		{
			this_i++;
			wid = va_arg(list, int);
			break;
		}
		else
			break;
	}
	*i = this_i - 1;

	return (wid);
}

/**
 * get_size - it calculates the size to cast the argument
 * @format: the formatted string
 * @i: the list of arguments to be printed.
 *
 * Return: the size
 */
int get_size(const char *format, int *i)
{
	int this_i = *i + 1;
	int size = 0;

	if (format[this_i] == 'l')
		size = LONG;
	else if (format[this_i] == 'h')
		size = SHORT;

	if (size == 0)
		*i = this_i - 1;
	else
		*i = this_i;

	return (size);
}

/**
 * handle_pr - it prints an argument based on its type
 * @format: the formatted string
 * @list: the list of arguments to be printed
 * @index: the index
 * @buf: Buffer array to handle print
 * @fl: Calculates active flags
 * @wid: get width.
 * @prec: Precision specification
 * @size: Size specifier
 * Return: 1 or 2
 */
int handle_pr(const char *format, int *index, va_list list, char buf[],
	int fl, int wid, int prec, int size)
{
	int i, len = 0, pr_ch = -1;
	format_t format_types[] = {
		{'c', pr_char}, {'s', pr_string}, {'%', pr_percent},
		{'i', pr_int}, {'d', pr_int}, {'b', pr_binary},
		{'u', pr_unsigned}, {'o', pr_octal}, {'x', pr_hex},
		{'X', pr_hexa_upper}, {'p', pr_pointer}, {'S', pr_unprintable},
		{'r', pr_reverse}, {'R', pr_RotStr}, {'\0', NULL}
	};
	for (i = 0; format_types[i].format != '\0'; i++)
		if (format[*index] == format_types[i].format)
			return (format_types[i].fass(list, buf, fl, wid, prec, size));

	if (format_types[i].format == '\0')
	{
		if (format[*index] == '\0')
			return (-1);
		len += write(1, "%%", 1);
		if (format[*index - 1] == ' ')
			len += write(1, " ", 1);
		else if (wid)
		{
			--(*index);
			while (format[*index] != ' ' && format[*index] != '%')
				--(*index);
			if (format[*index] == ' ')
				--(*index);
			return (1);
		}
		len += write(1, &format[*index], 1);
		return (len);
	}
	return (pr_ch);
}


