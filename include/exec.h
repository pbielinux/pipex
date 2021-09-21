/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbielik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 02:19:53 by pbielik           #+#    #+#             */
/*   Updated: 2021/09/21 02:19:55 by pbielik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "node.h"

typedef struct s_context
{
	int	fd[2];
	int	fd_close;
}				t_context;

typedef struct s_exec
{
	t_node		*lhs;
	t_node		*rhs;
	t_context	lhs_ctx;
	t_context	rhs_ctx;
}				t_exec;

void	exec(t_node *node, int file_in, int file_out, char **envp);

#endif
