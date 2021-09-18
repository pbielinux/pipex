#include "Parser.h"

static Node* parseCommand(Scanner *scanner);

Node* parse(Scanner *scanner)
{
	Token pipeToken;
	Token fetched;

	/* If there is no node, or there is a pipe node, we have an error */
	if (!Scanner_has_next(scanner))
		return ErrorNode_new("No more Readable Tokens!");
	else if (Scanner_peek(scanner).type == END_TOKEN)
		return ErrorNode_new("End Token Encountered!");
	else if (Scanner_peek(scanner).type == PIPE_TOKEN)
	{
		/* Pull the literal pipe and free it */
		pipeToken = Scanner_next(scanner);
		Str_drop(&pipeToken.lexeme);

		/* Now, free every token that comes after it since
		 * no more parsing will occur at the point that 
		 * an error node is reached, so that following memory 
		 * must be freed before returning the error*/
		while (Scanner_has_next(scanner))
		{
			fetched = Scanner_next(scanner);
			Str_drop(&fetched.lexeme);
		}

		return ErrorNode_new("Unexpected Pipe Encountered!");
	}
	else if (Scanner_peek(scanner).type == WORD_TOKEN)
		return parseCommand(scanner);
	
	return NULL; // To silent the errors
}

static Node* parseCommand(Scanner *scanner)
{
	StrVec	workingCommand;
	Token	cmd;
	Token	pipeToken;
	Node	*left;
	Node	*right;

	/* By virtue of being here, the next token is a command token by assumption */
	workingCommand = StrVec_value(1); /* Add all of the words of the command together */
	cmd = Scanner_next(scanner); /* Pull the next token from the scanner */
	StrVec_push(&workingCommand, cmd.lexeme); /* Push the retrieved token onto workingCommand */
	/* Keep Reading Until we hit a END_TOKEN or PIPE_TOKEN */
	while (Scanner_has_next(scanner))
	{
		/* If it is a command, then push it onto workingCommand */
		if (Scanner_peek(scanner).type == WORD_TOKEN)
		{
			cmd = Scanner_next(scanner);
			StrVec_push(&workingCommand, cmd.lexeme); /* Push the retrieved token onto workingCommand */
		}
		else if (Scanner_peek(scanner).type == END_TOKEN)
			return CommandNode_new(workingCommand);
		else if (Scanner_peek(scanner).type == PIPE_TOKEN)
		{
			/* If we have a pipe */
			left = CommandNode_new(workingCommand);
			/* Pull the literal pipe and free it */
			pipeToken = Scanner_next(scanner);
			Str_drop(&pipeToken.lexeme);
			/* Get the right node */
			right = parse(scanner);
			return PipeNode_new(left, right);
		}
	}
	return CommandNode_new(workingCommand);
}