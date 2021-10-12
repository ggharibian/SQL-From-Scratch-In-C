#ifndef DOUBLEHASH_H
#define DOUBLEHASH_H
#include "../AVL/AVL.h"
#include <cassert>
using namespace std;

template<typename Record>
class DoubleHash
{
public:

	static const int CAPACITY = 811;

	DoubleHash();

	void insert(const Record& value);

	void remove(int key);

	bool isPresent(int key);

	bool find(int key, Record& result);

	int size();

	template<typename U>
	friend ostream& operator <<(ostream& outs, const DoubleHash<U>& d);
private:

	static const int NEVER_USED = -1;

	static const int PREVIOUSLY_USED = -2;

	Record data[CAPACITY];
	int _used;

	int hash1(int key) const;
	int hash2(int key) const;
	int nextIndex(int key, int index);
	bool findIndex(int key, int& index);

	bool neverUsed(int index) const;
	bool isVacant(int index) const;
};

template<typename T>
DoubleHash<T>::DoubleHash()
{
	_used = 0;

	for (int i = 0; i < CAPACITY; i++) {
		data[i]._key = NEVER_USED;
	}
}

template<typename Record>
void DoubleHash<Record>::insert(const Record& value)
{
	assert(value._key >= 0);

	int index;

	if (!findIndex(value._key, index)) {
		assert(size() < CAPACITY);

		int hash2Value = hash2(value._key);

		while (!isVacant(index)) {
			index = nextIndex(value._key, index);
		}
		_used++;
	}

	data[index] = value;
}

template<typename Record>
void DoubleHash<Record>::remove(int key)
{
	assert(key >= 0);
	int index;

	if (findIndex(key, index)) {
		data[index]._key = PREVIOUSLY_USED;
		_used--;
	}
}

template<typename Record>
bool DoubleHash<Record>::isPresent(int key)
{
	assert(key >= 0);

	int index;

	return findIndex(key, index);
}

template<typename Record>
bool DoubleHash<Record>::find(int key, Record& result)
{
	assert(key >= 0);

	int index;

	if (findIndex(key, index)) {
		result = data[index];
		return true;
	}

	return false;
}

template<typename Record>
int DoubleHash<Record>::size()
{
	return _used;
}

#endif // !DOUBLEHASH_H

template<typename Record>
inline int DoubleHash<Record>::hash1(int key) const
{
	return key % CAPACITY;
}

template<typename Record>
inline int DoubleHash<Record>::hash2(int key) const
{
	return 1 + key % (CAPACITY - 2);
}

template<typename Record>
inline int DoubleHash<Record>::nextIndex(int key, int index)
{
	return (index + hash2(key)) % CAPACITY;
}

template<typename Record>
bool DoubleHash<Record>::findIndex(int key, int& index)
{
	int count = 0;

	index = hash1(key);

	while ((count < CAPACITY) && (!neverUsed(index)) && (data[index]._key != key))
	{
		++count;
		index = nextIndex(key, index);
	}

	return data[index]._key == key;
}

template<typename Record>
inline bool DoubleHash<Record>::neverUsed(int index) const
{
	return data[index]._key == NEVER_USED;
}

template<typename Record>
inline bool DoubleHash<Record>::isVacant(int index) const
{
	return data[index]._key < 0;
}

template<typename U>
inline ostream& operator<<(ostream& outs, const DoubleHash<U>& d)
{
	for (int i = 0; i < d.CAPACITY; i++) {

		outs << "[" << setfill('0') << setw(3) << i << "] ";

		if (!d.neverUsed(i)) {

			if (d.isVacant(i))
				outs << "- - - - - -";

			else {
				outs << d.data[i] << "(" << setw(3) << d.hash1(d.data[i]._key) << ")";
				if (d.hash1(d.data[i]._key) != i)
					outs << " *";
			}

		}
		outs << endl;
	}

	return outs;
}
