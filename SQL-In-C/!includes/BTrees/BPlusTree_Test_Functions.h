#ifndef BPLUSTREE_TEST_FUNCTIONS_H
#define BPLUSTREE_TEST_FUNCTIONS_H
#include <random>
#include <ctime>
#include "BPlusTree.h"
using namespace std;

BPlusTree<int> getBPlusTree();

void testBPlusTreeClearFunction();

void testBPlusTreeContains();

void testBPlusTreeGet();

void testBPlusTreeFind();

void testBPlusTreeInsert();

void testBPlusTreeErase();

void testBPlusTreeIsValid();

void testBPlusTreeOutput();

#endif // !BPLUSTREE_TEST_FUNCTIONS_H

