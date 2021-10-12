#ifndef LINKED_LIST_FUNCTIONS_H
#define LINKED_LIST_FUNCTIONS_H
#include <cassert>
#include "Node.h"
#include <iostream>
using namespace std;

//initializes head to NULL
template <typename T>
Node<T>* init_head(Node<T>*& head);

//deletes all the nodes in the list
template<typename T>
void delete_all(Node<T>*& head);

//true if head is NULL, false otherwise.
template <typename T>
bool isEmpty(const Node<T>* head);

//makes a copy of the list, returns a pointer to the last node:
template <typename T>
Node<T>* copy_list(const Node<T>* head);

//insert at the beginning of the list:
template <typename T>
Node<T>* insert_head(Node<T>*& head, T item);

//insert_after: if after is NULL, inserts at head
template <typename T>
Node<T>* insert_after(Node<T>*& head, Node<T>* after, const T& item);

//delete the node at the head of the list, reuturn the item:
template <typename T>
T delete_head(Node<T>*& head);

//print the list and return outs
template<typename T>
ostream& print_list(const Node<T>* head, ostream& outs = cout);

//================================================================

template<typename T>
Node<T>* init_head(Node<T>*& head)
{
	head = nullptr;
			//head is initialized to nullptr;

	return head;
}

template<typename T>
bool isEmpty(const Node<T>* head)
{
	return head == nullptr;
			//Checks if head is nullptr
}

template<typename T>
Node<T>* insert_head(Node<T>*& head, T item)
{
	head = new Node<T>(item, nullptr, head);
			//Creates a new head value

	if (head->_next != nullptr)
		head->_next->_prev = head;
			//If a node exists after head, it sets that Node's prev to head.

	return head;
}

template<typename T>
Node<T>* insert_after(Node<T>*& head, Node<T>* after, const T& item)
{
	Node<T>* temp = head;

	while (temp != after) {
		assert(temp != nullptr);
				//Will assert if after is not in head.

		temp = temp->_next;
	}	//Loop Iterates through linked list

	temp->_next = new Node<T>(item, temp, temp->_next);
			//Creates the new Node and sets it's next and prev values.

	if (temp->_next->_next != nullptr)
		temp->_next->_next->_prev = temp->_next;
			//If a node exists after "temp", then that Node's previous is set
			//to temp.

	return temp->_next;
}

template<typename T>
T delete_head(Node<T>*& head)
{
	assert(!isEmpty(head));
			//Asserts if list is empty.

	T item = head->_item;
			//Item stored for return.

	Node<T>* temp = head;

	head = head->_next;
			//Head is set to the next node after (which is now the new head)

	if (head != nullptr)
		head->_prev = nullptr;
			//If the list isn't empty, the new head's prev is set to nullptr.

	delete temp;
			//Old head is deleted.

	return item;
}

template<typename T>
void delete_all(Node<T>*& head)
{
	while (!isEmpty(head))
		delete_head(head);
}

template<typename T>
Node<T>* copy_list(const Node<T>* head)
{
	if (head == nullptr)
		return nullptr;
			//If the list is empty then no copying is required.

	Node<T>* newList = new Node<T>(head->_item);
			//Start of the new list.

	Node<T>* walkerHead = head->_next;
			//Walker for old list.

	Node<T>* walkerNewList = newList;
			//Walker for the new list.

	while (walkerHead != nullptr) {
		walkerNewList->_next = new Node<T>(walkerHead->_item, walkerNewList,
			nullptr);
		walkerHead = walkerHead->_next;
		walkerNewList = walkerNewList->_next;
	}	//Loop will create a new node for every value in the old list int the same
		//order.

	walkerNewList->_next = nullptr;
			//End is set to nullptr.

	return newList;
}

template<typename T>
ostream& print_list(Node<T>* head, ostream& outs)
{
	Node<T>* temp = head;

	outs << "H->";

	while (temp != nullptr) {
		outs << *temp;
		temp = temp->_next;
	}	//Iterates through and prints entire list.

	outs << "|||";

	return outs;
}


#endif // !LINKED_LIST_FUNCTIONS_H