#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#include "Str.h"
#include "Scanner.h"
#include "Parser.h"
#include "Node.h"
#include "exec.h"

#define BUFF_SIZE 1025

/**
 * This program reads an input line from stdin and prints textual
 * representations of the tokens scanned from lines of input.
 */

// These three functions provide the basis of a REPL:
// Read-Evaluate-Print-Loop
size_t	read(Str *line, FILE *stream);
Node	*eval(Str *input);
void	print(Node *node, size_t indention);
int		open_file(char *argv, int i);

int	main(int argc, char **argv, char **envp)
{
	StrVec	input = StrVec_value(argc);
	Str		line = Str_value(BUFF_SIZE);
	Node	*parse_tree;
	int		i;
	int filein;
	int fileout;

	
	input = StrVec_value(argc);
	line = Str_value(BUFF_SIZE);
	
	// Create the input line inserting pipes between commands
	i = 2;
	while (i < argc - 1)
	{
		StrVec_push(&input, Str_from(argv[i]));
		if (i < argc - 2)
			StrVec_push(&input, Str_from(" | "));
			i++;
	}
	i = 0;
	while (i < StrVec_length(&input))
	{
		Str_append(&line, Str_cstr(StrVec_ref(&input, i)));
		i++;
	}

	filein = open_file(argv[1], 2);
	fileout = open_file(argv[argc - 1], 1);
	
	parse_tree = eval(&line);
	//print(parse_tree, 0);
	exec(parse_tree, filein, fileout);

	Node_drop(parse_tree);
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

int	open_file(char *argv, int i)
{
	int	file;

	file = 0;
	if (i == 0)
		file = open(argv, O_CREAT | O_APPEND | O_WRONLY, 0644);
	else if (i == 1)
		file = open(argv, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	else if (i == 2)
		file = open(argv, O_RDONLY, 0);
	if (file == -1)
	{
		printf("ERROR!\n");
		exit(EXIT_FAILURE);
	}
	return (file);
}