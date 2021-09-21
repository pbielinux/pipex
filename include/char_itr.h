/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_itr.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbielik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 02:19:36 by pbielik           #+#    #+#             */
/*   Updated: 2021/09/21 02:19:39 by pbielik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHAR_ITR_H
# define CHAR_ITR_H

# include <stdlib.h>
# include <stdbool.h>

# include "str.h"

/* 
 * A char_itr is an iterator over an array of char data.
 */

typedef struct s_char_itr
{
	const char	*cursor;
	const char	*sentinel;
}				t_char_itr;

/*
 * Constructor. Resulting char_itr value does not own any
 * heap memory thus there is no drop function. Resulting
 * value's lifetime is dependent upon the start reference.
 */
t_char_itr	char_itr_value(const char *start, size_t length);

/**
 * Get a char_itr of a Str, starting from its first char value.
 * The lifetime of the char_itr is the shorter of the Str's lifetime
 * or an any mutation of the Str.
 */
t_char_itr	char_itr_of_str(const t_str *str);

/*
 * Returns a pointer to the current location of the iterator's cursor.
 */
const char	*char_itr_cursor(const t_char_itr *self);

/*
 * Returns true when there are additional characters to consume
 * in the iterable range.
 */
bool		char_itr_has_next(const t_char_itr *self);

/*
 * Peek and return the next character. Do not advance cursor.
 * Will crash with out of bounds error if no more characters
 * to consume.
 */
char		char_itr_peek(const t_char_itr *self);

/*
 * Read next character and advances cursor.
 * Will crash with out of bounds error if no more characters
 * to consume.
 */
char		char_itr_next(t_char_itr *self);

#endif
