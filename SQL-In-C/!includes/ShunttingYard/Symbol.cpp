#include "Symbol.h"

Symbol::Symbol(std::string str)
{
	_str = str;
}

Symbol& Symbol::operator=(std::string value)
{
	_str == value;
	return *this;
}

int Symbol::typeOf()
{
	return SYMBOL;
}

int Symbol::precedence()
{
	return 3;
}

string Symbol::string()
{
	return _str;
}

void Symbol::print(ostream& outs)
{
	outs << _str;
}
