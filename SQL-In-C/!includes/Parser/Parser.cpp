#include "Parser.h"

Parser::Parser()
{
	buildKeywordList();
	make_table(_table);
}

Parser::Parser(const char input[])
{
	buildKeywordList();
	make_table(_table);
	set_string(input);
}

void Parser::set_string(const char c[])
{
	_inputq = Queue<SToken>();
	_ptree.clear();

	string tempString;
	bool skipNext = false;
	_failed = false;
	_stok.set_string(c);

	SToken temp;

	while (!_stok.done()) {
		if (!skipNext)
			_stok >> temp;

		skipNext = false;

		if (temp.token_str() != "\0") {

			if (temp.token_str() == "\"") {

				_stok >> temp;

				while (temp.token_str()[0] != '\"') {
					tempString += temp.token_str();
					_stok >> temp;
				}

				_inputq.Push(SToken(tempString, ALPHA_TOKEN));

				tempString = "";

			}
			else if (temp.token_str() == ">" || temp.token_str() == "<") {
				tempString = temp.token_str();
				_stok >> temp;

				if (temp.token_str() == "=") {
					_inputq.Push(SToken(tempString + temp.token_str(), ALPHA_TOKEN));
				}
				else {
					_inputq.Push(SToken(tempString, ALPHA_TOKEN));
					skipNext = true;
				}

				tempString = "";
			}
			else {
				_inputq.Push(temp);
			}
			
		}

		/*if (!foundQuote) {

			_stok >> temp;

		}

		foundQuote = false;

		if (temp.token_str() != "\0") {

			if (temp.token_str() == "\"") {
				foundQuote = true;

				_stok >> temp;

				while (temp.token_str()[0] != '\"') {


					tempString += temp.token_str();


					_stok >> temp;


				}


				_inputq.Push(SToken(tempString, ALPHA_TOKEN));
				tempString = "";
			}
			else if (temp.token_str() == "\",") {

				_inputq.Push(SToken(temp.token_str().substr(1,1), temp.type()));

			}
			else{

				_inputq.Push(temp);

			}
		}*/

	}

	_failed = setParseTree();
}

void Parser::mark_cell(int table[MAX_ROWS][MAX_COLS_P], int row, int word, int newState)
{
	table[row][word] = newState;
}

void Parser::mark_cell_for_all(int table[MAX_ROWS][MAX_COLS_P], int row, int newState)
{
	Map<string, int>::Iterator it = _keywords.begin();
	while (it != _keywords.end()) {
		table[row][(*it).value] = newState;
		it++;
	}

}

void Parser::mark_success(int table[MAX_ROWS][MAX_COLS_P], int row)
{
	table[row][SUCCESS] = 1;
}

void Parser::make_table(int _table[][MAX_COLS_P])
{
	for (int i = 0; i < MAX_ROWS_P; i++) {
		for (int e = 0; e < MAX_COLS_P; e++) {
			//All table values are initialized to -1 by default. 
			//Represents a failing state.

			_table[i][e] = -1;
		}
	}
	//All State tree's for alpha, space, number, and punctuation 
	//tokens are initialized here.

//Alpha Tree
	mark_cell(_table, 0, SELECT, 1);

	mark_cell(_table, 1, STAR, 2);
	mark_cell(_table, 1, SYMBOL, 2);
	mark_cell_for_all(_table, 1, 2);

	mark_cell(_table, 2, FROM, 3);
	mark_cell(_table, 2, COMMA, 1);
	mark_cell(_table, 3, SYMBOL, 4);
	mark_cell_for_all(_table, 3, 4);
	mark_success(_table, 4);

	mark_cell(_table, 4, WHERE, 5);
	mark_cell(_table, 5, SYMBOL, 5);
	mark_cell_for_all(_table, 5, 5);
	mark_success(_table, 5);

	mark_cell(_table, 0, MAKE, 7);
	mark_cell(_table, 0, CREATE, 7);
	mark_cell(_table, 7, TABLE, 8);
	mark_cell(_table, 8, SYMBOL, 9);
	mark_cell_for_all(_table, 8, 9);
	mark_cell(_table, 9, FIELDS, 10);
	mark_cell(_table, 10, SYMBOL, 11);
	mark_cell_for_all(_table, 10, 11);
	mark_cell(_table, 11, COMMA, 10);
	mark_success(_table, 11);

	mark_cell(_table, 0, INSERT, 12);
	mark_cell(_table, 12, INTO, 13);
	mark_cell(_table, 13, SYMBOL, 14);
	mark_cell_for_all(_table, 13, 14);
	mark_cell(_table, 14, VALUES, 15);
	mark_cell(_table, 15, SYMBOL, 16);
	mark_cell_for_all(_table, 15, 16);
	mark_cell(_table, 16, COMMA, 15);
	mark_success(_table, 16);

	mark_cell(_table, 0, BATCH, 17);
	mark_cell(_table, 17, SYMBOL, 17);
	mark_cell_for_all(_table, 17, 17);
	mark_success(_table, 17);

	mark_cell(_table, 0, DROP, 18);
	mark_cell(_table, 18, TABLE, 19);
	mark_cell(_table, 18, SYMBOL, 19);
	mark_cell(_table, 19, SYMBOL, 19);
	mark_cell_for_all(_table, 18, 19);
	mark_cell_for_all(_table, 19, 19);
	mark_success(_table, 19);
	mark_success(_table, 18);
}

int Parser::getColumn(SToken t)
{
	if (_keywords.contains(Pair<string, int>(toLower(t.token_str())))) {
		return _keywords[toLower(t.token_str())];
	}
	else {
		return SYMBOL;
	}
}

bool Parser::setParseTree()
{
	SToken t;
	int currentState = 0, newState;
	while (currentState != -1 && !_inputq.Empty()) {
		t = _inputq.Pop();

		if (t.type() != SPACE_TOKEN) {

			newState = _table[currentState][getColumn(t)];

			switch (currentState) {
			case 0:
				_ptree["command"] += toLower(t.token_str());
				break;
			case 1:
				_ptree["field"] += t.token_str();
				break;
			case 3:
			case 8:
			case 13:
			case 19:
				_ptree["table"] += t.token_str();
				break;
			case 4:
				_ptree["where"] += "yes";
				break;
			case 5:
			case 10:
				_ptree["condition"] += t.token_str();
				break;
			case 15:
				_ptree["values"] += t.token_str();
				break;
			case 17:
				if (_ptree["values"].empty())
					_ptree["values"] += t.token_str();

				else
					_ptree["values"][0] += t.token_str();

				break;
			}

			currentState = newState;
		}
	}

	cout << currentState << endl;
	if (!_ptree.contains("where"))
	{
		_ptree["where"] += "no";
	}

	if (currentState != -1) {
		_failed = false;
		return true;
	}
	else {
		_failed = true;
		_ptree = MMap<string, string>();
		return false;
	}
}

void Parser::buildKeywordList()
{
	_keywords.insert("select", SELECT);
	_keywords.insert("*", STAR);
	_keywords.insert("from", FROM);
	_keywords.insert("where", WHERE);
	_keywords.insert("make", MAKE);
	_keywords.insert("create", CREATE);
	_keywords.insert(",", COMMA);
	_keywords.insert("table", TABLE);
	_keywords.insert("fields", FIELDS);
	_keywords.insert("field", FIELD);
	_keywords.insert("insert", INSERT);
	_keywords.insert("into", INTO);
	_keywords.insert("values", VALUES);
	_keywords.insert("batch", BATCH);
	_keywords.insert("drop", DROP);

}

string Parser::toLower(const string& str)
{
	string ans;
	for (int i = 0; i < str.size(); i++) {
		if (isalpha(str[i])) {
			ans += tolower(str[i]);
		}
		else {
			ans += str[i];
		}
	}

	return ans;
}

MMap<string, string> Parser::parseTree()
{
	return _ptree;
}

bool Parser::fail()
{
	return !_failed;
}
