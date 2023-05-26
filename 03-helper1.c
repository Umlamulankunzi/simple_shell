#include "00-main.h"

/**
 * _realloc - Reallocates a memory block using malloc and free.
 * @ptr: Pointer to the memory previously allocated.
 * @old_size: size of the allocated space for @ptr.
 * @new_size: size of the new memory block.
 *
 * Return: Pointer to the reallocated memory block.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *new_ptr, *old_ptr;
	unsigned int i;

	if (new_size == old_size)
		return (ptr);
	if (ptr == NULL)
	{
		new_ptr = malloc(new_size);
		if (new_ptr == NULL)
			return (NULL);
		return (new_ptr);
	}

	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}

	new_ptr = malloc(new_size);
	if (new_ptr == NULL)
		return (NULL);

	old_ptr = ptr;
	for (i = 0; i < old_size && i < new_size; i++)
	{
		new_ptr[i] = old_ptr[i];
	}

	free(ptr);
	return (new_ptr);
}

/**
 * _strtok - tokenizes string by breaking it up using a delimeter @delim
 * @str: string to tokenize
 * @delim: delimeter to use to tokenize string
 * Return: char * to tokenized string
 */
char *_strtok(char *str, const char *delim)
{
	/* keeps track of the string btwn function calls */
	static char *buffer;
	char *start = buffer;

	/* new string to tokenize, set buffer to the input string */
	if (str != NULL)
		buffer = str;

	if (buffer == NULL)
		return (NULL);

	/* skip over any leading delimiter characters */
	while (*buffer && _strchr(delim, *buffer))
		buffer++;

	/* if there are no more tokens, return NULL */
	if (!*buffer)
	{
		buffer = NULL;
		return (NULL);
	}

	/* find the end of the current token */
	start = buffer;
	while (*buffer && !_strchr(delim, *buffer))
		buffer++;

	/* if we've reached the end of the input string, set buffer to NULL */
	if (!*buffer)
		buffer = NULL;
	else
		*buffer++ = '\0';

	/* return the current token */
	return (start);
}

/**
 * _getline - reads input from @fd, storing input into @lineptr.
 * @lineptr: address of buffer to store input
 * @n: pointer to size of lineptr buffer
 * @fd: file descriptor to read from
 * Return: number of characters read if succcessful
 */
ssize_t _getline(char **lineptr, size_t *n, int fd)
{
	ssize_t i = 0, old_size = 0;
	int total = 0, j;
	char c, *buffer;

	if (*lineptr == NULL || *n == 0)
	{
		*n = INPUT_BUFFER_SIZE;
		*lineptr = malloc(*n * sizeof(char));
	}
	buffer = malloc(sizeof(char) * (*n));
	while ((total = read(fd, buffer, *n)) > 0)
	{
		for (j = 0; j < total; j++)
		{
			c = buffer[j];
			if (c == '\n')
			{
				free(buffer);
				(*lineptr)[i] = '\0';
				return (i);
			}
			if ((size_t)i == *n - 1)
			{
				old_size = *n;
				*n = 2 * (*n);
				*lineptr = _realloc(*lineptr, old_size, *n * sizeof(char));
			}
			(*lineptr)[i] = c;
			i++;
		}
	}
	if (total == 0 && i == 0)
	{
		free(buffer);
		return (-1);
	}
	(*lineptr)[i] = '\0';
	free(buffer);
	return (i);
}

/**
 * _strdup_ - duplicate string and return heap pointer to copy of str
 * @str: string
 * Return: char * to copy of string allocated in heap
 */
char *_strdup_(const char *str)
{
	size_t len;
	char *new_str;

	if (str == NULL)
		return (NULL);

	len = strlen(str) + 1; /* Include space for null terminator */
	new_str = (char *)malloc(len * sizeof(char));

	if (new_str == NULL)
		return (NULL); /* Error: unable to allocate memory */

	_strcpy(new_str, str);
	return (new_str);
}

/**
 * _strlen - Return the length of a string
 * @str: String to calculate length
 * Return: Length of the string
 **/
int _strlen(const char *str)
{
	int i;

	for (i = 0; str[i] != '\0'; i++)
		;
	return (i);
}
