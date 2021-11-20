#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
 * https://visualgo.net/en
 */

/*
 *
 *  Iterative sorting algorithms (comparison based)
 *   Selection Sort
 *	 Bubble Sort
 *	 Bubble Sort
 *	 Insertion Sort
 *
 *  Recursive sorting algorithms (comparison based)
 *	 Merge Sort
 *	 Quick Sort
 * 
 *  Radix sort (non-comparison based)
 *
 */
void Swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

/*
 *
 * SELECTION SORT
 *
 *   Given an array of n items
 *  	1. Find the largest item x, in the range of [0…n−1]
 *		2. Swap x with the (n−1) item
 *		3. Reduce n by 1 and go to Step 1
 *
 */
void Selection_Sort(int* arr, int number)
{
	int i, j, maxIndex;
	for(i=number-1; i >= 1; i--)
	{
		maxIndex = i;
		for(j=0; j<i; j++)
		{
			if(arr[j] >= arr[maxIndex])
			{
				maxIndex = j;
			}
		}	
		Swap(&arr[i], &arr[maxIndex]);
	}
}

/*  BUBBLE SORT
 *	 Given an array of n items
 *		1. Compare pair of adjacent items
 *		2. Swap if the items are out of order
 *		3. Repeat until the end of array 
 *	 The largest item will be at the last position
 *		4. Reduce n by 1 and go to Step 1
 *
 *	 Analogy
 *		 Large item is like “bubble” that floats to the end of the array
 *
 * Analysis
 *  1 iteration of the inner loop (test and swap) requires time bounded by a constant c
 *  Two nested loops
 * 		 Outer loop: exactly n iterations
 * 		 Inner loop:
 * 			 when i=0, (n−1) iterations
 * 			 when i=1, (n−2) iterations
 * 			 …
 * 			 when i=(n−1), 0 iterations
 *  Total number of iterations = 0+1+…+(n−1) = n(n−1)/2
 *  Total time = c n(n−1)/2 = O(n^2)
 */
void Bubble_Sort(int* arr, int number)
{
	for (int i = number-1; i >= 1; i--)
	{
		for (int j = 1; j <= i; j++)
		{
			if (arr[j-1] > arr[j])
			{
				Swap(&arr[j], &arr[j-1]);
			}
		}
	}
}

void BubbleSort2(int a[], int n)
{
	for (int i = n-1; i >= 1; i--)
	{
		bool is_sorted = true;           //Assume the array is sorted before the inner loop
		for (int j = 1; j <= i; j++)
		{
			if (a[j-1] > a[j]) 
			{
				Swap(&a[j], &a[j-1]);
				is_sorted = false;       //Any swapping willinvalidate the assumption
			}
		} // end of inner loop
		
		if (is_sorted) return;           //If the flag remains true after the inner loop sorted!
	}
}

/*
 * Insertion Sort
 * 
 *  Similar to how most people arrange a hand of poker cards
 * 	   Start with one card in your hand
 * 	   Start with one card in your hand
 * 	   Pick the next card and insert it into its proper sorted order
 * 	   Repeat previous step for all cards
 *
 * Analysis
 *  Outer-loop executes (n−1) times
 *  Number of times inner-loop is executed depends on the input
 * 		 Best-case: the array is already sorted and (a[j] > next) is always false
 * 		-	 No shifting of data is necessary
 * 		 Worst-case: the array is reversely sorted and (a[j] > next) is always true
 * 		-	 Insertion always occur at the front
 *  Therefore, the best-case time is O(n)
 *  And the worst-case time is O(n^2)
 */

void insertionSort(int a[], int n)
{
	for (int i = 1; i < n; i++)
	{
		int next = a[i];   //Next is the item to be inserted
		int j;
		for (j = i-1; j >= 0 && a[j] > next; j--)
		{
			a[j+1] = a[j]; //Shift sorted items to make place for next
		}
		a[j+1] = next;
	}
}

/*
 * Merge Sort
 *
 *   Merge Sort is a divide-and-conquer sorting algorithm
 *   Divide step 
 *		 Divide the array into two (equal) halves
 *		 Recursively sort the two halves
 *	 Conquer step
 *		 Merge the two halves to form a sorted array
 * O(n) extra memory storage needed 
 */
 
void merge(int a[], int low, int mid, int high)
{
	int n = high-low+1;
    
	// b is a temporary  array to store result
	int* b = calloc(n, sizeof(int));
	int left=low, right=mid+1, bIdx=0;

	// Normal Merging Where both halves have unmerged items 
	while (left <= mid && right <= high)
	{
		if (a[left] <= a[right])
			b[bIdx++] = a[left++];
		else
			b[bIdx++] = a[right++];
	}
	
	// Remaining items are copied into b[]
	while (left <= mid) b[bIdx++] = a[left++];
	while (right <= high) b[bIdx++] = a[right++];

	// Merged results are copied back into a[]
	for (int k = 0; k < n; k++)
		a[low+k] = b[k];

	free(b);	// Free remaing memory
} 

void mergeSort(int a[], int low, int high)
{
	if (low < high)
	{
		int mid = (low+high) / 2;
		
		//Divide a[ ] into two halves and recursively sort them
		mergeSort(a, low  , mid );
		mergeSort(a, mid+1, high);
		
		//Conquer: merge the two sorted halves
		//Function to merge a[low…mid] and a[mid+1…high] into a[low…high]
		merge(a, low, mid, high);
	}
}

/*
 * Quick Sort
 *
 *  Quick Sort is a divide-and-conquer algorithm
 * 	  Divide step
 * 	 	 Choose an item p (known as pivot) and partition the 
 *    Choose an item p (known as pivot) and partition the items of a[i...j] into two parts
 * 	 	 Items that are smaller than p
 * 	 	 Items that are greater than or equal to p
 * 	  Recursively sort the two parts
 *  Conquer step
 * 	  Do nothing!
 *
 *  partition() splits a[low...high] into two portions
 *		 a[low ... pivot–1] and a[pivot+1 ... high]
 *  Pivot item does not participate in any further sorting
 *  In comparison, Merge Sort spends most of the time in conquer step but very little time in divide step
 * 
 * Depth of recursion is log n
 *    Depth of recursion is log n
 *    Each level takes n or fewer comparisons, so the time complexity is O(n log n)
 */

int partition(int a[], int i, int j)
{
	int p = a[i];                         //p is the pivot
	int m = i;
	for (int k = i+1; k <= j; k++)        //Go through each element in unknown region
	{
		if (a[k] < p)
		{
			m++;
			Swap(&a[k], &a[m]);
		}
		else 
		{
			//Do nothing
		}
	}
	Swap(&a[i], &a[m]);         //Swap pivot with a[m]
	return m;                   //m is the index of pivot
}

void quickSort(int a[], int low, int high)
{
	if (low < high)
	{
		//Partition a[low...high] and return the index of the pivot item
		int pivotIdx = partition(a, low, high);
		
		//Recursively sort the two portions
		quickSort(a, low, pivotIdx-1);
		quickSort(a, pivotIdx+1, high);
	}
}

void print_array(int *array, size_t size)
{
	for(int i=0; i<size; i++)
	{
		printf("%d, ",array[i]);
	}
	printf("\n");
}

void main(void)
{
	int array[] = {3,2,4,1,2,5,6,11,3,5,7,8,9,0,10,12};
	int array_single_time_entry[] = {3,2,4,1,13,5,6,11,7,8,9,0,10,12};
	
	printf("Before sorting : \n");
	print_array(array, sizeof(array) / sizeof(array[0]));

	// Selection_Sort
	//Selection_Sort(array, sizeof(array) / sizeof(array[0]));
	
	//Bubble_Sort
	//Bubble_Sort(array, sizeof(array) / sizeof(array[0]));
	//BubbleSort2(array, sizeof(array) / sizeof(array[0]));

	//insertionSort
	//insertionSort(array, sizeof(array) / sizeof(array[0]));
	
	//Merge Sort
	//mergeSort(array_single_time_entry, 0, sizeof(array_single_time_entry) / sizeof(array_single_time_entry[0]));
	
	//quickSort
	//quickSort(array_single_time_entry, 0, sizeof(array_single_time_entry) / sizeof(array_single_time_entry[0]));
	
	//	
	printf("After sorting : \n");
	print_array(array, sizeof(array) / sizeof(array[0]));
}
