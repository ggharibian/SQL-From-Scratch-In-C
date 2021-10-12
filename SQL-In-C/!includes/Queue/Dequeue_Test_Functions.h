#ifndef DEQUEUE_TEST_FUNCTIONS_H
#define DEQUEUE_TEST_FUNCTIONS_H

#include <random>
#include <ctime>
#include <iostream>
#include "Dequeue.h"

Dequeue<int> getAscendingDequeue();

Dequeue<int> getDecendingDequeue();

Dequeue<int> getRandomDequeue();

void testDequeueCopyConstructor();

void testDequeueAssignmentOperator();

void testDequeueDeallocate();

void testDequeuePushFront();

void testDequeuePushBack();

void testDequeuePopFront();

void testDequeuePopBack();

void testDequeueFront();

void testDequeueEmpty();

void testDequeueOutput();

void testDequeueIterator();


#endif // !DEQUEUE_TEST_FUNCTIONS_H
