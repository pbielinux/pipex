#include "pipex.h"
#include "core_utils.h"

typedef enum	perms
{
	RW_APPEND	= 0,
	RW_TRUNC	= 1,
	R_ONLY		= 2
}				perms;

int	open_fd(char *file, int perms)
{
	int	fd;

	if (perms == RW_APPEND)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 777);
	else if (perms == RW_TRUNC)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 777);
	else if (perms == R_ONLY)
		fd = open(file, O_RDONLY, 777);
	if (fd == -1)
		exitOnError ("Error opening file", __FILE__, __LINE__);
	return (fd);
}

void	child_process(char **argv, char **envp, int *p)
{
	int		input_file;
	int		p[2];


	if (p() == -1)
		exitOnError("Pipe error!", __FILE__, __LINE__);

	input_file = open_fd(argv[1],);
	if (input_file == -1)
		exitOnError("Error opening input file", __FILE__, __LINE__);
	dup2(pipe[STDOUT_FILENO], STDOUT_FILENO);
	dup2(input_file, STDIN_FILENO);
	close(pipe[STDOUT_FILENO]);
	execute(argv[2], envp);
}


void	ft_pipex(int argc, char **argv, char **envp)
{
	int first;
	int	child_pid;

	if (pipe(p) == -1)
		exitOnError("Pipe error!", __FILE__, __LINE__);
	child_pid = fork();
	if (child_pid == -1)
		exitOnError("Fork failed", __FILE__, __LINE__);
	if (child_pid == 0)
		child_process(argv, envp, p);
	waitpid(child_pid, NULL, 0);
	parent_process(argv, envp);
	close(p[STDIN_FILENO]);
	close(p[STDIN_FILENO]);
}