#include "shell.h"

/**
 * **strtw - splits a string into words. Repeat delimiters are ignored
 * @str: the input string
 * @r: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **strtw(char *str, char *r)
{
int i, j, k, m, numwords = 0;
char **s;

if (str == NULL || str[0] == 0)
return (NULL);
if (!r)
r = " ";
for (i = 0; str[i] != '\0'; i++)
if (!delim(str[i], r) && (delim(str[i + 1], r) || !str[i + 1]))
numwords++;
if (numwords == 0)
return (NULL);
s = malloc((1 + numwords) *sizeof(char *));
if (!s)
return (NULL);
for (i = 0, j = 0; j < numwords; j++)
{
while (delim(str[i], r))
i++;
k = 0;
while (!delim(str[i + k], r) && str[i + k])
k++;
s[j] = malloc((k + 1) * sizeof(char));
if (!s[j])
{
for (k = 0; k < j; k++)
free(s[k]);
free(s);
return (NULL);
}
for (m = 0; m < k; m++)
s[j][m] = str[i++];
s[j][m] = 0;
}
s[j] = NULL;
return (s);
}

/**
 * **strtw2 - splits a string into words
 * @str: the input string
 * @r: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtw2(char *str, char r)
{
int i, j, k, m, numwords = 0;
char **s;

if (str == NULL || str[0] == 0)
return (NULL);
for (i = 0; str[i] != '\0'; i++)
if ((str[i] != r && str[i + 1] == r) ||
(str[i] != r && !str[i + 1]) || str[i + 1] == r)
numwords++;
if (numwords == 0)
return (NULL);
s = malloc((1 + numwords) *sizeof(char *));
if (!s)
return (NULL);
for (i = 0, j = 0; j < numwords; j++)
{
while (str[i] == r && str[i] != r)
i++;
k = 0;
while (str[i + k] != r && str[i + k] && str[i + k] != r)
k++;
s[j] = malloc((k + 1) * sizeof(char));
if (!s[j])
{
for (k = 0; k < j; k++)
free(s[k]);
free(s);
return (NULL);
}
for (m = 0; m < k; m++)
s[j][m] = str[i++];
s[j][m] = 0;
}
s[j] = NULL;
return (s);
}

