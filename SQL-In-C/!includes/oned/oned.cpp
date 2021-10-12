#include "oned.h"

bool isValid(int loc, int size) {
	return (loc < size && loc >= 0); //Checks if the index location loc is out
									 //of bounds.
}