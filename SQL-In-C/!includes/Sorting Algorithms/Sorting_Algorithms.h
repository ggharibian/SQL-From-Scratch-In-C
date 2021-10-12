#ifndef SORTING_ALGORITHMS_H
#define SORTING_ALGORITHMS_H
#include "../Heap/Heap.h"

//Heap Sort

void heapSort(int* arr, unsigned int size);

//Bubble Sort

void bubbleSort(int* arr, unsigned int size);

//Merge Sort

void mergeSort(int* arr, unsigned int size);

void mergeSort(int arr[], int l, int r);

void merge(int arr[], int l, int m, int r);

//Quick Sort

void quickSort(int* arr, unsigned int size);

void quickSort(int arr[], int low, int high);

int partition(int arr[], int low, int high);

//Selection Sort

void selectionSort(int* arr, unsigned int size);

#endif // !SORTING_ALGORITHMS_H
