#include "Parser.h"
#include "Token.h"

// Grammar
// NODE			::= CHAR_NODE | PAIR_NODE
// CHAR_NODE	::= CHAR_TOKEN
// PAIR_NODE	::= LPAREN_TOKEN NODE SPACE_TOKEN NODE RPAREN_TOKEN

static Node *parse_pair(Scanner *scanner);
static Node *parse_char(Scanner *scanner);

// NODE			::= CHAR_NODE | PAIR_NODE
Node *parse(Scanner *scanner)
{
	Token next = Scanner_peek(scanner);
	switch (next.type)
	{
	case CHAR_TOKEN:
		return parse_char(scanner);
	case LPAREN_TOKEN:
		return parse_pair(scanner);
	default:
		return ErrorNode_new("Expected ( or a Char");
	}
}

// CHAR_NODE	::= CHAR_TOKEN
static Node *parse_char(Scanner *scanner)
{
	Token	next = Scanner_next(scanner);
	return (CharNode_new(next.lexeme));
}

// PAIR_NODE	::= LPAREN_TOKEN NODE SPACE_TOKEN NODE RPAREN_TOKEN
static Node *parse_pair(Scanner *scanner)
{
	Token	next = Scanner_next(scanner);
	Node *left = parse(scanner);
	next = Scanner_next(scanner); // Consume space token, trust!
	Node *right = parse(scanner);
	next = Scanner_next(scanner); // Consume the rparen token, trust!

	return (PairNode_new(left, right));
}
