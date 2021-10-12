#ifndef RECORD_H
#define RECORD_H
#include <iostream>
#include <iomanip>
using namespace std;

template<typename T>
struct Record
{
    int _key;   //Integer value dictating a records location in the Hashtable.
    T _value;   //Value in the HashTable

    Record(int k = 0, T v = T());

                //NOTE: All comparisons are done only using the key.

    template<typename U>
    friend bool operator ==(const Record& left, const Record& right);

    template<typename U>
    friend bool operator >=(const Record& left, const Record& right);

    template<typename U>
    friend bool operator <=(const Record& left, const Record& right);

    template<typename U>
    friend bool operator >(const Record& left, const Record& right);

    template<typename U>
    friend bool operator <(const Record& left, const Record& right);

    template<typename U>
    friend ostream& operator <<(ostream& outs, const Record& print_me);
};


template<typename T>
Record<T>::Record(int k, T v) : _key(k), _value(v) {}

template<typename U>
bool operator==(const Record<U>& left, const Record<U>& right)
{
    return left._key == right._key;
}

template<typename U>
bool operator>=(const Record<U>& left, const Record<U>& right)
{
    return !(left < right);
}

template<typename U>
bool operator<=(const Record<U>& left, const Record<U>& right)
{
    return !(left > right);
}

template<typename U>
bool operator>(const Record<U>& left, const Record<U>& right)
{
    return left._key > right._key;
}

template<typename U>
bool operator<(const Record<U>& left, const Record<U>& right)
{
    return left._key < right._key;
}

template<typename U>
ostream& operator<<(ostream& outs, const Record<U>& print_me)
{
    outs << setfill('0') << setw(4) << print_me._key << ":" << setw(4) << print_me._value;
    return outs;
}
#endif // !RECORD_H



