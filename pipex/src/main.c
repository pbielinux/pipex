#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libft.h"

#define BUFF_SIZE 80

/**
 * This program reads an input line from stdin and prints textual
 * representations of the tokens scanned from lines of input.
 */

int	main(int argc, char **argv, char **envp)
{
	if (argc == 5)
		ft_putchar_fd('!', 1);
	else
	{
		ft_putstr_fd("\033[31mError: Bad arguments\n\e[0m", 2);
		ft_putstr_fd("Ex: ./pipex <file1> <cmd1> <cmd2> file2\n", 1);
	}
}


