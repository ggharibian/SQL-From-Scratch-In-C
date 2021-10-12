#ifndef CHAINHASH_H
#define CHAINHASH_H
#include "../oned/oned.h"
#include "../AVL/AVL.h"
template<typename Record>
class ChainHash
{
public:

	static const int TABLE_SIZE = 17;

	//Constructor

	ChainHash();

	//Insertion function

	void insert(const Record& value);

	//Removal Function

	void remove(unsigned long key);

	//Search Functions

	bool find(unsigned long key, Record& result);

	bool isPresent(unsigned long key);

	//Accessor Function

	int size();

	//Output Operator

	template<typename U>
	friend ostream& operator <<(ostream& outs, const ChainHash<U>& c);

	//Other Function(s)

	Record* getList(int& size);

private:

	int numRecords;	//Number of elements in the Hashtable.
	AVL<Record> data[TABLE_SIZE];
					//Array of AVL trees holding items in our Hash.

	int hash(unsigned long key);
			//Returns the array index of a key by hashing it
};

template<typename Record>
ChainHash<Record>::ChainHash() : numRecords(0) {}

template<typename Record>
void ChainHash<Record>::insert(const Record& value)
{
	if (data[hash(value._key)].insert(value))
		numRecords++;
}

template<typename Record>
inline void ChainHash<Record>::remove(unsigned long key)
{
	TreeNode<Record>* useless;
			//Useless pointer

	if (isPresent(key)) {
				//Checks if the key exists in the HashTable.

		data[hash(key)].erase(Record(key));
		numRecords--;

				//The key is removed from the hash and the size is decremented
	}
}

template<typename Record>
bool ChainHash<Record>::find(unsigned long key, Record& result)
{
	TreeNode<Record>* temp;

	if (data[hash(key)].search(Record(key), temp)) {
		result = temp->_item;
		return true;
	}		//If the key exists in the hash, the result is set to the item and
			//the function returns true.

	return false;
			//Otherwise, returns false.
}

template<typename Record>
bool ChainHash<Record>::isPresent(unsigned long key)
{
	TreeNode<Record>* useless;
			//Useless pointer

	return data[hash(key)].search(Record(key), useless);
			//returns whether the key exists in the hash.
}

template<typename Record>
inline int ChainHash<Record>::size()
{
	return numRecords;
			//Returns the number of records in the Hash.
}

template<typename Record>
Record* ChainHash<Record>::getList(int& size)
{
	int tempSize, numElements;
	Record* arr, *temp;

	size = 0;

	arr = new Record[size];

	for (int i = 0; i < TABLE_SIZE; i++) {

		temp = data[i].getTreeInorder(tempSize);

		if (tempSize > 0) {

			arr = reallocate<Record>(arr, size, size + tempSize);

			copy_list<Record>(arr + size - tempSize, temp, size, tempSize, tempSize);

		}

	}

	return arr;
}

template<typename Record>
int ChainHash<Record>::hash(unsigned long key)
{
	return static_cast<int>(key % TABLE_SIZE);
			//The key is hashed and returned.
}

#endif // !CHAINHASH_H

template<typename U>
inline ostream& operator<<(ostream& outs, const ChainHash<U>& c)
{
	for (int i = 0; i < c.TABLE_SIZE; i++) {
		outs << "[" << setfill('0') << setw(3) << i << "] ";

		c.data[i].printTreeInOrder(outs);

		outs << endl;
	}

	return outs;
}
