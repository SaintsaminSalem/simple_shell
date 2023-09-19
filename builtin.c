#include "shell.h"

/**
 * _theexit - exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Exits with a given exit status
 *         (0) if info->argv[0] != "exit"
 */
int _theexit(info_t *info)
{
	int exitcheck;

	if (info->argv[1])
	{
		exitcheck = _erratoi(info->argv[1]);
		if (exitcheck == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _thecd - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int _thecd(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s && (_puts("getcwd failure: "), perror(""), 1))
		return (1);
	dir = (info->argv[1]) ? info->argv[1] : _getenv(info, "HOME=");
	if (!dir)
		dir = _getenv(info, "PWD=") ?: "/";
	if (_strcmp(info->argv[1], "-") == 0)
		dir = _getenv(info, "OLDPWD=") ?: s;

	chdir_ret = chdir(dir);
	if (chdir_ret == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]);
		_eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _thehelp - displays help message
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int _thehelp(info_t *info)
{
	char **arg_array = info->argv;

	_puts("Help message: This is a simple shell.\n");
	return (0);
}
