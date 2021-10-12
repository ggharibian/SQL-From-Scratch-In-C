#ifndef NODE_H
#define NODE_H
#include <iostream>
using namespace std;

template<typename T>
struct Node {

	T _item;
	Node<T>* _next;
	Node<T>* _prev;

	Node(const T& item = T(), Node<T>* prev = nullptr, Node<T>* next = nullptr): _item(item), _next(next), _prev(prev){}
	template<typename U>
	friend ostream& operator <<(ostream& outs, const Node<U>& n);

};

template<typename U>
ostream& operator<<(ostream& outs, const Node<U>& n)
{
	outs << "[" << n._item << "]->";
	return outs;
}

#endif // !NODE_H
