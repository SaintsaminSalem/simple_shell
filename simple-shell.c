#include <stdio.h>

/**
 * main - Entry point of the program
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
	int age = 30;
	char gender = 'M';

	if (age >= 18)
	{
		if (gender == 'M')
		{
			printf("Welcome, sir! You are an adult male.\n");
		}
		else
		{
			printf("Welcome, ma'am! You are an adult female.\n");
		}
	}
	else
	{
		printf("Sorry, you are not an adult yet.\n");
	}
	return (0);
}
