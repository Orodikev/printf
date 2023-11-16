#include "main.h"

void printb(char buffer[], int *b_index);

/**
 * _printf - The main printf function
 * @f_p: Function format
 * Return: The characters to be printed.
 */
int _printf(const char *f_p, ...)
{
	int i = 0;
	int p = 0;
	int print_c = 0;
	int flags, width, precision, size, b_index = 0;
	va_list list;
	char buffer[BUFF_SIZE];

	if (f_p == NULL)
		return (-1);

	va_start(list, f_p);

	while (f_p && f_p[i] != '\0')
	{
		if (f_p[i] != '%')
		{
			buffer[b_index++] = f_p[i];
			if (b_index == BUFF_SIZE)
				printb(buffer, &b_index);
			print_c++;
		}
		else
		{
			printb(buffer, &b_index);
			flags = find_flags(f_p, &i);
			width = find_width(f_p, &i, list);
			precision = find_precision(f_p, &i, list);
			size = find_size(f_p, &i);
			++i;
			p = print_h(f_p, &i, list, buffer,
				flags, width, precision, size);
			if (p == -1)
				return (-1);
			print_c += p;
		
		}
		i++;
	}

	printb(buffer, &b_index);

	va_end(list);

	return (print_c);
}

/**
 * printb - Function to print buffer content.
 * @buffer: an array made of characters
 * @b_index: Index representing the length and next char is added.
 */
void printb(char buffer[], int *b_index)
{
	if (*b_index > 0)
		write(1, &buffer[0], *b_index);

	*b_index = 0;
}
