#ifndef MAIN_H
#define MAIN_H
#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>
#include <unistd.h>

#define UNUSED(x) (void)(x)
#define BUF_SIZE 1024

/* the flags */
#define MIN 1
#define PLUS 2
#define ZERO 4
#define HASH 8
#define SPACE 16

/* the sizes */
#define LONG 2
#define SHORT 1

/**
 * struct s_format - Struct op
 *
 * @s_format: The format.
 * @fass: The function associated.
 */
struct s_format
{
	char format;
	int (*fass)(va_list, char[], int, int, int, int);
};

/**
 * typedef struct s_format format_t - Struct op
 *
 * @s_format: The format.
 * @f_ass: The function associated.
 */
typedef struct s_format format_t;

int _printf(const char *format, ...);
int handle_pr(const char *format, int *i,
va_list list, char buf[], int fl, int wid, int prec, int size);

/****************** FUNCTIONS ******************/

/* Funtions to print chars and strings */
int pr_char(va_list types, char buf[],
	int fl, int wid, int prec, int size);
int pr_string(va_list types, char buf[],
	int fl, int wid, int prec, int size);
int pr_percent(va_list types, char buf[],
	int fl, int wid, int prec, int size);

/* Functions to print numbers */
int pr_int(va_list types, char buf[],
	int fl, int wid, int prec, int size);
int pr_binary(va_list types, char buf[],
	int fl, int wid, int prec, int size);
int pr_unsigned(va_list types, char buf[],
	int fl, int wid, int prec, int size);
int pr_octal(va_list types, char buf[],
	int fl, int wid, int prec, int size);
int pr_hex(va_list types, char buf[],
	int fl, int wid, int prec, int size);
int pr_hexa_upper(va_list types, char buf[],
	int fl, int wid, int prec, int size);

int pr_hexa(va_list types, char map_to[],
char buf[], int fl, char flag_ch, int wid, int prec, int size);

/* Function to print non printable characters */
int pr_unprintable(va_list types, char buf[],
	int fl, int wid, int prec, int size);

/* Funcion to print memory address */
int pr_pointer(va_list types, char buf[],
	int fl, int wid, int prec, int size);

/* Funciotns to handle other specifiers */
int get_fl(const char *format, int *i);
int get_wid(const char *format, int *i, va_list list);
int get_prec(const char *format, int *i, va_list list);
int get_size(const char *format, int *i);

/*Function to print string in reverse*/
int pr_reverse(va_list types, char buf[],
	int fl, int wid, int prec, int size);

/*Function to print a string in rot 13*/
int pr_RotStr(va_list types, char buf[],
	int fl, int wid, int prec, int size);

/* wid handler */
int handle_wr_char(char c, char buf[],
	int fl, int wid, int prec, int size);
int wr_number(int is_positive, int ind, char buf[],
	int fl, int wid, int prec, int size);
int wr_num(int ind, char bff[], int fl, int wid, int prec,
	int length, char padd, char extra_c);
int wr_pointer(char buf[], int ind, int length,
	int wid, int fl, char padd, char extra_c, int padd_start);

int wr_unsigned(int is_negative, int ind,
char buf[],
	int fl, int wid, int prec, int size);

/****************** UTILS ******************/
int is_printable(char);
int append_hexa_code(char, char[], int);

long int convert_size_number(long int num, int size);
long int convert_size_unsigned(unsigned long int num, int size);

#endif
