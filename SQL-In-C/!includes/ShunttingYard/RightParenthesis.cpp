#include "RightParenthesis.h"

RightParenthesis::RightParenthesis() : LogicalOperator(")") {}

int RightParenthesis::typeOf()
{
	return RPAREN;
}

void RightParenthesis::print(ostream& outs)
{
	outs << ")";
}

int RightParenthesis::precedence()
{
	return 4;
}
