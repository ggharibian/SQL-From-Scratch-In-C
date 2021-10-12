#ifndef MMAP_TEST_FUNCTIONS_H
#define MMAP_TEST_FUNCTIONS_H
#include <random>
#include <ctime>
#include "MultiMap.h"
using namespace std;

MMap<int, int> getMMap();

void testMMapClearFunction();

void testMMapContains();

void testMMapGet();

void testMMapFind();

void testMMapInsert();

void testMMapErase();

void testMMapCount();

void testMMapIsValid();

void testMMapOutput();

#endif // !MMAP_TEST_FUNCTIONS_H
