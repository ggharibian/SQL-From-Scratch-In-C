#ifndef PARSER_H
#define PARSER_H
#include "../STokenizer/STokenizer.h"
#include "../Maps/MultiMap.h"
#include "../Maps/Map.h"
#include "../Queue/Queue.h"
#include <string>
#include <iostream>
using namespace std;

class Parser {
public:
    Parser();
    Parser(const char input[]);
    void set_string(const char c[]);
    MMap<string, string> parseTree();
    bool fail();
private:
    enum {
        ZERO,
        SELECT,
        FROM,
        WHERE,
        LAST,
        FIRST,
        CREATE,
        STAR,
        SYMBOL,
        MAKE,
        COMMA,
        TABLE,
        FIELD,
        QUOTE,
        INSERT,
        INTO,
        VALUES,
        FIELDS,
        BATCH,
        GREATERTHAN,
        LESSTHAN,
        DROP,

        MAX_ROWS_P = 30,
        MAX_COLS_P = 50,

        SUCCESS = MAX_COLS_P - 1
        

    };

    Queue<SToken> _inputq;
    MMap<string, string> _ptree;
    Map<string, int> _keywords;
    int _table[MAX_ROWS_P][MAX_COLS_P];
	STokenizer _stok;
    bool _failed;

    //Helper functions

    void mark_cell(int table[MAX_ROWS][MAX_COLS_P], int row, int word, int newState);

    void mark_cell_for_all(int table[MAX_ROWS][MAX_COLS_P], int row, int newState);

    void mark_success(int table[MAX_ROWS][MAX_COLS_P], int row);

    //create table for all the tokens we will recognize
    //                      (e.g. doubles, words, etc.)

    void make_table(int _table[][MAX_COLS_P]);

    int getColumn(SToken t);

    bool setParseTree();

    void buildKeywordList();

    string toLower(const string& str);
};

#endif // !PARSER_H
