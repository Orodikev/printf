#include "main.h"
/*
 * hwrt_char -  Function to print a string
 * @c: character types.
 * @buffer: The array to handle the print function
 * @flags:  Determines the raised flags
 * @width: Gives the printing width
 * @precision: Specifies the precision for printing
 * @size: Specifies the size to be printed
 *
 * Return: Total number of printed characters.
 */
int hwrt_char(char c, char buffer[],
	int flags, int width, int precision, int size)
{
	int i = 0;
	char padd = ' ';

	UNUSED(precision);
	UNUSED(size);

	if (flags & FUNC_Z)
		padd = '0';

	buffer[i++] = c;
	buffer[i] = '\0';

	if (width > 1)
	{
		buffer[BUFF_SIZE - 1] = '\0';
		for (i = 0; i < width - 1; i++)
			buffer[BUFF_SIZE - i - 2] = padd;

		if (flags & FUNC_MIN)
			return (write(1, &buffer[0], 1) +
					write(1, &buffer[BUFF_SIZE - i - 1], width - 1));
		else
			return (write(1, &buffer[BUFF_SIZE - i - 1], width - 1) +
					write(1, &buffer[0], 1));
	}

	return (write(1, &buffer[0], 1));
}

/**
 * num_wrt -  Function to print the string
 * @neg: List of arguments
 * @index: Character types to be printed
 * @buffer: Buffer array to handle print
 * @flags:  Determines the active flags
 * @width: Finds the width of printing.
 * @precision: Specifies the precision
 * @size: Specifies the size
 *
 * Return: The total printed characters.
 */
int num_wrt(int neg, int index, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = BUFF_SIZE - index - 1;
	char padd = ' ', ex_ch = 0;

	UNUSED(size);

	if ((flags & FUNC_Z) && !(flags & FUNC_MIN))
		padd = '0';
	if (neg)
		ex_ch = '-';
	else if (flags & FUNC_PL)
		ex_ch = '+';
	else if (flags & FUNC_S)
		ex_ch = ' ';

	return (write_no(index, buffer, flags, width, precision,
		length, padd, ex_ch));
}

/**
 * write_no - Use a buffer to write a character
 * @index: specifies the start index
 * @buffer: Buffer
 * @flags: Flags
 * @width: Gives the width of print
 * @prec: specifies the precision
 * @length: Specifies the lengh
 * @padd: Pading char
 * @ex_c: Extra char
 *
 * Return: Total number of printed chars.
 */
int write_no(int index, char buffer[],
	int flags, int width, int prec,
	int length, char padd, char ex_c)
{
	int i, padd_start = 1;

	if (prec == 0 && index == BUFF_SIZE - 2 && buffer[index] == '0' && width == 0)
		return (0);
	if (prec == 0 && index == BUFF_SIZE - 2 && buffer[index] == '0')
		buffer[index] = padd = ' ';
	if (prec > 0 && prec < length)
		padd = ' ';
	while (prec > length)
		buffer[--index] = '0', length++;
	if (ex_c != 0)
		length++;
	if (width > length)
	{
		for (i = 1; i < width - length + 1; i++)
			buffer[i] = padd;
		buffer[i] = '\0';
		if (flags & FUNC_MIN && padd == ' ')
		{
			if (ex_c)
				buffer[--index] = ex_c;
			return (write(1, &buffer[index], length) + write(1, &buffer[1], i - 1));
		}
		else if (!(flags & FUNC_MIN) && padd == ' ')
		{
			if (ex_c)
				buffer[--index] = ex_c;
			return (write(1, &buffer[1], i - 1) + write(1, &buffer[index], length));
		}
		else if (!(flags & FUNC_MIN) && padd == '0')
		{
			if (ex_c)
				buffer[--padd_start] = ex_c;
			return (write(1, &buffer[padd_start], i - padd_start) +
				write(1, &buffer[index], length - (1 - padd_start)));
		}
	}

	if (ex_c)
		buffer[--index] = ex_c;
	return (write(1, &buffer[index], length));
}

/**
 * unsgnd_wrt - function to print unsigned number
 * @neg: indicates a negative number
 * @index: the starting index of the number in the buffer
 * @buffer: An array made of characters
 * @flags: specifies the active flags
 * @width: specifies the width of the print
 * @precision: specifies the precision of the print
 * @size: specifies the size of print
 *
 * Return: The total number written
 */
int unsgnd_wrt(int neg, int index,
	char buffer[],
	int flags, int width, int precision, int size)
{
	int length = BUFF_SIZE - index - 1, i = 0;
	char padd = ' ';

	UNUSED(neg);
	UNUSED(size);

	if (precision == 0 && index == BUFF_SIZE - 2 && buffer[index] == '0')
		return (0);

	if (precision > 0 && precision < length)
		padd = ' ';

	while (precision > length)
	{
		buffer[--index] = '0';
		length++;
	}

	if ((flags & FUNC_Z) && !(flags & FUNC_MIN))
		padd = '0';

	if (width > length)
	{
		for (i = 0; i < width - length; i++)
			buffer[i] = padd;

		buffer[i] = '\0';

		if (flags & FUNC_MIN)
		{
			return (write(1, &buffer[index], length) + write(1, &buffer[0], i));
		}
		else
		{
			return (write(1, &buffer[0], i) + write(1, &buffer[index], length));
		}
	}

	return (write(1, &buffer[index], length));
}

/**
 * pointer_wrt - Function to print the memory address of a char
 * @buffer: Array of characters
 * @index: starting index in the buffer
 * @length: The length of the passed numbers
 * @width: specifies the printing width
 * @flags: specifies the active flags
 * @padd: The padding characters
 * @ex_c: stores any extra character
 * @padd_start: the index where padding begines
 *
 * Return: Total number of printed characters.
 */
int pointer_wrt(char buffer[], int index, int length,
	int width, int flags, char padd, char ex_c, int padd_start)
{
	int i;

	if (width > length)
	{
		for (i = 3; i < width - length + 3; i++)
			buffer[i] = padd;
		buffer[i] = '\0';
		if (flags & FUNC_MIN && padd == ' ')
		{
			buffer[--index] = 'x';
			buffer[--index] = '0';
			if (ex_c)
				buffer[--index] = ex_c;
			return (write(1, &buffer[index], length) + write(1, &buffer[3], i - 3));
		}
		else if (!(flags & FUNC_MIN) && padd == ' ')
		{
			buffer[--index] = 'x';
			buffer[--index] = '0';
			if (ex_c)
				buffer[--index] = ex_c;
			return (write(1, &buffer[3], i - 3) + write(1, &buffer[index], length));
		}
		else if (!(flags & FUNC_MIN) && padd == '0')
		{
			if (ex_c)
				buffer[--padd_start] = ex_c;
			buffer[1] = '0';
			buffer[2] = 'x';
			return (write(1, &buffer[padd_start], i - padd_start) +
				write(1, &buffer[index], length - (1 - padd_start) - 2));
		}
	}
	buffer[--index] = 'x';
	buffer[--index] = '0';
	if (ex_c)
		buffer[--index] = ex_c;
	return (write(1, &buffer[index], BUFF_SIZE - index - 1));
}

