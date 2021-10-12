#ifndef AVL_H
#define AVL_H
#include "../BST/BST_Functions.h"
using namespace std;

template <typename T>
class AVL {
public:

	//Constructor

	AVL();
	AVL(const T* sorted_list, int size = -1);

	//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

	//Big Three

	AVL(const AVL<T>& copy_me);
	AVL<T>& operator =(const AVL<T>& rhs);
	~AVL();

	//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

	//Accessor Function
	T Top();

	//Insertion Function
	bool insert(const T& insert_me);

	//Deletion Functions
	void erase(const T& target);
	void clear();

	//Search Function
	bool search(const T& target, TreeNode<T>*& found_ptr);

	//Empty
	bool Empty();

	//Output Operator
	template<typename U>
	friend ostream& operator <<(ostream& outs, const AVL<U>& tree);

	//Addition Operator
	AVL<T>& operator +=(const AVL<T>& rhs);

	T* getTreeInorder(int& size);

	void printTreeInOrder(ostream& outs = cout) const;

private:
	int size();

	TreeNode<T>* root;
};

template<typename T>
AVL<T>::AVL()
{
	root = nullptr;
}

template<typename T>
AVL<T>::AVL(const T* sorted_list, int size)
{
	root = tree_from_sorted_list(sorted_list, size);
}

template<typename T>
AVL<T>::AVL(const AVL<T>& copy_me)
{
	root = tree_copy<T>(copy_me.root);
}

template<typename T>
AVL<T>& AVL<T>::operator=(const AVL<T>& rhs)
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
AVL<T>::~AVL()
{
	tree_clear(root);
}

template<typename T>
T AVL<T>::Top()
{
	return root->_item;
}

template<typename T>
bool AVL<T>::insert(const T& insert_me)
{
	if (tree_search(root, insert_me) == nullptr) {
		tree_insert(root, insert_me);
		rotate(root);
		return true;
	}
	return false;
}

template<typename T>
void AVL<T>::erase(const T& target)
{
	tree_erase(root, target);
	rotate(root);
}

template<typename T>
void AVL<T>::clear()
{
	tree_clear(root);
	root = nullptr;
}

template<typename T>
bool AVL<T>::search(const T& target, TreeNode<T>*& found_ptr)
{
	return tree_search(root, target, found_ptr);
}

template<typename T>
bool AVL<T>::Empty()
{
	return root == nullptr;
}

template<typename T>
AVL<T>& AVL<T>::operator+=(const AVL<T>& rhs)
{
	tree_add(root, rhs.root);
	//The two trees added together.

	rotate(root);

	return *this;
}

template<typename T>
T* AVL<T>::getTreeInorder(int& size)
{
	size = getNumElements(root);
	T* arr = new T[size];

	list_from_tree(root, arr, size);
	size = getNumElements(root);
	return arr;
}

template<typename T>
inline void AVL<T>::printTreeInOrder(ostream& outs) const
{
	tree_print_inorder(root, outs);
	outs << "|||";
}

template<typename T>
int AVL<T>::size()
{
	return getNumElements(root);
}

template<typename U>
ostream& operator<<(ostream& outs, const AVL<U>& tree)
{
	tree_print(tree.root, 0, outs);

	return outs;
}

#endif // !AVL_H
