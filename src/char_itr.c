/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_itr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbielik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 23:35:43 by pbielik           #+#    #+#             */
/*   Updated: 2021/09/20 23:35:46 by pbielik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "char_itr.h"

t_char_itr	char_itr_value(const char *start, size_t length)
{
	t_char_itr	ci_val;

	ci_val.cursor = start;
	ci_val.sentinel = start + length;
	return (ci_val);
}

bool	char_itr_has_next(const t_char_itr *self)
{
	return (self->cursor < self->sentinel);
}

char	char_itr_peek(const t_char_itr *self)
{
	if (char_itr_has_next(self))
	{
		return (*self->cursor);
	}
	else
	{
		fprintf(stderr, "%s:%d - Out of Bounds", __FILE__, __LINE__);
		exit(EXIT_FAILURE);
	}
}

char	char_itr_next(t_char_itr *self)
{
	if (char_itr_has_next(self))
	{
		return (*self->cursor++);
	}
	else
	{
		fprintf(stderr, "%s:%d - Out of Bounds", __FILE__, __LINE__);
		exit(EXIT_FAILURE);
	}
}
