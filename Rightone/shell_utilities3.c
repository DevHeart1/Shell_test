#include "shell.h"

/**
 * _isdigit -  checks for a digit (0 through 9)
 *
 * @c: character to check
 *
 * Return: 1 if c is uppercase or 0 otherwise
 */

int _isdigit(int c)
{
	if (c >= '0' && c <= '9')
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

/**
 * _atoi - Convert a string to an integer.
 *
 * @s: The pointer to convert
 *
 * Return: A integer
 */
int _atoi(char *s)
{
	int c = 0;
	unsigned int i = 0;
	int min = 1;
	int j = 0;

	while (s[c])
	{
		if (s[c] == '-')
			min *= -1;

		while (s[c] >= '0' && s[c] <= '9')
		{
			j = 1;
			i = (i * 10) + (s[c] - '0');
			c++;
		}

		if (j == 1)
		{
			break;
		}
		c++;
	}

	i *= min;
	return (i);
}

/**
 * illegal_status - Prints an "illegal status" error message.
 * @argv: The argument causing the illegal status.
 * @command_num: The command number.
 * @status: Exit status
 */
void illegal_status(char *argv, int command_num, char *status)
{
	char *shell_name;

	(void)argv;

	shell_name = _getenv("_");
	write(STDERR_FILENO, shell_name, _strlen(shell_name));
	if (!shell_name)
		free(shell_name);

	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, int_convert_string(command_num),
			_strlen(int_convert_string(command_num)));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, "exit: Illegal number", 20);
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, status, _strlen(status));
	write(STDERR_FILENO, "\n", 1);
}

/**
 * int_convert_string - Convert an integer to a string.
 * @number: The integer to convert.
 * Return: The string representation of the integer, or NULL if failed.
 */
char *int_convert_string(int number)
{
	int num_digits, place_value, index = 0, is_negative = 0, x;
	char *result;

	num_digits = number;
	place_value = 1;
	if (number < 0)
		is_negative = 1;
	result = malloc(sizeof(char) * (abs(num_digits) + 2 + is_negative));
	if (result == NULL)
		return (NULL);
	if (is_negative)
	{
		result[index] = '-';
		index++;
	}
	for (x = 0; num_digits > 9 || num_digits < -9; x++)
	{
		num_digits /= 10;
		place_value *= 10;
	}
	num_digits = number;
	for (; x >= 0; x--)
	{
		if (num_digits < 0)
		{
			result[index] = (num_digits / place_value) * -1 + '0';
			index++;
		}
		else
		{
			result[index] = (num_digits / place_value) + '0';
			index++;
		}
		num_digits %= place_value;
		place_value /= 10;
	}
	result[index] = '\0';
	return (result);
}
