#include "main.h"

/**
 * pointer_printf - function to print the value of a pointer
 * @types: List the arguments passed to the function
 * @buffer: Array to handle the print function
 * @flags:  Determines the raised flags
 * @width: Finds the width of the print
 * @precision: Gives the specific precision of the print
 * @size: specifies the size
 * Return: The total number of printed chars.
 */
int pointer_printf(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char ch = 0, padd = ' ';
	int index = BUFF_SIZE - 2, length = 2, padd_start = 1;
	unsigned long no_ads;
	char map_to[] = "0123456789abcdef";
	void *ads = va_arg(types, void *);

	UNUSED(width);
	UNUSED(size);

	if (ads == NULL)
		return (write(1, "(nil)", 5));

	buffer[BUFF_SIZE - 1] = '\0';
	UNUSED(precision);

	no_ads = (unsigned long)ads;

	while (no_ads > 0)
	{
		buffer[index--] = map_to[no_ads % 16];
		no_ads /= 16;
		length++;
	}

	if ((flags & FUNC_Z) && !(flags & FUNC_MIN))
		padd = '0';
	if (flags & FUNC_PL)
		ch = '+', length++;
	else if (flags & FUNC_S)
		ch = ' ', length++;

	index++;

	/*return (write(1, &buffer[i], BUFF_SIZE - i - 1));*/
	return (pointer_wrt(buffer, index, length,
		width, flags, padd, ch, padd_start));
}

/******** Function for special characters**********/
/**
 * special_printf - A function to print ascii codes in hexa
 * of non printable chars
 * @types: list of the passed arguments
 * @buffer: An array that handles the print function
 * @flags:  Determines the raised flags
 * @width: Determines the width of the print
 * @precision: Gives the specific precision
 * @size: Gives the specific size
 * Return: All the printed characters
 */
int special_printf(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int i;
	int offset = 0;
	char *str = va_arg(types, char *);

	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		return (write(1, "(null)", 6));

	/**while (str[i] != '\0')**/
	for (i = 0; str[i] != '\0'; i++)
	{
		if (printability_check(str[i]))
			buffer[i + offset] = str[i];
		else
			offset += hex_append(str[i], buffer, i + offset);

	}

	buffer[i + offset] = '\0';

	return (write(1, buffer, i + offset));
}

/**
 * reverse_printf - Function to print a reverse string.
 * @types: Passed arguments list
 * @buffer:an array to curry print
 * @flags:  Determines the active flags
 * @width: Finds the print width
 * @precision: gives the specified precision
 * @size: gives the specified size
 * Return: The printed characters
 */

int reverse_printf(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char *str;
	int i, count = 0;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);

	str = va_arg(types, char *);

	if (str == NULL)
	{
		UNUSED(precision);

		str = ")Null(";
	}
	for (i = 0; str[i]; i++)
		;

	for (i = i - 1; i >= 0; i--)
	{
		char z = str[i];

		write(1, &z, 1);
		count++;
	}
	return (count);
}
/******** Function for printing strings in ROT13 ********/
/**
 * rot13_printf - Function printing strings in rot13.
 * @types: Passed arguments list
 * @buffer: An array to handle the print
 * @flags:  Determines the active flags
 * @width: Gives the width of print
 * @precision: Gives the precision of the print
 * @size: Gives the size of the print
 * Return: Total number of chars printed
 */
int rot13_printf(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char ec;
	char *str;
	unsigned int i, j;
	int count = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(types, char *);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		str = "(AHYY)";
	for (i = 0; str[i]; i++)
	{
		for (j = 0; in[j]; j++)
		{
			if (in[j] == str[i])
			{
				ec = out[j];
				write(1, &ec, 1);
				count++;
				break;
			}
		}
		if (!in[j])
		{
			ec = str[i];
			write(1, &ec, 1);
			count++;
		}
	}
	return (count);
}

