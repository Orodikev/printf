#include "main.h"

/**
 * find_size - Determine the size where the argument is casted
 * @format: The string where the arguments are printed
 * @li: Argument list to be printed
 *
 * Return: Precision.
 */
int find_size(const char *format, int *li)
{
	int cr = *li + 1;
	int size = 0;

	if (format[cr] == 'l')
		size = LONG_STR;
	else if (format[cr] == 'h')
		size = SHORT_STR;

	if (size == 0)
		*li = cr - 1;
	else
		*li = cr;

	return (size);
}
