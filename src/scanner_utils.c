/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbielik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 23:37:13 by pbielik           #+#    #+#             */
/*   Updated: 2021/09/20 23:37:16 by pbielik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>

#include "scanner.h"

static t_str	build_word(t_scanner *self);

void	throw_useless_input(t_scanner *self)
{
	while (char_itr_has_next(&self->char_itr))
	{
		if ((char_itr_peek(&self->char_itr)) == '\t')
			char_itr_next(&self->char_itr);
		else if ((char_itr_peek(&self->char_itr)) == '\n')
			char_itr_next(&self->char_itr);
		else if ((char_itr_peek(&self->char_itr)) == ' ')
			char_itr_next(&self->char_itr);
		else
			break ;
	}
}

void	fill_next_pos(t_scanner *self)
{
	t_token	next;

	throw_useless_input(self);
	if (!char_itr_has_next(&self->char_itr))
	{
		next.type = END_TOKEN;
		self->next = next;
		return ;
	}
	if (char_itr_peek(&self->char_itr) == '|')
	{
		next.type = PIPE_TOKEN;
		next.lexeme = str_from("|");
		self->next = next;
		char_itr_next(&self->char_itr);
		return ;
	}
	next.type = WORD_TOKEN;
	next.lexeme = build_word(self);
	self->next = next;
}

static t_str	build_word(t_scanner *self)
{
	t_str		building_wrd;
	char		peeked_char;
	char		next_char;
	t_splice	splice;

	building_wrd = str_value(1025);
	while ((char_itr_has_next(&self->char_itr)))
	{
		if (((char_itr_peek(&self->char_itr)) == '|')
			| ((char_itr_peek(&self->char_itr)) == '\0'))
			break ;
		peeked_char = char_itr_peek(&self->char_itr);
		if (peeked_char == '\t' | peeked_char == '\n' | peeked_char == ' ')
			break ;
		next_char = char_itr_next(&self->char_itr);
		splice.index = str_length(&building_wrd);
		splice.delete_count = 0;
		splice.items = &next_char;
		splice.insert_count = 1;
		str_splice(&building_wrd, splice);
	}
	return (building_wrd);
}
