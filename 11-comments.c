#include "00-main.h"

/**
 * remove_comment - searches for and sets # comment char in @buffer to \0
 * @buffer: string to search for comment char
 *
 */
void remove_comment(char *buffer)
{
	char *comment;

	comment = _strchr(buffer, COMMENT_CHAR);
	if (comment != NULL)
		*comment = '\0';

}
