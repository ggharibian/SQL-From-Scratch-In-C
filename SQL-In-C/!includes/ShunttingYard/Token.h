#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
using namespace std;
enum Tokens { TOKEN, LPAREN, RPAREN, SYMBOL, LOPERATOR, COPERATOR, RECORDNUMBERS};
class Token
{
public:
	Token() {};
	virtual int typeOf() { return TOKEN; }
	virtual void print(ostream&){}

private:
};

#endif // !TOKEN_H

