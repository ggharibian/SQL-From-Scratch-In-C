#pragma once
#include "../../!includes/Stack/Stack.h"
#include "../../!includes/Queue/Queue.h"
#include "Token.h"
#include "LogicalOperator.h"
#include "ConditionalOperator.h"
#include "LeftParenthesis.h"
#include "RightParenthesis.h"
#include "Symbol.h"

void printTokens(Queue<Token*> toPrint);
class ShuntingYard
{
public:
	ShuntingYard(Queue<Token*> infix);
	Queue<Token*>& postfix();
private:
	Queue<Token*> _infix;
	Queue<Token*> _postfix;
};