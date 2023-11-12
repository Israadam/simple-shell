#include "shell.h"

/**
 * shll - main shell loop
 * @info: the parameter & return info struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
<<<<<<< HEAD:sh_loop.c
int shll(info_t *info, char **avm)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		init_info(info);
		
		if (inter(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		r = set_input(info);
		if (r != -1)
		{
			str_info(info, avm);
			builtin_ret = check_builtin(info);
			
			if (builtin_ret == -1)
				find_command(info);
		}
		else if (inter(info))
			_putchar('\n');
		free_infor(info, 0);
	}
	wrt_history(info);
	free_infor(info, 1);
	
	if (!inter(info) && info->status)
		exit(info->status);
	
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
=======
int shll(info_t *info, char **av)
{
ssize_t r = 0;
int builtin_ret = 0;

while (r != -1 && builtin_ret != -2)
{
clear_info(info);
if (interactive(info))
_puts("$ ");
_eputchar(BUF_FLUSH);
r = get_input(info);
if (r != -1)
{
set_info(info, av);
builtin_ret = find_builtin(info);
if (builtin_ret == -1)
find_cmd(info);
}
else if (interactive(info))
_putchar('\n');
free_info(info, 0);
}
write_history(info);
free_info(info, 1);
if (!interactive(info) && info->status)
exit(info->status);
if (builtin_ret == -2)
{
if (info->err_num == -1)
exit(info->status);
exit(info->err_num);
}
return (builtin_ret);
>>>>>>> c05c887373f6021e6b6001093d9b9e183d1bf6f8:shloop.c
}

/**
 * find_builtin - finds a builtin command
 * @info: the parameter & return info struct
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int find_builtin(info_t *info)
{
<<<<<<< HEAD:sh_loop.c
	int i, built_ret = -1;
	builtin_table b[] = {
		{"exit", _exitsh},
		{"env", _prenv},
		{"help", _dirp},
		{"history", _histlst},
		{"setenv", _newsetenv},
		{"unsetenv", _unsetenv},
		{"cd", _cd},
		{"alias",_my_alias},
		{NULL, NULL}
	};
	
	for (i = 0; b[i].type; i++)
		if (_strcmp(info->argv[0], b[i].type) == 0)
		{
			info->line_count++;
			built_ret = b[i].func(info);
			break;
		}
	return (built_ret);
=======
int i, built_in_ret = -1;
builtin_table builtintbl[] = {
{"exit", _myexit},
{"env", _myenv},
{"help", _myhelp},
{"history", _myhistory},
{"setenv", _mysetenv},
{"unsetenv", _myunsetenv},
{"cd", _mycd},
{"alias", _myalias},
{NULL, NULL}
};

for (i = 0; builtintbl[i].type; i++)
if (_strcmp(info->argv[0], builtintbl[i].type) == 0)
{
info->line_count++;
built_in_ret = builtintbl[i].func(info);
break;
}
return (built_in_ret);
>>>>>>> c05c887373f6021e6b6001093d9b9e183d1bf6f8:shloop.c
}

/**
 * fork_cmdd - forks a an exec thread to run cmd
 * @info: the parameter & return info struct
 * Return: void
 */
void fork_cmdd(info_t *info)
{
<<<<<<< HEAD:sh_loop.c
	pid_t child_pid;
	child_pid = fork();
	
	if (child_pid == -1)
	{

		perror("Error:");
		return;
	}
	if (child_pid == 0)

	{
		if (execve(info->path, info->argv, set_environ(info)) == -1)
		{
			free_infor(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}

	}
	else
	{
		wait(&(info->status));
		
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				_error(info, "Permission denied\n");
		}
=======
pid_t child_pid;
child_pid = fork();
if (child_pid == -1)
{
/* TODO: PUT ERROR FUNCTION */
perror("Error:");
return;
}
if (child_pid == 0)
{
if (execve(info->path, info->argv, get_environ(info)) == -1)
{
free_info(info, 1);
if (errno == EACCES)
exit(126);
exit(1);
}
/* TODO: PUT ERROR FUNCTION */
}
else
{
wait(&(info->status));
if (WIFEXITED(info->status))
{
info->status = WEXITSTATUS(info->status);
if (info->status == 126)
print_error(info, "Permission denied\n");
}
}
}

>>>>>>> c05c887373f6021e6b6001093d9b9e183d1bf6f8:shloop.c

	}

}
/**
 * find_command - finds a command in PATH
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void find_command(info_t *info)
{
<<<<<<< HEAD:sh_loop.c
	char *path = NULL;
	int i, k;
	info->path = info->argv[0];
	
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!delim(info->arg[i], " \t\n"))
			k++;
	
	if (!k)
		return;
	path = path_str(info, get_env(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_command(info);
	}
	else
	{
		if ((inter(info) || get_env(info, "PATH=")
					|| info->argv[0][0] == '/') && _cmd(info, info->argv[0]))
			fork_command(info);
		
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			_error(info, "not found\n");
		}
	}
}
=======
char *path = NULL;
int i, k;
info->path = info->argv[0];
if (info->linecount_flag == 1)
{
info->line_count++;
info->linecount_flag = 0;
}
for (i = 0, k = 0; info->arg[i]; i++)
if (!is_delim(info->arg[i], " \t\n"))
k++;
if (!k)
return;
path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
if (path)
{
info->path = path;
fork_cmd(info);
}
else
{
if ((interactive(info) || _getenv(info, "PATH=")
|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
fork_cmd(info);
else if (*(info->arg) != '\n')
{
info->status = 127;
print_error(info, "not found\n");
}
}
}

>>>>>>> c05c887373f6021e6b6001093d9b9e183d1bf6f8:shloop.c
