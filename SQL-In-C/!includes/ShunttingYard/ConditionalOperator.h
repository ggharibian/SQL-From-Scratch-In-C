#ifndef CONDITIONALOPERATOR_H
#define CONDITIONALOPERATOR_H

#include "LogicalOperator.h"
#include <string>
using namespace std;

class ConditionalOperator : public LogicalOperator
{
public:

	ConditionalOperator(string oper);

	int typeOf();
};

#endif // !CONDITIONALOPERATOR_H

