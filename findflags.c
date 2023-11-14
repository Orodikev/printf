#include "main.h"

/**
 * find_flags - Function to determine the raised flags
 * @format: Strings where the arguments are printed
 * @pr: Used to store the parameter given.
 * Return: Flags:
 */
int find_flags(const char *format, int *pr)
{
	/* - + 0 # ' ' */
	/* 1 2 4 8  16 */
	int jk, cr;
	int flags = 0;
	const char FLAGS_CH[] = {'-', '+', '0', '#', ' ', '\0'};
	const int FLAGS_ARR[] = {FUNC_MIN, FUNC_PL, FUNC_Z, FUNC_H, FUNC_S, 0};

	for (cr = *pr + 1; format[cr] != '\0'; cr++)
	{
		for (jk = 0; FLAGS_CH[jk] != '\0'; jk++)
			if (format[cr] == FLAGS_CH[jk])
			{
				flags |= FLAGS_ARR[jk];
				break;
			}

		if (FLAGS_CH[jk] == 0)
			break;
	}

	*pr = cr - 1;

	return (flags);
}
