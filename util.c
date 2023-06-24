#include "monty.h"
#include <ctype.h>

/**
 * _isdigit - checks if string is a number
 * @str: (char *) string
 * Return: 1 if string is a number, otherwise -1
*/
int _isdigit(char *str)
{
	int i = 0;

	while (str[i])
	{
		if (!(isdigit(str[i])))
			return (-1);
		i++;
	}
	return (1);
}
