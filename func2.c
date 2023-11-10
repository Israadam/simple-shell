#include "shell.h"

/**
 * base10 - function prints a decimal (integer) number (base 10)
 * @input: the input
 * @file: the file descriptor to write to
 *
 * Return: number of characters printed
 */
int base10(int input, int file)
{
	int (*m_putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int all, current;

	if (file == STDERR_FILENO)
		m_putchar = _eputchar;
	if (input < 0)
	{
		all = -input;
	m_putchar('-');
		count++;
	}
	else
	all = input;
	current = all;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (all / i)
		{
			m_putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	m_putchar('0' + current);
	count++;

	return (count);
}

/**
 * _error - prints an error message
 * @info: the parameter & return info struct
 * @strer: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void _error(info_t *info, char *strer)
{
	_eputs(info->fname);
	_eputs(": ");
	base10(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(strer);
}

/**
 * str_to_int - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int str_to_int(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;  /* TODO: why does this make main return 255? */
	for (i = 0;  s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * rm_comments - function replaces first instance of '#' with '\0'
 * @buff: address of the string to modify
 *
 * Return: Always 0;
 */
void rm_comments(char *buff)
{
	int i;

	for (i = 0; buff[i] != '\0'; i++)
		if (buff[i] == '#' && (!i || buff[i - 1] == ' '))
		{
			buff[i] = '\0';
			break;
		}
}
/**
 * convertnum - converter function, a clone of itoa
 * @num: number
 * @base: base
 * @flag: argument flags
 *
 * Return: string
 */
char *convertnum(long int num, int flag, int base)
{
	static char *ar;
	static char buf[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flag & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	ar = flag & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buf[49];
	*ptr = '\0';

	do	{
		*--ptr = ar[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}
