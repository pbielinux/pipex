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

#define BUFF_SIZE 1025

/**
 * This program reads an input line from stdin and prints textual
 * representations of the tokens scanned from lines of input.
 */

t_node	*eval(t_str *input);
void	print(t_node *node, size_t indention);
int		open_file(char *argv, int i);

int	main(int argc, char **argv, char **envp)
{
	t_str		line;
	t_node		*parse_tree;
	int			i;

	line = str_value(BUFF_SIZE);
	i = 2;
	while (i < argc - 1)
	{
		str_append(&line, argv[i]);
		if (i < argc - 2)
			str_append(&line, " | ");
		i++;
	}
	parse_tree = eval(&line);
	exec(parse_tree, open_file(argv[1], 2), open_file(argv[argc - 1], 1), envp);
	node_drop(parse_tree);
	str_drop(&line);
	return (EXIT_SUCCESS);
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
	t_strvec	*words;

	i = 0;
	while (i++ < ident)
		putchar(' ');
	if (node->type == COMMAND_NODE)
	{
		i = 0;
		printf("COMMAND:");
		words = &node->data.command;
		while (i < strvec_length(words))
			printf(" %s", str_cstr(strvec_ref(words, i++)));
		putchar('\n');
	}
	else if (node->type == PIPE_NODE)
	{
		printf("PIPE:\n");
		print(node->data.pipe.left, ident + 4);
		print(node->data.pipe.right, ident + 4);
	}
	else
		printf("ERROR: %s\n", node->data.error);
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
	if (file == -1)
	{
		printf("ERROR!\n");
		exit(EXIT_FAILURE);
	}
	return (file);
}
