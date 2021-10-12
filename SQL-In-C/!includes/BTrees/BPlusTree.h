#ifndef BPLUSTREE_H
#define BPLUSTREE_H
#include <iostream>
#include <iomanip>
#include <cassert>
#include <stack>
#include "BTree_Util_Functions.h"
using namespace std;

template <class T>
class BPlusTree
{
public:
    class Iterator {
    public:
        friend class BPlusTree;
        Iterator(BPlusTree<T>* _it = nullptr, int _key_ptr = 0) :it(_it), key_ptr(_key_ptr) {}

        T operator *() {
            assert(it != nullptr && key_ptr < it->data_count);
            return it->data[key_ptr];
        }

        Iterator operator++(int un_used) {
            assert(key_ptr < it->data_count);

            if (++key_ptr == it->data_count) {
                it = it->next;
                key_ptr = 0;
            }

            return *this;
        }

        Iterator operator++() {
            assert(it != nullptr && key_ptr < it->data_count);

            Iterator hold = Iterator(it, key_ptr);

            if (++key_ptr == it->data_count) {
                it = it->next;
                key_ptr = 0;
            }

            return hold;
            
        }

        Iterator next() {
            assert(it != nullptr && key_ptr < it->data_count);

            Iterator temp = Iterator(it, key_ptr);

            if (++temp.key_ptr == temp.it->data_count) {
                temp.it = temp.it->next;
                temp.key_ptr = 0;
            }

            return temp;

        }

        friend bool operator ==(const Iterator& lhs, const Iterator& rhs) {
            return lhs.it == rhs.it && lhs.key_ptr == rhs.key_ptr;
        }

        friend bool operator !=(const Iterator& lhs, const Iterator& rhs) {
            return !(lhs == rhs);
        }

        void print_Iterator(ostream& outs) const{
            if (*this != Iterator())
                outs << "[" << it->data[key_ptr] << "]";
            else
                outs << "|||";
        }

        friend ostream& operator <<(ostream& outs, const Iterator& iter) {
            iter.print_Iterator(outs);
            return outs;
        }

        bool is_null() { return !it; }
    private:
        BPlusTree<T>* it;
        int key_ptr;
    };

    BPlusTree();
    //big three:
    BPlusTree(const BPlusTree<T>& other);
    ~BPlusTree();
    BPlusTree<T>& operator =(const BPlusTree<T>& RHS);

    bool insert(const T& entry);                //insert entry into the tree
    bool remove(const T& entry);                //remove entry from the tree

    void clear_tree();                          //clear this object (delete all nodes etc.)
    void copy_tree(const BPlusTree<T>& other);  //copy other into this object
    bool contains(const T& entry);        //true if entry can be found in the array

    T& get(const T& entry);                     //return a reference to entry in the tree
    const T& get(const T& entry)const;          //return a reference to entry in the tree
    T& get_existing(const T& entry);            //return a reference to entry in the tree

    BPlusTree<T>::Iterator find(const T& entry);              //return an iterator to this key. NULL if not there.


    BPlusTree<T>::Iterator lower_bound(const T& key);  //return first that goes NOT BEFORE
                                         // key entry or next if does not
                                         // exist >= entry
    BPlusTree<T>::Iterator upper_bound(const T& key);  //return first that goes AFTER key

    int size() const;                           //count the number of elements in the tree
    bool empty() const;                         //true if the tree is empty

    void print_tree(int level = 0,
        ostream& outs = cout) const; //print a readable version of the tree
    friend ostream& operator<<(ostream& outs,
        const BPlusTree<T>& print_me) {
        print_me.print_tree(0, outs);
        return outs;
    }
    bool is_valid();

    BPlusTree<T>::Iterator begin();
    BPlusTree<T>::Iterator end();

private:
    static const int MINIMUM = 2;
    static const int MAXIMUM = 2 * MINIMUM;

    int data_count;                     //number of data elements
    T data[MAXIMUM + 1];                //holds the keys
    int child_count;                    //number of children
    BPlusTree* subset[MAXIMUM + 2];     //subtrees
    BPlusTree* next;
    int _size;

    bool is_leaf() const
    {
        return child_count == 0;
    }        //true if this is a leaf node

    T* find_ptr(const T& entry);        //return a pointer to this key. NULL if not there.

    //insert element functions
    bool loose_insert(const T& entry);  //allows MAXIMUM+1 data elements in the root
    void fix_excess(int i);             //fix excess of data elements in child i

    //remove element functions:
    bool loose_remove(const T& entry);  //allows MINIMUM-1 data elements in the root

    BPlusTree<T>* fix_shortage(int i);  //fix shortage of data elements in child i
                                        // and return the smallest key in this subtree
    BPlusTree<T>* get_smallest_node();
    BPlusTree<T>* get_biggest_node();
    T& get_smallest();        //entry := leftmost leaf
    void get_biggest(T& entry);         //entry := rightmost leaf
    void remove_biggest(T& entry);      //remove the biggest child of this tree->entry
    void transfer_left(int i);          //transfer one element LEFT from child i
    void transfer_right(int i);         //transfer one element RIGHT from child i
    BPlusTree<T>* merge_with_next_subset(int i);    //merge subset i with subset i+1

    void copy_tree(const BPlusTree<T>& other, BPlusTree<T>*& bpt = nullptr);
};

template<class T>
BPlusTree<T>::BPlusTree() : data_count(0),
child_count(0), next(nullptr), _size(0)
{
    for (int i = 0; i < MAXIMUM + 1; i++)
        data[i] = T();
    //Sets all the values in the BPlusTree to default

    for (int i = 0; i < MAXIMUM + 2; i++)
        subset[i] = nullptr;
    //Sets all the pointers in the subset to null.
}

template<class T>
BPlusTree<T>::BPlusTree(const BPlusTree<T>& other)
{
    BPlusTree* bpt = nullptr;
    copy_tree(other, bpt);
    //Copies the other BPlusTree.
}

template<class T>
BPlusTree<T>::~BPlusTree()
{       //The BPlusTree is deallocated after this function call.
    clear_tree();
    //Clears the BPlusTree.
}

template<class T>
BPlusTree<T>& BPlusTree<T>::operator=(const BPlusTree<T>& RHS)
{
    if (this == &RHS)
        return *this;
    //Checks for self reference


    clear_tree();
    BPlusTree* temp = nullptr;
    copy_tree(RHS, temp);
    //The tree is copied over to this.

    return *this;
}

template<class T>
bool BPlusTree<T>::insert(const T& entry)
{
    if (!loose_insert(entry))
        return false;
    //Inserts the value in the tree (if it doesn't exist); 
    //otherwise, returns false.

    _size++;
    //Size is increased
    if (data_count > MAXIMUM) {
        //If the root is at maximum

        BPlusTree* temp = new BPlusTree();
        //A new BPlusTree is created as a subset of the root.

        copy_array(temp->data, data, temp->data_count, data_count);
        copy_array(temp->subset, subset, temp->child_count, child_count);
        //All the values of the root are copied over to the subtree.

        data_count = 0;
        child_count = 1;

        subset[0] = temp;

        fix_excess(0);
        //The excess of the subtree is fixed.

    }

    return true;
}

template<class T>
bool BPlusTree<T>::remove(const T& entry)
{
    if (!loose_remove(entry)) {
        return false;
    }
    _size--;

    if (data_count == 0 && child_count == 1) {
        BPlusTree* temp = subset[0];

        copy_array(data, temp->data, data_count, temp->data_count);
        copy_array(subset, temp->subset, child_count, temp->child_count);
    }

    return true;
}

template<class T>
void BPlusTree<T>::clear_tree()
{
    for (int i = 0; i < child_count; i++)
        if (subset[i] != nullptr)
            subset[i]->clear_tree();
    //Recursive call


    for (int i = 0; i < child_count; i++) {
        subset[i]->child_count = 0;
        subset[i]->data_count = 0;
        subset[i]->_size = 0;
        subset[i]->next = nullptr;
        delete subset[i];
        subset[i] = nullptr;
    }
    //Every subset in the current root is deleted.

    child_count = 0;
    data_count = 0;
    _size = 0;
    next = nullptr;
    //All values are reset to zero.

}

template<class T>
void BPlusTree<T>::copy_tree(const BPlusTree<T>& other)
{
    BPlusTree* tempBPT = nullptr;
    copy_tree(other, tempBPT);
}

template<class T>
void BPlusTree<T>::copy_tree(const BPlusTree<T>& other, BPlusTree<T>*& bpt)
{
    for (int i = other.child_count - 1; i >= 0; i--) {

        subset[i] = new BPlusTree();

        subset[i]->copy_tree(*other.subset[i], bpt);

    }

    if (other.is_leaf()) {
        next = bpt;
        bpt = this;
    }

    data_count = other.data_count;
    child_count = other.child_count;
    _size = other._size;
    //The other's values are copied into this.

    for (int i = 0; i <= data_count; i++)
        data[i] = other.data[i];
    //Individual data items are copied to the array.
}

template<class T>
bool BPlusTree<T>::contains(const T& entry)
{
    return find_ptr(entry) != nullptr;
    //Checks if the pointer to the item exists in the tree.
}

template<class T>
T* BPlusTree<T>::find_ptr(const T& entry)
{
    int i = first_ge(data, data_count, entry);

    bool found = i < data_count && data[i] == entry;

    if (found) {
        if (is_leaf())
            return data + i;
        //If the item is found, the pointer is returned.
        else
            return subset[i + 1]->find_ptr(entry);
        //If it's not the root, then the search continues for the root
    }

    else if (is_leaf())
        return nullptr;
    //If it's not there, then the function returns null.

    else
        return subset[i]->find_ptr(entry);
    //Continue=s in the subset if not found.

}

template<class T>
bool BPlusTree<T>::loose_insert(const T& entry)
{
    int i = first_ge(data, data_count, entry);

    bool found = i < data_count&& data[i] == entry;

    if (found) {
        if (is_leaf())
            return true;
        //If the item already exists then it isn't inserted into the
        //BPlusTree

        else {

            bool hasBeenInserted = subset[i + 1]->loose_insert(entry);

            if (subset[i + 1]->data_count > MAXIMUM)
                fix_excess(i + 1);

            return hasBeenInserted;

        }
    }
    else if (is_leaf()) {
        insert_item(data, i, data_count, entry);
        return true;
    }

    else {

        bool hasBeenInserted = subset[i]->loose_insert(entry);

        if (subset[i]->data_count > MAXIMUM)
            fix_excess(i);

        return hasBeenInserted;

    }
}

template<class T>
void BPlusTree<T>::fix_excess(int i)
{
    BPlusTree* temp = new BPlusTree();

    split(subset[i]->data, subset[i]->data_count, temp->data, temp->data_count);
    split(subset[i]->subset, subset[i]->child_count, temp->subset, temp->child_count);

    //The BPlusTree is split down the middle of it's data elements and 
    //turned into two seperate subtrees.

    temp->next = subset[i]->next;
    subset[i]->next = temp;

    T item;

    detach_item(subset[i]->data, subset[i]->data_count, item);

    insert_item(data, i, data_count, item);
    //The item in the middle of the data object is removed and moved
    //to the top.

    insert_item(subset, i + 1, child_count, temp);

    if (temp->is_leaf())
        insert_item(temp->data, 0, temp->data_count, item);
}

template<class T>
bool BPlusTree<T>::loose_remove(const T& entry)
{
    int i = first_ge(data, data_count, entry);
    bool found = i < data_count&& data[i] == entry;

    T temp;
    int tempIndex;

    if (found) {
        if (is_leaf()) {

            delete_item(data, i, data_count, temp);
            return true;
        }
        else
        {

            bool temp = subset[i + 1]->loose_remove(entry);

            if (subset[i + 1]->data_count < MINIMUM) {
                fix_shortage(i + 1);
            }

            tempIndex = first_ge(data, data_count, entry);

            if (tempIndex < data_count && data[tempIndex] == entry) {

                data[tempIndex] = subset[i + 1]->get_smallest();
            }
            else {


                tempIndex = first_ge(subset[i]->data, subset[i]->data_count, entry);

                if (tempIndex < subset[i]->data_count && subset[i]->data[tempIndex] == entry) {
                    subset[i]->data[tempIndex] = subset[i]->subset[tempIndex + 1]->get_smallest();
                }

            }

            return temp;
        }
    }
    else if (is_leaf()) {

        return false;
    }
    else {
        bool temp = subset[i]->loose_remove(entry);

        if (subset[i]->data_count < MINIMUM) {
            fix_shortage(i);
        }

        return temp;
    }

}

template<class T>
BPlusTree<T>* BPlusTree<T>::fix_shortage(int i)
{
    if (i > 0 && subset[i - 1]->data_count > MINIMUM) {
        transfer_right(i - 1);
    }
    else if (i < child_count - 1 && subset[i + 1]->data_count > MINIMUM) {

        transfer_left(i + 1);

    }
    else if (i > 0) {

        merge_with_next_subset(i - 1);

    }
    else {

        merge_with_next_subset(i);

    }

    return subset[i];
}

template<class T>
BPlusTree<T>* BPlusTree<T>::get_smallest_node()
{
    if (child_count != 0)
        return subset[0]->get_smallest_node();

    return this;
}

template<class T>
BPlusTree<T>* BPlusTree<T>::get_biggest_node()
{
    if (!is_leaf())
        subset[child_count - 1]->get_biggest_node();

    return this;
}

template<class T>
T& BPlusTree<T>::get_smallest()
{
    return get_smallest_node()->data[0];
}

template<class T>
void BPlusTree<T>::get_biggest(T& entry)
{
    entry = get_biggest_node()->data[data_count - 1];
}

template<class T>
void BPlusTree<T>::remove_biggest(T& entry)
{
    if (is_leaf())
        detach_item(data, data_count, entry);

    else {

        subset[child_count - 1]->remove_biggest(entry);

        if (subset[child_count - 1]->data_count < MINIMUM)
            fix_shortage(child_count - 1);
    }
}

template<class T>
void BPlusTree<T>::transfer_left(int i)
{
    T temp;
    BPlusTree* tempBT;

    if (!subset[i]->is_leaf()) {
        attach_item(subset[i - 1]->data, subset[i - 1]->data_count, data[i - 1]);

        delete_item(subset[i]->data, 0, subset[i]->data_count, data[i - 1]);

        if (!subset[i]->is_leaf()) {

            delete_item(subset[i]->subset, 0, subset[i]->child_count, tempBT);

            attach_item(subset[i - 1]->subset, subset[i - 1]->child_count, tempBT);

        }
    }
    else {
        attach_item(subset[i - 1]->data, subset[i - 1]->data_count, subset[i]->data[0]);
        delete_item(subset[i]->data, 0, subset[i]->data_count, temp);
        data[i - 1] = subset[i]->data[0];
    }

}

template<class T>
void BPlusTree<T>::transfer_right(int i)
{
    T temp;
    BPlusTree* tempBT;
    if (!subset[i]->is_leaf()) {

        insert_item(subset[i + 1]->data, 0, subset[i + 1]->data_count, data[i]);

        detach_item(subset[i]->data, subset[i]->data_count, data[i]);

        if (!subset[i]->is_leaf()) {

            detach_item(subset[i]->subset, subset[i]->child_count, tempBT);

            insert_item(subset[i + 1]->subset, 0, subset[i + 1]->child_count, tempBT);

        }
    }
    else {
        detach_item(subset[i]->data, subset[i]->data_count, data[i]);
        insert_item(subset[i + 1]->data, 0, subset[i + 1]->data_count, data[i]);
    }
}

template<class T>
BPlusTree<T>* BPlusTree<T>::merge_with_next_subset(int i)
{
    T temp;
    BPlusTree* tempBPT;

    delete_item(data, i, data_count, temp);

    if (!subset[i]->is_leaf()) {
        attach_item(subset[i]->data, subset[i]->data_count, temp);
    }

    merge(subset[i]->data, subset[i]->data_count,
        subset[i + 1]->data, subset[i + 1]->data_count);


    merge(subset[i]->subset, subset[i]->child_count,
        subset[i + 1]->subset, subset[i + 1]->child_count);


    subset[i + 1]->data_count = 0;
    subset[i + 1]->child_count = 0;

    delete_item(subset, i + 1, child_count, tempBPT);

    if (subset[i]->is_leaf()) {
        subset[i]->next = tempBPT->next;
    }

    delete tempBPT;

    return subset[i];

    /*T temp;
    BPlusTree* tempBT;

    insert_item(subset[i + 1]->data, 0, subset[i + 1]->data_count, data[i]);

    delete_item(data, i, data_count, temp);

    merge(subset[i]->data, subset[i]->data_count,
        subset[i + 1]->data, subset[i + 1]->data_count);


    merge(subset[i]->subset, subset[i]->child_count,
        subset[i + 1]->subset, subset[i + 1]->child_count);


    subset[i + 1]->data_count = 0;
    subset[i + 1]->child_count = 0;

    delete_item(subset, i + 1, child_count, tempBT);*/
}

template<class T>
T& BPlusTree<T>::get(const T& entry)
{
    if (!contains(entry))
        insert(entry);

    return *find_ptr(entry);
    //Returns the item at the pointer location of entry.
}

template<class T>
const T& BPlusTree<T>::get(const T& entry) const
{
    return get(entry);
    //Returns get(entry) (obviously)
}

template<class T>
T& BPlusTree<T>::get_existing(const T& entry)
{
    return *find_ptr(entry);
    //Returns the value assuming it exists
}

template<class T>
typename BPlusTree<T>::Iterator BPlusTree<T>::find(const T& entry)
{
    int i = first_ge(data, data_count, entry);

    bool found = i < data_count&& data[i] == entry;

    if (found) {
        if (is_leaf())
            return BPlusTree<T>::Iterator(this, i);
        //If the value is found at the leaf, then the iterator of it
        //is returned.
        else
            return subset[i + 1]->find(entry);
        //If the value is found not at the leaf then we search for
        //the root version as well.
    }

    else if (is_leaf())
        return BPlusTree<T>::Iterator();
    //null is returned if not there.

    else
        return subset[i]->find(entry);
    //If not found, then we search in the subtree.
}

template<class T>
typename BPlusTree<T>::Iterator BPlusTree<T>::lower_bound(const T& key)
{
    BPlusTree<T>::Iterator it = begin();

    while (it != end() && *it < key) {
        it++;
    }

    return it;
}

template<class T>
typename BPlusTree<T>::Iterator BPlusTree<T>::upper_bound(const T& key)
{
    BPlusTree<T>::Iterator it = begin();

    while (it != end() && *it <= key) {
        it++;
    }

    return it;
}

template<class T>
int BPlusTree<T>::size() const
{
    return _size;
    //Size is returned.
}

template<class T>
bool BPlusTree<T>::empty() const
{
    return _size == 0;
}

template<class T>
void BPlusTree<T>::print_tree(int level, ostream& outs) const
{
    if (!is_leaf())
        subset[child_count - 1]->print_tree(level + 1, outs);

    for (int i = data_count - 1; i >= 0; i--) {

        outs << setw(level * 4) << "" << "[" << data[i] << "]" << endl;

        if (!is_leaf()) {
            subset[i]->print_tree(level + 1, outs);
        }

    }
}

template<class T>
bool BPlusTree<T>::is_valid()
{
    //should check that every data[i] < data[i+1]

    for (int i = 0; i < data_count - 1; i++) {
        if (data[i] > data[i + 1])
            return false;
    }

    if (is_leaf())
        return true;


    //data[data_count-1] must be less than equal to 
    //  every subset[child_count-1]->data[ ]
    if (data[data_count - 1] > subset[child_count - 1]->data[0]) {
        return false;
    }

    //every data[i] is greater than every subset[i]->data[ ]
    for (int i = 0; i < data_count; i++) {
        if (data[i] <= subset[i]->data[subset[i]->data_count - 1]) {
            return false;
        }
    }
    //B+Tree: Every data[i] is equal to subset[i+1]->smallest
    /*for (int i = 0; i < data_count; i++) {
        if (data[i] != subset[i + 1]->get_smallest_node()) {
            return false;
        }
    }*/
    //Recursively validate every subset[i]
    for (int i = 0; i < child_count; i++) {
        if (!subset[i]->is_valid()) {
            return false;
        }
    }
    return true;
}

template<class T>
typename BPlusTree<T>::Iterator BPlusTree<T>::begin()
{
    if (!empty())
        return BPlusTree<T>::Iterator(get_smallest_node(), 0);

    return BPlusTree<T>::Iterator();
}

template<class T>
typename BPlusTree<T>::Iterator BPlusTree<T>::end()
{
    return BPlusTree<T>::Iterator();
}

#endif // !BPLUSTREE_H

