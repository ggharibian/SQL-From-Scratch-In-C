#include "LeftParenthesis.h"

LeftParenthesis::LeftParenthesis() : LogicalOperator("(") {}

int LeftParenthesis::typeOf()
{
	return LPAREN;
}

void LeftParenthesis::print(ostream& outs)
{
	outs << "(";
}

int LeftParenthesis::precedence()
{
	return 0;
}
