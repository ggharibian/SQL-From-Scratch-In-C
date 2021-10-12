#ifndef ONED_H
#define ONED_H
#include <cassert>
#include <iostream>
#include <iomanip>
using namespace std;

//DEFINITIONS

bool isValid(int loc, int size);
											//Function that takes in an
											//array size and index location
											//and returns whether the index
											//is within the array's range.
									//Precondition: None
									//Postcondition: The function will return
									//true if 0 <= loc < size.

template<typename T>
T read(T* arr, int loc, int size);
											//This function returns the value
											//at location "loc" the array 
											//"arr".
									//Precondition: 0 <= loc < size
									//				0 <= size <= len(arr)
									//Postcondition: The value at the index
									//location "loc" has been returned.

template<typename T>
T& get(T* arr, int loc, int size);
											//This function returns the 
											//reference location of the value
											//at index "loc" the array "arr".
									//Precondition: 0 <= loc < size
									//				0 <= size <= len(arr)
									//Postcondition: The value at the index
									//location "loc" has been returned.

template<typename T>
void write(T* arr, T value, int loc, int size);
											//This function takes in a value
											//and an index location in an 
											//array and assigns the value at
											//that array.
									//Precondition: 0 <= loc < size
									//				loc < size <= len(arr)
									//Postcondition: The location "loc" in the
									//array has been assigned the value 
									//"value".

template<typename T>
T* findInArray(T* arr, T value, int size);
											//This function takes in a array
											//and value and returns a pointer
											//location in the array where the
											//value appears. Returns nullptr 
											//if not in the array.
									//Precondition: size <= len(arr)
									//Postcondition: The pointer location in
									//arr where the value appears is returned.
template<typename T>
int indexOf(T* arr, T value, int size);
											//This function takes in a array
											//and value and returns the index
											//location in the array where the
											//value appears. Returns -1 if not
											//in the array.
									//Precondition: size <= len(arr)
									//Postcondition: The index location in arr
									//where the value appears is returned.

template<typename T>
void shiftLeft(T* location, T* arr, int& size);
												//Function that takes in an
												//array and pointer and 
												//deletes the location from  
												//the array and reducing the
												//size.
										//Precondition: size <= len(arr)
										//				location < arr + size
										//				location >= arr
										//Postcondition: The value at location
										//				has been deleted
										//				(overwritten).

template<typename T>
void shiftRight(T* location, T* arr, int& size, int capacity);
												//Function that takes in an
												//array and pointer and 
												//deletes the location from  
												//the array and reducing the
												//size.
										//Precondition: size <= len(arr)
										//				location < arr + size
										//				location >= arr
										//Postcondition: The value at location
										//				has been deleted
										//				(overwritten).

template<typename T>
void copy_list(T* destination, T* source, int destSize, int srcSize,
	int numElements);
												//Function that copies
												//"numElements" values from a
												//source array to a 
												//destination array.
										//Precondition: 
										//		  destSize <= len(destination)
										//				srcSize <= len(source)
										//				numElements < destSize
										//				numElements < srcSize
										//Postcondition: "numElements" values
										//from source has been copied to 
										//destination.

template<typename T>
T* allocate(int capacity);
											//This function returns a dynamic
											//array with the length
											// "capacity".
									//Precondition: capacity >= 0
									//Postcondition: An array of size capacity
									//has been returned.

template<typename T>
T* reallocate(T* arr, int& currentCapacity, int newCapacity);
											//This function takes in an array
											//of a certain capacity and
											//returns a pointer to a new array
											//with a new capacity and the same
											//values. The old array is 
											//deleted.
									//Precondition: newCapacity >= 0
									//				currentCapacity >= 0
									//Postcondition: An array of size 
									//newCapacity with the same values as arr
									//has been returned.

template<typename T>
void deallocate(T* arr);
											//This function takes in a dynamic
											//array and deallocates it.
									//Precondition: 0 <= loc < size
									//				loc < size <= len(arr)
									//Postcondition: The arr has been
									//deallocated.

template<typename T>
void print(T* arr, int size, ostream& outs = cout, int width = -1);
												//Print array function that
												//utilizes pointers.

										//Precondition: size <= len(arr),
										//				size >= 0
										//Postcondition: size elements of
										//				of arr have been
										//				printed.

template<typename T>
void init(T* arr, int size, const T& value = T());
											//This function assigns "size"
											//values in the array "arr" 
											//to "value".
									//Precondition: 0 <= loc < size
									//				loc < size <= len(arr)
									//Postcondition: The location "loc" in the
									//array has been assigned the value 
									//"value".

//DECLARATIONS

template<typename T>
T read(T* arr, int loc, int size) {
	assert(isValid(loc, size));	//Exits the program if loc is not a valid 
								//location.

	return get(arr, loc, size);
						//The value at loc is returned.
}

template<typename T>
T& get(T* arr, int loc, int size) {
	assert(isValid(loc, size));	//Exits the program if loc is not a valid 
								//location.

	T* current = loc + arr;
							//The reference location designated by the 
							//inputted index value.
	return *current;
						//The reference location designated by loc is returned
}

template<typename T>
void write(T* arr, T value, int loc, int size) {
	assert(isValid(loc, size));	//Exits the program if loc is not a valid 
								//location.

	get(arr, loc, size) = value;
						//Assigns the desired index with the value "value".
}

template<typename T>
T* findInArray(T* arr, T value, int size) {
	assert(size >= 0);
						//Exits program if an invalid size has been inputted.

	T* walker = arr;
	T* end = arr + size;
						//Walker and end pointers used for iterating through
						//the entire array.

	while (walker < end) {
					//this loop will iterate through the entire array of
					//values.
		if (*walker == value) {

			return walker;
						//The reference location of the desired
						//value. This is returned if the current location
						//of the walker is equal to the value we are looking
						//for.
		}

		walker++;
	}

	return nullptr;
				//Returns -1 if the value is not found in the array.
}

template<typename T>
int indexOf(T* arr, T value, int size)
{
	T* temp = findInArray(arr, value, size);
	if (temp != NULL)
		return findInArray(arr, value, size) - arr;

	return -1;
}

template<typename T>
void shiftLeft(T* location, T* arr, int& size) {

	T* end = arr + size;		//Pointer at end of array.

	T* next = location + 1;		//Walker that traces the following value after
								//"location".


	while (next < end) {
		//Loop iterating over size - 1 elements
		//in the array. 
		//NOTE: The last value in the array does not
		//need to be swapped. It is garbage after the
		//loop.

		*location = *next;
				//Overrides value at "location" with the
				//following value.

		location++;
		next++;
				//Iterate to the next value.
	}

	size--;
			//Decreases size after element has been removed.
}

template<typename T>
void shiftRight(T* location, T* arr, int& size, int capacity){
	assert(size < capacity && location - arr <= size);
	size++;

	T* current = arr + size - 2;
	T* next = current + 1;		//Walker that traces the following value after
								//"location".

	T temp;
	while (current >= location) {
		//Loop iterating over size - 1 elements
		//in the array. 
		//NOTE: The last value in the array does not
		//need to be swapped. It is garbage after the
		//loop.

		temp = *current;
		*current = *next;
		*next = temp;
		//Overrides value at "location" with the
		//following value.

		current--;
		next--;
		//Iterate to the next value.
	}

	*location = T();
	//Decreases size after element has been removed.
}

template<typename T>
void copy_list(T* destination, T* source, int destCapacity, int srcCapcity,
	int numElements) {

	if (numElements != 0) {
		assert(isValid(numElements - 1, srcCapcity));
		assert(isValid(numElements - 1, destCapacity));
						//The program will end if the number of elements being
						//copied is greater than the size of either of the
						//arrays.
	}

	T* sourceWalker = source;
	T* destinationWalker = destination;
						//Walker pointers for both arrays to iterate over
						//parallel indexes in both arrays.

	T* sourceEnd = source + numElements;
						//Pointer to the end of the first "numElements" values
						//in the source array.
						

	while (sourceWalker < sourceEnd) {
					//This loop will iterate through the first "numElements"
					//values in the array.

		*destinationWalker = *sourceWalker;
		sourceWalker++;
		destinationWalker++;
					//The values from the source array will be copied to the
					//equivalent indices of the destination array.
	}
}

template<typename T>
T* allocate(int capacity)
{
	return new T[capacity];
							//creates a new dynamic array with the size 
							//"capacity" and returns it. 
}

template<typename T>
T* reallocate(T* arr, int& currentCapacity, int newCapacity)
{
	assert(newCapacity >= 0);
					//The program will exit if the new capacity is not
					//"valid" capacity (must be greater than 0).

	T* newArr = new T[newCapacity];
					//A new dynamic array created to replace the current
					//array.

	if (newCapacity < currentCapacity) {
		copy_list(newArr, arr, newCapacity, currentCapacity, newCapacity);
	}
	else {
		copy_list(newArr, arr, newCapacity, currentCapacity, currentCapacity);
		init(newArr + currentCapacity, newCapacity - currentCapacity);
	}
					//Copies all the elements from the current array to the
					//new array.

	delete[] arr;
					//The old array has been deleted.

	currentCapacity = newCapacity;

	return newArr;
					//The new array is returned.
}

template<typename T>
void deallocate(T* arr) {
	delete[] arr;
					//Deletes the array at the location "arr".
}

template<typename T>
void print(T* arr, int size, ostream& outs, int width) {
	T* end = arr + size;		//Pointer at the end of the array.

	while (arr < end) {

		if (width >= 0)
			outs << setw(width) << *arr;
		else
			outs << *arr << " ";
		arr++;
		//Loop iterates through and prints the first size
		//elements of the array.

	}
}

template<typename T>
void init(T* arr, int size, const T& value) {

	T* current = arr;
	T* end = arr + size;
						//variables for the reference location of the start
						//end of the array.
	while (current < end) {
		*current = value;
		current++;
					//Goes through the entire array and reassigns every 
					//location to the value "value".
	}
}

#endif