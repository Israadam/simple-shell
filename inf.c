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
