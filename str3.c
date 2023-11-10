#include "shell.h"
/**
 **_strchr - locates a character in a string
 *@par: the string to be parsed
 *@cha: the character to look for
 *Return: (s) a pointer to the memory area s
 */
char *_strchr(char *par, char cha)
{
	do {
		if (*par == cha)
			return (par);
	} while (*par++ != '\0');

	return (NULL);
}

/**
 **_strncat - concatenates two strings
 *@dest: the first string
 *@amount: the amount of bytes to be maximally used
 *@src: the second string
 *Return: the concatenated string
 */
char *_strncat(char *dest, char *src, int amount)
{
	int i;
	int j;
	char *s = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < amount)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < amount)
		dest[i] = '\0';
	return (s);
}

/**
 **_strncpy - copies a string
 *@dest: the destination string to be copied to
 *@amount: the amount of characters to be copied
 *@src: the source string
 *
 *Return: the concatenated string
 */
char *_strncpy(char *dest, char *src, int amount)
{
	int it;
	int j;
	char *str = dest;

	it = 0;
	while (src[it] != '\0' && it < amount - 1)
	{
		dest[it] = src[it];
		it++;
	}
	if (it < amount)
	{
		j = it;
		while (j < amount)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (str);
}
