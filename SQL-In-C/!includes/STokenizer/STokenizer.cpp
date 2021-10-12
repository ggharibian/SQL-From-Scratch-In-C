#include "STokenizer.h"
int STokenizer::_table[MAX_ROWS][MAX_COLUMNS];

//------------------------------------------
//Constructor
//------------------------------------------

STokenizer::STokenizer()
{
			//Starting at the beginning of the string
	_pos = 0;

			//The adjacency table is created and initialized.
	make_table(_table);

			//Note: Buffer is not initialized as no string has been inputted 
			//to the tokenizer.
}

STokenizer::STokenizer(const char str[])
{
	strncpy_s(_buffer, str, MAX_BUFFER);

			//Starting at the beginning of the string
	_pos = 0;

			//The adjacency table is created and initialized.
	make_table(_table);
}

//------------------------------------------
//State Functions
//------------------------------------------

bool STokenizer::done()
{
	return _pos == MAX_BUFFER || _buffer[_pos] == '\0';
}

bool STokenizer::more()
{
			//Returns true if _pos is not at the end of the string.
	return !done();
}

//------------------------------------------
//Mutator Function
//------------------------------------------

void STokenizer::set_string(const char str[])
{

	strncpy_s(_buffer, str, MAX_BUFFER - 1);

			//Position is reset to zero.
	_pos = 0;
}

//------------------------------------------
//Helper Functions
//------------------------------------------

void STokenizer::mark_cells(int table[MAX_ROWS][MAX_COLUMNS], int row, char from, char to, int newState)
{
	for (char current = from; current <= to; current++) {
				//Loop iterates over ever character value between the char "from" and char "to"

		table[row][static_cast<int>(current)] = newState;
				//For a given character, the next state location at a the 
				//current state is set to "newState"

	}
}

void STokenizer::mark_cells(int table[MAX_ROWS][MAX_COLUMNS], int row, string allChars, int newState)
{
	for (int currentIndex = 0; currentIndex < allChars.size(); currentIndex++) {
				//Loop iterates through every character value in the string

		table[row][static_cast<int>(allChars[currentIndex])] = newState;
				//For a given character, the next state location at a the 
				//current state is set to "newState"
	}
}

void STokenizer::mark_success(int table[MAX_ROWS][MAX_COLUMNS], int row)
{
	table[row][SUCCESS_COL] = 1;
}

void STokenizer::make_table(int _table[][MAX_COLUMNS])
{
	for (int i = 0; i < MAX_ROWS; i++) {
		for (int e = 0; e < MAX_COLUMNS; e++) {
					//All table values are initialized to -1 by default. 
					//Represents a failing state.

			_table[i][e] = -1;
		}
	}
			//All State tree's for alpha, space, number, and punctuation 
			//tokens are initialized here.

	//Alpha Tree
	mark_cells(_table, 0, 'A', 'Z', 1);
	mark_cells(_table, 0, 'a', 'z', 1);
	mark_cells(_table, 1, 'A', 'Z', 1);
	mark_cells(_table, 1, 'a', 'z', 1);
	mark_success(_table, 1);
	mark_success(_table, 0);

	//Space Tree
	mark_cells(_table, 0, ' ', ' ', 2);
	mark_cells(_table, 0, '	', '	', 2);
	mark_cells(_table, 2, ' ', ' ', 2);
	mark_cells(_table, 2, '	', '	', 2);
	mark_success(_table, 2);

	//Number Tree
	mark_cells(_table, 0, '0', '9', 3);
	mark_cells(_table, 3, '0', '9', 3);
	mark_cells(_table, 3, '.', '.', 6);
	mark_cells(_table, 6, '0', '9', 7);
	mark_cells(_table, 7, '0', '9', 7);
	mark_success(_table, 3);
	mark_success(_table, 7);

	//Punctuation Tree
	mark_cells(_table, 0, ",<.>/?;:'\"]}[{\\|+=_-)(*&^%$#@!", 4);
	mark_success(_table, 4);
}

bool STokenizer::get_token(int start_state, SToken& ST)
{

	string tok = "";

	int tokenType = get_token_recursive(start_state, tok);

	ST = SToken(tok, tokenType);

	return ST.token_str() == "UNKNOWN";

}

int STokenizer::get_token_recursive(int start_state, string& SToken)
{
	if (_buffer[_pos] >= 0 && _buffer[_pos] <= 127 && _table[start_state][static_cast<int>(_buffer[_pos])] != -1) {

		//cout << "FAIL STATE NOT REACHED \n======================" << endl;
		start_state = _table[start_state][static_cast<int>(_buffer[_pos])];
		//cout << "start_state: " << start_state << endl;
		SToken += _buffer[_pos];
		//cout << "SToken: " << SToken << endl;
		//cout << "_buffer[_pos]: " << static_cast<int>(_buffer[_pos]) << endl;
		_pos++;
		//cout << "_pos: " << _pos << endl;
		return get_token_recursive(start_state, SToken);
	}

	if (_buffer[_pos] < 0 && _buffer[_pos] > 127 || _table[start_state][SUCCESS_COL] == 1) {
		//cout << "REACHED SUCCESS STATE\n==================" << endl;
		//cout << "SToken: " << SToken << endl;
		//cout << "start_state: " << start_state << endl;
		switch (start_state) {

		case 1:
			//If the last state represents a ALPHA SToken.
			return ALPHA_TOKEN;

		case 2:
			//If the last state represents a SPACE SToken.
			return SPACE_TOKEN;

		case 3:
		case 7:
			//If the last state represents a NUMBER SToken.
			return NUMBER_TOKEN;

		case 4:
			//If the last state represents a PUNCTUATION SToken.
			return PUNCTUATION_TOKEN;

		default:
			//If the last state represents a UNKNOWN SToken.
			_pos++;
			return UNKNOWN_TOKEN;
		}
	}
	else {
		//cout << "_buffer[_pos]: " << static_cast<int>(_buffer[_pos]) << endl;
		//cout << "NOT REACHED SUCCESS STATE\n=========================" << endl;
		_pos--;
		//cout << "_pos: " << _pos << endl;
		SToken = SToken.substr(0, SToken.size() - 1);
		//cout << "SToken: " << SToken << endl;
	}
}

STokenizer& operator>>(STokenizer& s, SToken& t)
{
	s.get_token(0, t);
	return s;
}
