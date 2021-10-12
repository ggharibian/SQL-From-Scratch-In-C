#ifndef HEAP_H
#define HEAP_H
#include "../oned/oned.h"
#include <iostream>
#include <cassert>
using namespace std;

template<typename T>
class Heap {
public:

    //Constructor

    Heap();

    //Big Three Functions

    Heap(const Heap<T>& copy_me);
    Heap<T>& operator =(const Heap<T>& rhs);
    ~Heap();

    //Insertion Function

    void insert(const T& insert_me);

    //Peek and Pop Functions

    T Peek();

    T Pop();

    //Empty Function

    bool is_empty() const;

    //Accessor Functions

    unsigned int size() const;
    unsigned int capacity() const;

    //OStream Operator

    friend ostream& operator << (ostream& outs, const Heap<T>& print_me) {
        print_me.print_tree(outs);
        return outs;
    }

private:

    //Private Helper Functions

    void print_tree(ostream& outs = cout) const;
    void print_tree(unsigned int root, unsigned int level = 0,
        ostream& outs = cout) const;

    bool is_leaf(unsigned int i) const;
    unsigned int parent_index(unsigned int i) const;
    unsigned int left_child_index(unsigned int i)const;
    unsigned int right_child_index(unsigned int i) const;
    unsigned int big_child_index(unsigned int i) const;
    void swap_with_parent(unsigned int i);

    T* _arr;    //Array holding the items of the heap
    unsigned int _how_many; //Number of elements in the heap
    unsigned int _capacity; //Capacity of the internal array object
};

template<typename T>
Heap<T>::Heap() : _how_many(0), _capacity(3) {
    _arr = allocate<T>(_capacity);
            //Allocates a new array object.
}

template<typename T>
Heap<T>::Heap(const Heap<T>& copy_me)
{
    _how_many = copy_me.size();
    _capacity = copy_me.capacity();
    _arr = allocate<T>(_capacity);
    copy_list<T>(_arr, copy_me._arr, _capacity, _capacity, _capacity);

            //Copies all the elements of the other array into the original.
}

template<typename T>
inline Heap<T>& Heap<T>::operator=(const Heap<T>& rhs)
{
    if (_arr == rhs._arr)
        return *this;
            //If the two arrays are the same, then nothing will happen.

    _how_many = rhs.size();
    _capacity = rhs.capacity();
    _arr = allocate<T>(_capacity);
    copy_list<T>(_arr, rhs._arr, _capacity, _capacity, _capacity);

    return *this;
}

template<typename T>
Heap<T>::~Heap()
{
    delete[] _arr;
}

template<typename T>
void Heap<T>::insert(const T& insert_me)
{
    if (_how_many == _capacity) {
        int c = _capacity;
        _arr = reallocate<T>(_arr, c, c * 2);
        _capacity = c;
    }
            //If the number of elements in the heap is equal to capacity of 
            //the array, the array's capacity is doubled.

    int index = _how_many;
    _arr[index] = insert_me;
            //The item is inserted into the heap.

    while (index != 0 && _arr[index] > _arr[parent_index(index)]) {
        swap_with_parent(index);
        index = parent_index(index);

                //The heap is heapified; the item will be swapped with the 
                //items above it until it is bigger than all the items 
                //below and smaller than all the otems above.
    }

    _how_many++;
            //number of elements is increased.
}

template<typename T>
T Heap<T>::Peek()
{
    assert(!is_empty());

    return _arr[0];
}

template<typename T>
T Heap<T>::Pop()
{
    assert(!is_empty());

    int index = 0;
    T item = _arr[index];
            //The item at the top is saved.

    _how_many--;
    _arr[index] = _arr[_how_many];
    _arr[_how_many] = item;
            //The item is put at the bottom of the heap and essentially 
            //"deleted". The bottom item is put on the top.

    while (!is_leaf(index) && _arr[index] < _arr[big_child_index(index)]) {
        index = big_child_index(index);
        swap_with_parent(index);
    }
            //The item at the top is swapped downwards until it is in the 
            //right place in the heap.

    if (_how_many == _capacity / 2 && _capacity > 3) {
        int c = _capacity;
        _arr = reallocate<T>(_arr, c, c / 2);
        _capacity = c;
    }
            //If the number of elements is reduced to half the capacity, 
            //then the array is reduced to half.

    return item;
            //The item is returned
}

template<typename T>
bool Heap<T>::is_empty() const
{
    return _how_many == 0;
            //Returns if the heap is empty.
}

template<typename T>
unsigned int Heap<T>::size() const
{
    return _how_many;
            //Returns number of spaces used in the array.
}

template<typename T>
inline unsigned int Heap<T>::capacity() const
{
    return _capacity;
            //Returns the total capacity of the array.
}

template<typename T>
void Heap<T>::print_tree(ostream& outs) const
{
    print_tree(0, 0, outs);
}

template<typename T>
void Heap<T>::print_tree(unsigned int root, unsigned int level, 
    ostream& outs) const
{
    if (root < _how_many) {
        print_tree(right_child_index(root), level + 1, outs);
        outs << setw(level * 4) << "" << "[" << _arr[root] << "]" << endl;
        print_tree(left_child_index(root), level + 1, outs);
    }
            //Conditional Statement: Goes through every tree branch a prints
            //the items using a inorder traversal.
}

template<typename T>
bool Heap<T>::is_leaf(unsigned int i) const
{
    return left_child_index(i) >= _how_many && right_child_index(i) 
        >= _how_many;
            //Checks if the left and right children are greater than the
            //number of elements in an array.
}

template<typename T>
unsigned int Heap<T>::parent_index(unsigned int i) const
{
    return (i - 1) / 2;
            //Returns the index of the parent.
}

template<typename T>
unsigned int Heap<T>::left_child_index(unsigned int i) const
{
    return 2 * i + 1;
            //Returns the index of the left child.
}

template<typename T>
inline unsigned int Heap<T>::right_child_index(unsigned int i) const
{
    return 2 * i + 2;
            //Returns the index of the right child.
}

template<typename T>
unsigned int Heap<T>::big_child_index(unsigned int i) const
{
    if (left_child_index(i) >= _how_many)
        return right_child_index(i);

    if (right_child_index(i) >= _how_many)
        return left_child_index(i);

            //First checks if either branch is empty. return the other one if
            //so.

    if (_arr[left_child_index(i)] > _arr[right_child_index(i)])
        return left_child_index(i);
    else
        return right_child_index(i);

            //Then compares the items in the branches and returns the 
            //index of bigger one.
}

template<typename T>
void Heap<T>::swap_with_parent(unsigned int i)
{
    T temp = _arr[i];
    _arr[i] = _arr[parent_index(i)];
    _arr[parent_index(i)] = temp;

            //Swaps two elements in the array.
}

#endif // !HEAP_H