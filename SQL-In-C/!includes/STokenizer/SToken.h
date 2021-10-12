#ifndef STOKEN_H
#define STOKEN_H
#include <iostream>
#include <string>
#include <iomanip>
#include "Constants.h"
using namespace std;


class SToken
{
public:
    //Constructors

    SToken();
    SToken(string str, int type);

    //Output Operator
    friend ostream& operator <<(ostream& outs, const SToken& t);
    friend bool operator ==(const SToken& lhs, const SToken& rhs);

    //Accessor Functions
    int type();
    string type_string() const;
    string token_str() const;

private:
    string _token;  //The string of the SToken.
    int _type;      //The type of the SToken.
};

#endif // !STOKEN_H
