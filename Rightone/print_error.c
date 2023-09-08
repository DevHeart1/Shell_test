#include "shell.h"

/**
 * _putchar - Prints a character to standard error
 * @c: Character to be printed
 * Return: An integer
 */

int _putchar(char c)
{
	return (write(2, &c, 1));
}


/**
 * _puts - prints a given string
 * @str: String to be printed
 * Return: Void
 */

void _puts(char *str)
{
	while (*str != '\0')
	{
		_putchar(*str);
		str++;
	}
}


/**
 * _error - Prints custom erro message to standard error
 * @prog: Program name
 * @count: Command count
 * @cmd: Command entered by user
 * Return: Void
 *
 */

void _error(char *prog, int count, char *cmd)
{
	_puts(prog);
	_puts(": ");
	_putchar(count);
	_puts(": ");
	_puts(cmd);
	_puts(": not found\n");
}

