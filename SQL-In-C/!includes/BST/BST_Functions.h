#ifndef BST_FUNCTIONS_H
#define BST_FUNCTIONS_H

#include <iostream>
#include <iomanip>
#include <cassert>
#include "TreeNode.h"

template <typename T>
void tree_insert(TreeNode<T>*& root, const T& insert_me);

template <typename T>
TreeNode<T>* tree_search(TreeNode<T>* root, const T& target);

template <typename T>
bool tree_search(TreeNode<T>* root, const T& target, TreeNode<T>*& found_ptr);

template<typename T>
void tree_print(TreeNode<T>* root, int level = 0,
    ostream& outs = cout);

template<typename T>
const void tree_print_inorder(TreeNode<T>* root, ostream& outs = cout);

template<typename T>
void tree_print_preorder(TreeNode<T>* root, ostream& outs = cout);

template<typename T>
void tree_print_postorder(TreeNode<T>* root, ostream& outs = cout);

template<typename T>       //prints detailes info about each node
void tree_print_debug(TreeNode<T>* root, int level = 0,
    ostream& outs = cout);

template <typename T>       //clear the tree
void tree_clear(TreeNode<T>*& root);

template <typename T>       //erase target from the tree
bool tree_erase(TreeNode<T>*& root, const T& target);

template <typename T>       //erase rightmost node from the tree
                            // store the item in max_value
void tree_remove_max(TreeNode<T>*& root, T& max_value);

template <typename T>       //return copy of tree pointed to by root
TreeNode<T>* tree_copy(TreeNode<T>* root);

template <typename T>       //Add tree src to dest
void tree_add(TreeNode<T>*& dest, const TreeNode<T>* src);


template <typename T>       // sorted array -> tree
TreeNode<T>* tree_from_sorted_list(const T* a, int size);

template<typename T>
void list_from_tree(TreeNode<T>* root, T*& a, int& size);

template<typename T>
int getNumElements(TreeNode<T>* root);

// ---------------- ROTATIONS --------------------------
template <typename T>
TreeNode<T>* rotate_right(TreeNode<T>*& root);
template <typename T>
TreeNode<T>* rotate_left(TreeNode<T>*& root);
template <typename T>
TreeNode<T>* rotate(TreeNode<T>*& root); //decide which rotate is needed based on balance factor

//======================================================================

template<typename T>
void tree_insert(TreeNode<T>*& root, const T& insert_me)
{
    if (root == nullptr)
        root = new TreeNode<T>(insert_me);

    else if (insert_me < root->_item)
        tree_insert(root->_left, insert_me);

    else
        tree_insert(root->_right, insert_me);

    root->update_height();
}

template<typename T>
TreeNode<T>* tree_search(TreeNode<T>* root, const T& target)
{
    if (root == nullptr || root->_item == target)
        return root;

    else if (target < root->_item)
        return tree_search(root->_left, target);

    else
        return tree_search(root->_right, target);
}

template<typename T>
bool tree_search(TreeNode<T>* root, const T& target, TreeNode<T>*& found_ptr)
{
    found_ptr = tree_search(root, target);

    return found_ptr != nullptr;
}

template<typename T>
void tree_print(TreeNode<T>* root, int level, ostream& outs)
{
    if (root) {
        tree_print(root->_right, level + 1, outs);
        outs << setw(level * 4) << "" << "[" << root->_item << "]" << endl;
        tree_print(root->_left, level + 1, outs);
    }
}

template<typename T>
const void tree_print_inorder(TreeNode<T>* root, ostream& outs)
{
    if (root) {
        tree_print_inorder(root->_left, outs);
        outs << "[" << root->_item << "]->";
        tree_print_inorder(root->_right, outs);
    }
}

template<typename T>
void tree_print_preorder(TreeNode<T>* root, ostream& outs)
{
    if (root) {
        outs << "[" << root->_item << "]->";
        tree_print_preorder(root->_left, outs);
        tree_print_preorder(root->_right, outs);
    }
}

template<typename T>
void tree_print_postorder(TreeNode<T>* root, ostream& outs)
{
    if (root) {
        tree_print_postorder(root->_left, outs);
        tree_print_postorder(root->_right, outs);
        outs << "[" << root->_item << "]->";
    }
}

template<typename T>
void tree_print_debug(TreeNode<T>* root, int level, ostream& outs)
{
    if (root) {
        tree_print(root->_right, level + 1, outs);
        outs << setw(level * 4) << "" << "[" << root->_item << "]" << endl;
        tree_print(root->_left, level + 1, outs);
    }
}

template<typename T>
void tree_clear(TreeNode<T>*& root)
{
    if (root) {
        tree_clear(root->_left);
        tree_clear(root->_right);
        delete root;
        root = nullptr;
    }
}

template<typename T>
bool tree_erase(TreeNode<T>*& root, const T& target)
{
    if (!root)
        return false;

    if (root->_item == target) {
        if (root->_left == nullptr) {
            TreeNode<T>* temp = root;
            root = temp->_right;
            delete temp;
        }
        else {
            tree_remove_max(root->_left, root->_item);
            //root->_item = max_val;
        }
        return true;
    }

    bool found;

    if (target < root->_item) {
        found = tree_erase(root->_left, target);
        root->update_height();
    }
    else {
        found = tree_erase(root->_right, target);
        root->update_height();
    }

    return found;
}

template<typename T>
void tree_remove_max(TreeNode<T>*& root, T& max_value)
{
    if (root->_right != nullptr)
        tree_remove_max(root->_right, max_value);
    else {
        max_value = root->_item;
        TreeNode<T>* temp = root;
        root = temp->_left;
        delete temp;
    }
}

template<typename T>
TreeNode<T>* tree_copy(TreeNode<T>* root)
{
    if (!root)
        return nullptr;

    return new TreeNode<T>(root->_item, tree_copy(root->_left), 
        tree_copy(root->_right));
}

template<typename T>
void tree_add(TreeNode<T>*& dest, const TreeNode<T>* src)
{
    if (src) {
        tree_insert(dest, src->_item);
        tree_add(dest, src->_right);
        tree_add(dest, src->_left);
    }
}

template<typename T>
TreeNode<T>* tree_from_sorted_list(const T* a, int size)
{

    if (size == 0)
        return nullptr;

    return new TreeNode<T>(a[size / 2], 

        tree_from_sorted_list(a, size / 2), 

        tree_from_sorted_list(a + size / 2 + 1, size - size / 2 - 1));

}

template<typename T>
void list_from_tree(TreeNode<T>* root, T*& a, int& size)
{
    if (root) {
        list_from_tree(root->_right, a, size);
        a[--size] = root->_item;
        list_from_tree(root->_left, a, size);
    }
}

template<typename T>
int getNumElements(TreeNode<T>* root)
{
    if (root == nullptr)
        return 0;

    return 1 + getNumElements(root->_right) + getNumElements(root->_left);
}

template<typename T>
TreeNode<T>* rotate_right(TreeNode<T>*& root)
{
    TreeNode<T>* temp = root->_left;
    root->_left = temp->_right;
    temp->_right = root;
    root->update_height();
    temp->update_height();
    root = temp;
    return root;
}

template<typename T>
inline TreeNode<T>* rotate_left(TreeNode<T>*& root)
{
    TreeNode<T>* temp = root->_right;
    root->_right = temp->_left;
    temp->_left = root;
    root->update_height();
    temp->update_height();
    root = temp;
    return root;
}

template<typename T>
TreeNode<T>* rotate(TreeNode<T>*& root)
{
    //assert(root != nullptr);
    if (root != nullptr) {

        rotate(root->_right);
        rotate(root->_left);

        if (root->balance_factor() > 1) {

            if (root->_right->balance_factor() == -1) {
                rotate_right(root->_right);
            }

            rotate_left(root);
        }

        if (root->balance_factor() < -1) {

            if (root->_left->balance_factor() == 1) {
                rotate_left(root->_left);
            }

            rotate_right(root);
        }
    }
    return root;
}




#endif // !BST_FUNCTIONS_H