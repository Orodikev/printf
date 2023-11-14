#ifndef MAIN_H
#define MAIN_H
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

#define UNUSED(x) (void)(x)
#define BUFF_SIZE 1024

/* FLAGS */
#define FUNC_MIN 1
#define FUNC_PL 2
#define FUNC_Z 4
#define FUNC_H 8
#define FUNC_S 16

/* SIZES */
#define LONG_STR 2
#define SHORT_STR 1

/**
 * struct form - Struct
 *
 * @form: The format.
 * @fun: The function associated.
 */
struct form
{
	char form;
	int (*fun)(va_list, char[], int, int, int, int);
};

/**
 * typedef struct form form_t - Struct op
 *
 * @form: The specific format.
 * @fun_t: The associated function.
 */
typedef struct form form_t;

int _printf(const char *format, ...);
int print_h(const char *form, int *i,
va_list list, char buffer[], int flags, int width, int precision, int size);

/*************Function Prototypes to print characters and strings************/

int char_printfun(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int string_printfun(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int percent_printfun(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int integer_printf(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int binary_printf(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int unsigned_printf(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int octal_printf(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int hexa_printf(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int Up_hexa_printf(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int hexaval_printf(va_list types, char map_to[],
char buffer[], int flags, char flag_ch, int width, int precision, int size);
int special_printf(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int pointer_printf(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int find_flags(const char *format, int *i);
int find_width(const char *format, int *i, va_list list);
int find_precision(const char *format, int *i, va_list list);
int find_size(const char *format, int *i);
int reverse_printf(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int rot13_printf(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int hwrt_char(char c, char buffer[],
	int flags, int width, int precision, int size);
int num_wrt(int is_positive, int ind, char buffer[],
	int flags, int width, int precision, int size);
int write_no(int ind, char bff[], int flags, int width, int precision,
	int length, char padd, char extra_c);
int pointer_wrt(char buffer[], int ind, int length,
	int width, int flags, char padd, char extra_c, int padd_start);
int unsgnd_wrt(int is_negative, int ind,
char buffer[],
	int flags, int width, int precision, int size);

/**Functions for utils*****/
int printability_check(char);
int hex_append(char, char[], int);
int digit_check(char);

long int size_num(long int num, int size);
long int size_unsg(unsigned long int num, int size);

#endif
