#include "SQL.h"

SQL::SQL() : _queryNumber(0) {
	fstream f;

	cout << "LOADING TABLE INFO..." << endl;

	open_fileRW(f, "tbldata.txt");

	string tempTableName;

	while (!f.eof()) {

		getline(f, tempTableName);

		if (!tempTableName.empty())
			_table_names.push_back(tempTableName);

	}

	for (int i = 0; i < _table_names.size(); i++) {

		_tableMap[_table_names[i]] = Table(_table_names[i]);

	}

	cout << "COMPLETE." << endl;
}

SQL::~SQL()
{
	cout << "table names: " << _table_names << endl;
	fstream f;

	f.open("tbldata.txt", std::ofstream::out | std::ofstream::trunc);
	f.close();

	f.open("tbldata.txt");

	if (!_table_names.empty()) {
		int i;

		for (i = 0; i < _table_names.size() - 1; i++) {
			f << _table_names[i] << endl;
		}

		f << _table_names[i];
	}

	cout << "DATA SAVED." << endl;
	f.close();
}

void SQL::run()
{
	string command;

	cout << "> "; getline(cin, command);

	while (command != "exit") {
		runCommand(command);
		cout << "> "; getline(cin, command);
	}

}

void SQL::runCommand(const string& command)
{
	_p = Parser(command.c_str());

	MMap<string, string> ptree = _p.parseTree();

	if (_p.fail()) {
		cout << "ERROR: INVALID COMMAND; PLEASE ENTER VALID COMMAND." << endl;
	}
	else if (ptree["command"][0] == "batch") {

		runBatch(ptree["values"][0]);
	}
	else if (ptree["command"][0] == "select") {
		if (_tableMap.contains(ptree["table"][0])) {

			if (ptree["field"][0] == "*") {

				if (ptree["where"][0] == "yes") {

					cout << _tableMap[ptree["table"][0]].select_conditional(ptree["condition"]);

				}

				else {

					cout << _tableMap[ptree["table"][0]].select_all();

				}

			}

			else if (ptree["where"][0] == "yes"){

				cout << _tableMap[ptree["table"][0]].select(ptree["field"]).select_conditional(ptree["condition"]);

			}
			else {

				cout << _tableMap[ptree["table"][0]].select(ptree["field"]);

			}
			cout << "SQL: DONE." << endl;
		}
		else {

			cout << "ERROR: TABLE DOES NOT EXIST." << endl;

		}

	}
	else if (ptree["command"][0] == "make" || ptree["command"][0] == "create") {
		
		cout << ptree["command"][0] << " table " << ptree["table"][0] << ", cols: " << ptree["condition"] << endl;

		_table_names.push_back(ptree["table"][0]);

		_tableMap[_table_names[_table_names.size() - 1]] = Table(_table_names[_table_names.size() - 1], ptree["condition"]);

		cout << "SQL: DONE." << endl;
	}
	else if (ptree["command"][0] == "insert") {
		cout << command << endl;
		if (_tableMap.contains(ptree["table"][0])) {

			_tableMap[ptree["table"][0]].insert_into(ptree["values"]);

			cout << "SQL: DONE." << endl;
		}
		else {
			cout << "ERROR: CANNOT INSERT INTO NON-EXISTENT TABLE." << endl;
		}
	}
	else if (ptree["command"][0] == "drop") {
		/*int i;
		while ()
		ptree["values"][0];*/
	}
	cout << endl;
}

void SQL::runBatch(string filename)
{
	string line;
	fstream f;
	f.open(filename.c_str());
	if (f.fail()) {
		cout << "ERROR: FILE DOES NOT EXIST." << endl;
	}
	else {
		while (!f.eof()) {
			getline(f, line);

			if (line.size() != 0 && line[0] != '/' && line[0] != '\n' && line[0] != '\0') {
				cout << "[" << _queryNumber++ << "] " << line << endl;
				runCommand(line);
			}
			else {
				cout << line << endl;
			}
		}

		f.close();
	}
	cout << endl << endl << "------- END OF BATCH PROCESS -------" << endl;
}
