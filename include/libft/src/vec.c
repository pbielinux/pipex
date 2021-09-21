/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbielik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 23:38:18 by pbielik           #+#    #+#             */
/*   Updated: 2021/09/20 23:38:20 by pbielik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include	"guards.h"
#include	"vec.h"
#include	"stacktrace.h"

static void	ensure_capacity(t_vec *self, size_t n);
static void	exit_on_error(unsigned int line);

t_vec	vec_value(size_t capacity, size_t item_size)
{
	t_vec	vec;

	vec.item_size = item_size;
	vec.length = 0;
	vec.capacity = capacity;
	vec.buffer = calloc(capacity, item_size);
	omm_guard(vec.buffer, __FILE__, __LINE__);
	return (vec);
}

void	vec_drop(t_vec *self)
{
	free(self->buffer);
	self->buffer = NULL;
	self->capacity = 0;
	self->length = 0;
}

size_t	vec_length(const t_vec *self)
{
	return (self->length);
}

const void	*vec_items(const t_vec *self)
{
	return (self->buffer);
}

bool	vec_equals(const t_vec *self, const t_vec *other)
{
	int		current_pos;
	char	*self_char;
	char	*other_char;

	if (self->length != other->length)
		return (false);
	current_pos = 0;
	while (current_pos < (self->length * self->item_size))
	{
		self_char = (char *)(self->buffer) + current_pos;
		other_char = (char *)(other->buffer) + current_pos;
		if (*self_char != *other_char)
			return (false);
		current_pos++;
	}
	return (true);
}

void	*vec_ref(const t_vec *self, size_t index)
{
	if (index < self->length)
		return (self->buffer + (index * self->item_size));
	else
	{
		print_stacktrace();
		exit_on_error(__LINE__);
	}
	return (NULL);
}

void	vec_get(const t_vec *self, size_t index, void *out)
{
	if (index < self->length)
		memcpy(out, vec_ref(self, index), self->item_size);
	else
	{
		print_stacktrace();
		exit_on_error(__LINE__);
	}
}

void	vec_set(t_vec *self, size_t index, const void *value)
{
	if (index == self->length)
		vec_splice(self, index, 0, value, 1);
	else
		vec_splice(self, index, 1, value, 1);
}

void	vec_splice(t_vec *self, size_t index, size_t delete_count,
		const void *items, size_t insert_count)
{
	char	*dest;
	char	*src;
	int		items_left;
	int		i;

	if ((index + delete_count) > self->length)
	{
		print_stacktrace();
		exit_on_error(__LINE__);
	}
	else if (index > self->length + 0)
	{
		print_stacktrace();
		exit_on_error(__LINE__);
	}
	ensure_capacity(self, index + insert_count + 0);
	if (delete_count > 0)
	{
		items_left = delete_count;
		while (items_left > 0)
		{
			i = index;
			while (i < (self->length - 1))
			{
				dest = (char *)(self->buffer) + (i * self->item_size);
				src = (char *)(self->buffer) + ((i + 1) * self->item_size);
				memcpy(dest, src, self->item_size);
				i++;
			}
			self->length--;
			items_left--;
		}
	}
	if (insert_count > 0)
	{
		items_left = insert_count;
		while (items_left > 0)
		{
			i = (self->length);
			while (i > index)
			{
				dest = (char *)(self->buffer) + (i * self->item_size);
				src = (char *)(self->buffer) + ((i - 1) * self->item_size);
				memcpy(dest, src, self->item_size);
				i--;
			}
			dest = (char *)(self->buffer) + (index * self->item_size);
			src = (char *)(items);
			memcpy(dest, src, self->item_size);
			items += self->item_size;
			index++;
			self->length++;
			items_left--;
		}
	}
}

static void	ensure_capacity(t_vec *self, size_t n)
{
	size_t	new_capacity;

	if (n > self->capacity)
	{
		new_capacity = n * 2;
		self->buffer = realloc(self->buffer, new_capacity * self->item_size);
		omm_guard(self->buffer, __FILE__, __LINE__);
		self->capacity = new_capacity;
	}
}

static void	exit_on_error(unsigned int line)
{
	fprintf(stderr, "%s:%d - Out of Bounds\n", __FILE__, line);
	exit(EXIT_FAILURE);
}
