#include "shell.h"

/**
 * is_executable_file - Checks if a file is an executable command.
 * @info: The info struct.
 * @path: Path to the file.
 *
 * Return: 1 if it's an executable, 0 otherwise.
 */
int is_executable_file(info_t *info, char *path)
{
	struct stat st;

	if (!path || stat(path, &st) == -1)
	{
		perror("stat");
		return (0);
	}
	return (S_ISREG(st.st_mode) != 0);
}
/**
 * *find_command_in_path - Finds a command in the PATH string.
 * @info: The info struct.
 * @pathstr: The PATH string.
 * @cmd: The command to find.
 *
 * Return: Full path of the command if found, or NULL.
 */
char *find_command_in_path(info_t *info, char *pathstr, char *cmd)
{
	if (!pathstr)
		return (NULL);

	char *path = strtok(pathstr, ":");

	while (path != NULL)
	{
		char *full_path = malloc(strlen(path) + strlen(cmd) + 2);

		if (full_path == NULL)
		{
			perror("malloc");
			return (NULL);
		}
		sprintf(full_path, "%s/%s", path, cmd);

		if (is_executable_file(info, full_path))
			return (full_path);

		free(full_path);
		path = strtok(NULL, ":");
	}
	return (NULL);
}
