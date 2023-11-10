#include "shell.h"

/**
 * set_envir - returns the string array copy of our environ
 * @parg: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **set_envir(info_t *parg)
{
if (!parg->environ || parg->env_changed)
{
parg->environ = list_to_strings(parg->env);
parg->env_changed = 0;
}
return (parg->envir);
}


/**
 * _rmenv - Remove an environment variable
 * @parg:Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int _rmenv(info_t *parg, char *var)
{
list_t *node = parg->env;
size_t i = 0;
char *p;

if (!node || !var)
return (0);

while (node)
{
p = starts_with(node->str, var);
if (p && *p == '=')
{
parg->env_changed = delete_node_at_index(&(parg->env), i);
i = 0;
node = parg->env;
continue;
}
node = node->next;
i++;
}
return (parg->env_changed);
}

/**
 * _nwsenv - Initialize a new environment variable,
 *             or modify an existing one
 * @parg: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 *  Return: Always 0
 */
int _nwsenv(info_t *parg, char *var, char *value)
{
char *buf = NULL;
list_t *node;
char *p;

if (!var || !value)
return (0);

buf = malloc(_strlen(var) + _strlen(value) + 2);
if (!buf)
return (1);
_strcpy(buf, var);
_strcat(buf, "=");
_strcat(buf, value);
node = parg->env;
while (node)
{
p = starts_with(node->str, var);
if (p && *p == '=')
{
free(node->str);
node->str = buf;
parg->env_changed = 1;
return (0);
}
node = node->next;
}
add_node_end(&(parg->env), buf, 0);
free(buf);
parg->env_changed = 1;
return (0);
}
