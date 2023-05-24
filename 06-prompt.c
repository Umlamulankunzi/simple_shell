#include "00-main.h"


/**
 * prompt - prints prompt to stdout
 *
 */
void prompt(void)
{
	print(STDOUT_FILENO, "$ ");
}
