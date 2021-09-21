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

t_char_itr	char_itr_of_str(const t_str *str)
{
	return (char_itr_value(str_cstr(str), str_length(str)));
}

const char	*char_itr_cursor(const t_char_itr *self)
{
	return (self->cursor);
}
