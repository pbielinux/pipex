#ifndef NODE_H
#define NODE_H

#include "Str.h"
#include "StrVec.h"

typedef enum	NodeType
{
	ERROR_NODE = -1,
	COMMAND_NODE = 0,
	PIPE_NODE = 1
}				NodeType;

typedef struct Node Node; // Forward Declaration

typedef const char *ErrorValue;

typedef StrVec CommandValue;

typedef struct	PipeValue {
	Node	*left;
	Node	*right;
}				PipeValue;

typedef union	NodeValue {
	ErrorValue		error;
	CommandValue	command;
	PipeValue		pipe;
}				NodeValue;

struct Node
{
	NodeType	type;
	NodeValue	data;
};

/*
* Node Constructors
*/
Node	*CommandNode_new(StrVec words);

Node	*PipeNode_new(Node *left, Node *right);

Node	*ErrorNode_new(const char *msg);

/*
* Node Destructor
*/
void	*Node_drop(Node *self);

#endif
