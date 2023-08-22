#include "main.h"

/**
 * print_char - it prints a char
 * @types: the list a of arguments
 * @buf: the buf array to handle print
 * @flg:  it calculates active flags
 * @wid: the width
 * @prec: the precision specification
 * @size: the size specifier
 * Return: the number of chars printed
 */
int print_char(va_list types, char buf[],
	int flg, int wid, int prec, int size)
{
	char c = va_arg(types, int);

	return (handle_write_char(c, buf, flg, wid, prec, size));
}

/**
 * print_string - it prints a string
 * @types: the list a of arguments
 * @buf: the buf array to handle print
 * @flg:  it calculates active flags
 * @wid: the width.
 * @prec: the precision specification
 * @size: the size specifier
 * Return: the number of chars printed
 */
int print_string(va_list types, char buf[],
	int flg, int wid, int prec, int size)
{
	int len = 0, i;
	char *s = va_arg(types, char *);

	UNUSED(buf);
	UNUSED(flg);
	UNUSED(wid);
	UNUSED(prec);
	UNUSED(size);
	if (s == NULL)
	{
		s = "(null)";
		if (prec >= 6)
			s = "      ";
	}

	while (s[len] != '\0')
		len++;

	if (prec >= 0 && prec < len)
		len = prec;

	if (wid > len)
	{
		if (flg & F_MINUS)
		{
			write(1, &s[0], len);
			for (i = wid - len; i > 0; i--)
				write(1, " ", 1);
			return (wid);
		}
		else
		{
			for (i = wid - len; i > 0; i--)
				write(1, " ", 1);
			write(1, &s[0], len);
			return (wid);
		}
	}

	return (write(1, s, len));
}

/**
 * print_percent - it prints a percent sign
 * @types: the lista of arguments
 * @buf: the buf array to handle print
 * @flg:  it calculates active flags
 * @wid: the width.
 * @prec: the precision specification
 * @size: the size specifier
 * Return: the number of chars printed
 */
int print_percent(va_list types, char buf[],
	int flg, int wid, int prec, int size)
{
	UNUSED(types);
	UNUSED(buf);
	UNUSED(flg);
	UNUSED(wid);
	UNUSED(prec);
	UNUSED(size);
	return (write(1, "%%", 1));
}

/**
 * print_int - it print int
 * @types: the lista of arguments
 * @buf: the buf array to handle print
 * @flg:  it calculates active flags
 * @wid: the width.
 * @prec: the precision specification
 * @size: the size specifier
 * Return: the number of chars printed
 */
int print_int(va_list types, char buf[],
	int flg, int wid, int prec, int size)
{
	int i = BUFF_SIZE - 2;
	int is_neg = 0;
	long int n = va_arg(types, long int);
	unsigned long int num;

	n = convert_size_number(n, size);

	if (n == 0)
		buf[i--] = '0';

	buf[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)n;

	if (n < 0)
	{
		num = (unsigned long int)((-1) * n);
		is_neg = 1;
	}

	while (num > 0)
	{
		buf[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (write_number(is_neg, i, buf, flg, wid, prec, size));
}

/**
 * print_binary - it prints an unsigned number
 * @types: the lista of arguments
 * @buf: the buf array to handle print
 * @flg:  it calculates active flags
 * @wid: the width.
 * @prec: the precision specification
 * @size: the size specifier
 * Return: the numbers of char printed.
 */
int print_binary(va_list types, char buf[],
	int flg, int wid, int prec, int size)
{
	unsigned int n, m, i, sum;
	unsigned int a[32];
	int c;

	UNUSED(buf);
	UNUSED(flg);
	UNUSED(wid);
	UNUSED(prec);
	UNUSED(size);

	n = va_arg(types, unsigned int);
	m = 2147483648; /* (2 ^ 31) */
	a[0] = n / m;
	for (i = 1; i < 32; i++)
	{
		m /= 2;
		a[i] = (n / m) % 2;
	}
	for (i = 0, sum = 0, c = 0; i < 32; i++)
	{
		sum += a[i];
		if (sum || i == 31)
		{
			char z = '0' + a[i];

			write(1, &z, 1);
			c++;
		}
	}
	return (c);
}

