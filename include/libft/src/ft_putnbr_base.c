/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbielik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 02:42:33 by pbielik           #+#    #+#             */
/*   Updated: 2021/09/21 02:42:36 by pbielik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_base(unsigned long n, char *base)
{
	unsigned int	base_length;
	int				num_length;

	num_length = 1;
	base_length = ft_strlen(base);
	if (n == 0)
	{
		write(1, "0", 1);
		return (num_length);
	}
	if (n >= base_length)
	{
		num_length += ft_putnbrBase(n / base_length, base);
		write(1, &base[n % base_length], 1);
	}
	else if (n < base_length)
		write(1, &base[n], 1);
	return (num_length);
}
