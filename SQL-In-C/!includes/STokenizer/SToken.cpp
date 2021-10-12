#include "SToken.h"

//------------------------------------------
//Constructor
//------------------------------------------

SToken::SToken()
{
			//Everything is initialized to "zero" values.
	_token = "";
	_type = UNKNOWN_TOKEN;
}

SToken::SToken(string str, int type)
{
	_token = str;
	_type = type;
}

//------------------------------------------
//Accessor Functions
//------------------------------------------

int SToken::type()
{
			//Returns the type of the SToken.
	return _type;
}

string SToken::type_string() const
{
	switch (_type) {
			//Switch statement required for returning the corresponding string
			//output for a specific SToken type.

	case (ALPHA_TOKEN):

		return "ALPHA";

	case (SPACE_TOKEN):

		return "SPACE";

	case (NUMBER_TOKEN):

		return "NUMBER";

	case (PUNCTUATION_TOKEN):

		return "PUNCTUATION";

	default:

		return "UNKNOWN";
	};
}

string SToken::token_str() const
{
			//Returns the SToken's string value.
	return _token;
}

//------------------------------------------
//Output Operator
//------------------------------------------

ostream& operator<<(ostream& outs, const SToken& t)
{
			//Ouputs SToken in "|Hello|" format.
	outs << '|' << t.token_str() << '|';
	return outs;
}

bool operator==(const SToken& lhs, const SToken& rhs)
{
	return lhs.type_string() == rhs.type_string() && lhs.token_str() == rhs.token_str();
}
