#ifndef BTREE_H
#define BTREE_H
#include <iostream>
#include <iomanip>
#include <cassert>
#include "BTree_Util_Functions.h"

template <class T>
class BTree
{
public:
    BTree(bool dups = false);

    //big three:
    BTree(const BTree<T>& other);
    ~BTree();
    BTree<T>& operator =(const BTree<T>& RHS);

    bool insert(const T& entry);                //insert entry into the tree
    bool remove(const T& entry);                //remove entry from the tree

    void clear_tree();                          //clear this object (delete all nodes etc.)
    void copy_tree(const BTree<T>& other);      //copy other into this object

    bool contains(const T& entry);              //true if entry can be found in the array
    T& get(const T& entry);                     //return a reference to entry in the tree
    const T& get(const T& entry)const;          //return a reference to entry in the tree
    T& get_existing(const T& entry);            //return a reference to entry in the tree
    T* find(const T& entry);                    //return a pointer to this key. NULL if not there.

    int size() const;                           //count the number of elements in the tree
    bool empty() const;                         //true if the tree is empty
    bool is_valid(bool isRoot = true);

    void print_tree(int level = 0, ostream& outs = cout) const; //print a readable version of the tree

    friend ostream& operator<<(ostream& outs, const BTree<T>& print_me) {
        print_me.print_tree(0, outs);
        return outs;
    }                              //true if duplicate keys may be inserted

    
private:
    
    static const int MINIMUM = 1;
    static const int MAXIMUM = 2 * MINIMUM;

    int data_count;
    bool _duplicates;                                //number of data elements
    T data[MAXIMUM + 1];                            //holds the keys
    int child_count;                                //number of children
    BTree* subset[MAXIMUM + 2];                     //subtrees

    bool loose_remove(const T& entry);              //allows MINIMUM-1 data elements in the root

    void remove_biggest(T& entry);                  //remove the biggest child of this tree->entry

    bool is_leaf() const { return child_count == 0; }   //true if this is a leaf node

    //insert element functions
    bool loose_insert(const T& entry);              //allows MAXIMUM+1 data elements in the root
    void fix_excess(int i);                         //fix excess of data elements in child i

    //remove element functions:
    void fix_shortage(int i);                       //fix shortage of data elements in child i
    void rotate_left(int i);                        //transfer one element LEFT from child i
    void rotate_right(int i);                       //transfer one element RIGHT from child i
    void merge_with_next_subset(int i);             //merge subset i with subset i+1

};

#endif // !BTREE_H

template<class T>
BTree<T>::BTree(bool dups): _duplicates(dups), data_count(0), child_count(0)
{
    for (int i = 0; i < MAXIMUM + 1; i++)
        data[i] = T();
            //Setting default values for all the items in the root.

    for (int i = 0; i < MAXIMUM + 2; i++)
        subset[i] = nullptr;
            //All subtree branches are set to nullptr by default.

}

//Big Three Functions

template<class T>
BTree<T>::BTree(const BTree<T>& other)
{
    for (int i = 0; i < MAXIMUM + 1; i++)
        data[i] = T();

    for (int i = 0; i < MAXIMUM + 2; i++)
        subset[i] = nullptr;

    copy_tree(other);
    
}

template<class T>
BTree<T>::~BTree()
{
    clear_tree();
}

template<class T>
BTree<T>& BTree<T>::operator=(const BTree<T>& RHS)
{
    if (this == &RHS)
        return *this;

    clear_tree();
    copy_tree(RHS);

    return *this;
}

template<class T>
bool BTree<T>::insert(const T& entry)
{
    loose_insert(entry);
            //Inserts the value at a position within the set, and leaves it
            //in excess.
    
    if (data_count > MAXIMUM) {
                //If the root is in excess...

        BTree* temp = new BTree(_duplicates);
                //A new treenode is created and held with all of the root's
                //values.

        copy_array(temp->data, data, temp->data_count, data_count);

        copy_array(temp->subset, subset, temp->child_count, child_count);

        data_count = 0;
        child_count = 1;
                //The root is emptied.

        subset[0] = temp;

        fix_excess(0);
                //fix_excess is called on the root.

        return true;
    }

}

template<class T>
bool BTree<T>::remove(const T& entry)
{
    if (!loose_remove(entry))
        return false;

    if (data_count == 0 && child_count == 1) {

        BTree* temp = subset[0];

        copy_array(data, temp->data, data_count, temp->data_count);
        copy_array(subset, temp->subset, child_count, temp->child_count);

    }

    return true;
}

template<class T>
void BTree<T>::clear_tree()
{
    for (int i = 0; i < child_count; i++)
        if (subset[i] != nullptr)
            subset[i]->clear_tree();
    //Recursive call


    for (int i = 0; i < child_count; i++) {
        //delete subset[i];
        subset[i] = nullptr;
    }
            //Every subset in the current root is deleted.

    child_count = 0;
    data_count = 0;
            //All values are reset to zero.
}

template<class T>
void BTree<T>::copy_tree(const BTree<T>& other)
{
    data_count = other.data_count;
    child_count = other.child_count;
            //The other's values are copied into this.

    for (int i = 0; i <= data_count; i++)
        data[i] = other.data[i];
            //Individual data items are copied to the array.

    for (int i = 0; i < other.child_count; i++) {

            subset[i] = new BTree();

            subset[i]->copy_tree(*other.subset[i]);

    }

}

template<class T>
bool BTree<T>::is_valid(bool isRoot)
{
    const bool debug = true;

    for (int i = 0; i < child_count; i++) {
        if (!subset[i]->is_valid(false))
            return false;
                //Recursive call
    }

    if (data_count > 1)
        for (int i = 0; i < data_count - 1; i++)
            if (data[i] > data[i + 1]) {
                return false;
                    //Returns false if any element is not in increasing order.
            }

            //Checks for the remaining laws are passed.

    if (!isRoot && data_count < MINIMUM 
        || data_count > MAXIMUM 
        || !is_leaf() && child_count != data_count + 1) 
    {
        return false;
    }
    for (int i = 0; i < data_count; i++) {
        if (!is_leaf()
            && (subset[i]->data[subset[i]->data_count - 1] > data[i]
                || subset[i + 1]->data[0] < data[i]))
        {
            return false;
        }
    }

    return true;
}

template<class T>
bool BTree<T>::loose_insert(const T& entry)
{
    int i = first_ge(data, data_count, entry);
            //Gets the first index of the item greater than or equal to after.

    if (i != data_count && data[i] == entry && !_duplicates)
        return false;
            //Checks if a duplicate value is found.

    else if (is_leaf()) {
        insert_item(data, i, data_count, entry);
    }

    else {
        bool ans = subset[i]->loose_insert(entry);
                //holds value of the item's found token.

        if (subset[i]->data_count > MAXIMUM)
            fix_excess(i);
                //If there's an excess, it will be fixed.

        return ans;
    }

}

template<class T>
void BTree<T>::fix_excess(int i)
{
    BTree* temp = new BTree(_duplicates);

    split(subset[i]->data, subset[i]->data_count, temp->data, temp->data_count);
    split(subset[i]->subset, subset[i]->child_count, temp->subset, temp->child_count);

            //The BTree is split down the middle of it's data elements and 
            //turned into two seperate subtrees.

    

    T item;

    detach_item(subset[i]->data, subset[i]->data_count, item);

    insert_item(data, i, data_count, item);
            //The item in the middle of the data object is removed and moved
            //to the top.

    insert_item(subset, i + 1, child_count, temp);

}

template<class T>
bool BTree<T>::loose_remove(const T& entry)
{
    T temp;
    int i = first_ge(data, data_count, entry);

    bool found = (data[i] == entry);

    if (is_leaf()) {
        if (!found) {
            return false;
        }
        else {
            delete_item(data, i, data_count, temp);
            return true;
        }
    }

    else if (!found) {
        found = subset[i]->loose_remove(entry);
        if (subset[i]->data_count == MINIMUM - 1)
            fix_shortage(i);

        return found;
    }

    else {
        subset[i]->remove_biggest(data[i]);

        if (subset[i]->data_count < MINIMUM)
            fix_shortage(i);

        return true; // Indicate that we removed the target.
    }

}

template<class T>
void BTree<T>::fix_shortage(int i)
{
    T temp;
    BTree* tempBT;

    if (i > 0 && subset[i - 1]->data_count > MINIMUM)
        rotate_right(i - 1);

    else if (i < data_count && subset[i + 1]->data_count > MINIMUM)
        rotate_left(i + 1);

    else if (i > 0)
        merge_with_next_subset(i - 1);

    else
        merge_with_next_subset(i);
}

template<class T>
void BTree<T>::remove_biggest(T& entry)
{
    int i = data_count - 1;

    if (i + 2 > child_count)
        delete_item(data, i, data_count, entry);

    else {
        subset[data_count]->remove_biggest(entry);

        if (subset[data_count]->data_count < MINIMUM)
            fix_shortage(data_count);

    }
}

template<class T>
void BTree<T>::rotate_left(int i)
{
    T temp;
    BTree* tempBT;
    i--;

    attach_item(subset[i]->data, subset[i]->data_count, data[i]);

    delete_item(subset[i + 1]->data, 0, subset[i + 1]->data_count, data[i]);

    if (!subset[i + 1]->is_leaf()) {

        delete_item(subset[i + 1]->subset, 0, subset[i + 1]->child_count, tempBT);

        attach_item(subset[i]->subset, subset[i]->child_count, tempBT);

    }

}

template<class T>
void BTree<T>::rotate_right(int i)
{
    T temp;
    BTree* tempBT;
    i++;

    insert_item(subset[i]->data, 0, subset[i]->data_count, data[i - 1]);

    detach_item(subset[i - 1]->data, subset[i - 1]->data_count, data[i - 1]);

    if (!subset[i - 1]->is_leaf()) {

        detach_item(subset[i - 1]->subset, subset[i - 1]->child_count, tempBT);

        insert_item(subset[i]->subset, 0, subset[i]->child_count, tempBT);

    }

}

template<class T>
void BTree<T>::merge_with_next_subset(int i)
{
    T temp;
    BTree* tempBT;

    insert_item(subset[i + 1]->data, 0, subset[i + 1]->data_count, data[i]);

    delete_item(data, i, data_count, temp);

    merge(subset[i]->data, subset[i]->data_count,
        subset[i + 1]->data, subset[i + 1]->data_count);


    merge(subset[i]->subset, subset[i]->child_count,
        subset[i + 1]->subset, subset[i + 1]->child_count);


    subset[i + 1]->data_count = 0;
    subset[i + 1]->child_count = 0;

    delete_item(subset, i + 1, child_count, tempBT);


            //NOTE: Code for right-hand merge

    /*attach_item(subset[i - 1]->data, subset[i - 1]->data_count, data[i - 1]);

    delete_item(data, i - 1, data_count, temp);

    merge(subset[i - 1]->data, subset[i - 1]->data_count,
        subset[i]->data, subset[i]->data_count);

    merge(subset[i - 1]->subset, subset[i - 1]->child_count,
        subset[i]->subset, subset[i]->child_count);

    subset[i]->data_count = 0;
    subset[i]->child_count = 0;

    delete_item(subset, i, child_count, tempBT);*/

}

template<class T>
bool BTree<T>::contains(const T& entry)
{
    return find(entry) != nullptr;
}

template<class T>
T& BTree<T>::get(const T& entry)
{
    //If entry is not in the tree, add it to the tree
    //assert(contains(entry));

    const bool debug = false;

    if (!contains(entry))
        insert(entry);

    return get_existing(entry);
}

template<class T>
const T& BTree<T>::get(const T& entry) const
{
    return get(entry);
}

template<class T>
T& BTree<T>::get_existing(const T& entry)
{
    const bool debug = false;

    int i = first_ge(data, data_count, entry);

    bool found = (i < data_count&& data[i] == entry);

    if (is_leaf())
        if (found) {
            return data[i];
        }
        else {

            assert(found);
        }
    if (found) //inner node
        return subset[i + 1]->get(entry);
    //or just return true?
    else //not found yet...
        return subset[i]->get(entry);
}

template<class T>
T* BTree<T>::find(const T& entry)
{
    int i = first_ge(data, data_count, entry);

    if (i < data_count && data[i] == entry)
        return data + i;

    else if (is_leaf())
        return nullptr;

    else
        return subset[i]->find(entry);
}

template<class T>
int BTree<T>::size() const
{
    int ans = 0;

    for (int i = 0; i < child_count; i++)
        ans += subset[i]->size();

    ans += data_count;

    return ans;
}

template<class T>
bool BTree<T>::empty() const
{
    return is_leaf() && data_count == 0;
}

template<class T>
void BTree<T>::print_tree(int level, ostream& outs) const
{

    if (child_count != 0 && subset[child_count - 1] != nullptr)
        subset[child_count - 1]->print_tree(level + 1, outs);

    for (int i = data_count - 1; i >= 0; i--) {

        outs << setw(level * 4) << "" << "[" << data[i] << "]" << endl;
        if (child_count > 0 && subset[i] != nullptr) {

            subset[i]->print_tree(level + 1, outs);
        }

    }
}

//template<typename Item>
//void Set<Item>::getUnionRec(Set<Item>& other, Set<Item>& ans)
//{
//    for (int i = 0; i < child_count; i++)
//        if (subset[i] != nullptr)
//            subset[i]->getUnionRec(other, ans);
//
//    for (int i = 0; i < data_count; i++) {
//        if (other.find(data[i]) != nullptr)
//            ans.insert(data[i]);
//    }
//}
//
//template<typename Item>
//void Set<Item>::getIntersectionRec(Set<Item>& other)
//{
//    for (int i = 0; i < child_count; i++)
//        if (subset[i] != nullptr)
//            subset[i]->getIntersectionRec(other);
//
//    for (int i = 0; i < data_count; i++) {
//        if (other.find(data[i]) == nullptr)
//            other.insert(data[i]);
//    }
//}
//
//template<typename Item>
//Set<Item> Set<Item>::getUnion(Set<Item>& other)
//{
//    Set<Item> ans;
//    getUnionRec(other, ans);
//    return ans;
//}
//
//template<typename Item>
//Set<Item> Set<Item>::getIntersection(Set<Item>& other)
//{
//    Set<Item> ans(other);
//    getIntersectionRec(ans);
//    return ans;
//}