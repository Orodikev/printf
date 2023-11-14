#include "main.h"

/**
 * printability_check - Checks if the argument given is printable
 * @ca: The argument to be checked.
 *
 i* Return:If printable 1,if not printable 0.
 */
int printability_check(char ca)
{
	if (ca >= 32 && ca < 127)
		return (1);

	return (0);
}

/**
 * hex_append - Append ascci in hexadecimal code to buffer
 * @buffer: An array made of character arguments
 * @i: Index at which to start appending.
 * @ascii_code: ASSCI CODE.
 * Return: Always 3
 */
int hex_append(char ascii_code, char buffer[], int i)
{
	char map_to[] = "0123456789ABCDEF";

	if (ascii_code < 0)
		ascii_code *= -1;

	buffer[i++] = '\\';
	buffer[i++] = 'x';

	buffer[i++] = map_to[ascii_code / 16];
	buffer[i] = map_to[ascii_code % 16];

	return (3);
}

/**
 * digit_check - Checks if the given character is a digit
 * @ca: Character argument to be checked
 *
 * Return: 1 if ca is a digit, 0 otherwise
 */
int digit_check(char ca)
{
	if (ca >= '0' && ca <= '9')
		return (1);

	return (0);
}

/**
 * size_num - function to cast a number to the defined size.
 * @num: Number to be casted.
 * @size: Number representing the character to be casted
 *
 * Return: The casted value of num
 */
long int size_num(long int num, int size)
{
	if (size == LONG_STR)
		return (num);
	else if (size == SHORT_STR)
		return ((short)num);

	return ((int)num);
}

/**
 * size_unsg - Function to cast the given number to the specified size
 * @num: The given argument to be casted
 * @size: Represent the total numbers casted
 *
 * Return: The value of num casted successfully
 */
long int size_unsg(unsigned long int num, int size)
{
	if (size == LONG_STR)
		return (num);
	else if (size == SHORT_STR)
		return ((unsigned short)num);

	return ((unsigned int)num);
}

