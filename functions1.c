#include "main.h"

/**
 * print_unsigned - it prints an unsigned number
 * @types: the list a of arguments
 * @buf: the buf array to handle print
 * @flg: it calculates active flags
 * @wid: the width
 * @prec: the precision specification
 * @size: the size specifier
 * Return: the number of chars printed.
 */
int print_unsigned(va_list types, char buf[],
	int flg, int wid, int prec, int size)
{
	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buf[i--] = '0';

	buf[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buf[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (write_unsgnd(0, i, buf, flg, wid, prec, size));
}

/**
 * print_octal - it prints an unsigned number in octal notation
 * @types: the lista of arguments
 * @buf: the buf array to handle print
 * @flg: it calculates active flags
 * @wid: the width
 * @prec: the precision specification
 * @size: the size specifier
 * Return: the number of chars printed
 */
int print_octal(va_list types, char buf[],
	int flg, int wid, int prec, int size)
{

	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int num0 = num;

	UNUSED(wid);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buf[i--] = '0';

	buf[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buf[i--] = (num % 8) + '0';
		num /= 8;
	}

	if (flg & F_HASH && num0 != 0)
		buf[i--] = '0';

	i++;

	return (write_unsgnd(0, i, buf, flg, wid, prec, size));
}

/**
 * print_hexadecimal - it prints an unsigned number in hexadecimal notation
 * @types: the lista of arguments
 * @buf: the buf array to handle print
 * @flg: it calculates active flags
 * @wid: the width
 * @prec: the precision specification
 * @size: the size specifier
 * Return: the number of chars printed
 */
int print_hexadecimal(va_list types, char buf[],
	int flg, int wid, int prec, int size)
{
	return (print_hexa(types, "0123456789abcdef", buf,
		flg, 'x', wid, prec, size));
}

/**
 * print_hexa_upper - it prints an unsigned number in upper hexadecimal notation
 * @types: the lista of arguments
 * @buf: the buf array to handle print
 * @flg: it calculates active flags
 * @wid: the width
 * @prec: the precision specification
 * @size: the size specifier
 * Return: the number of chars printed
 */
int print_hexa_upper(va_list types, char buf[],
	int flg, int wid, int prec, int size)
{
	return (print_hexa(types, "0123456789ABCDEF", buf,
		flg, 'X', wid, prec, size));
}

/**
 * print_hexa - it prints a hexadecimal number in lower or upper
 * @types: the lista of arguments
 * @map_to: the array of values to map the number to
 * @buf: the buf array to handle print
 * @flg: it calculates active flags
 * @flg_ch: it calculates active flags
 * @wid: the width
 * @prec: the precision specification
 * @size: the size specifier
 * Return: the number of chars printed
 */
int print_hexa(va_list types, char map_to[], char buf[],
	int flg, char flg_ch, int wid, int prec, int size)
{
	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int num0 = num;

	UNUSED(wid);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buf[i--] = '0';

	buf[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buf[i--] = map_to[num % 16];
		num /= 16;
	}

	if (flg & F_HASH && num0 != 0)
	{
		buf[i--] = flg_ch;
		buf[i--] = '0';
	}

	i++;

	return (write_unsgnd(0, i, buf, flg, wid, prec, size));
}

