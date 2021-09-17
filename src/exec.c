#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#include "exec.h"

#define FORKED_CHILD 0

static void	exec_command(Node *node);

void	exec(Node *node)
{
	switch (node->type) {
		case COMMAND_NODE:
			exec_command(node);
			break;
		default:
			printf("TODO\n");
			break;
	}
}

static void	exec_command(Node *node)
{
	if (fork() == FORKED_CHILD) {
		// TODO
		char *argv[2] = {"ls", 0};
		execvp(argv[0], argv);
	}
	wait(NULL);
	return;
}