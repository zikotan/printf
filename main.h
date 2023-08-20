#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#define BUF_SZ 1024

int _printf(const char *format, ...);
int handling(const char *frmt, int *i, va_list list, char buf[], int fl, int w, int prec, int sz);

int get_fl(const char *format, int *i);
int get_w(const char *format, int *i, va_list list);
int get_prec(const char *format, int *i, va_list list);
int get_sz(const char *format, int *i);

#endif

