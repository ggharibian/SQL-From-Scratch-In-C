#ifndef LEFTPARENTHESIS
#define LEFTPARENTHESIS

#include <iostream>
#include "LogicalOperator.h"
using namespace std;

class LeftParenthesis : public LogicalOperator
{
public:
	LeftParenthesis();
	int typeOf();
	void print(ostream& outs);
	int precedence();
};

#endif // !LEFTPARENTHESIS