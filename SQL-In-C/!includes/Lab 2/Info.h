#ifndef INFO_H
#define INFO_H
#include <string>
#include "..\..\..\!includes\PQueue\Info.h"
using namespace std;

template<typename T>
struct Info {
	T _item;	//Item to stored in the heap
	int _priority;	//The priority level of the item

	Info(T item = T(), int priority = 1) : _item(item), _priority(priority) {	}

			//Note: All functions for the structure are based off the priority
			//of the items

	bool friend operator ==(const Info& i1, const Info& i2) {
		i1._priority == i2._priority;
	}
	bool friend operator >=(const Info& i1, const Info& i2) {
		return !(i1 < i2);
	}

	bool friend operator <=(const Info& i1, const Info& i2) {
		return !(i1 > i2);
	}

	bool friend operator >(const Info& i1, const Info& i2) {
		return i1._priority > i2._priority;
	}

	bool friend operator <(const Info& i1, const Info& i2) {
		return i1._priority < i2._priority;
	}

	inline ostream& operator<<(ostream& outs, const Info<T>& print_me)
	{
		// TODO: insert return statement here
	}

	bool friend operator ==(const Info<T>& lhs, const Info<T>& rhs) {
		lhs._priority == rhs._priority;
	}
	bool friend operator >=(const Info<T>& lhs, const Info<T>& rhs) {
		return !(lhs < rhs);
	}

	bool friend operator <=(const Info<T>& lhs, const Info<T>& rhs) {
		return !(lhs > rhs);
	}

	bool friend operator >(const Info<T>& lhs, const Info<T>& rhs) {
		return lhs._priority > rhs._priority;
	}

	bool friend operator <(const Info<T>& lhs, const Info<T>& rhs) {
		return lhs._priority < rhs._priority;
	}
};

#endif // !INFO_H
