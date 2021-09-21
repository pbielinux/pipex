/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbielik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 02:23:32 by pbielik           #+#    #+#             */
/*   Updated: 2021/09/21 02:23:34 by pbielik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_H
# define NODE_H

# include "str.h"
# include "str_vec.h"

typedef enum node_type
{
	ERROR_NODE = -1,
	COMMAND_NODE = 0,
	PIPE_NODE = 1
}			t_node_type;

typedef struct s_node	t_node;

typedef const char		*t_error_value;

typedef t_strvec		t_command_value;

typedef struct s_pipe_value
{
	t_node	*left;
	t_node	*right;
}				t_pipe_value;

typedef union node_value
{
	t_error_value		error;
	t_command_value		command;
	t_pipe_value		pipe;
}				t_node_value;

struct s_node
{
	t_node_type		type;
	t_node_value	data;
};

/*
* node Constructors
*/
t_node	*command_node_new(t_strvec words);

t_node	*pipe_node_new(t_node *left, t_node *right);

t_node	*error_node_new(const char *msg);

/*
* node Destructor
*/
void	*node_drop(t_node *self);

#endif
