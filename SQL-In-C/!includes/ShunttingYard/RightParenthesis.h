#ifndef RIGHTPARENTHEISIS
#define RIGHTPARENTHEISIS

#include <iostream>
#include "LogicalOperator.h"
using namespace std;

class RightParenthesis : public LogicalOperator
{
public:
	RightParenthesis();
	int typeOf();
	void print(ostream& outs);
	int precedence();
};

#endif // !RIGHTPARENTHEISIS

