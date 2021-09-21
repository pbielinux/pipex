/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbielik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 23:37:13 by pbielik           #+#    #+#             */
/*   Updated: 2021/09/20 23:37:16 by pbielik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>

#include "scanner.h"

t_scanner	scanner_value(t_char_itr char_itr)
{
	t_token		next;
	t_scanner	itr;

	next.type = END_TOKEN;
	next.lexeme = str_from("");
	itr.char_itr = char_itr;
	itr.next = next;
	fill_next_pos(&itr);
	str_drop(&next.lexeme);
	return (itr);
}

bool	scanner_has_next(const t_scanner *self)
{
	if (self->next.type == END_TOKEN)
		return (false);
	else
		return (true);
}

t_token	scanner_peek(const t_scanner *self)
{	
	return (self->next);
}

t_token	scanner_next(t_scanner *self)
{
	t_token	to_give;

	to_give = scanner_peek(self);
	fill_next_pos(self);
	return (to_give);
}
