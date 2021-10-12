#ifndef RECORDNUMS_H
#define RECORDNUMS_H
#include <iostream>
#include <string>
#include <vector>
#include "Token.h"
using namespace std;


class RecordNums : public Token
{
public:

	RecordNums(vector<long> rNums);

	int typeOf();

	int precedence();

	vector<long> records();

	void print(ostream& outs);

private:
	vector<long> _recordNumbers;
};

#endif // !RECORDNUMS_H

