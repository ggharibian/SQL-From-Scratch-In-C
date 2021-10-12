#ifndef PQUEUE_H
#define PQUEUE_H
#include "../Heap/Heap.h"
#include "Info.h"

template <typename T>
class PQueue
{
public:

    //Constructor
    PQueue(bool debug = false);

    //Insertion Function
    void insert(const T& value, int p);

    //Accessor Function
    T Front();
    int size() const;

    //Pop Functions

    T Pop();
    Info<T> Pop_Debug();

    //Empty Function
    bool is_empty() const;

    //Output Function / Operator
    void print_tree(ostream& outs) const;

    template<typename U>
    friend ostream& operator <<(ostream& outs, const PQueue<U>& print_me);

private:

    bool _debug;    //True if the Queue is in debug mode.
    Heap<Info<T>> _heap;    //Internal heap for storing Info structs.
    int _time;  //Current timestamp.

};

template<typename T>
PQueue<T>::PQueue(bool debug) : _time(0), _debug(debug) {}

template<typename T>
void PQueue<T>::insert(const T& value, int p)
{
    _heap.insert(Info<T>(value, p, _time++));
            //An info struct is inserted into the heap with the current time
            //stamp, an inputted value, and an inputted priority.
}

template<typename T>
T PQueue<T>::Front()
{
    return _heap.Peek()._item;
            //The item with the highest priority is returned.
}

template<typename T>
T PQueue<T>::Pop()
{
    return _heap.Pop()._item;
            //The item with the highest priority is removed then returned.
}

template<typename T>
Info<T> PQueue<T>::Pop_Debug()
{
    assert(_debug);
    return _heap.Pop();
            //Returns the Info item at the top of the PQueue
            //NOTE: I only implemented this function for the lab since it
            //asks for us to "pop then print them (the elements)" in
            //descending order of priority. This function is only used for
            //this lab to show the priority and the time stamp in main, and
            //will not be used in the future. The regular pop function will
            //only pop the item.
}

template<typename T>
bool PQueue<T>::is_empty() const
{
    return _heap.is_empty();
            //Returns if there are no more items in the PQueue.
}

template<typename T>
int PQueue<T>::size() const
{
    return _heap.size();
            //Returns the number of items in the PQueue.
}

template<typename T>
void PQueue<T>::print_tree(ostream& outs) const
{
    outs << _heap;
            //Prints the PQueue as a tree.
}

template<typename U>
ostream& operator<<(ostream& outs, const PQueue<U>& print_me)
{
    outs << print_me._heap;
    return outs;
}

#endif // !PQUEUE_H