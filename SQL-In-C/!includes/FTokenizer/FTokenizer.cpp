#include "FTokenizer.h"

FTokenizer::FTokenizer(char* fname): _pos(0), _blockPos(0), _more(true)
{
	_f.open(fname);
			//Opens the file with the name "fname".

	get_new_block();
			//Initializes the STokenizer object with values read from the file.
}
FTokenizer::~FTokenizer()
{
	_f.close();
}
SToken FTokenizer::next_token()
{
	SToken t;

	_stk >> t;

	return t;
}
bool FTokenizer::more()
{
	if (_stk.done() && _f.eof()) {
		_more = false;
	}

	return _more;
}
int FTokenizer::pos()
{
	return _pos;
}
int FTokenizer::block_pos()
{
	return _blockPos;
}
bool FTokenizer::get_new_block()
{
	if (_f.eof() || _stk.more()) {
		return false;
	}


	char line[MAX_BUFFER];

	_f.read(line, MAX_BUFFER);

	_pos++;

	_stk.set_string(line);
}

FTokenizer& operator>>(FTokenizer& f, SToken& t)
{
	f.get_new_block();

	t = f.next_token();

	return f;
}
