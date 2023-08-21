#include "main.h"

/**
 * is_printable - it evaluates if a char is printable
 * @c: the char to be evaluated.
 *
 * Return: it returns 1 if c is printable, 0 otherwise
 */
int is_printable(char c)
{
	if (c >= 32 && c < 127)
		return (1);

	return (0);
}

/**
 * append_hexa_code - it appends ascci in hexadecimal code to buffer
 * @buf: the array of chars
 * @i: the index at where t append
 * @asc_code: the ASSCI CODE
 * Return: it returns 3
 */
int append_hexa_code(char asc_code, char buf[], int i)
{
	char map_to[] = "0123456789ABCDEF";
	if (asc_code < 0)
		asc_code *= -1;

	buf[i++] = '\\';
	buf[i++] = 'x';

	buf[i++] = map_to[asc_code / 16];
	buf[i] = map_to[asc_code % 16];

	return (3);
}

/**
 * convert_size_number - it casts a number to the specified size
 * @n: the number to be casted
 * @size: the number indicating the type to be casted
 *
 * Return: it returns a casted value of n
 */
long int convert_size_number(long int n, int size)
{
	if (size == LONG)
		return (n);
	else if (size == SHORT)
		return ((short)n);

	return ((int)n);
}

/**
 * convert_size_unsigned - it casts a number to the specified size
 * @n: the number to be casted
 * @size: the number indicating the type to be casted
 *
 * Return: it returns the casted value of n
 */
long int convert_size_unsigned(unsigned long int n, int size)
{
	if (size == LONG)
		return (n);
	else if (size == SHORT)
		return ((unsigned short)n);

	return ((unsigned int)n);
}

