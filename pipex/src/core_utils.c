#include <execinfo.h>
#include <stdio.h>
#include <stdlib.h>

#include "core_utils.h"
#include "libft.h"

void exitOnError(char *msg, char *file, unsigned line)
{
	ft_putstr_fd( file, stderr);
	ft_putchar_fd( ':', stderr);
	ft_putnbr_fd( line, stderr);
	ft_putchar_fd( ' ', stderr);
	ft_putstr_fd( msg, stderr);
	print_stacktrace();
	exit(EXIT_FAILURE);
}

void print_stacktrace()
{
	int		i;
	void	*array[16];
	int		stack_num;
	char	**stacktrace;

	stack_num = backtrace(array, 16);
	stacktrace = backtrace_symbols(array, stack_num);
	while ( i < stack_num)
	{
		ft_putstr_fd(stacktrace[i], stderr);
		i++;
	}
	free(stacktrace);
}