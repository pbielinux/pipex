#ifndef PIPEX_H
# define PIPEX_H

#include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>

#include "libft.h"

typedef struct	s_context
{
	int	fd[2];		// For stdin/stdout
	int	fd_close;	// Close an fd? -1 if not
}				t_context;

void	ft_pipex(int argc, char **argv, char **envp);

#endif // !PIPEX_H