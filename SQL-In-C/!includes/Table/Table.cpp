#include "Table.h"

int Table::_serialNumber = 0;

Table::Table() {}

Table::Table(const string& name, const vector<string> fields): _table_name(name), _last_record_num(0), _empty(true)
{
	fstream file;

	file.open(_table_name + ".bin", std::ofstream::out | std::ofstream::trunc);
	file.close();

	open_fileRW(file, (name + ".bin").c_str());
	file.close();

	set_fields(fields);

	file.open(_table_name + "_fields.txt", std::ofstream::out | std::ofstream::trunc);
	file.close();

	open_fileRW(file, (name + "_fields.txt").c_str());

	if (!fields.empty()) {
		int i;

		for (i = 0; i < fields.size() - 1; i++) {
			file << fields[i] << endl;
		}

		file << fields[i];
	}

	file.close();
}

Table::Table(const string& name): _table_name(name) {
	fstream file;
	string field;
	vector<string> temp;

	open_fileW(file, (_table_name + "_fields.txt").c_str());   //opens txt file

	while (!file.eof()) {
		getline(file, field);
		temp.push_back(field);
	}

	set_fields(temp);   //set fields to vector
	reindex();

	file.close();
}

void Table::set_fields(vector<string> fields) {
	for (int i = 0; i < fields.size(); i++) {
		_field_names.push_back(fields[i]);
		_field_names_map[fields[i]] = i;
		_indices.push_back(MMap<string, long>());
	}
}
void Table::reindex() {
	fstream file;
	Record r;
	vector<string> temp;

	int recno = 0;

	open_fileRW(file, (_table_name + ".bin").c_str());

	r.read(file, recno, getFields().size());    //first record

	while (!file.eof()) {
		temp = r.getRecord();  // returns vector of strings

		 //push all record info into each indices multimap

		for (int i = 0; i < _indices.size(); i++) {
			_indices[i][temp[i]] += recno;
		}

		r.read(file, ++recno, getFields().size());    //first record
	}
}

void Table::insert_into(vector<string> v) {
	fstream f;

	_empty = false;

	open_fileRW(f, (_table_name + ".bin").c_str());

	Record r(v);

	_last_record_num = r.write(f);

	for (int i = 0; i < _indices.size(); i++) {
		_indices[i][v[i]] += _last_record_num;    //inserts into indices structures
	}

	f.close();
}

vector<string> Table::getFields() {
	return _field_names;
}

Table Table::select_all() {
	fstream file;
	Record r;

	string tempName = _table_name + to_string(_serialNumber++);

	vector<string> tempFieldNames = _field_names;

	open_fileRW(file, (_table_name + ".bin").c_str());

	int recno = 0;

	Table tempTable(tempName, tempFieldNames);

	r.read(file, recno++, getFields().size());

	while (!file.eof()) {
		Record temp_record = r;
		tempTable.insert_into(temp_record.getRecord());
		r.read(file, recno++, getFields().size());
	}

	file.close();

	return tempTable;
}

//Table Table::selectRows(vector<string> v)
//{
//	fstream file;
//	Record r;
//
//	string tempName = _table_name + to_string(_serialNumber++);
//
//	vector<string> tempFieldNames = _field_names;
//
//	open_fileRW(file, (_table_name + ".bin").c_str());
//
//	int recno = 0;
//
//	Table tempTable(tempName, tempFieldNames);
//
//	r.read(file, recno++, getFields().size());
//
//	while (!file.eof()) {
//		Record temp_record = r;
//		tempTable.insert_into(temp_record.getRecord());
//		r.read(file, recno++, getFields().size());
//	}
//
//	file.close();
//
//	return tempTable;
//}

Table Table::select_conditional(vector<string> condition) {
	Tokenizer t(condition);
	ShuntingYard s(t.getTokens());
	RPN r(s.postfix());

	return select(_field_names, r(_field_names_map, _indices));
}

//_indices[_field_names_map[fields[i]]];
Table Table::select(vector<string> fields, vector<long> recordNumbers)
{
	fstream file;
	Record r;

	string tempName = _table_name + to_string(_serialNumber++);

	vector<string> tempFieldNames = fields;

	open_fileRW(file, (_table_name + ".bin").c_str());

	Table tempTable(tempName, tempFieldNames);

	vector<string> tempRecords;

	for (int i = 0; i < recordNumbers.size(); i++) {
		r.read(file, recordNumbers[i], getFields().size());

		for (int e = 0; e < fields.size(); e++) {

			tempRecords.push_back(r.getRecord()[_field_names_map[fields[e]]]);

		}

		tempTable.insert_into(tempRecords);
		tempRecords.clear();
	}

	file.close();

	return tempTable;
}
//Table::Table(const string& name, vector<string> fields): _name(name), _recordNumber(0), serialNumber(1)
//{
//	//Open the file
//	string temp;
//	fstream output;
//	fstream field_names;
//
//	set_fields(fields);
//
//	output.open(_name + ".bin", std::ofstream::out | std::ofstream::trunc);
//	output.close();
//
//	open_fileRW(output, (_name + ".bin").c_str());
//
//	output.open(_name + "_fields.txt", std::ofstream::out | std::ofstream::trunc);
//	output.close();
//
//	open_fileRW(field_names, (_name + "_fields.txt").c_str());
//
//	for (int i = 0; i < fields.size(); i++) {
//		field_names << fields[i] << endl;
//	}
//
//	output.close();
//	field_names.close();
//}
//
//Table::Table(const string& name): _name(name), _recordNumber(0), serialNumber(1)
//{
//	vector<string> tempV;
//	assert(file_exists((_name + ".bin").c_str()));
//
//	fstream f;
//	open_fileRW(f, (_name + ".bin").c_str());
//
//	fstream ffile;
//	open_fileRW(ffile, (_name + "_fields.txt").c_str());
//
//	string s;
//
//	while (!ffile.eof()) {
//		getline(ffile, s);
//		cout << s << endl;
//	}
//	
//
//}
//
//void Table::insert_into(vector<string> v)
//{
//	insert_into(Record(v));
//}
//
//void Table::insert_into(Record r)
//{
//	fstream f;
//
//	open_fileRW(f, (_name + ".bin").c_str());
//
//	_recordNumber = r.write(f);
//
//}
//
//Table Table::select_all() {
//	fstream f, tempStr;
//	open_fileRW(f, (_name + ".bin").c_str());
//
//	string tempName = _name + "_temp";
//	Map<string, int> tempFieldNames = _field_names;
//
//	tempStr.open(tempName + ".bin", std::ofstream::out | std::ofstream::trunc);
//	tempStr.close();
//
//	Table temp(tempName, getFields(_field_names));
//
//	Record r;
//
//	int numrecord = 0;
//
//	r.read(f, numrecord);
//
//	while (!f.eof()) {
//		numrecord++;
//		Record tempRecord = r;
//		temp.insert_into(tempRecord);
//		r.read(f, numrecord);
//	}
//
//	f.close();
//	return temp;
//}
//
//Table Table::selectSimpleCondition(vector<string> tokens)
//{
//	if (tokens[1] == "=") {
//		//return Table(tokens[0], vector<string>().push_back(tokens[2]));
//		return *this;
//	}
//}
//
//Table Table::select(vector<string> fields)
//{
//	fstream f;
//	Record r;
//
//	open_fileW(f, _name.c_str());
//	return *this;
//}
//
//vector<string> Table::getFields(Map<string, int> fieldNames)
//{
//	vector<string> f;
//
//	Map<string, int>::Iterator it = fieldNames.begin();
//
//	while (it != fieldNames.end()) {
//		f.push_back((*(it++)).key);
//	}
//
//	return f;
//
//}
//
//void Table::set_fields(vector<string> fields)
//{
//	for (int i = 1; i < fields.size() + 1; i++) {
//		_field_names[fields[i - 1]] = i;
//	}
//}
//
//vector<string> Table::getFields()
//{
//	vector<string> f;
//
//	Map<string, int>::Iterator it = _field_names.begin();
//
//	while (it != _field_names.end()) {
//		f.push_back((*(it++)).key);
//	}
//
//	return f;
//}

