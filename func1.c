#include "main.h"

/************************* PRINT UNSIGNED NUMBER *************************/
/**
 * pr_unsigned - prints an unsigned number
 * @types: the list of arguments
 * @buf: the buffer array to handle print
 * @fl:  it calculates active flags
 * @wid: the width
 * @prec: the precision specification
 * @size: the size specifier
 * Return: the number of chars printed.
 */
int pr_unsigned(va_list types, char buf[],
	int fl, int wid, int prec, int size)
{
	int i = BUF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);

	num = convert_size_unsignedd(num, size);

	if (num == 0)
		buf[i--] = '0';

	buf[BUF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buf[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (wr_unsignedd(0, i, buf, fl, wid, prec, size));
}

/************* PRINT UNSIGNED NUMBER IN OCTAL  ****************/
/**
 * pr_octal - prints an unsigned number in octal notation
 * @types: the list of arguments
 * @buf: the buffer array to handle print
 * @fl:  it calculates active flags
 * @wid: the width
 * @prec: the precision specification
 * @size: the size specifier
 * Return: the number of chars printed
 */
int pr_octal(va_list types, char buf[],
	int fl, int wid, int prec, int size)
{

	int i = BUF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(wid);

	num = convert_size_unsignedd(num, size);

	if (num == 0)
		buf[i--] = '0';

	buf[BUF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buf[i--] = (num % 8) + '0';
		num /= 8;
	}

	if (fl & HASH && init_num != 0)
		buf[i--] = '0';

	i++;

	return (wr_unsignedd(0, i, buf, fl, wid, prec, size));
}

/************** PRINT UNSIGNED NUMBER IN HEXADECIMAL **************/
/**
 * pr_hex - prints an unsigned number in hexadecimal notation
 * @types: the list of arguments
 * @buf: the buffer array to handle print
 * @fl:  it calculates active flags
 * @wid: the width
 * @prec: the precision specification
 * @size: the size specifier
 * Return: the number of chars printed
 */
int pr_hex(va_list types, char buf[],
	int fl, int wid, int prec, int size)
{
	return (pr_hexa(types, "0123456789abcdef", buf,
		fl, 'x', wid, prec, size));
}

/************* PRINT UNSIGNED NUMBER IN UPPER HEXADECIMAL **************/
/**
 * pr_hexa_upper - prints an unsigned number in upper hexadecimal notation
 * @types: the list of arguments
 * @buf: the buffer array to handle print
 * @fl:  it calculates active flags
 * @wid: the width
 * @prec: the precision specification
 * @size: the size specifier
 * Return: the number of chars printed
 */
int pr_hexa_upper(va_list types, char buf[],
	int fl, int wid, int prec, int size)
{
	return (pr_hexa(types, "0123456789ABCDEF", buf,
		fl, 'X', wid, prec, size));
}

/************** PRINT HEXX NUM IN LOWER OR UPPER **************/
/**
 * pr_hexa - prints a hexadecimal number in lower or upper
 * @types: the list of arguments
 * @map_to: Array of values to map the number to
 * @buf: the buffer array to handle print
 * @fl:  it calculates active flags
 * @fl_ch: it calculates active flags
 * @wid: the width
 * @prec: the precision specification
 * @size: the size specifier
 * @size: the size specification
 * Return: the number of chars printed
 */
int pr_hexa(va_list types, char map_to[], char buf[],
	int fl, char fl_ch, int wid, int prec, int size)
{
	int i = BUF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(wid);
	num = convert_size_unsignedd(num, size);
	if (num == 0)
		buf[i--] = '0';
	buf[BUF_SIZE - 1] = '\0';
	while (num > 0)
	{
		buf[i--] = map_to[num % 16];
		num /= 16;
	}
	if (fl & HASH && init_num != 0)
	{
		buf[i--] = fl_ch;
		buf[i--] = '0';
	}
	i++;

	return (wr_unsignedd(0, i, buf, fl, wid, prec, size));
}

