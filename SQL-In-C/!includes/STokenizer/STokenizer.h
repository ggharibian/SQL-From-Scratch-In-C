#ifndef STOKENIZER_H
#define STOKENIZER_H
#include "Constants.h"
#include "SToken.h"
#include <string>
using namespace std;

class STokenizer
{
public:
    //Constructor

    STokenizer();
    STokenizer(const char str[]);

    //State Functions
    bool done();            //true: there are no more tokens
    bool more();            //true: there are more tokens
    //

    //Extraction Operator
    //---------------
    //extract one SToken (very similar to the way cin >> works)
    friend STokenizer& operator >> (STokenizer& s, SToken& t);

    //Mutator Function
    //set a new string as the input string
    void set_string(const char str[]);

private:

    //Helper functions

    void mark_cells(int table[MAX_ROWS][MAX_COLUMNS], int row, char from, char to, int newState);

    void mark_cells(int table[MAX_ROWS][MAX_COLUMNS], int row, string allChars, int newState);

    void mark_success(int table[MAX_ROWS][MAX_COLUMNS], int row);

    //create table for all the tokens we will recognize
    //                      (e.g. doubles, words, etc.)

    void make_table(int _table[][MAX_COLUMNS]);

    //extract the longest string that match
    //     one of the acceptable SToken types
    bool get_token(int start_state, SToken& SToken);

    int get_token_recursive(int start_state, string& SToken);


    //---------------------------------


    char _buffer[MAX_BUFFER];       //input string
    int _pos;                       //current position in the string
    static int _table[MAX_ROWS][MAX_COLUMNS];
};

#endif // !STOKENIZER_H
