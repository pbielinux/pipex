/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbielik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 23:37:01 by pbielik           #+#    #+#             */
/*   Updated: 2021/09/20 23:37:02 by pbielik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_node	*parse_command(t_scanner *scanner);
static t_node	*parse_pipe(t_scanner *scanner, t_strvec *working_cmd);

t_node	*parse(t_scanner *scanner)
{
	t_token	pipe_token;
	t_token	fetched;

	if (!scanner_has_next(scanner))
		return (error_node_new("No more Readable Tokens!"));
	else if (scanner_peek(scanner).type == END_TOKEN)
		return (error_node_new("End Token Encountered!"));
	else if (scanner_peek(scanner).type == PIPE_TOKEN)
	{
		pipe_token = scanner_next(scanner);
		str_drop(&pipe_token.lexeme);
		while (scanner_has_next(scanner))
		{
			fetched = scanner_next(scanner);
			str_drop(&fetched.lexeme);
		}
		return (error_node_new("Unexpected Pipe Encountered!"));
	}
	else if (scanner_peek(scanner).type == WORD_TOKEN)
		return (parse_command(scanner));
	return (NULL);
}

static t_node	*parse_command(t_scanner *scanner)
{
	t_strvec	working_cmd;
	t_token		cmd;

	working_cmd = strvec_value(1);
	cmd = scanner_next(scanner);
	strvec_push(&working_cmd, cmd.lexeme);
	while (scanner_has_next(scanner))
	{
		if (scanner_peek(scanner).type == WORD_TOKEN)
		{
			cmd = scanner_next(scanner);
			strvec_push(&working_cmd, cmd.lexeme);
		}
		else if (scanner_peek(scanner).type == END_TOKEN)
			return (command_node_new(working_cmd));
		else if (scanner_peek(scanner).type == PIPE_TOKEN)
			return (parse_pipe(scanner, &working_cmd));
	}
	return (command_node_new(working_cmd));
}

static t_node	*parse_pipe(t_scanner *scanner, t_strvec *working_cmd)
{
	t_token	pipe_token;
	t_node	*left;
	t_node	*right;

	left = command_node_new(*working_cmd);
	pipe_token = scanner_next(scanner);
	str_drop(&pipe_token.lexeme);
	right = parse(scanner);
	return (pipe_node_new(left, right));
}
