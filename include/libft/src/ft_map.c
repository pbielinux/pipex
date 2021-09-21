/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbielik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 02:41:36 by pbielik           #+#    #+#             */
/*   Updated: 2021/09/21 02:41:37 by pbielik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_map(double nb, t_range range)
{
	return (range.out_min + ((range.out_max - range.out_min)
			/ (range.in_max - range.in_min)) * (nb - range.in_min));
}
