#include "shell.h"

/**
 * _exitsh - exits the shell
 * @parg: Structure containing potential arguments. Used to maintain
 *constant function prototype.
 *Return: exits with a given exit status
 *(0) if info.argv[0] != "exit"
 */
int _exitsh(info_t *parg)
{
int exitcheck;

if (parg->argv[1])  /* If there is an exit arguement */
{
exitcheck = _erratoi(parg->argv[1]);
if (exitcheck == -1)
{
parg->status = 2;
print_error(parg, "Illegal number: ");
_puts(parg->argv[1]);
_putchar('\n');
return (1);
}
parg->err_num = _erratoi(parg->argv[1]);
return (-2);
}
parg->err_num = -1;
return (-2);
}


/**
 * _dirp - changes the current directory of the process
 * @parg: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 *  Return: Always 0
 */
int _dirp(info_t *parg)
{
char **arg_array;

arg_array = parg->argv;
_puts("help call works. Function not yet implemented \n");
if (0)
_puts(*arg_array); /* temp att_unused workaround */
return (0);
}

/**
 * _cd - changes the current directory of the process
 * @parg: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 *  Return: Always 0
 */
int _cd(info_t *parg)
{
char *s, *dir, buffer[1024];
int chdir_ret;

s = getcwd(buffer, 1024);
if (!s)
_puts("TODO: >>getcwd failure emsg here<<\n");
if (!parg->argv[1])
{
dir = _getenv(parg, "HOME=");
if (!dir)
chdir_ret = chdir((dir = _getenv(parg, "PWD=")) ? dir : "/");
else
chdir_ret = chdir(dir);
}
else if (_strcmp(parg->argv[1], "-") == 0)
{
if (!_getenv(parg, "OLDPWD="))
{
_puts(s);
_putchar('\n');
return (1);
}
_puts(_getenv(parg, "OLDPWD=")), _putchar('\n');
chdir_ret = chdir((dir = _getenv(parg, "OLDPWD=")) ? dir : "/");
}
else
chdir_ret = chdir(parg->argv[1]);
if (chdir_ret == -1)
{
print_error(parg, "can't cd to ");
_puts(parg->argv[1]), _eputchar('\n');
}
else
{
_setenv(parg, "OLDPWD", _getenv(parg, "PWD="));
_setenv(parg, "PWD", getcwd(buffer, 1024));
}
return (0);
}
