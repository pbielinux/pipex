#ifndef TOKEN_H
#define TOKEN_H

#include "Str.h"

typedef enum	TokenType {
	END_TOKEN = -1,
	WORD_TOKEN = 0,
	PIPE_TOKEN = 1,
}				TokenType;

typedef struct	Token {
	TokenType	type;
	Str		lexeme; // Normally this would be a slice!
}				Token;

#endif
