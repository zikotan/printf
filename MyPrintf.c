#include "main.h"

/**
 * pr_buf - it prints the buffer contents if it exist
 * @buf: Array of chars
 * @buf_i: Index at which to add next char, represents the length.
 */
void pr_buf(char buf[], int *buf_i)
{
	if (*buf_i > 0)
		write(1, &buf[0], *buf_i);

	*buf_i = 0;
}

/**
 * _printf - the printf function
 * @format: the format
 * Return: chars
 */
int _printf(const char *format, ...)
{
	int i, p = 0, s = 0;
	int fl, w, prec, sz, bf_i = 0;
	va_list list;
	char buf[BUF_SZ];

	if (format == NULL)
		return (-1);

	va_start(list, format);

	for (i = 0; format && format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			buf[bf_i++] = format[i];
			if (bf_i == BUF_SZ)
				pr_buf(buf, &bf_i);
			s++;
		}
		else
		{
			pr_buf(buf, &bf_i);
			fl = get_fl(format, &i);
			w = get_w(format, &i, list);
			prec = get_prec(format, &i, list);
			sz = get_sz(format, &i);
			++i;
			p = handling(format, &i, list, buf,
				fl, w, prec, sz);
			if (p == -1)
				return (-1);
			s += p;
		}
	}

	pr_buf(buf, &bf_i);

	va_end(list);

	return (s);
}
