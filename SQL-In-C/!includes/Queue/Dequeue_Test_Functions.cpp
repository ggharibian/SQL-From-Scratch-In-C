#include "Dequeue_Test_Functions.h"

Dequeue<int> getAscendingDequeue()
{	//Returns an ascending Dequeue.
	Dequeue<int> q;

	for (int i = 1; i <= 10; i++)
		q.PushBack(i * 10);

	return q;
}

Dequeue<int> getDecendingDequeue()
{	//Returns an decending Dequeue.
	Dequeue<int> q;

	for (int i = 10; i >= 1; i--)
		q.PushBack(i * 10);

	return q;
}

Dequeue<int> getRandomDequeue()
{	//Returns a Dequeue of random values
	Dequeue<int> q;

	for (int i = 0; i < 10; i++)
		q.PushBack(rand() % 100 + 1);

	return q;
}

void testDequeueCopyConstructor()
{
	cout << "============ Testing Copy Constructor ============" << endl;
	cout << endl << "Copying Filled Dequeue:" << endl;
	cout << "//Calling 'copy = q'; copy ==> H->[10]->[20]-> ... ->[100]->|||"
		<< endl << endl;

	Dequeue<int> q = getAscendingDequeue();

	Dequeue<int> copy(q);

	cout << "Popping " << q.PopFront() << " out of q." << endl << endl;

	cout << "Printing s: " << q << endl;
	cout << "Printing copy: " << copy;

	cout << endl << endl << "Copying Empty Dequeue:" << endl;
	cout << "//Calling 'otherCopy(s)'; otherCopy ==> H->|||" << endl << endl;

	q.~Dequeue();

	Dequeue<int> otherCopy(q);

	cout << "Printing s: " << q << endl;
	cout << "Printing otherCopy: " << otherCopy << endl;

	cout << "\n============ END TEST ========================" << endl << endl;
}

void testDequeueAssignmentOperator()
{
	cout << "============ Testing '=' operator ============" << endl;
	cout << endl << "Copying Filled Dequeue:" << endl;
	cout << "//Calling 'copy = q'; copy ==> H->[10]->[20]-> ... ->[100]->|||"
		<< endl << endl;

	Dequeue<int> q = getAscendingDequeue();

	Dequeue<int> copy = q;

	cout << "Popping " << q.PopFront() << " out of q." << endl << endl;

	cout << "Printing s: " << q << endl;
	cout << "Printing copy: " << copy;

	cout << endl << endl << "Self Reference:" << endl;
	cout << "//Calling 'q =  s'; q ==> H->[20]->[30]-> ... ->[100]->|||"
		<< endl << endl;

	q = q;

	cout << "Printing s: " << q << endl;

	cout << endl << endl << "Copying Empty Dequeue:" << endl;
	cout << "//Calling 'copy = q'; copy ==> H->|||" << endl << endl;

	q.~Dequeue();

	copy = q;

	cout << "Printing s: " << q << endl;
	cout << "Printing copy: " << copy;

	

	cout << "\n============ END TEST ========================" << endl << endl;
}

void testDequeueDeallocate() {
	cout << "============ Testing Deallocation ============" << endl << endl;
	cout << "//Calling q.~Dequeue(); H->[10]->[20]->... ==> H->|||"
		<< endl << endl;

	Dequeue<int> q = getAscendingDequeue();

	cout << q << endl << endl;

	q.~Dequeue();

	cout << q << endl;

	cout << "\n============ END TEST ========================" << endl << endl;
}

void testDequeuePushFront()
{
	cout << "============ Testing PushFront() ============" << endl;
	cout << endl << "//Adding multiples of 10 to s: 100 -> 90 -> 80 -> ... 20 -> 10 -> |||"
		<< endl << endl;

	Dequeue<int> q;

	cout << q << endl << endl;

	for (int i = 10; i >= 1; i--)
		cout << *q.PushFront(i * 10) << " has been PushFronted." << endl;

	cout << endl << q << endl;

	cout << "\n============ END TEST ========================" << endl << endl;
}

void testDequeuePushBack()
{	//Tests 
	cout << "============ Testing PushBack() ============" << endl;
	cout << endl <<"//Adding multiples of 10 to s: 10 -> 20 -> 30 -> ... 90 -> 100 -> |||"
		<< endl << endl;

	Dequeue<int> q;

	cout << q << endl << endl;

	for (int i = 10; i >= 1; i--)
		cout << *q.PushBack(i * 10) << " has been PushBacked." << endl;

	cout << endl << q << endl;

	cout << "\n============ END TEST ========================" << endl << endl;
}

void testDequeuePopFront() {
	cout << "============ Testing PopFront() ============" << endl;
	cout << endl << "Popping all values from a Dequeue:" << endl;
	cout << "//H->[10]->[20]->[30]->... ==> H->|||" << endl << endl;

	Dequeue<int> q;

	q = getAscendingDequeue();

	cout << q << endl << endl;

	while (!q.Empty())
		cout << q.PopFront() << " has been popped." << endl;

	cout << endl << q << endl;

	
	cout << "\n============ END TEST ========================" << endl << endl;
}

void testDequeuePopBack()
{
	cout << "============ Testing PopBack() ============" << endl;
	cout << endl << "Popping all values from a Dequeue:" << endl;
	cout << "//H->[10]->[20]->[30]->... ==> H->|||" << endl << endl;

	Dequeue<int> q;

	q = getAscendingDequeue();

	cout << q << endl << endl;

	while (!q.Empty())
		cout << q.PopBack() << " has been popped." << endl;

	cout << endl << q << endl;


	cout << "\n============ END TEST ========================" << endl << endl;
}

void testDequeueFront()
{
	cout << "============ Testing Front ============" << endl;
	cout << endl << "Accessing Front of filled Dequeue:" << endl;
	cout << "//Calling q.Front() ==> 100"
		<< endl << endl;

	Dequeue<int> q = getDecendingDequeue();

	cout << q << endl << endl;

	cout << "q.Front() = " << q.Front() << endl;

	cout << "\n============ END TEST ========================" << endl << endl;
}

void testDequeueEmpty()
{
	cout << "============ Testing Empty ============" << endl;
	cout << endl << "Checking if filled Dequeue is empty:" << endl;
	cout << "//Calling q.Empty() ==> 0 (false)"
		<< endl << endl;

	Dequeue<int> q = getAscendingDequeue();

	cout << q << endl << endl;
	cout << "q.Empty() = " << q.Empty() << endl;

	q.~Dequeue();

	cout << endl << endl << "Checking if empty Dequeue is empty:" << endl;
	cout << "//Calling q.Empty() ==> 1 (true)"
		<< endl << endl;

	cout << q << endl << endl;
	cout << "q.Empty() = " << q.Empty() << endl;

	cout << "\n============ END TEST ========================" << endl << endl;
}

void testDequeueOutput()
{	//Tests 
	cout << "============ Testing Print / '<<' ============" << endl;
	cout << endl << "//Adding multiples of 10 to s: 10 -> 20 -> 30 -> ... 90 -> 100 -> |||"
		<< endl << endl;

	Dequeue<int> q = getAscendingDequeue();

	cout << "q.Print() ==> ";
	q.Print();

	cout << endl << "'cout << s' ==> ";
	cout << q << endl;


	cout << "\n============ END TEST ========================" << endl << endl;
}

void testDequeueIterator()
{
	cout << "============ Testing Dequeue Iterator ============" << endl << endl;
	cout << "Calling the current value of the iterator in the Dequeue:";
	cout << endl << "//*iter ==> [10]->"
		<< endl << endl;

	Dequeue<int> q = getAscendingDequeue();

	cout << q << endl << endl;

	Dequeue<int>::Iterator iter = q.Begin();

	cout << "*iter = " << *iter << endl << endl;

	cout << "Calling the next value of the Dequeue using iterator:";
	cout << endl << "//*(iter.Next()) ==> [20]->"
		<< endl << endl;

	cout << q << endl << endl;
	cout << "*(iter.Next()) = " << *(iter.Next()) << endl << endl;

	cout << "Calling a prev value of the Dequeue using iterator:";
	cout << endl << "//*(iter.Next().Prev()) ==> [10]->"
		<< endl << endl;

	cout << q << endl << endl;
	cout << "*(iter.Next().Prev()) = " << *(iter.Next().Prev()) << endl << endl;

	cout << "Accessing a value inside iterator using '->':";
	cout << endl << "//iter->_obj ==> 10"
		<< endl << endl;

	cout << q << endl << endl;
	cout << "iter->_obj = " << *iter << endl << endl;

	cout << "Calling the prefix and postfix '++' operators:";
	cout << endl << "//otherIter = ++iter; otherIter, iter ==> [20]->, [20]->"
		<< endl << endl;

	iter = q.Begin();

	cout << "Calling otherIter = ++iter" << endl << endl;
	Dequeue<int>::Iterator otherIter = ++iter;

	cout << "*otherIter = " << *otherIter << endl;
	cout << "*iter = " << *iter << endl;

	cout << endl << "//otherIter = iter++; otherIter, iter ==> [10]->, [20]->"
		<< endl;

	iter = q.Begin();

	cout << endl << "Calling otherIter = iter++" << endl;
	otherIter = iter++;

	cout << "*otherIter = " << *otherIter << endl;
	cout << "*iter = " << *iter << endl;

	cout << endl;

	cout << "Calling the prefix and postfix '--' operators:";
	cout << endl << "//otherIter = --iter; otherIter, iter ==> [20]->, [20]->"
		<< endl << endl;

	iter = q.Begin().Next().Next();

	cout << "Calling otherIter = --iter" << endl << endl;
	otherIter = --iter;

	cout << "*otherIter = " << *otherIter << endl;
	cout << "*iter = " << *iter << endl;

	cout << endl << "//otherIter = iter--; otherIter, iter ==> [30]->, [20]->"
		<< endl;

	iter = q.Begin().Next().Next();

	cout << endl << "Calling otherIter = iter--" << endl;
	otherIter = iter--;

	cout << "*otherIter = " << *otherIter << endl;
	cout << "*iter = " << *iter << endl;

	cout << endl << "Calling the '!=' operators:";
	cout << endl << "//otherIter != iter ==> 1 (true) "
		<< endl << endl;

	cout << "otherIter != iter: " << (otherIter != iter) << endl;

	cout << endl << "//otherIter != otherIter ==> 0 (false) "
		<< endl << endl;

	cout << "otherIter != otherIter: " << (otherIter != otherIter) << endl;

	cout << "\n============ END TEST ========================" << endl << endl;
}