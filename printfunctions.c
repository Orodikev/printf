#include "main.h"

/****************** A function to print characters *************************/

/**
 * charprintfun - A function that Prints a char
 * @types: Argument list
 * @buffer: Array to handle the print function
 * @flags:  Determines all active flags
 * @width: Width of the character
 * @precision: Specific precision
 * @size: specifies the size
 * Return: The total number of characters that have been printed
 */
int char_printfun(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char c = va_arg(types, int);

	return (hwrt_char(c, buffer, flags, width, precision, size));
}
/************ function to print a string *******************/
/**
 * string_printfun - A function that prints a string
 * @types: The list of arguments passed to the function
 * @buffer: Buffer array to handle print
 * @flags:  Determines all the active flags
 * @width: Gets the width of the string.
 * @precision: specifies the precision
 * @size: Specifies the size
 * Return: Total number of characters printed
 */
int string_printfun(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = 0, i;
	char *str = va_arg(types, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
			str = "      ";
	}

	while (str[length] != '\0')
		length++;

	if (precision >= 0 && precision < length)
		length = precision;

	if (width > length)
	{
		if (flags & FUNC_MIN)
		{
			write(1, &str[0], length);
			for (i = width - length; i > 0; i--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (i = width - length; i > 0; i--)
				write(1, " ", 1);
			write(1, &str[0], length);
			return (width);
		}
	}

	return (write(1, str, length));
}
/************************* Function to print % sign*************************/
/**
 * percent_printfun - function to print the percent(%) sign
 * @types: The list of arguments
 * @buffer: The buffer that handles the print
 * @flags:  Determines the total active flags
 * @width: Obtains the width.
 * @precision: Specifies the precision
 * @size: specifies the size
 * Return: On success returns the number of char printed
 */
int percent_printfun(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}

/************ A function to print integer characters******************/
/**
 * integer_printf - A function to print integer arguments
 * @types: The passed arguments
 * @buffer: An array that handles the print
 * @flags:  Determines the raised flags
 * @width: Finds the width.
 * @precision: Specifies the precision
 * @size: specifies the size
 * Return: All the characters printed
 */
int integer_printf(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	int neg = 0;
	long int n = va_arg(types, long int);
	unsigned long int num;

	n = size_num(n, size);

	if (n == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)n;

	if (n < 0)
	{
		num = (unsigned long int)((-1) * n);
		neg = 1;
	}

	while (num > 0)
	{
		buffer[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (num_wrt(is_negative, i, buffer, flags, width, precision, size));
}

/************* A function to print binary type ****************/
/**
 * binary_printf - Function to print unsigned number
 * @types: The arguments passed
 * @buffer: An array buffer that handles the print
 * @flags:  Determines the active flags
 * @width: Obtains the width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: The total number of characters printed
 */
int binary_printf(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	unsigned int n, m, i, sum;
	unsigned int a[32];
	int count;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	n = va_arg(types, unsigned int);
	m = 2147483648; /* (2 ^ 31) */
	a[0] = n / m;
	for (i = 1; i < 32; i++)
	{
		m /= 2;
		a[i] = (n / m) % 2;
	}
	for (i = 0, sum = 0, count = 0; i < 32; i++)
	{
		sum += a[i];
		if (sum || i == 31)
		{
			char z = '0' + a[i];

			write(1, &z, 1);
			count++;
		}
	}
	return (count);
}

