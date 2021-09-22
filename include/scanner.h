/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbielik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 02:25:34 by pbielik           #+#    #+#             */
/*   Updated: 2021/09/21 02:25:36 by pbielik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCANNER_H
# define SCANNER_H

# include <stdbool.h>

# include "token.h"
# include "char_itr.h"

/** 
 * Scanner is a peekable iterator that produces Tokens from a CharItr input.
 **/

typedef struct s_scanner
{
	t_char_itr	char_itr;
	t_token		next;
}				t_scanner;

/**
 * A Scanner consumes a CharItr and produces Tokens.
 **/
t_scanner	scanner_value(t_char_itr char_itr);

/**
 * Scanner_has_next returns true when there is another Token to
 * peek or take with next, false otherwise.
 */
bool		scanner_has_next(const t_scanner *self);

/**
 * Peek the next Token without advancing the Scanner. The Scanner
 * still owns the Token (and, importantly, its lexeme Str).
 */
t_token		scanner_peek(const t_scanner *self);

/**
 * Take the next Token and advance the Scanner. The caller of
 * Scanner_next owns the returned Token and is responsible for
 * calling Str_drop on its lexeme Str. 
 *
 * When there are no more tokens in the stream, return a token of
 * END_TOKEN type with an empty Str lexeme.
 */
t_token		scanner_next(t_scanner *self);

void		fill_next_pos(t_scanner *self);
void		throw_useless_input(t_scanner *self);

#endif
