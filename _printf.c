#include "main.h"

void print_buffer(char buf[], int *buf_i);

/**
 * _printf - the printf function
 * @format: the format
 * Return: it return printed chars
 */
int _printf(const char *format, ...)
{
	int i, pr = 0, pr_ch = 0;
	int flg, wid, prec, size, buf_i = 0;
	va_list list;
	char buf[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(list, format);

	for (i = 0; format && format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			buf[buf_i++] = format[i];
			if (buf_i == BUFF_SIZE)
				print_buffer(buf, &buf_i);
			/* write(1, &format[i], 1);*/
			pr_ch++;
		}
		else
		{
			print_buffer(buf, &buf_i);
			flg = get_flags(format, &i);
			wid = get_width(format, &i, list);
			prec = get_precision(format, &i, list);
			size = get_size(format, &i);
			++i;
			pr = handle_print(format, &i, list, buf,
				flg, wid, prec, size);
			if (pr == -1)
				return (-1);
			pr_ch += pr;
		}
	}

	print_buffer(buf, &buf_i);

	va_end(list);

	return (pr_ch);
}

/**
 * print_buffer - it prints the contents of the buffer if it exist
 * @buf: the chars array
 * @buf_i: the index at which to add next char
 */
void print_buffer(char buf[], int *buf_i)
{
	if (*buf_i > 0)
		write(1, &buf[0], *buf_i);

	*buf_i = 0;
}

