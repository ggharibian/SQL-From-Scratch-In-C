#include "Tokenizer.h"

Tokenizer::Tokenizer(vector<string> tokens)
{
	for (int i = 0; i < tokens.size(); i++) {
		if (tokens[i] == ")") {
			_tokens.Push(new RightParenthesis());
		}
		else if (tokens[i] == "(") {
			_tokens.Push(new LeftParenthesis());
		}
		else if (tokens[i] == "<" || tokens[i] == ">" || tokens[i] == "<=" || tokens[i] == ">=" || tokens[i] == "=") {
			_tokens.Push(new LogicalOperator(tokens[i]));
		}
		else if (tokens[i] == "and" || tokens[i] == "or") {
			_tokens.Push(new ConditionalOperator(tokens[i]));
		}
		else {
			_tokens.Push(new Symbol(tokens[i]));
		}
	}
}

Queue<Token*> Tokenizer::getTokens()
{
	return _tokens;
}
