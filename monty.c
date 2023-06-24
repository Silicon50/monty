#include "monty.h"

/**
 * init_monty - initialise global (monty) variable
 */
void init_monty(void)
{
	monty.arg = NULL;
	monty.ln = 0;
	monty.stack = NULL;
}

/**
 * check_args - opens byte code file
 * @ac: argument cound
 * @av: argument vector
 * Return: file pointer to byte code
 */
FILE *check_args(int ac, char **av)
{
	FILE *fp;

	if (ac != 2)
	{
		dprintf(STDERR_FILENO, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}

	fp = fopen(av[1], "r");
	if (!fp)
	{
		dprintf(STDERR_FILENO, "Error: Can't open file %s\n", av[1]);
		exit(EXIT_FAILURE);
	}

	return (fp);
}

/**
 * main - runs a bytecode
 *
 * @ac: (int) argument count
 * @av: (char **) argument vector
 * Return: 0 on success
 */
int main(int ac, char **av)
{
	FILE *fp;
	char *lineptr = NULL, *opcode;
	const char DELIM[3] = " \t\n";
	size_t n = 0;
	ssize_t flag;
	void (*func)(stack_t **, unsigned int);

	fp = check_args(ac, av);

	while ((flag = getline(&lineptr, &n, fp) != -1))
	{
		monty.ln++;
		opcode = strtok(lineptr, DELIM);
		if (opcode)
		{
			func = get_ops(opcode);
			if (!func)
			{
				dprintf(2, "L%d: unknown instruction %s\n", monty.ln, opcode);
				exit(EXIT_FAILURE);
			}
			monty.arg = strtok(NULL, DELIM);
			func(&monty.stack, monty.ln);
		}
	}
	free(lineptr);
	fclose(fp);
	return (0);
}
