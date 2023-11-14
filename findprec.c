#include "main.h"

/**
 * find_precision - Function to determine the precision to print
 * @format: The string where arguments are printed
 * @ar: Argument list to be printed.
 * @list: Argument list.
 *
 * Return: Precision.
 */
int find_precision(const char *format, int *ar, va_list list)
{
	int cr = *ar + 1;
	int precision = -1;

	if (format[cr] != '.')
		return (precision);

	precision = 0;

	for (cr += 1; format[cr] != '\0'; cr++)
	{
		if (digit_check(format[cr]))
		{
			precision *= 10;
			precision += format[cr] - '0';
		}
		else if (format[cr] == '*')
		{
			cr++;
			precision = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*ar = cr - 1;

	return (precision);
}

