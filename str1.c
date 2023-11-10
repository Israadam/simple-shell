#include "shell.h"
/**
 * _strcat - concatenates two strings
 * @dest: the destination buffer
 * @src: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}


/**
 * _strcmp - performs lexicogarphic comparison of two strangs.
 * @first: the first strang
 * @second: the second strang
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int _strcmp(char *first, char *second)
{
	while (*first && *second)
	{
		if (*first != *second)
			return (*first - *second);
		first++;
		second++;
	}
	if (*first == *second)
		return (0);
	else
		return (*first < *second ? -1 : 1);
}
/**
 * _strlen - returns the length of a string
 * @str: the string whose length to check
 *
 * Return: integer length of string
 */
int _strlen(char *str)
{
	int i = 0;

	if (!str)
		return (0);

	while (*str++)
		i++;
	return (i);
}
/**
 * start_with - checks if needle starts with haystack
 * @stackstr: string to search
 * @needle: the substring to find
 *
 * Return: address of next char of haystack or NULL
 */
char *start_with(const char *stackstr, const char *needle)
{
	while (*needle)
		if (*needle++ != *stackstr++)
			return (NULL);
	return ((char *)stackstr);
}
