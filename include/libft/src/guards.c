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

void	*omm_guard(void *ptr, char *file, int number)
{
	if (ptr == NULL)
	{
		fprintf(stderr, "%s:%d Out of Memory", file, number);
		exit(EXIT_FAILURE);
	}
	return (ptr);
}
