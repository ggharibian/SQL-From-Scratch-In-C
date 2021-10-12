#ifndef TABLE_H
#define TABLE_H
#include "record.h"
#include "../../!includes/Maps/MultiMap.h"
#include "../../!includes/Maps/Map.h"
#include "../../!includes/ShunttingYard/RPN.h"
#include "../../!includes/ShunttingYard/ShunttingYard.h"
#include "../../!includes/ShunttingYard/Tokenizer.h"
#include <iomanip>

class Table {
public:

    //ctors
    Table();
    Table(const string& name, const vector<string> fields);
    Table(const string& name);


    void insert_into(vector<string> v);

    //select
    Table select_all();
    //Table selectRows(vector<string> v);
    Table select_conditional(vector<string> condition);
    Table select(vector<string> fields, vector<long> recordNumbers = vector<long>());

    //set and get
    vector<string> getFields();

    //ostream operator
    friend ostream& operator <<(ostream& outs, const Table& t) {
        for (int i = 0; i < t._field_names.size(); i++) {
            cout << left << setw(15) << t._field_names[i] << "|";
        }
        cout << endl;

        fstream file;
        Record r;
        open_fileW(file, (t._table_name + ".bin").c_str());

        int recno = 0;
        r.read(file, recno++, t._field_names.size());

        while (!file.eof()) {
            outs << r << endl;
            r.read(file, recno++, t._field_names.size());
        }

        return outs;
    }
private:
    //private vars
    string _table_name;

    vector<MMap<string, long> > _indices;   
                               //indices
                               //each has an index and each index holds a type
                               //holds a type of data(last,first) that has all
                               //of the last names from the table

    vector<string> _field_names;

    Map<string, int> _field_names_map;

    bool _empty;

    int _last_record_num;

    static int _serialNumber;

    //helper function
    void reindex();
    void set_fields(vector<string> fields);
};

#endif // TABLE_H
