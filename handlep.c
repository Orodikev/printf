#include "main.h"
/**
 * print_h - Function to print an argument depending on the type
 * @form: The formatted string where arguments are printed.
 * @list: Argument list printed.
 * @index: Represent the index.
 * @buffer: Array to print.
 * @flags: Determines the raised flags
 * @width: Finds the width.
 * @precision: specifies the precision
 * @size: Specifies the size
 * Return: 1 or 2;
 */
int print_h(const char *form, int *index, va_list list, char buffer[],
	int flags, int width, int precision, int size)
{
	int i, in_length = 0, chars_printed = -1;
	form_t fmt_types[] = {
		{'c', char_printfun}, {'s', string_printfun}, {'%', percent_printfun},
		{'i', integer_printf}, {'d', integer_printf}, {'b', binary_printf},
		{'u', unsigned_printf}, {'o', octal_printf}, {'x', hexa_printf},
		{'X', up_hexa_printf}, {'p', pointer_printf}, {'S', special_printf},
		{'r', reverse_printf}, {'R', rot13_printf}, {'\0', NULL}
	};
	for (i = 0; fmt_types[i].form != '\0'; i++)
		if (form[*index] == fmt_types[i].form)
			return (fmt_types[i].fun(list, buffer, flags, width, precision, size));

	if (fmt_types[i].form == '\0')
	{
		if (form[*index] == '\0')
			return (-1);
		in_length += write(1, "%%", 1);
		if (form[*index - 1] == ' ')
			in_length += write(1, " ", 1);
		else if (width)
		{
			--(*index);
			while (form[*index] != ' ' && form[*index] != '%')
				--(*index);
			if (form[*index] == ' ')
				--(*index);
			return (1);
		}
		in_length += write(1, &form[*index], 1);
		return (in_length);
	}
	return (chars_printed);
}
