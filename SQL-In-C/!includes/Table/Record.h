#ifndef RECORD_H
#define RECORD_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

class Record {
public:
    //when you construct a Record, it's either empty or it
    //  contains a word
    Record() :  _numFields(0) {
        _record[0][0] = NULL;
    }

    Record(const vector<string>& v) {
        for (int i = 0; i < MAX_ROWS; i++) {
            _record[i][0] = NULL;
        }
        for (int i = 0; i < v.size(); i++) {
            strcpy_s(_record[i], v[i].c_str());
        }
        _numFields = v.size();
    }

    vector<string> getRecord() {
        vector<string> v;

        for (int i = 0; i < MAX_ROWS; i++) {
            v.push_back(static_cast<string>(_record[i]));
        }

        return v;
    }

    long write(fstream& outs);              //returns the record number
    long read(fstream& ins, long _recno, int numFields);    //returns the number of bytes
                                            //      read = MAX, or zero if
                                            //      read passed the end of file


    friend ostream& operator<<(ostream& outs,
        const Record& r);

private:
    static const int MAX_ROWS = 20, MAX_COLS = 50;
    int _numFields;
    char _record[MAX_ROWS][MAX_COLS];
};

//[    |    |     |    |    |     |]
//-------------------------------------------------

//utility functions
bool file_exists(const char filename[]);
void open_fileRW(fstream& f, const char filename[]) throw(char*);
void open_fileW(fstream& f, const char filename[]);


#endif // RECORD_H
