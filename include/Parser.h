/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbielik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 02:24:08 by pbielik           #+#    #+#             */
/*   Updated: 2021/09/21 02:24:09 by pbielik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "node.h"
# include "scanner.h"

/**
 * Given a Scanner, returns a pointer to the `Node` at
 * the root of the parse tree. The caller of `parse`
 * owns the resulting `Node*` and is responsible for
 * calling `Node_drop` to free its allocated memory.
 */
t_node	*parse(t_scanner *scanner);

#endif
