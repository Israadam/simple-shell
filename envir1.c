#include "shell.h"

/**
 * _prenv - prints the current environment
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _prenv(info_t *info)
{
print_str(info->env);
return (0);
}

/**
 * populate_env - populates env linked list
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int populate_env(info_t *info)
{
list_t *node = NULL;
size_t i;

for (i = 0; environ[i]; i++)
end_list(&node, environ[i], 0);
info->env = node;
return (0);
}

/**
 * _getvarenv - gets the value of an environ variable
 * @info: Structure containing potential arguments. Used to maintain
 * @namevr: env var name
 * Return: the value
 */
char *_getvarenv(info_t *info, const char *namevr)
{
list_t *node = info->env;
char *p;

while (node)
{
p = start_with(node->str, namevr);
if (p && *p)
return (p);
node = node->next;
}
return (NULL);
}

/**
 * _newsetenv - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _newsetenv(info_t *info)
{
if (info->argc != 3)
{
_eputs("Incorrect number of arguements\n");
return (1);
}
if (_nwsenv(info, info->argv[1], info->argv[2]))
return (0);
return (1);
}

/**
 * _rmunsetenv - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _rmunsetenv(info_t *info)
{
int i;

if (info->argc == 1)
{
_eputs("Too few arguements.\n");
return (1);
}
for (i = 1; i <= info->argc; i++)
_rmenv(info, info->argv[i]);
return (0);
}
