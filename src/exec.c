#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
# include <fcntl.h>

#include "exec.h"

#define FORKED_CHILD 0

typedef struct	Context
{
	int	fd[2];		// For stdin/stdout
	int	fd_close;	// Close an fd? -1 if not
}				Context;


static int	exec_node(Node *node, Context *ctx);
static int	exec_command(Node *node, Context *ctx);
static int	exec_pipe(Node *node, Context *ctx);


void	exec(Node *node, int file_in, int file_out)
{
	int	children;
	Context	ctx = {
		{
			file_in,
			file_out
		},
		-1
	};
	children = exec_node(node, &ctx);
	for (int i = 0; i < children; i++)
		wait(NULL);
}

static int	exec_node(Node *node, Context *ctx)
{
	if (node->type == COMMAND_NODE)
		return exec_command(node, ctx);
	else if (node->type == PIPE_NODE)
		return exec_pipe(node, ctx);
	else {
		printf("TODO\n");
		return (0);
	}
}

static int	exec_command(Node *node, Context *ctx)
{
	int execSuccessVal = 1;
	StrVec	*words;
	char	**argv;
	size_t	argc;
	size_t	i;

	if (fork() == FORKED_CHILD)
	{
		// Evaluate the context
		// Establish the child's fd table
		dup2(ctx->fd[STDIN_FILENO], STDIN_FILENO); /* Redirect STDIN */
		dup2(ctx->fd[STDOUT_FILENO], STDOUT_FILENO); /* Redirect STDOUT */
		/* If applicable, close the FD passed by context */
		if (ctx->fd_close >= 0)
			close(ctx->fd_close);

		words = &node->data.command;
		argc = StrVec_length(words);
		argv = malloc(sizeof(StrVec) * argc + 1);
		argv[argc] = NULL; /* Make last character NULL */

		i = 0;
		while (i < argc)
		{
			argv[i] = Str_ref(StrVec_ref(words, i), 0);
			i++;
		}

		if (execvp(argv[0], argv) == -1)
		{
			execSuccessVal = 0;
			exit (0);
		}
		free(argv);
	}
	return (execSuccessVal); // One child was spawned;
}

static int	exec_pipe(Node *node, Context *ctx)
{
	int	childrenSpawned = 0;
	// TODO: Establish Pipe
	int p[2];
	pipe(p);	// p_read	p[0];
				// p_write	p[1];

	/* Create context for LHS */
	Node	*lhs = node->data.pipe.left;
	Context	lhs_ctx = *ctx;
	lhs_ctx.fd[STDOUT_FILENO] = p[STDOUT_FILENO]; /* Redirect STDOUT */
	lhs_ctx.fd_close = p[STDIN_FILENO]; /* Close pipe in since LHS doesn't need it */
	childrenSpawned += exec_node(lhs, &lhs_ctx);

	/* Create Context for RHS */
	Node	*rhs = node->data.pipe.right;
	Context	rhs_ctx = *ctx;
	rhs_ctx.fd[STDIN_FILENO] = p[STDIN_FILENO]; /* Redirect STDIN */
	rhs_ctx.fd_close = p[STDOUT_FILENO]; /* Close pipe out since RHS doesn't need it */
	childrenSpawned += exec_node(rhs, &rhs_ctx);

	// Need to close both of parents pipe ends;
	close(p[STDIN_FILENO]);
	close(p[STDOUT_FILENO]);

	return childrenSpawned;
}