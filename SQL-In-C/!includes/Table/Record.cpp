#include "record.h"

bool file_exists(const char filename[]) {
    const bool debug = false;

    fstream ff;

    ff.open(filename,
        std::fstream::in | std::fstream::binary);

    if (ff.fail()) {
        if (debug) cout << "file_exists(): File does NOT exist: " << filename << endl;
        return false;
    }

    if (debug) cout << "file_exists(): File DOES exist: " << filename << endl;

    ff.close();

    return true;
}

void open_fileRW(fstream& f, const char filename[]) throw(char*) {
    const bool debug = false;
            //openning a nonexistent file for in|out|app causes a fail()
            //  so, if the file does not exist, create it by openning it for
            //  output:

    if (!file_exists(filename)) {

        //create the file

        f.open(filename, std::fstream::out | std::fstream::binary);

        if (f.fail()) {

            cout << "file open (RW) failed: with out|" << filename << "]" << endl;
            throw("file RW failed  ");

        }
        else {

            if (debug) cout << "open_fileRW: file created successfully: " << filename << endl;

        }
    }
    else {

        f.open(filename,
            std::fstream::in | std::fstream::out | std::fstream::binary);

        if (f.fail()) {

            cout << "file open (RW) failed. [" << filename << "]" << endl;
            throw("file failed to open.");

        }
    }
}

void open_fileW(fstream& f, const char filename[]) {
    //ONLY OPENS THE FILE TO GET INFO, NOT TO WRITE INTO THE FILE

    f.open(filename,
        std::fstream::in | std::fstream::out | std::fstream::binary);

    if (f.fail()) {
        cout << "file open failed: " << filename << endl;
        throw("file failed to open.");
    }
}

long Record::write(fstream& outs) {
    //write to the end of the file.

    outs.seekg(0, outs.end);

    long pos = outs.tellp();    //retrieves the current position of the
                                //      file pointer

    outs.write(&_record[0][0], sizeof(_record));

    return pos / sizeof(_record);  //record number
}

long Record::read(fstream& ins, long _recno, int numFields) {
    _numFields = numFields;
    long pos = _recno * sizeof(_record);

    ins.seekg(pos, ios_base::beg);

    ins.read(&_record[0][0], sizeof(_record));

            //don't you want to mark the end of  the cstring with null?
            //_record[] => [zero'\0'trash trash trash trash]
            //don't need the null character, but for those of us with OCD and PTSD:

    return ins.gcount();

}
ostream& operator<<(ostream& outs,
    const Record& r) {

    for (int i = 0; i < r._numFields; i++) {

        outs << left << setw(15) << r._record[i] << "|";

    }

    return outs;
}
