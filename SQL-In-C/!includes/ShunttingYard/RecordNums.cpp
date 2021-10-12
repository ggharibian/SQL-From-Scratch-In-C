#include "RecordNums.h"

RecordNums::RecordNums(vector<long> rNums)
{
	_recordNumbers = rNums;
}

int RecordNums::typeOf()
{
	return RECORDNUMBERS;
}

int RecordNums::precedence()
{
	return 3;
}

vector<long> RecordNums::records()
{
	return _recordNumbers;
}

void RecordNums::print(ostream& outs)
{
	for (int i = 0; i < _recordNumbers.size(); i++) {
		outs << _recordNumbers[i] << " ";
	}
}
