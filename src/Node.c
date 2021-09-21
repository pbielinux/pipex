/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbielik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 23:36:42 by pbielik           #+#    #+#             */
/*   Updated: 2021/09/20 23:36:44 by pbielik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "node.h"
#include "guards.h"

t_node	*error_node_new(const char *msg)
{
	t_node	*new;

	new = malloc(sizeof(t_node));
	omm_guard(new, __FILE__, __LINE__);
	new->type = ERROR_NODE;
	new->data.error = msg;
	return (new);
}

t_node	*command_node_new(t_strvec words)
{
	t_node	*new;

	new = malloc(sizeof(t_node));
	omm_guard(new, __FILE__, __LINE__);
	new->type = COMMAND_NODE;
	new->data.command = words;
	return (new);
}

t_node	*pipe_node_new(t_node *left, t_node *right)
{
	t_node	*new;

	new = malloc(sizeof(t_node));
	omm_guard(new, __FILE__, __LINE__);
	new->type = PIPE_NODE;
	new->data.pipe.left = left;
	new->data.pipe.right = right;
	return (new);
}

void	*node_drop(t_node *self)
{
	if (self->type == ERROR_NODE)
		free (self);
	else if (self->type == COMMAND_NODE)
	{
		strvec_drop(&(self->data.command));
		free (self);
	}
	else if (self->type == PIPE_NODE)
	{
		node_drop(self->data.pipe.left);
		node_drop(self->data.pipe.right);
		free(self);
	}
	return (NULL);
}
