#ifndef BST_H
#define BST_H
#include <iostream>
#include <cassert>
#include "BST_Functions.h"
using namespace std;

template <typename T>
class BST {
public:

	//Constructor

	BST();
	BST(const T* sorted_list, int size = -1);

	//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

	//Big Three
	BST(const BST<T>& copy_me);
	BST<T>& operator =(const BST<T>& rhs);
	~BST();

	//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

	//Insertion Function
	void insert(const T& insert_me);

	//Deletion Functions
	void erase(const T& target);
	void clear();

	//Search Function
	bool search(const T& target, TreeNode<T>*& found_ptr);

	//Output Operator
	template<typename U>
	friend ostream& operator <<(ostream& outs, const BST<U>& tree);

	//Addition Operator
	BST<T>& operator +=(const BST<T>& rhs);
private:
	TreeNode<T>* root;
};

//------------------------------------------
//Constructor
//------------------------------------------

template<typename T>
BST<T>::BST() : root(nullptr) {}

//------------------------------------------
//Big Three Functions
//------------------------------------------

template<typename T>
BST<T>::BST(const T* sorted_list, int size) : root(tree_from_sorted_list(sorted_list, size)) {}

template<typename T>
BST<T>::BST(const BST<T>& copy_me)
{
	root = tree_copy<T>(copy_me.root);
			//A copy of the copy_me is assigned to root.
}

template<typename T>
BST<T>& BST<T>::operator=(const BST<T>& rhs)
{
	if (root == rhs.root)
		return *this;
			//Check o=for self reference.

	tree_clear(root);
			//Original root is deleted

	root = tree_copy(rhs.root);
			//root is assigned to a copy of rhs.


	return *this;
}

template<typename T>
BST<T>::~BST()
{
	tree_clear(root);
			//Tree is deleted.
}

//------------------------------------------
//Insertion Function
//------------------------------------------

template<typename T>
void BST<T>::insert(const T& insert_me)
{
	tree_insert(root, insert_me);
			//The value insert_me is inserted into the correct location of the
			//tree.
}

//------------------------------------------
//Deletion Functions
//------------------------------------------

template<typename T>
void BST<T>::erase(const T& target)
{
	tree_erase(root, target);
			//The value target is erased from the tree.
}

template<typename T>
void BST<T>::clear()
{
	tree_clear(root);
			//The tree is deleted.

	root = nullptr;
}

//------------------------------------------
//Search Function
//------------------------------------------

template<typename T>
bool BST<T>::search(const T& target, TreeNode<T>*& found_ptr)
{
	return tree_search(root, target, found_ptr);
}

//------------------------------------------
//Addition Operator
//------------------------------------------

template<typename T>
BST<T>& BST<T>::operator+=(const BST<T>& rhs)
{
	tree_add(root, rhs.root);
			//The two trees added together.

	return *this;
}

//------------------------------------------
//Output Operator
//------------------------------------------

template<typename U>
ostream& operator<<(ostream& outs, const BST<U>& tree)
{

	tree_print(tree.root, 0, outs);
			
	return outs;
}

#endif // !BST_H
