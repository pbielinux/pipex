/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbielik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 02:33:23 by pbielik           #+#    #+#             */
/*   Updated: 2021/09/21 02:33:25 by pbielik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STR_H
# define STR_H

# include "vec.h"

/**
 * str is just an alias of Vec to make its purpose of storing
 * char data and the following functions clear.
 */
typedef struct s_vec	t_str;

/**
 * Construct an empty str value. Owner is responsible for calling
 * str_drop when its lifetime expires.
 */
t_str		str_value(size_t capacity);

/**
 * Owner of a str must call to expire its buffer data's lifetime.
 * Frees any heap memory the str owns.
 */
void		str_drop(t_str *self);

/**
 * Returns the length of the str _not_ including the null terminating
 * character.
 */
size_t		str_length(const t_str *self);

/**
 * Returns a pointer to a character at a specific offset. Caller is
 * free to modify the memory address returned, but not beyond it.
 */
char		*str_ref(const t_str *self, size_t index);

/**
 * Returns a pointer to the first character of the str's buffer.
 * Returned value should be used for read purposes only. To mutate
 * the str, make use of str_splice, str_append, or str_set.
 */
const char	*str_cstr(const t_str *self);

/**
 * Construct a new str value from a C-string. str_from will _copy_
 * the `cstr` contents to a new heap allocated buffer. Caller is 
 * responsible for calling str_drop when its lifetime expires.
 *
 * Usage: str s = str_from("hello, world");
 */
t_str		str_from(const char *cstr);

/**
 * Starting from `index`, remove `delete_count` items from `self`,
 * and insert `insert_count` values from `cstr` at that index of `self`.
 */
void		str_splice(
				t_str *self,
				size_t index,
				size_t delete_count,
				const char *cstr,
				size_t insert_count);

/**
 * Append a C-string to a str. Will dynamically grow the str's 
 * memory allocation to be able to store the cstr's character
 * contents if necessary.
 */
void		str_append(t_str *self, const char *cstr);

/**
 * Get a character at a specific index of the str.
 */
char		str_get(const t_str *self, size_t index);

/**
 * Set a character at a specific index of the str. If the index
 * is the length of the str, it will append the character to the
 * end of the str and terminate with a null character.
 */
void		str_set(t_str *self, size_t index, const char value);

#endif
