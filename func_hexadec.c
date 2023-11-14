#include "main.h"
/**
 * unsigned_printf - A function to print unsigned numbers
 * @types: The list of arguments available
 * @buffer: An array used to print
 * @flags:  Determines the raised flags
 * @width: finds the width of the print
 * @precision: Holds the specific precision
 * @size: Size specifier
 * Return: The total number of chars printed successfully
 */
int unsigned_printf(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	unsigned long int no = va_arg(types, unsigned long int);

	no = size_unsg(no, size);

	if (no == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (no > 0)
	{
		buffer[i--] = (no % 10) + '0';
		no /= 10;
	}

	i++;

	return (unsgnd_wrt(0, i, buffer, flags, width, precision, size));
}

/************* Function for printing octal numbers**********************/
/**
 * octal_printf - Converts unsigned numbers to octal format
 * @types: Argument list provided
 * @buffer: Buffer used to perfume the print action
 * @flags:  finds all the raised flags
 * @width: Finds the width of the print
 * @precision: Specifies the precision of print
 * @size: Represents the size of print
 * Return: Total number of chars printed
 */
int octal_printf(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{

	int i = BUFF_SIZE - 2;
	unsigned long int no = va_arg(types, unsigned long int);
	unsigned long int init_no = no;

	UNUSED(width);

	no = size_unsg(no, size);

	if (no == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (no > 0)
	{
		buffer[i--] = (no % 8) + '0';
		no /= 8;
	}

	if (flags & FUNC_H && init_no != 0)
		buffer[i--] = '0';

	i++;

	return (unsgnd_wrt(0, i, buffer, flags, width, precision, size));
}

/****** Function to convert unsigned number to hexadecimal *********/
/**
 * hexa_printf - A function to convert an unsigned number to
 * hexadecimal notation
 * @types: Arguments provided
 * @buffer: An array to handle the print
 * @flags:  Determines all the raised flags
 * @width: Contains the width of printing
 * @precision: Contains the specific precision for printing
 * @size: finds the specified printing size
 * Return: The chars that have been printed
 */
int hexa_printf(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (hexaval_printf(types, "0123456789abcdef", buffer,
		flags, 'x', width, precision, size));
}

/**** Function to print unsigned number to upper hexadecimal********/
/**
 * up_hexa_printf - Converts an unsigned number to
 * upper hexadecimal and prints it.
 * @types: List of arguments passed
 * @buffer: The array to handle the print function
 * @flags:  Determines all high flags
 * @width: Calculates the width of the print
 * @precision: give the specific precision
 * @size: Gives the specific print size
 * Return: The printed characters in upper hexadecimal
 */
int up_hexa_printf(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (hexaval_printf(types, "0123456789ABCDEF", buffer,
		flags, 'X', width, precision, size));
}

/***Function that converts Hexa number and print in lower or upper case***/
/**
 * hexaval_printf - converts an unsigned number to lower or upper hexadecimal
 * @types: Gives the list of all arguments
 * @map_to: An array where all the numbers are mapped to
 * @buffer: A buffer array where the print function takes place
 * @flags:  Determines all the activated flags
 * @flag_ch: Store the calculated active flags
 * @width: Stores the width of the print
 * @precision: specifies the precision of print
 * @size: Specifies the size of the print
 * Return: The characters printed
 */
int hexaval_printf(va_list types, char map_to[], char buffer[],
	int flags, char flag_ch, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	unsigned long int no = va_arg(types, unsigned long int);
	unsigned long int init_no = no;

	UNUSED(width);

	no = size_unsg(no, size);

	if (no == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (no > 0)
	{
		buffer[i--] = map_to[no % 16];
		no /= 16;
	}

	if (flags & FUNC_H && init_no != 0)
	{
		buffer[i--] = flag_ch;
		buffer[i--] = '0';
	}

	i++;

	return (unsgnd_wrt(0, i, buffer, flags, width, precision, size));
}
