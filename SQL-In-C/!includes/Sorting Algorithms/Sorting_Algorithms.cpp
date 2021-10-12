#include "Sorting_Algorithms.h"

// --------------------------------------------------------------------
// ---------------------------- HEAP SORT -----------------------------
// --------------------------------------------------------------------

void heapSort(int* arr, unsigned int size)
{
    Heap<int> h;

    for (int i = 0; i < size; i++)
        h.insert(arr[i]);

    for (int i = size - 1; i >= 0; i--)
        arr[i] = h.Pop();
}

/*
* All elements of the array are inserted into a max heap:
* 
* 5, 2, 7, 1, 10, 3 ---->       10
*                            3      7
*                          1   2  5
* 
* Every element of the max heap is popped, then inserted back into the array
* starting from the end; 
* 
* Inserting 10:
* 
* 5, 2, 7, 1, 10, [10]
*                  ^
*                  |
*                  -----------  [10]
*                             3      7
*                           1   2  5
* 
* Inserting 7:
* 
* 
* 5, 2, 7, 1, [7], 10
*              ^
*              |
*              ---------------  [7]
*                             3     5
*                           1   2  
* Inserting 5:
*
*
* 5, 2, 7, [5], 7, 10
*           ^
*           |
*           ------------------  [5]
*                             3     
*                           1   2
* 
* Inserting 3:
*
*
* 5, 2, [3], 5, 7, 10
*        ^
*        |
*        ---------------------  [3]
*                             2
*                           1  
* 
* Inserting 3:
*
*
* 5, [2], 7, 5, 7, 10
*     ^
*     |
*     ------------------------  [2]
*                             1
* 
* Inserting 3:
*
*
* [1], 2, 7, 5, 7, 10
*  ^
*  |
*  ---------------------------  [1]
* 
* Final Array:
*
* 1, 2, 7, 5, 7, 10
* 
*/

// --------------------------------------------------------------------
// ---------------------------- BUBBLE SORT ---------------------------
// --------------------------------------------------------------------

void bubbleSort(int* arr, unsigned int size)
{
    int temp;
    bool complete = false;

    for (int i = 0; i < size - 1 && !complete; i++) {
        complete = true;

        for (int e = 0; e < size - i - 1; e++) {

            if (arr[e] > arr[e + 1]) {

                temp = arr[e];
                arr[e] = arr[e + 1];
                arr[e + 1] = temp;

                complete = false;

            }

        }
    }
}

/*
* Bubble sort goes through the entire array and swaps two consecutive elements
* until the largest value is at the top:
* 
*       [5], [2], 7, 1, 10, 3
*        ^                  ^
*        |                  |
*        e                  size - i - 1
* 
*       2, [5], [7], 1, 10, 3
*           ^
*           |
*           e
* 
*       2, 5, [7], [1], 10, 3
*              ^
*              |
*              e
* 
*       2, 5, 1, [7], [10], 3
*                 ^
*                 |
*                 e
* 
*       2, 5, 1, 7, [10], [3]
*                    ^
*                    |
*                    e
* 
*       2, 5, 1, 7, 3, 10
* 
*       i--; the cycle repeats with a smaller i:
*       
*       [2], [5], 1, 7, 3, 10
*        ^              ^
*        |              |
*        e              size - i - 1
* 
*       2, [5], [1], 7, 3, 10
*           ^
*           |
*           e
* 
*       2, 1, [5], [7], 3, 10
*              ^
*              |
*              e
* 
*       2, 1, 5, [7], [3], 10
*                 ^
*                 |
*                 e
* 
*       2, 1, 5, 3, 7, 10
* 
*       i--; the cycle repeats until the list is sorted:
* 
*       1, 2, 3, 5, 7, 10
*/
// --------------------------------------------------------------------
// ---------------------------- MERGE SORT ----------------------------
// --------------------------------------------------------------------

        //Algorithm taken from: https://www.geeksforgeeks.org/merge-sort/

void mergeSort(int* arr, unsigned int size)
{
    mergeSort(arr, 0, size - 1);
}

void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {

        // Same as (l+r)/2, but avoids 
        // overflow for large l and h
        int m = l + (r - l) / 2;

        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

void merge(int arr[], int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;

    // Create temp arrays 
    int* L = new int[n1];
    int* R = new int[n2];

    // Copy data to temp arrays L[] and R[] 
    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // Merge the temp arrays back into arr[l..r]

    // Initial index of first subarray
    int i = 0;

    // Initial index of second subarray
    int j = 0;

    // Initial index of merged subarray
    int k = l;

    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of
    // L[], if there are any 
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of
    // R[], if there are any 
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }

    delete[] L;
    delete[] R;
}

/*
* Merge sort will split the list in half, then will split the seperated lists
* in half until there are songle list sub parts, then the lists are recombined
* in order until the original, sorted list is reformed (Divide and Conquer):
* 
*           [5, 2, 7, 1, 3, 10]
* 
*           [5, 2, 7, 1] [3, 10]
* 
*           [5, 2] [7, 1] [3] [10]
* 
*           [5] [2] [7] [1] [3] [10]
* 
*           [5, 2] [7, 1] [3, 10]
* 
*           [1, 2, 5, 7] [3, 10]
* 
*           [1, 2, 3, 5, 7, 10]
* 
*/
// --------------------------------------------------------------------
// ---------------------------- QUICK SORT ----------------------------
// --------------------------------------------------------------------

        //Algorithm taken from: https://www.geeksforgeeks.org/quick-sort/

void quickSort(int* arr, unsigned int size)
{
    quickSort(arr, 0, size - 1);
}

int partition(int arr[], int low, int high)
{
    int pivot = arr[high];    // pivot 
    int i = (low - 1);  // Index of smaller element 
    int temp;

    for (int j = low; j <= high - 1; j++)
    {
        // If current element is smaller than or 
        // equal to pivot 
        if (arr[j] <= pivot)
        {
            i++;    // increment index of smaller element 
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}

/* The main function that implements QuickSort
 arr[] --> Array to be sorted,
  low  --> Starting index,
  high  --> Ending index */
void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        /* pi is partitioning index, arr[p] is now
           at right place */
        int pi = partition(arr, low, high);

        // Separately sort elements before 
        // partition and after partition 
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

/*
* Quick sort works using a similar divide and conquer algorithm as merge sort;
* The array is split in half by a pivot point (the last element, in our case)
* where items less than the pivot are below and items greater than the pivot
* are above. After this, the two halves are also partitioned by the largest
* value and made into smaller arrays. After this is over, the entire array
* will be sorted:
* 
*   Ex.
* 
*       7, 2, 10, 1, 3, [5]
*                        ^
*                        |
*                   5 <----------------- Initial Pivot Point
*                 /   \
*       2, 1, [3]      7, [10]
*           /     \        /
*       2, [1]     []    [7]
*       /       \
*      []        [2]
* 
* When the arrays are put back together, the list is sorted:
* 
*       1, 2, 3, 5, 7, 10
* 
*/

// --------------------------------------------------------------------
// ------------------------- SELECTION SORT ---------------------------
// --------------------------------------------------------------------

void selectionSort(int* arr, unsigned int size)
{
	int minLoc = 0, temp;

	for (int i = 0; i < size - 1; i++) {
		minLoc = i;

		for (int e = i + 1; e < size; e++) {

			if (arr[e] < arr[minLoc])
				minLoc = e;

		}

		temp = arr[minLoc];
		arr[minLoc] = arr[i];
		arr[i] = temp;

	}
}


/*
* Selections sort iterates starting from the begninning of the array;
* it finds the smallest value in the list and swaps it with the first element
* , then the iterator moves on. This happens until the list is sorted:
*
*   Ex.
*
*       7, 2, 10, 1, 3, 5
*       ^         ^
*       |         |
*       i         e
*
*       Swap 7 and 1:
*
*       1, 2, 10, 7, 3, 5
*          ^
*          |
*         i,e
*
*       Swap 2 and 2:
*
*       1, 2, 10, 7, 3, 5
*             ^      ^
*             |      |
*             i      e
*
*       Swap 10 and 3:
*
*       1, 2, 3, 7, 10, 5
*                ^     ^
*                |     |
*                i     e
*
*       Swap 7 and 5:
*
*       1, 2, 3, 5, 10, 7
*                   ^   ^
*                   |   |
*                   i   e
*
*       Swap 10 and 7:
*
*       1, 2, 3, 5, 7, 10
*
*       Now the list is sorted.
*
*/