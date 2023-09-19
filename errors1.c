#include "shell.h"

/**
 * string_to_integer_err - converts a string to an integer with error handling
 * @s: the string to be converted
 * Return: the converted number on success, -1 on error
 */
int string_to_integer_err(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;

	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_shell_error - prints an error message related to the shell
 * @info: the parameter & return info struct
 * @error_message: string containing the error message
 */
void print_shell_error(info_t *info, char *error_message)
{
	_eputs(info->fname);
	_eputs(": ");
	print_line_number(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(error_message);
}

/**
 * print_line_number - prints a line number (decimal)
 * @line_number: the line number to print
 * @fd: the file descriptor to write to
 * Return: number of characters printed
 */
int print_line_number(int line_number, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int absolute_value, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (line_number < 0)
	{
		absolute_value = -line_number;
		__putchar('-');
		count++;
	}
	else
		absolute_value = line_number;
	current = absolute_value;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (absolute_value / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * convert_to_string - converts a number to a string
 * @num: the number to convert
 * @base: the base for conversion
 * @flags: argument flags
 * Return: a string representation of the number
 */
char *convert_to_string(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do {
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_first_comment - replaces the first '#' character with '\0'
 * @buf: address of the string to modify
 */
void remove_first_comment(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}
