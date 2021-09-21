/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_vec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbielik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 23:37:54 by pbielik           #+#    #+#             */
/*   Updated: 2021/09/20 23:37:55 by pbielik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str_vec.h"

t_strvec	strvec_value(size_t capacity)
{
	return (vec_value(capacity, sizeof(t_str)));
}

void	strvec_drop(t_strvec *self)
{
	t_str	to_drop;

	while (strvec_length(self) != 0)
	{
		to_drop = strvec_pop(self);
		str_drop(&to_drop);
	}
	vec_drop(self);
}

size_t	strvec_length(const t_strvec *self)
{
	return (vec_length(self));
}

t_str	*strvec_ref(const t_strvec *self, size_t index)
{
	return ((t_str *)(vec_ref(self, index)));
}

void	strvec_push(t_strvec *self, t_str value)
{
	vec_set(self, vec_length(self), &value);
}

t_str	strvec_pop(t_strvec *self)
{
	t_str	popped_str;

	popped_str = *((t_str *)(vec_ref(self, vec_length(self) - 1)));
	vec_splice(self, vec_length(self) - 1, 1, NULL, 0);
	return (popped_str);
}

void	strvec_set(t_strvec *self, size_t index, t_str value)
{
	t_str	old_str;

	if (index == vec_length(self))
	{
		vec_splice(self, vec_length(self), 0, &value, 1);
	}
	else
	{
		old_str = *((t_str *)(vec_ref(self, index)));
		vec_set(self, index, &value);
		str_drop(&old_str);
	}
}
