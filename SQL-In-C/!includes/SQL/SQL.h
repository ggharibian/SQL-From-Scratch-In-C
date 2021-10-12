#ifndef SQL_H
#define SQL_H
#include <iostream>
#include <vector>
#include "../Parser/Parser.h"
#include "../Table/Table.h"
using namespace std;
class SQL {
public:
	SQL();
	~SQL();

	void run();
private:
	vector<string> _table_names;
	Map<string, Table> _tableMap;
	Parser _p;
	int _queryNumber;

	void runCommand(const string& command);
	void runBatch(string filename);
};

#endif // !SQL_H