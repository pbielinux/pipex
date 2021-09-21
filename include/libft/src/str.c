/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbielik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 23:38:04 by pbielik           #+#    #+#             */
/*   Updated: 2021/09/20 23:38:05 by pbielik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>
#include "str.h"
#include "vec.h"

static char	g_null = '\0';

/* 
 * Helper function that will terminate the program with an appropriate
 * error message, given a line reference to the error
 */
static void	exit_on_error(unsigned int line);

t_str	str_value(size_t capacity)
{
	t_str	s;

	s = vec_value(capacity + 1, sizeof(char));
	vec_set(&s, 0, &g_null);
	return (s);
}

void	str_drop(t_str *self)
{
	vec_drop(self);
}

size_t	str_length(const t_str *self)
{
	return (vec_length(self) - 1);
}

const char	*str_cstr(const t_str *self)
{
	return ((char *)vec_ref(self, 0));
}

char	*str_ref(const t_str *self, const size_t index)
{
	return ((char *)vec_ref(self, index));
}

t_str	str_from(const char *cstr)
{
	t_str	newstr;
	int		i;

	i = 0;
	newstr = str_value(1);
	while (*(cstr + i) != g_null)
	{
		vec_set(&newstr, i, cstr + i);
		i++;
	}
	vec_set(&newstr, i, &g_null);
	return (newstr);
}

void	str_splice(t_str *self, size_t index, size_t delete_count,
		const char *cstr, size_t insert_count)
{
	if (delete_count + index > str_length(self))
	{
		exit_on_error(__LINE__);
	}
	else if (index > str_length(self))
	{
		exit_on_error(__LINE__);
	}
	vec_splice(self, index, delete_count, cstr, insert_count);
}

void	str_append(t_str *self, const char *cstr)
{
	size_t	cstrlength;

	cstrlength = 0;
	while (*(cstr + cstrlength) != g_null)
	{
		cstrlength++;
	}
	str_splice(self, str_length(self), 0, cstr, cstrlength);
}

char	str_get(const t_str *self, size_t index)
{
	if ((index < 0) || (index >= str_length(self)))
	{
		exit_on_error(__LINE__);
	}
	return (*((char *)vec_ref(self, index)));
}

void	str_set(t_str *self, size_t index, const char value)
{
	if (index < str_length(self))
	{
		str_splice(self, index, 1, &value, 1);
	}
	else if (index == str_length(self))
	{
		str_splice(self, index, 0, &value, 1);
	}
	else
		exit_on_error(__LINE__);
}

/* Helper Functions */
static void	exit_on_error(unsigned int line)
{
	fprintf(stderr, "%s:%d - Out of Bounds", __FILE__, line);
	exit(EXIT_FAILURE);
}
