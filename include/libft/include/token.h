/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbielik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 02:34:09 by pbielik           #+#    #+#             */
/*   Updated: 2021/09/21 02:37:16 by pbielik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "str.h"

typedef enum token_type
{
	END_TOKEN = -1,
	WORD_TOKEN = 0,
	PIPE_TOKEN = 1,
}				t_token_type;

typedef struct s_token
{
	t_token_type	type;
	t_str			lexeme;
}				t_token;

#endif
