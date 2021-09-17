#include "Node.h"
#include "Guards.h"

/*
*	Constructors
*/

Node *ErrorNode_new(const char *msg)
{
	Node *node = malloc(sizeof(Node));
	OOM_GUARD(node, __FILE__, __LINE__);
	node->type = ERROR_NODE;
	node->data.error = msg;
	return node;
}

Node *CommandNode_new(StrVec words)
{
	Node *node = malloc(sizeof(Node));
	OOM_GUARD(node, __FILE__, __LINE__);
	node->type = COMMAND_NODE;
	node->data.command= words;
	return node;
};

Node *PipeNode_new(Node *left, Node *right)
{
	Node *node = malloc(sizeof(Node));
	OOM_GUARD(node, __FILE__, __LINE__);
	node->type = PIPE_NODE;
	node->data.pipe.left = left;
	node->data.pipe.right = right;
	return node;
}

/*
*	Destructor
*/

void *Node_drop(Node *self)
{
	/* Handle By Cases */
	if (self->type == ERROR_NODE)
		free (self);
	else if (self->type == COMMAND_NODE)
	{
		StrVec_drop(&(self->data.command));
		free (self);
	}
	else if (self->type == PIPE_NODE)
	{
		/* Pipe node is special because you have to recursively free the command nodes */
		Node_drop(self->data.pipe.left);
		Node_drop(self->data.pipe.right);
		free(self);
	}
	return NULL;
};
