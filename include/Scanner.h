#ifndef TOKEN_ITR_H
#define TOKEN_ITR_H

#include <stdbool.h>

#include "Token.h"
#include "CharItr.h"

/** 
 * Scanner is a peekable iterator that produces Tokens from a CharItr input.
 **/

typedef struct	Scanner
{
	CharItr	char_itr;
	Token	next;
}				Scanner;


/**
 * A Scanner consumes a CharItr and produces Tokens.
 **/
Scanner Scanner_value(CharItr char_itr);

/**
 * Scanner_has_next returns true when there is another Token to
 * peek or take with next, false otherwise.
 */
bool Scanner_has_next(const Scanner *self);

/**
 * Peek the next Token without advancing the Scanner. The Scanner
 * still owns the Token (and, importantly, its lexeme Str).
 */
Token Scanner_peek(const Scanner *self);

/**
 * Take the next Token and advance the Scanner. The caller of
 * Scanner_next owns the returned Token and is responsible for
 * calling Str_drop on its lexeme Str. 
 *
 * When there are no more tokens in the stream, return a token of
 * END_TOKEN type with an empty Str lexeme.
 */
Token Scanner_next(Scanner *self);

#endif
