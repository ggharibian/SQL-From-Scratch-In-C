#ifndef LOGICALOPERATOR_H
#define LOGICALOPERATOR_H

#include "Token.h"
#include <string>
using namespace std;

class LogicalOperator : public Token
{
public:

	LogicalOperator(string oper);

	int typeOf();

	virtual string value();

	virtual void print(ostream& outs);

	virtual int precedence();
private:
	string _operator;
};

#endif // !LOGICALOPERATOR_H

