#ifndef DEQUEUE_H
#define DEQUEUE_H

#include <iostream>
#include "../Linked List Functions/Linked_List_Functions.h"

template<typename T>
class Dequeue
{
public:
	class Iterator {
	public:
		friend class Dequeue;

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
	Dequeue() :_head(nullptr), _tail(nullptr) {}

	//Big Three
	~Dequeue();
	Dequeue(const Dequeue<T>& other);
	Dequeue<T>& operator =(const Dequeue& rhs);

	//Size Function
	int Size();

	//Iterator Functions
	Dequeue<T>::Iterator Begin();
	Dequeue<T>::Iterator End();

	//Insertion Functions
	Dequeue<T>::Iterator PushFront(T item);
	Dequeue<T>::Iterator PushBack(T item);

	//Removal Functions
	T PopFront();
	T PopBack();

	//Empty Function
	bool Empty();

	//Accessor Function
	T Front();

	//Output Function / Operator
	ostream& Print(ostream& outs = cout) {
		return print_list(_head, outs);
	}
	friend ostream& operator <<(ostream& outs, const Dequeue& q) {
		return print_list(q._head, outs);
	}

private:
	Node<T>* _head;
	Node<T>* _tail;
};

//------------------------------------------
//Big Three Functions
//------------------------------------------

template<typename T>
Dequeue<T>::~Dequeue()
{
	delete_all(_head);
	_head = _tail = nullptr;
}

template<typename T>
Dequeue<T>::Dequeue(const Dequeue<T>& other)
{
	_head = copy_list(other._head);
	_tail = _head;

	if (_tail != nullptr) {

		while (_tail->_next != nullptr) {
			_tail = _tail->_next;
		}

	}
}

template<typename T>
Dequeue<T>& Dequeue<T>::operator=(const Dequeue& rhs)
{
	if (rhs._head == _head) {
		return *this;
	}

	delete_all(_head);
	_tail = nullptr;

	_head = copy_list(rhs._head);
	_tail = _head;

	if (_tail != nullptr) {

		while (_tail->_next != nullptr) {
			_tail = _tail->_next;
		}

	}

	return *this;
}

//------------------------------------------
//Size Function
//------------------------------------------

template<typename T>
int Dequeue<T>::Size()
{
	int size = 0;

	Node<T>* walker = _head;

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
typename Dequeue<T>::Iterator Dequeue<T>::Begin()
{
	return Dequeue<T>::Iterator(_head);
}

template<typename T>
typename Dequeue<T>::Iterator Dequeue<T>::End()
{
	return Dequeue<T>::Iterator(_tail);
}

//------------------------------------------
//Push Function
//------------------------------------------

template<typename T>
typename Dequeue<T>::Iterator Dequeue<T>::PushFront(T item)
{
	if (Empty()) {
		insert_head(_head, item);
		_tail = _head;
	}
	else {
		insert_head(_head, item);
	}

	return Dequeue<T>::Iterator(_head);
}

template<typename T>
typename Dequeue<T>::Iterator Dequeue<T>::PushBack(T item)
{
	if (Empty()) {
		insert_head(_head, item);
		_tail = _head;
	}
	else {
		_tail = insert_after(_head, _tail, item);
	}

	return Dequeue<T>::Iterator(_tail);
}

//------------------------------------------
//Pop Function
//------------------------------------------

template<typename T>
T Dequeue<T>::PopFront()
{
	assert(!Empty());
	T item = delete_head(_head);

	if (_head == nullptr)
		_tail = nullptr;

	return item;
}

template<typename T>
T Dequeue<T>::PopBack()
{
	assert(!Empty());

	Node<T>* temp = _tail->_prev;

	T item = delete_head(_tail);

	_tail = temp;

	if (_tail != nullptr)
		_tail->_next = nullptr;
	else
		_head = _tail;

	return item;
}\
//------------------------------------------
//Empty Function
//------------------------------------------

template<typename T>
bool Dequeue<T>::Empty()
{
	return isEmpty(_head);
}

//------------------------------------------
//Accessor Function
//------------------------------------------

template<typename T>
T Dequeue<T>::Front()
{
	assert(!Empty());
	return _head->_item;
}

#endif // !DEQUEUE_H
