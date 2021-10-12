#include "ConditionalOperator.h"

ConditionalOperator::ConditionalOperator(string oper) : LogicalOperator(oper) {}

int ConditionalOperator::typeOf()
{
	return COPERATOR;
}
