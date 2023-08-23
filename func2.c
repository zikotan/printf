#include "main.h"

/**
 * pr_pointer - it prints the value of a pointer variable
 * @types: the list of arguments
 * @buf: the buffer array to handle print
 * @fl:  it calculates active flags
 * @wid: the width
 * @prec: the precision specification
 * @size: the size specifier
 * Return: the number of chars printed.
 */
int pr_pointer(va_list types, char buf[],
	int fl, int wid, int prec, int size)
{
	char plus_c = 0, padd = ' ';
	int ind = BUF_SIZE - 2, l = 2, padd_start = 1; /* l=2, for '0x' */
	unsigned long num_addrs;
	char map_to[] = "0123456789abcdef";
	void *addrs = va_arg(types, void *);

	UNUSED(wid);
	UNUSED(size);

	if (addrs == NULL)
		return (write(1, "(nil)", 5));

	buf[BUF_SIZE - 1] = '\0';
	UNUSED(prec);

	num_addrs = (unsigned long)addrs;

	while (num_addrs > 0)
	{
		buf[ind--] = map_to[num_addrs % 16];
		num_addrs /= 16;
		l++;
	}

	if ((fl & ZERO) && !(fl & MIN))
		padd = '0';
	if (fl & PLUS)
		plus_c = '+', l++;
	else if (fl & SPACE)
		plus_c = ' ', l++;

	ind++;

	return (wr_pointer(buf, ind, l,
		wid, fl, padd, plus_c, padd_start));
}

/**
 * pr_unprintable - it prints ascii codes in hexa of non printable chars
 * @types: the list of arguments
 * @buf: the buffer array to handle print
 * @fl:  it calculates active flags
 * @wid: the width
 * @prec: the precision specification
 * @size: the size specifier
 * Return: the number of chars printed
 */
int pr_unprintable(va_list types, char buf[],
	int fl, int wid, int prec, int size)
{
	int i = 0, offset = 0;
	char *str = va_arg(types, char *);

	UNUSED(fl);
	UNUSED(wid);
	UNUSED(prec);
	UNUSED(size);

	if (str == NULL)
		return (write(1, "(null)", 6));

	while (str[i] != '\0')
	{
		if (is_printable(str[i]))
			buf[i + offset] = str[i];
		else
			offset += append_hexa_code(str[i], buf, i + offset);

		i++;
	}

	buf[i + offset] = '\0';

	return (write(1, buf, i + offset));
}

/**
 * pr_reverse - it prints reverse string.
 * @types: the list of arguments
 * @buf: the buffer array to handle print
 * @fl:  it calculates active flags
 * @wid: the width
 * @prec: the precision specification
 * @size: the size specifier
 * Return: the numbers of chars printed
 */
int pr_reverse(va_list types, char buf[],
	int fl, int wid, int prec, int size)
{
	char *str;
	int i, count = 0;

	UNUSED(buf);
	UNUSED(fl);
	UNUSED(wid);
	UNUSED(size);

	str = va_arg(types, char *);

	if (str == NULL)
	{
		UNUSED(prec);

		str = ")Null(";
	}
	for (i = 0; str[i]; i++)
		;

	for (i = i - 1; i >= 0; i--)
	{
		char z = str[i];

		write(1, &z, 1);
		count++;
	}
	return (count);
}

/**
 * pr_RotStr: it prints a string in rot13
 * @types: the list of arguments
 * @buf: the buffer array to handle print
 * @fl:  it calculates active flags
 * @wid: the width
 * @prec: the precision specification
 * @size: the size specifier
 *
 * Return: the numbers of chars printed
 */
int pr_RotStr(va_list types, char buf[],
	int fl, int wid, int prec, int size)
{
	char x;
	char *str;
	unsigned int i, j;
	int count = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(types, char *);
	UNUSED(buf);
	UNUSED(fl);
	UNUSED(wid);
	UNUSED(prec);
	UNUSED(size);

	if (str == NULL)
		str = "(AHYY)";
	for (i = 0; str[i]; i++)
	{
		for (j = 0; in[j]; j++)
		{
			if (in[j] == str[i])
			{
				x = out[j];
				write(1, &x, 1);
				count++;
				break;
			}
		}
		if (!in[j])
		{
			x = str[i];
			write(1, &x, 1);
			count++;
		}
	}
	return (count);
}


