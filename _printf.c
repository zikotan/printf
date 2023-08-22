#include "main.h"

void pr_buf(char buf[], int *buf_i)

/**
 * _printf - Printf function
 * @format: format
 * Return: the printed chars
 */
int _printf(const char *format, ...)
{
	int i, pr = 0, pr_ch = 0;
	int fl, wd, prec, size, buf_i = 0;
	va_list list;
	char buf[BUF_SIZE];

	if (format == NULL)
		return (-1);
	va_start(list, format);
	for (i = 0; format && format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			buf[buf_i++] = format[i];
			if (buf_i == BUF_SIZE)
				pr_buf(buf, &buf_i);
			/* write(1, &format[i], 1);*/
			pr_ch++;
		}
		else
		{
			pr_buf(buf, &buf_i);
			fl = get_fl(format, &i);
			wd = get_wid(format, &i, list);
			prec = get_prec(format, &i, list);
			size = get_size(format, &i);
			++i;
			pr = handle_pr(format, &i, list, buf,
				fl, wd, prec, size);
			if (pr == -1)
				return (-1);
			pr_ch += pr;
		}
	}
	pr_buf(buf, &buf_i);
	va_end(list);

	return (pr_ch);
}

/**
 * pr_buf - it prints the buffer contents if it exist
 * @buf: the chars array
 * @buf_i: the index where to add next char
 */
void pr_buf(char buf[], int *buf_i)
{
	if (*buf_i > 0)
		write(1, &buf[0], *buf_i);
	*buf_i = 0;
}

