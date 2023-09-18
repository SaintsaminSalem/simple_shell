#include "shell.h"

/**
 * copy_string - Copies a string.
 * @destination: The destination string to be copied to.
 * @source: The source string.
 * @n: The number of characters to be copied.
 *
 * Return: The concatenated string.
 */
char *copy_string(char *destination, char *source, int n)
{
	int i, j;
	char *result = destination;

	i = 0;
	while (source[i] != '\0' && i < n - 1)
	{
		destination[i] = source[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			destination[j] = '\0';
			j++;
		}
	}
	return (result);
}
/**
 * concatenate_string - Concatenates two strings.
 * @destination: The first string.
 * @source: The second string.
 * @n: The maximum number of bytes to be used.
 *
 * Return: The concatenated string.
 */
char *concatenate_string(char *destination, char *source, int n)
{
	int i, j;
	char *result = destination;

	i = 0;
	j = 0;

	while (destination[i] != '\0')
		i++;
	while (source[j] != '\0' && j < n)
	{
		destination[i] = source[j];
		i++;
		j++;
	}
	if (j < n)
		destination[i] = '\0';
	return (result);
}

/**
 * find_character - Locates a character in a string.
 * @str: The string to be parsed.
 * @c: The character to look for.
 *
 * Return: A pointer to the memory area str.
 */
char *find_character(char *str, char c)
{
	do {
		if (*str == c)
			return (str);
	} while (*str++ != '\0');

	return (NULL);
}
