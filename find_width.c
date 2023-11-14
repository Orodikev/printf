#include "main.h"

/**
 * find_width - A function to determine the width for printing
 * @format: The string where the arguments will be printed.
 * @i: Argument list that is to printed.
 * @list: list of arguments.
 *
 * Return: The width for printing.
 */
int find_width(const char *format, int *i, va_list list)
{
	int ct;
	int width = 0;

	for (ct = *i + 1; format[ct] != '\0'; ct++)
	{
		if (digit_check(format[ct]))
		{
			width *= 10;
			width += format[ct] - '0';
		}
		else if (format[ct] == '*')
		{
			ct++;
			width = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*i = ct - 1;

	return (width);
}
