#ifndef INFO_H
#define INFO_H
#include <iostream>
using namespace std;

template <typename T>
struct Info {
    T _item;    //The item being stored.
    int _priority;  //The priority of the item.
    int _timeStamp; //The time stamp of when the item was inserted.

    //Constructors

    Info();
    Info(T i, int p, int t);

    //Output Operator

    friend ostream& operator <<(ostream& outs, const Info<T>& print_me) {
        outs << "{ " << print_me._item << ", " << print_me._priority
            << ", " << print_me._timeStamp << " }";

        return outs;
    }

    //Comparison Operators

            //NOTE: If the priorities of two items are the same, then the time
            //stamp will be used instead.

    bool friend operator ==(const Info<T>& lhs, const Info<T>& rhs) {
        return lhs._priority == rhs._priority;
    }
    bool friend operator >=(const Info<T>& lhs, const Info<T>& rhs) {
        return !(lhs < rhs);
    }

    bool friend operator <=(const Info<T>& lhs, const Info<T>& rhs) {
        return !(lhs > rhs);
    }

    bool friend operator >(const Info<T>& lhs, const Info<T>& rhs) {
        if (lhs._priority == rhs._priority)
            return lhs._timeStamp < rhs._timeStamp;

        return lhs._priority > rhs._priority;
    }

    bool friend operator <(const Info<T>& lhs, const Info<T>& rhs) {
        if (lhs._priority == rhs._priority)
            return lhs._timeStamp > rhs._timeStamp;

        return lhs._priority < rhs._priority;
    }
};

template<typename T>
Info<T>::Info() : _item(T()), _priority(0), _timeStamp(0) {}

template<typename T>
Info<T>::Info(T i, int p, int t) : _item(i), _priority(p), _timeStamp(t) {}

#endif // !INFO_H
