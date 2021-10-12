#ifndef MAP_TEST_FUNCTIONS
#define MAP_TEST_FUNCTIONS
#include <random>
#include <ctime>
#include "Map.h"
using namespace std;

Map<int, int> getMap();

void testMapClearFunction();

void testMapContains();

void testMapGet();

void testMapFind();

void testMapInsert();

void testMapErase();

void testMapIsValid();

void testMapOutput();

#endif // !MAP_TEST_FUNCTIONS
