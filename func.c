#include "main.h"

/**
 * pr_char - it prints a char
 * @types: the list of arguments
 * @buf: the buffer array to handle print
 * @fl:  Calculates active flags
 * @wid: the width
 * @prec: the precision specification
 * @size: the size specifier
 * Return: the number of chars printed
 */
int pr_char(va_list types, char buf[],
	int fl, int wid, int prec, int size)
{
	char c = va_arg(types, int);

	return (handle_wr_char(c, buf, fl, wid, prec, size));
}

/**
 * pr_string - it prints a string
 * @types: the list of arguments
 * @buf: the buffer array to handle print
 * @fl:  Calculates active flags
 * @wid: the width
 * @prec: the precision specification
 * @size: the size specifier
 * Return: the number of chars printed
 */
int pr_string(va_list types, char buf[],
	int fl, int wid, int prec, int size)
{
	int l = 0, i;
	char *str = va_arg(types, char *);

	UNUSED(buf);
	UNUSED(fl);
	UNUSED(wid);
	UNUSED(prec);
	UNUSED(size);
	if (str == NULL)
	{
		str = "(null)";
		if (prec >= 6)
			str = "      ";
	}

	while (str[l] != '\0')
		l++;

	if (prec >= 0 && prec < l)
		l = prec;

	if (wid > l)
	{
		if (fl & MIN)
		{
			write(1, &str[0], l);
			for (i = wid - l; i > 0; i--)
				write(1, " ", 1);
			return (wid);
		}
		else
		{
			for (i = wid - l; i > 0; i--)
				write(1, " ", 1);
			write(1, &str[0], l);
			return (wid);
		}
	}

	return (write(1, str, l));
}

/**
 * pr_percent - it prints a percent sign
 * @types: the list of arguments
 * @buf: the buffer array to handle print
 * @fl:  Calculates active flags
 * @wid: the width
 * @prec: the precision specification
 * @size: the size specifier
 * Return: the number of chars printed
 */
int pr_percent(va_list types, char buf[],
	int fl, int wid, int prec, int size)
{
	UNUSED(types);
	UNUSED(buf);
	UNUSED(fl);
	UNUSED(wid);
	UNUSED(prec);
	UNUSED(size);
	return (write(1, "%%", 1));
}

/**
 * pr_int - Print int
 * @types: the list of arguments
 * @buf: the buffer array to handle print
 * @fl:  Calculates active flags
 * @wid: the width
 * @prec: the precision specification
 * @size: the size specifier
 * Return: the number of chars printed
 */
int pr_int(va_list types, char buf[],
	int fl, int wid, int prec, int size)
{
	int i = BUF_SIZE - 2;
	int is_negative = 0;
	long int n = va_arg(types, long int);
	unsigned long int num;

	n = convert_size_number(n, size);

	if (n == 0)
		buf[i--] = '0';

	buf[BUF_SIZE - 1] = '\0';
	num = (unsigned long int)n;

	if (n < 0)
	{
		num = (unsigned long int)((-1) * n);
		is_negative = 1;
	}

	while (num > 0)
	{
		buf[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (wr_number(is_negative, i, buf, fl, wid, prec, size));
}

/**
 * pr_binary - it prints an unsigned number
 * @types: the list of arguments
 * @buf: the buffer array to handle print
 * @fl:  Calculates active flags
 * @wid: the width
 * @prec: the precision specification
 * @size: the size specifier
 * Return: the numbers of char printed.
 */
int pr_binary(va_list types, char buf[],
	int fl, int wid, int prec, int size)
{
	unsigned int n, m, i, sum;
	unsigned int a[32];
	int count;

	UNUSED(buf);
	UNUSED(fl);
	UNUSED(wid);
	UNUSED(prec);
	UNUSED(size);

	n = va_arg(types, unsigned int);
	m = 2147483648U;
	a[0] = n / m;
	for (i = 1; i < 32; i++)
	{
		m /= 2;
		a[i] = (n / m) % 2;
	}
	for (i = 0, sum = 0, count = 0; i < 32; i++)
	{
		sum += a[i];
		if (sum || i == 31)
		{
			char z = '0' + a[i];

			write(1, &z, 1);
			count++;
		}
	}
	return (count);
}


