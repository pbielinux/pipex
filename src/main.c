/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbielik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 23:36:32 by pbielik           #+#    #+#             */
/*   Updated: 2021/09/20 23:36:34 by pbielik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#include "libft.h"
#include "node.h"
#include "scanner.h"
#include "exec.h"
#include "char_itr.h"
#include "parser.h"

#define BUFF_SIZE 1024

t_node		*eval(t_str *input);
void		print(t_node *node, size_t indention);
int			open_file(char *argv, int i);
static int	print_usage(void);

int	main(int argc, char **argv, char **envp)
{
	t_str		line;
	t_node		*parse_tree;
	int			i;

	if (argc >= 5)
	{
		line = str_value(BUFF_SIZE);
		i = 2;
		while (i < argc - 1)
		{
			str_append(&line, argv[i]);
			if (i++ < argc - 2)
				str_append(&line, " | ");
		}
		parse_tree = eval(&line);
		exec(parse_tree, open_file(argv[1], 2),
			open_file(argv[argc - 1], 1), envp);
		node_drop(parse_tree);
		str_drop(&line);
		return (EXIT_SUCCESS);
	}
	else
		return (print_usage());
}

t_node	*eval(t_str *line)
{
	t_scanner	scanner;

	scanner = scanner_value(char_itr_of_str(line));
	return (parse(&scanner));
}

void	print(t_node *node, size_t ident)
{
	size_t		i;

	i = 0;
	while (i++ < ident)
		ft_putchar(' ');
	if (node->type == COMMAND_NODE)
	{
		i = 0;
		ft_putstr("COMMAND:");
		while (i < strvec_length(&node->data.command))
		{
			ft_putchar(' ');
			ft_putstr(str_cstr(strvec_ref(&node->data.command, i++)));
		}
		ft_putchar('\n');
	}
	else if (node->type == PIPE_NODE)
	{
		ft_putstr("PIPE:\n");
		print(node->data.pipe.left, ident + 4);
		print(node->data.pipe.right, ident + 4);
	}
	else
		ft_putstr("ERROR: \n");
}

int	open_file(char *argv, int i)
{
	int	file;

	file = 0;
	if (i == 0)
		file = open(argv, O_CREAT | O_APPEND | O_WRONLY, 0644);
	else if (i == 1)
		file = open(argv, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	else if (i == 2)
		file = open(argv, O_RDONLY, 0);
	return (file);
}

static int	print_usage(void)
{
	ft_putstr_fd("\033[31mError: Bad argument\n\e[0m", 2);
	ft_putstr_fd("Ex: ./pipex <file1> <cmd1> <cmd2> <cmd...> <file2>\n", 1);
	return (EXIT_SUCCESS);
}
