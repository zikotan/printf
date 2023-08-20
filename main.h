#ifndef MAIN_H
#define MAIN_H
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

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
 * typedef struct s_format fmt_t - Struct op
 *
 * @s_format: The format.
 * @f_ass: The function associated.
 */
typedef struct s_format fmt_t;

int _printf(const char *format, ...);
int handle_pr(const char *format, int *i,
va_list list, char buffer[], int flags, int width, int precision, int size);

/* Funciotns to handle other specifiers */
int get_fl(const char *format, int *i);
int get_wid(const char *format, int *i, va_list list);
int get_prec(const char *format, int *i, va_list list);
int get_size(const char *format, int *i);

#endif

