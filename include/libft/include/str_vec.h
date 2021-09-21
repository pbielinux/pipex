/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_vec.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbielik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 02:30:47 by pbielik           #+#    #+#             */
/*   Updated: 2021/09/21 02:30:48 by pbielik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STR_VEC_H
# define STR_VEC_H

# include "vec.h"
# include "str.h"

/* strvec is a vector of str values. */
typedef t_vec	t_strvec;

/* Construct an empty strvec value. Owner is 
 * responsible for calling str_drop when its 
 * lifetime expires.
 */
t_strvec	strvec_value(size_t capacity);

/* Owner of strvec must call drop to expire
 * its lifetime and the heap memory its str
 * items own. */
void		strvec_drop(t_strvec *self);

/* Returns the # of strs in the strvec */
size_t		strvec_length(const t_strvec *self);

/* Returns a pointer to a str at given index.  */
t_str		*strvec_ref(const t_strvec *self, size_t index);

/* Push a str value onto the end of the strvec.
 * The strvec self becomes the owner of str value. */
void		strvec_push(t_strvec *self, t_str value);

/* Pop a str value off the end of the strvec.
 * After popping, strvec's length is reduced by one.
 * The popped str is returned and becomes owned
 * by the caller of strvec_pop. */
t_str		strvec_pop(t_strvec *self);

/* Set a str at a specific index. If the index
 * is the length of the strvec, value will be appended.
 * Otherwise, whatever str was previously at the
 * index will be dropped and then replaced with value.
 * The strvec self becomes the owner of str value. */
void		strvec_set(t_strvec *self, size_t index, t_str value);

#endif
