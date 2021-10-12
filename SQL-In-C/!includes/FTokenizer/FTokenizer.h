#ifndef FTOKENIZER_H
#define FTOKENIZER_H
#include <iostream>
#include <fstream>
#include "../STokenizer/STokenizer.h"
using namespace std;
class FTokenizer
{
public:
    const int MAX_BLOCK = MAX_BUFFER;

    FTokenizer(char* fname);    //Constructor

    ~FTokenizer();      //Closes the file after the program has finished.

    SToken next_token(); //Returns the next SToken from the file.

    bool more();        //returns the current value of _more

    int pos();          //returns the value of _pos

    int block_pos();     //returns the value of _blockPos

    friend FTokenizer& operator >> (FTokenizer& f, SToken& t);

    bool get_new_block(); //gets the new block from the file
    ifstream _f;   //file being tokenized
    STokenizer _stk;     //The STokenizer object to tokenize current block
    int _pos;           //Current position in the file
    int _blockPos;      //Current position in the current block
    bool _more;         //false if last SToken of the last block
                        //  has been processed and now we are at
                        //  the end of the last block.
private:
    
};

#endif // !FTOKENIZER_H
