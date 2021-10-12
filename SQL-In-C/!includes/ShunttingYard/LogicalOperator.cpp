#include "LogicalOperator.h"

LogicalOperator::LogicalOperator(string oper) : _operator(oper) {}

int LogicalOperator::typeOf()
{
	return LOPERATOR;
}

string LogicalOperator::value()
{
	return _operator;
}

void LogicalOperator::print(ostream& outs)
{
	outs << _operator;
}

int LogicalOperator::precedence()
{
	if (_operator == "and") {
		return 2;
	}
	if (_operator == "or") {
		return 1;
	}
	return 3;
}
