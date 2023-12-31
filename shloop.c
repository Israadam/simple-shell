#include "shell.h"
/**
 * check_builtin - finds a builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *0 if builtin executed successfully,
 *1 if builtin found but not successful,
 *-2 if builtin signals exit()
 */
int check_builtin(info_t *info)
{
int i, built_in_ret = -1;
builtin_table builtintbl[] = {
{"exit", _exitsh},
{"env", _prenv},
{"help", _currentdr},
{"history", _histlst},
{"setenv", _newsetenv},
{"unsetenv", _unsetenv},
{"cd", _ccd},
{"alias", _my_alias},
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
}
/**
 * shll - main shell loop
 * @info: the parameter & return info struct
 * @av: the argument vector from main()
 * Return: 0 on success, 1 on error, or error code
 */
int shll(info_t *info, char **av)
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
str_info(info, av);
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
}



/**
 * fork_command - forks a an exec thread to run cmd
 * @info: the parameter & return info struct
 * Return: void
 */
void fork_command(info_t *info)
{
pid_t child_pid;

child_pid = fork();
if (child_pid == -1)
{

perror("Error:");
return;
}
if (child_pid == 0)
{
if (execve(info->path, info->argv, set_env(info)) == -1)
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
}
}
/**
 * find_command - finds a command in PATH
 * @info: the parameter & return info struct
 * Return: void
 */
void find_command(info_t *info)
{
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
