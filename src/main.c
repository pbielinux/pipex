#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Str.h"
#include "Scanner.h"
#include "Parser.h"
#include "Node.h"
#include "exec.h"

#define BUFF_SIZE 80

/**
 * This program reads an input line from stdin and prints textual
 * representations of the tokens scanned from lines of input.
 */

// These three functions provide the basis of a REPL:
// Read-Evaluate-Print-Loop
size_t	read(Str *line, FILE *stream);
Node	*eval(Str *input);
void	print(Node *node, size_t indention);

int	main()
{
	Str line = Str_value(BUFF_SIZE);
	while (read(&line, stdin))
	{
		Node *parse_tree = eval(&line);
		print(parse_tree, 0);
		exec(parse_tree);
		Node_drop(parse_tree);
	}
	Str_drop(&line);
	return EXIT_SUCCESS;
}

size_t	read(Str *line, FILE *stream)
{
	printf("Parser> ");

	// Clear Str contents
	Str_splice(line, 0, Str_length(line), NULL, 0);

	static char buffer[BUFF_SIZE];
	while (fgets(buffer, BUFF_SIZE, stream) != NULL)
	{
		Str_append(line, buffer);
		if (strchr(buffer, '\n') != NULL)
			break;
	}
	return Str_length(line);
}

Node*	eval(Str *line)
{
	Scanner scanner = Scanner_value(CharItr_of_Str(line));
	return parse(&scanner);
}

void	print(Node *node, size_t ident)
{
	size_t	i;
	StrVec	*words;

	i = 0;
	while (i++ < ident)
		putchar(' ');
	if (node->type == COMMAND_NODE)
	{
		i = 0;
		printf("COMMAND:");
		words = &node->data.command;
		while (i < StrVec_length(words))
		{
			printf(" %s", Str_cstr(StrVec_ref(words, i)));
			i++;
		}
		putchar('\n');
	}
	else if (node->type == PIPE_NODE)
	{
		printf("PIPE:\n");
		print(node->data.pipe.left, ident + 4);
		print(node->data.pipe.right, ident + 4);
	}
	else
		printf("ERROR: %s\n", node->data.error);
}
