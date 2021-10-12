#ifndef SYMBOL_H
#define SYMBOL_H
#include <iostream>
#include <string>
#include "Token.h"
using namespace std;


class Symbol : public Token
{
public:

	Symbol(string str);

	Symbol& operator =(string value);

	int typeOf();

	int precedence();

	string string();

	void print(ostream& outs);

private:
	std::string _str;
};

#endif // !SYMBOL_H

