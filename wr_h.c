#include "main.h"

/************************* WRITE HANDLE *************************/
/**
 * handle_wr_char - it prints a string
 * @c: the char types.
 * @buf: the buffer array to handle print
 * @fl: it calculates active flags.
 * @wid: the width
 * @prec: the precision specifier
 * @size: the size specifier
 *
 * Return: the number of chars printed.
 */
int handle_wr_char(char c, char buf[],
	int fl, int wid, int prec, int size)
{
	int i = 0;
	char padd = ' ';

	UNUSED(prec);
	UNUSED(size);

	if (fl & ZERO)
		padd = '0';

	buf[i++] = c;
	buf[i] = '\0';

	if (wid > 1)
	{
		buf[BUF_SIZE - 1] = '\0';
		for (i = 0; i < wid - 1; i++)
			buf[BUF_SIZE - i - 2] = padd;

		if (fl & MIN)
			return (write(1, &buf[0], 1) +
					write(1, &buf[BUF_SIZE - i - 1], wid - 1));
		else
			return (write(1, &buf[BUF_SIZE - i - 1], wid - 1) +
					write(1, &buf[0], 1));
	}

	return (write(1, &buf[0], 1));
}

/************************* WRITE NUMBER *************************/
/**
 * wr_number - it prints a string
 * @is_negative: Lista of arguments
 * @ind: char types.
 * @buf: the buffer array to handle print
 * @fl: it calculates active flags
 * @wid: the width
 * @prec: the precision specifier
 * @size: the size specifier
 *
 * Return: the number of chars printed.
 */
int wr_number(int is_negative, int ind, char buf[],
	int fl, int wid, int prec, int size)
{
	int l = BUF_SIZE - ind - 1;
	char padd = ' ', plus_ch = 0;

	UNUSED(size);

	if ((fl & ZERO) && !(fl & MIN))
		padd = '0';
	if (is_negative)
		plus_ch = '-';
	else if (fl & PLUS)
		plus_ch = '+';
	else if (fl & SPACE)
		plus_ch = ' ';

	return (wr_num(ind, buf, fl, wid, prec,
		l, padd, plus_ch));
}

/**
 * wr_num - it writes a number using a bufffer
 * @ind: Index at which the number starts on the buf
 * @buffer: the buffer
 * @fl: the flags
 * @wid: the width
 * @prec: the precision specifier
 * @l: the number length
 * @padd: the pading char
 * @plus_c: the extra char
 *
 * Return: the number of printed chars.
 */
int wr_num(int ind, char buf[],
	int fl, int wid, int prec,
	int l, char padd, char plus_c)
{
	int i, padd_start = 1;

	if (prec == 0 && ind == BUF_SIZE - 2 && buf[ind] == '0' && wid == 0)
		return (0); /* printf(".0d", 0)  no char is printed */
	if (prec == 0 && ind == BUF_SIZE - 2 && buf[ind] == '0')
		buf[ind] = padd = ' '; /* wid is displayed with padding ' ' */
	if (prec > 0 && prec < l)
		padd = ' ';
	while (prec > l)
		buf[--ind] = '0', l++;
	if (plus_c != 0)
		l++;
	if (wid > l)
	{
		for (i = 1; i < wid - l + 1; i++)
			buf[i] = padd;
		buf[i] = '\0';
		if (fl & MIN && padd == ' ')/* Asign extra char to left of buf */
		{
			if (plus_c)
				buf[--ind] = plus_c;
			return (write(1, &buf[ind], l) + write(1, &buf[1], i - 1));
		}
		else if (!(fl & MIN) && padd == ' ')/* extra char to left of buff */
		{
			if (plus_c)
				buf[--ind] = plus_c;
			return (write(1, &buf[1], i - 1) + write(1, &buf[ind], l));
		}
		else if (!(fl & MIN) && padd == '0')/* extra char to left of padd */
		{
			if (plus_c)
				buf[--padd_start] = plus_c;
			return (write(1, &buf[padd_start], i - padd_start) +
				write(1, &buf[ind], l - (1 - padd_start)));
		}
	}
	if (plus_c)
		buf[--ind] = plus_c;
	return (write(1, &buf[ind], l));
}

/**
 * wr_unsignedd - it writes an unsigned number
 * @is_negative: the number indicating if the num is negative
 * @ind: the index at which the number starts in the buffer
 * @buf: the array of chars
 * @fl: the flags specifiers
 * @wid: the width specifier
 * @prec: the precision specifier
 * @size: the size specifier
 *
 * Return: the number of written chars.
 */
int wr_unsignedd(int is_negative, int ind,
	char buf[],
	int fl, int wid, int prec, int size)
{
	int l = BUF_SIZE - ind - 1, i = 0;
	char padd = ' ';

	UNUSED(is_negative);
	UNUSED(size);

	if (prec == 0 && ind == BUF_SIZE - 2 && buf[ind] == '0')
		return (0); /* printf(".0d", 0)  no char is printed */

	if (prec > 0 && prec < l)
		padd = ' ';

	while (prec > l)
	{
		buf[--ind] = '0';
		l++;
	}

	if ((fl & ZERO) && !(fl & MIN))
		padd = '0';

	if (wid > l)
	{
		for (i = 0; i < wid - l; i++)
			buf[i] = padd;

		buf[i] = '\0';

		if (fl & MIN) /* Asign extra char to left of buf [buf>padd]*/
		{
			return (write(1, &buf[ind], l) + write(1, &buf[0], i));
		}
		else /* Asign extra char to left of padding [padd>buf]*/
		{
			return (write(1, &buf[0], i) + write(1, &buf[ind], l));
		}
	}

	return (write(1, &buf[ind], l));
}

/**
 * wr_pointer - it write a memory address
 * @buf: the arrays of chars
 * @ind: the index at which the number starts in the buffer
 * @l: the length of number
 * @wid: the width specifier
 * @fl: the flags specifier
 * @padd: the char representing the padding
 * @plus_c: the char representing extra char
 * @padd_start: the index at which padding should start
 *
 * Return: the number of written chars.
 */
int wr_pointer(char buf[], int ind, int l,
	int wid, int fl, char padd, char plus_c, int padd_start)
{
	int i;

	if (wid > l)
	{
		for (i = 3; i < wid - l + 3; i++)
			buf[i] = padd;
		buf[i] = '\0';
		if (fl & MIN && padd == ' ')/* Asign extra char to left of buf */
		{
			buf[--ind] = 'x';
			buf[--ind] = '0';
			if (plus_c)
				buf[--ind] = plus_c;
			return (write(1, &buf[ind], l) + write(1, &buf[3], i - 3));
		}
		else if (!(fl & MIN) && padd == ' ')/* extra char to left of buf */
		{
			buf[--ind] = 'x';
			buf[--ind] = '0';
			if (plus_c)
				buf[--ind] = plus_c;
			return (write(1, &buf[3], i - 3) + write(1, &buf[ind], l));
		}
		else if (!(fl & MIN) && padd == '0')/* extra char to left of padd */
		{
			if (plus_c)
				buf[--padd_start] = plus_c;
			buf[1] = '0';
			buf[2] = 'x';
			return (write(1, &buf[padd_start], i - padd_start) +
				write(1, &buf[ind], l - (1 - padd_start) - 2));
		}
	}
	buf[--ind] = 'x';
	buf[--ind] = '0';
	if (plus_c)
		buf[--ind] = plus_c;
	return (write(1, &buf[ind], BUF_SIZE - ind - 1));
}


