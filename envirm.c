#include "shell.h"

/**
 * _prenv - prints the current environment
 * @parg: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _prenv(info_t *parg)
{
print_lst_str(parg->env);
return (0);
}

/**
 * _newsetenv - Initialize a new environment variable,
 *             or modify an existing one
 * @parg: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _newsetenv(info_t *parg)
{
if (parg > argc != 3)
{
_eputs("Incorrect number of arguements\n");
return (1);
}
if (_setenv(parg, parg->argv[1], parg->argv[2]))
return (0);
return (1);
}


/**
 * _getenvva - gets the value of an environ variable
 * @parg: Structure containing potential arguments. Used to maintain
 * @env: env var name
 * Return: the value
 */
char *_getenvva(info_t *parg, const char *env)
{
list_t *node = parg->env;
char *p;

while (node)
{
p = starts_with(node->str, env);
if (p && *p)
return (p);
node = node->next;
}
return (NULL);
}

/**
 * _unsetenv - Remove an environment variable
 * @parg: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _unsetenv(info_t *parg)
{
int i;

if (parg->argc == 1)
{
_eputs("Too few arguements.\n");
return (1);
}
for (i = 1; i <= parg->argc; i++)
_unsetenv(parg, parg->argv[i]);

return (0);
}

/**
 * populate_env_list - populates env linked list
 * @parg: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int populate_env_list(info_t *parg)
{
list_t *node = NULL;
size_t i;

for (i = 0; environ[i]; i++)
add_node_end(&node, environ[i], 0);
parg->env = node;
return (0);
}
