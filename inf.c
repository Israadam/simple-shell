#include "shell.h"

/**
<<<<<<< HEAD
 * init_info - initializes info_t struct
 * @stadd: struct address
 */
void init_info(info_t *stadd)
=======
 * clr_info - initializes info_t struct
 * @info: struct address
 */
void clr_info(info_t *info)
>>>>>>> c05c887373f6021e6b6001093d9b9e183d1bf6f8
{
info->arg = NULL;
info->argv = NULL;
info->path = NULL;
info->argc = 0;
}


/**
 * frees_info - frees info_t struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */
void frees_info(info_t *info, int all)
{
ffree(info->argv);
info->argv = NULL;
info->path = NULL;
if (all)
{
if (!info->cmd_buf)
free(info->arg);
if (info->env)
free_list(&(info->env));
if (info->history)
free_list(&(info->history));
if (info->alias)
free_list(&(info->alias));
ffree(info->environ);
info->environ = NULL;
bfree((void **)info->cmd_buf);
if (info->readfd > 2)
close(info->readfd);
_putchar(BUF_FLUSH);
}
}
/**
 * itz_info - initializes info_t struct
 * @info: struct address
 * @av: argument vector
 */
void itz_info(info_t *info, char **av)
{
<<<<<<< HEAD
	int i = 0;
	stadd->fname = av[0];
	
	if (stadd->arg)
	{
		stadd->argv = strspt(stadd->arg, " \t");
		
		if (!stadd->argv)
		{
			stadd->argv = malloc(sizeof(char *) * 2);
			
			if (stadd->argv)
			{
				stadd->argv[0] = _strdup(stadd->arg);
				stadd->argv[1] = NULL;
			}
		}
		for (i = 0; stadd->argv && stadd->argv[i]; i++)
			;
		stadd->argc = i;
		replace_alias(stadd);
		replace_vars(stadd);
	}
}

/**
 * free_infor - frees info_t struct fields
 * @stadd: struct address
 * @all: true if freeing all fields
 */
void free_infor(info_t *stadd, int all)
{
	str_free(stadd->argv);
	stadd->argv = NULL;
	stadd->path = NULL;

	if (all)
	{
		if (!stadd->cmd_buf)
			free(stadd->arg);
		if (stadd->env)
			free_node(&(stadd->env));

		if (stadd->history)
			free_node(&(stadd->history));

		if (stadd->alias)
			free_node(&(stadd->alias));
		str_free(stadd->environ);
		stadd->environ = NULL;
		free_pointer((void **)stadd->cmd_buf);

		if (stadd->readfd > 2)
			close(stadd->readfd);
		_putchar(BUF_FLUSH);
	}
}
=======
int i = 0;
info->fname = av[0];
if (info->arg)
{
info->argv = strtow(info->arg, " \t");
if (!info->argv)
{
info->argv = malloc(sizeof(char *) * 2);
if (info->argv)
{
info->argv[0] = _strdup(info->arg);
info->argv[1] = NULL;
}
}
for (i = 0; info->argv && info->argv[i]; i++);
info->argc = i;
replace_alias(info);
replace_vars(info);
}
}

>>>>>>> c05c887373f6021e6b6001093d9b9e183d1bf6f8
