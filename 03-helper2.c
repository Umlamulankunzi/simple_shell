#include "00-main.h"


/**
 * _strcat - Concatenates @dest and @src strings
 * @dest: string to append the src string
 * @src: string to append to @dest
 * Return: pointer to @dest
 */
char *_strcat(char *dest, const char *src)
{
	int len_dest, count;

	len_dest = _strlen(dest);

	for (count = 0; src[count] != '\0'; count++, len_dest++)
		dest[len_dest] = src[count];

	dest[len_dest] = '\0';
	return (dest);
}


/**
* _strcmp - compares two strings if they are equal or not
* @str1: first string
* @str2: second string
* Return: 0 if @str1 equal to @str2, Else negative or positive int
*/
int _strcmp(char *str1, char *str2)
{
	int count = 0;

	while (str1[count] && (str1[count] == str2[count]))
		count++;

	return (str1[count] - str2[count]);
}


/**
 * _strcpy - Copy a string @src to @dest
 * @dest: Destination to store @src
 * @src: Source string
 * Return: pointer to @dest
 */
char *_strcpy(char *dest, const char *src)
{
	int i;

	for (i = 0; src[i] != '\0'; i++)
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}


/**
 * _strchr - searches for a character @ch in string @str
 * @str: string
 * @ch: ascii value of char to search for
 * Return: char pointer to first occurrence of char Else NULL if not found
 */
char *_strchr(const char *str, int ch)
{
	if (str == NULL)
	{
		return (NULL);
	}

	/* Loop through the string until the end or until the character is found */
	while (*str != '\0')
	{
		/* Check if the character matches */
		if (*str == ch)
		{
			/* Return a pointer to the first occurrence of the char */
			return ((char *)str);
		}
		str++;
	}

	return (NULL);
}


/**
* _atoi - converts ascii to integer
* @str: string to convert
* Return: int
*/
int _atoi(const char *str)
{
	int result = 0;
	int digit, sign = 1;

	/* Handle leading whitespace */
	while (*str == ' ' || *str == '\t')
		str++;

	/* Handle sign */
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
	{
		sign = 1;
		str++;
	}

	while (*str >= '0' && *str <= '9')
	{
		digit = *str - '0';
		result = result * 10 + digit;
		str++;
	}

	return (sign * result);
}
