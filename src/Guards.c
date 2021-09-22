/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   guards.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbielik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 23:36:21 by pbielik           #+#    #+#             */
/*   Updated: 2021/09/20 23:36:23 by pbielik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

#include "libft.h"

void	*omm_guard(void *ptr, char *file, int number)
{
	if (ptr == NULL)
	{
		ft_putstr_fd(file, 2);
		ft_putnbr_fd(number, 2);
		ft_putstr_fd(" - Out of Memory", 2);
		exit(EXIT_FAILURE);
	}
	return (ptr);
}
