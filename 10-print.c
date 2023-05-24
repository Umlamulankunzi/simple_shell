#include "00-main.h"


/**
 * _putchar - writes the character c to stdout
 * @fd: File dsecriptor to write to
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(int fd, char c)
{
	return (write(fd, &c, 1));
}


/**
 * _puts - writes the string s to stdout
 * @fd: File dsecriptor to write to
 * @s: The string to print
 *
 * Return: On success the length of the string.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _puts(int fd, char *s)
{
	int count = 0;

	while (s[count])
		count++;

	return (write(fd, s, count));
}


/**
 * _putnbr - prints an integer
 * @fd: File dsecriptor to write to
 * @n: The integer to print
 *
 * Return: On success the number of digits printed.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putnbr(int fd, int n)
{
	int count = 0;

	if (n < 0)
	{
		count += _putchar(fd, '-');
		n = -n;
	}

	if (n / 10)
		count += _putnbr(fd, n / 10);

	count += _putchar(fd, n % 10 + '0');

	return (count);
}

/**
 * print - custom printf function that handles %s and %d specifiers
 * @fd: File dsecriptor to write to
 * @format: string containing format specifiers
 *
 * Return: number of characters printed
 */
int print(int fd, const char *format, ...)
{
	va_list args;
	int i = 0, count = 0;

	va_start(args, format);

	if (!format)
		return (-1);

	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			if (format[i] == 'c')
				count += _putchar(fd, va_arg(args, int));
			else if (format[i] == 's')
				count += _puts(fd, va_arg(args, char *));
			else if (format[i] == 'd')
				count += _putnbr(fd, va_arg(args, int));
			else
			{
				_putchar(fd, '%');
				if (format[i])
				{
					_putchar(fd, format[i]);
					count += 2;
				}
				else
					count++;
			}
		}
		else
		{
			_putchar(fd, format[i]);
			count++;
		}
		i++;
	}
	va_end(args);
	return (count);
}
