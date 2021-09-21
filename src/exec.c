/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbielik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 23:35:59 by pbielik           #+#    #+#             */
/*   Updated: 2021/09/20 23:36:01 by pbielik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

#include "exec.h"
#include "libft.h"

#define FORKED_CHILD 0

static int	exec_node(t_node *node, t_context *ctx, char **envp);
static int	exec_command(t_node *node, t_context *ctx, char **envp);
static int	exec_pipe(t_node *node, t_context *ctx, char **envp);
static char	*find_path(char *cmd, char **envp);

void	exec(t_node *node, int file_in, int file_out, char **envp)
{
	int			i;
	int			children;
	t_context	ctx;

	ctx.fd[0] = file_in;
	ctx.fd[1] = file_out;
	ctx.fd_close = -1;
	children = exec_node(node, &ctx, envp);
	i = 0;
	while (i++ < children)
		wait(NULL);
}

static int	exec_node(t_node *node, t_context *ctx, char **envp)
{
	if (node->type == COMMAND_NODE)
		return (exec_command(node, ctx, envp));
	else if (node->type == PIPE_NODE)
		return (exec_pipe(node, ctx, envp));
	else
		return (0);
}

static int	exec_command(t_node *node, t_context *ctx, char **envp)
{
	t_strvec	*words;
	char		**argv;
	size_t		i;

	if (fork() == FORKED_CHILD)
	{
		dup2(ctx->fd[STDIN_FILENO], STDIN_FILENO);
		dup2(ctx->fd[STDOUT_FILENO], STDOUT_FILENO);
		if (ctx->fd_close >= 0)
			close(ctx->fd_close);
		words = &node->data.command;
		argv = malloc(sizeof(t_strvec) * strvec_length(words) + 1);
		argv[strvec_length(words)] = NULL;
		i = 0;
		while (i < strvec_length(words))
		{
			argv[i] = str_ref(strvec_ref(words, i), 0);
			i++;
		}
		if (execve(find_path(argv[0], envp), argv, envp) == -1)
			exit (0);
		free(argv);
	}
	return (1);
}

static int	exec_pipe(t_node *node, t_context *ctx, char **envp)
{
	int			children_spawned;
	int			p[2];
	t_exec		cmd;

	pipe(p);
	children_spawned = 0;
	cmd.lhs = node->data.pipe.left;
	cmd.lhs_ctx = *ctx;
	cmd.lhs_ctx.fd[STDOUT_FILENO] = p[STDOUT_FILENO];
	cmd.lhs_ctx.fd_close = p[STDIN_FILENO];
	children_spawned += exec_node(cmd.lhs, &cmd.lhs_ctx, envp);
	cmd.rhs = node->data.pipe.right;
	cmd.rhs_ctx = *ctx;
	cmd.rhs_ctx.fd[STDIN_FILENO] = p[STDIN_FILENO];
	cmd.rhs_ctx.fd_close = p[STDOUT_FILENO];
	children_spawned += exec_node(cmd.rhs, &cmd.rhs_ctx, envp);
	close(p[STDIN_FILENO]);
	close(p[STDOUT_FILENO]);
	return (children_spawned);
}

static char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	int		i;
	char	*part_path;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
			return (path);
		i++;
	}
	return (0);
}
