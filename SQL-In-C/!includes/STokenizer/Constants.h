#ifndef CONSTANTS_H
#define CONSTANTS_H

enum {
	MAX_COLUMNS = 129,	//Max number of columns in _table (represents how many
						//ascii characters on ascii table).
	MAX_ROWS = 50,		//Max number of rows in _table (represents the number
						//of states in the state machine).
	MAX_BUFFER = 100000,	//Max input string length.

	SUCCESS_COL = 128,

	//--- Token Types ---
	UNKNOWN_TOKEN = -1,	
	ALPHA_TOKEN = 0,
	SPACE_TOKEN = 1,
	NUMBER_TOKEN = 2,
	PUNCTUATION_TOKEN = 3
};

#endif // !CONSTANTS_H
