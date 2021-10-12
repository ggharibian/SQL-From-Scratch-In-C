#ifndef STACK_H
#define STACK_H
#include <iostream>
#include "../Linked List Functions/Linked_List_Functions.h"

template<typename T>
class Stack {

public:
	class Iterator {
	public:
		friend class Stack;

		Iterator(Node<T>* ptr = nullptr) : _ptr(ptr) {}

		Iterator Next() {
			return Iterator(_ptr->_next);
		}

		Iterator Prev() {
			return Iterator(_ptr->_prev);
		}

		Node<T>& operator *() {	//Accesses the object at this location in
								//the Stack.
			assert(_ptr);
			return *_ptr;
		}

		const Node<T> operator *() const {
			assert(_ptr);
			return *_ptr;
		}

		Node<T>* operator ->() {	//Accesses the elements 
									//of the Object at this
									//Iterator.
			assert(_ptr);
			return _ptr;
		}

		const Node<T>* operator ->() const {
			assert(_ptr);
			return _ptr;
		}

		friend Iterator operator ++(Iterator& it, int unused) {
			//prefix

			Iterator old;
			//Holds the old value to return at the end.
			old = it;
			it = it.Next();
			return old;
		}

		Iterator& operator ++() {
			//postfix

			*this = (*this).Next();
			return *this;
		}

		friend Iterator operator --(Iterator& it, int unused) {
			//prefix

			Iterator old;
			//Holds the old value to return at the end.
			old = it;
			it = it.Prev();
			return old;
		}

		Iterator& operator --() {
			//postfix

			*this = (*this).Prev();
			return *this;
		}

		friend bool operator !=(const Iterator& left, const Iterator& right) {
			return left._ptr != right._ptr;
		}

	private:
		Node<T>* _ptr; //Traces a Node location in a Stack object.
	};

	//Constructor
    Stack() :_top(nullptr) {}

	//Big Three
    ~Stack();
    Stack(const Stack<T>& other);
    Stack<T>& operator =(const Stack<T>& rhs);

	//Size
    int Size();

	//Iterator Functions
	Stack<T>::Iterator Begin();

	//Push Function
    Stack<T>::Iterator Push(T item);

	//Pop Function
    T Pop();

	//Accessor Function
    T Top();

	//Empty Function
    bool Empty();

	//Output Function / Operator
	ostream& Print(ostream& outs = cout) {
		return print_list(_top, outs);
	}
    friend ostream& operator << (ostream& outs, const Stack& s) {
        return print_list(s._top, outs);
    }
private:
    Node<T>* _top;
};

//------------------------------------------
//Big Three Functions
//------------------------------------------

template<typename T>
Stack<T>::~Stack()
{
    delete_all(_top);
}

template<typename T>
Stack<T>::Stack(const Stack<T>& other)
{
    _top = copy_list(other._top);
}

template<typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& rhs)
{
    if (_top == rhs._top) {
        return *this;
    }

	delete_all(_top);

	_top = copy_list(rhs._top);

    return *this;
}

//------------------------------------------
//Size Function
//------------------------------------------

template<typename T>
int Stack<T>::Size()
{
    int size = 0;

    Node<T>* walker = _top;

    while (walker != nullptr) {
        size++;
        walker = walker->_next;
    }

    return size;
}

//------------------------------------------
//Iterator Function
//------------------------------------------

template<typename T>
typename Stack<T>::Iterator Stack<T>::Begin()
{
	return Stack<T>::Iterator(_top);
}

//------------------------------------------
//Push Function
//------------------------------------------

template<typename T>
typename Stack<T>::Iterator Stack<T>::Push(T item)
{
    return Stack<T>::Iterator(insert_head(_top, item));
}

//------------------------------------------
//Pop Function
//------------------------------------------

template<typename T>
T Stack<T>::Pop()
{
    return delete_head(_top);
}

//------------------------------------------
//Accessor Function
//------------------------------------------

template<typename T>
T Stack<T>::Top()
{
    assert(!Empty());
    return _top->_item;
}

//------------------------------------------
//Empty Function
//------------------------------------------

template<typename T>
bool Stack<T>::Empty()
{
    return isEmpty(_top);
}

#endif // !STACK_H