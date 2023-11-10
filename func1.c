#include "shell.h"

/**
 *alpha_check - checks for alphabetic character
 *@c: The character to input
 *Return: 1 if c is alphabetic, 0 otherwise
 */

int alpha_check(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}
/**
 * inter - returns true if shell is interactive mode
 * @add: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int inter(info_t *add)
{
	return (isatty(STDIN_FILENO) && add->readfd <= 2);
}
/**
 * is_atoi - converts a string to an integer
 *@c: the string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
 */

int is_atoi(char *c)
{
	int i;
	int sign = 1;
	int flag = 0;
	int output;
	unsigned int result = 0;

	for (i = 0; c[i] != '\0' && flag != 2; i++)
	{
		if (c[i] == '-')
			sign *= -1;

		if (c[i] >= '0' && c[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (c[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
/**
 * delim - checks if character is a delimeter
 * @c: the char to check
 * @del: the delimeter string
 * Return: 1 if true, 0 if false
 */
int delim(char c, char *del)
{
	while (*del)
		if (*del++ == c)
			return (1);
	return (0);
}
