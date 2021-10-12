#ifndef TREENODE_H
#define TREENODE_H
#include <iostream>
using namespace std;

template <typename T>
struct TreeNode {
    T _item;
    TreeNode<T>* _left;
    TreeNode<T>* _right;
    int _height;
    int balance_factor() {
        //balance factor = height of the right subtree 
        //                        - the height of the left subtree
        //a NULL child has a height of -1
        //a leaf has a height of 0

        int leftH, rightH;
        if (!_left)
            leftH = -1;
        else
            leftH = _left->height();

        if (!_right)
            rightH = -1;
        else
            rightH = _right->height();

        return rightH - leftH;

    }

    int height() {
        // Height of a node is 1 + height of the "taller" child
        //A leaf node has a height of zero: 1 + max(-1,-1)

        int leftH, rightH;

        if (_left == nullptr)
            leftH = -1;

        else
            leftH = _left->_height;

        if (_right == nullptr)
            rightH = -1;

        else
            rightH = _right->_height;

        return 1 + max(rightH, leftH);

    }
    int update_height() {
        _height = height();
        return height();
        //set the _height member variable (call height();)
    }

    TreeNode(T item = T(), TreeNode* left = nullptr,
        TreeNode* right = nullptr) :
        _item(item), _left(left), _right(right)
    {

        //don't forget to set the _height.
        update_height();
    }
    friend ostream& operator <<(ostream& outs,
        const TreeNode<T>& t_node) {
        outs << "|" << t_node._item << "|";

        return outs;
    }
};

#endif // !TREENODE_H
