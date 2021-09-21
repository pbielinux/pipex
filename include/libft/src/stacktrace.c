/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stacktrace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbielik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 23:37:28 by pbielik           #+#    #+#             */
/*   Updated: 2021/09/20 23:37:30 by pbielik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execinfo.h>
#include <stdio.h>
#include <stdlib.h>

void	print_stacktrace(void)
{
	int		i;
	void	*array[16];
	int		stack_num;
	char	**stacktrace;

	stack_num = backtrace(array, 16);
	stacktrace = backtrace_symbols(array, stack_num);
	i = 0;
	while (i < stack_num)
	{
		printf("%s\n", stacktrace[i]);
		i++;
	}
	free(stacktrace);
}
