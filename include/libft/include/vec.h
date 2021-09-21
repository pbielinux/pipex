/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbielik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 02:36:18 by pbielik           #+#    #+#             */
/*   Updated: 2021/09/21 02:36:19 by pbielik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC_H
# define VEC_H 

# include <stdlib.h>
# include <stdbool.h>

/**
 * vec - a dynamically growable array of any type.
 */

/**
 * The vec struct is a "thick pointer".
 *
 * Users of vec should not access these members directly!
 * Instead, use the operations exposed in the functions below.
 */
typedef struct s_vec
{
	size_t	item_size;
	size_t	length;
	size_t	capacity;
	void	*buffer;
}				t_vec;

/* Constructor / Destructor */

/**
 * Construct a vec value. Owner is responsible for calling
 * vec_drop when its lifetime expires.
 *
 * @param capacity - initial number of items it can store
 * @param item_size - sizeof an individual item
 * @return initialized vec value.
 */
t_vec		vec_value(size_t capacity, size_t item_size);

/**
 * Owner must call to expire a vec value's lifetime.
 * Frees any heap memory the vec owns.
 * Resets length, capacity to zero, buffer to NULL.
 */
void		vec_drop(t_vec *self);

/* Accessors */

/**
 * Returns the number of items in the vec.
 */
size_t		vec_length(const t_vec *self);

/**
 * Returns a pointer to the items array _for reading only_.
 * You should not write to the returned memory directly!
 */
const void	*vec_items(const t_vec *self);

/**
 * Compare deep equality with another vec. Should return true
 * if vecs are equal in length and buffer content.
 */
bool		vec_equals(const t_vec *self, const t_vec *other);

/* Operations */

/**
 * Get a pointer to the item at `index`. You may
 * write to this reference, but not beyond it.
 */
void		*vec_ref(const t_vec *self, size_t index);

/**
 * Copy the item at `index` to the memory of `out`.
 */
void		vec_get(const t_vec *self, size_t index, void *out);

/**
 * Assign an item at `index` to be a copy of `value`.
 * Valid indices include 0-length. When the index is equal
 * to length, the item is appended to the vec.
 */
void		vec_set(t_vec *self, size_t index, const void *value);

/**
 * Starting from `index`, remove `delete_count` items from `self`'s buffer, 
 * and insert `insert_count` values from `items` at that index of `self`.
 * All items inserted become owned by the `vec`.
 *
 * This is a swiss army knife function for inserting, removing, and overwriting
 * items with a `vec`.
 *
 * Attempting to delete beyond the end of the vec's elements or insert beyond
 * the length of the vec will result in an out of bounds crash.
 *
 * Example - Given:
 * 1. a vec `v` with elements [100, 200, 300, 400] and an int[] a 
 * 2. an array `a` with elements [800, 900]
 * The following examples are indepentent and assume the starting values above.
 * Call:                        | v's Items after:
 * vec_splice(&v, 2, 0, a, 2)   | [100, 200, 800, 900, 300, 400]
 * vec_splice(&v, 2, 1, a, 2)   | [100, 200, 800, 900, 400]
 * vec_splice(&v, 0, 0, a, 2)   | [800, 900, 100, 200, 300, 400]
 * vec_splice(&v, 0, 3, a, 1)   | [800, 400]
 */

typedef struct s_count
{
	size_t	delete_count;
	size_t	insert_count;
}	t_count;

void		vec_splice(
				t_vec *self,
				size_t index,
				size_t delete_count,
				const void *items,
				size_t insert_count);

#endif
