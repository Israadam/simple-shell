#include "shell.h"

/**
 * init_info - initializes info_t struct
 * @stadd: struct address
 */
void init_info(info_t *stadd)
{
	stadd->arg = NULL;
	stadd->argv = NULL;
	stadd->path = NULL;
	stadd->argc = 0;
}

/**
 * frees_info - frees info_t struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */
void free_infor(info_t *info, int all)
{
	free(info->argv);
	info->argv = NULL;
	info->path = NULL;
	
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		
		if (info->env)
			free_node(&(info->env));
		
		if (info->history)
			free_node(&(info->history));
		
		if (info->alias)
			free_node(&(info->alias));
		free(info->environ);
		info->environ = NULL;
		free_pointer((void **)info->cmd_buf);
		
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}
/**
 * str_info - initializes info_t struct
 * @stadd: struct address
 * @av: argument vector
 */
void str_info(info_t *stadd, char **av)
{
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
