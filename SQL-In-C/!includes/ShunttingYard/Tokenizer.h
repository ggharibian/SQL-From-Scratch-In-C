#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>
#include <vector>
#include "Token.h"
#include "LogicalOperator.h"
#include "ConditionalOperator.h"
#include "LeftParenthesis.h"
#include "RightParenthesis.h"
#include "Symbol.h"
#include "../Queue/Queue.h"
using namespace std;

class Tokenizer
{
public:
	Tokenizer(vector<string> tokens);

	Queue<Token*> getTokens();

private:
	Queue<Token*> _tokens;
};

#endif // !TOKENIZER_H

