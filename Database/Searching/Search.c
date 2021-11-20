/* SEARCHING:
 *
 * Searching Algorithms are designed to check for an element or retrieve an element 
 * from any data structure where it is stored. Based on the type of search operation,
 * these algorithms are generally classified into two categories:

 * 1) Sequential Search: In this, the list or array is traversed sequentially and every 
 * element is checked. For example: Linear Search.

 * 2) Interval Search: These algorithms are specifically designed for searching in sorted 
 * data-structures. These type of searching algorithms are much more efficient than Linear 
 * Search as they repeatedly target the center of the search structure and divide the search 
 * space in half. For Example: Binary Search.
 */

#include <stdio.h>

// C code to linearly search x in arr[]. If x
// is present then return its location, otherwise
// return -1
int LinearSearch(int arr[], int n, int x)
{
	int i;
	for (i = 0; i < n; i++)
		if (arr[i] == x)
			return i;
	return -1;
}

/*
 * Given a sorted array of n uniformly distributed values arr[], 
 * write a function to search for a particular element x in the array. 
 * Linear Search finds the element in O(n) time, Jump Search takes O(√ n) time and Binary Search take O(Log n) time. 
 * The Interpolation Search is an improvement over Binary Search for instances, where the values in a sorted array are 
 * uniformly distributed. Binary Search always goes to the middle element to check. On the other hand, interpolation search
 * may go to different locations according to the value of the key being searched. For example, if the value of the key is
 * closer to the last element, interpolation search is likely to start search toward the end side.
 *
 * If x is present in arr[0..n-1], then returns
 * index of it, else returns -1.
 *
 * The idea of formula is to return higher value of pos
 * when element to be searched is closer to arr[hi]. And
 * smaller value when closer to arr[lo]
 * pos = lo + [ (x-arr[lo])*(hi-lo) / (arr[hi]-arr[Lo]) ]
 *
 * arr[] ==> Array where elements need to be searched
 * x     ==> Element to be searched
 * lo    ==> Starting index in arr[]
 * hi    ==> Ending index in arr[]
 */
int interpolationSearch(int arr[], int lo, int hi, int x)
{
	int pos;
	// Since array is sorted, an element present
	// in array must be in range defined by corner
	if (lo <= hi && x >= arr[lo] && x <= arr[hi]) {
		// Probing the position with keeping
		// uniform distribution in mind.
		pos = lo
			+ (((double)(hi - lo) / (arr[hi] - arr[lo]))
					* (x - arr[lo]));

		// Condition of target found
		if (arr[pos] == x)
			return pos;

		// If x is larger, x is in right sub array
		if (arr[pos] < x)
			return interpolationSearch(arr, pos + 1, hi, x);

		// If x is smaller, x is in left sub array
		if (arr[pos] > x)
			return interpolationSearch(arr, lo, pos - 1, x);
	}
	return -1;
}

// A recursive binary search function. It returns
// location of x in given array arr[l..r] is present,
// otherwise -1
int BinarySearch_Recursive(int arr[], int l, int r, int x)
{
	if (r >= l) {
		int mid = l + (r - l) / 2;

		// If the element is present at the middle
		// itself
		if (arr[mid] == x)
			return mid;

		// If element is smaller than mid, then
		// it can only be present in left subarray
		if (arr[mid] > x)
			return BinarySearch_Recursive(arr, l, mid - 1, x);

		// Else the element can only be present
		// in right subarray
		return BinarySearch_Recursive(arr, mid + 1, r, x);
	}

	// We reach here when element is not
	// present in array
	return -1;
}

// A iterative binary search function. It returns
// location of x in given array arr[l..r] if present,
// otherwise -1
int BinarySearch(int arr[], int l, int r, int x)
{
	while (l <= r)
	{
		int m = l + (r - l) / 2;

		// Check if x is present at mid
		if (arr[m] == x)
		{
			return m;
		}
		// If x greater, ignore left half
		if (arr[m] < x)
		{
			l = m + 1;
		}
		// If x is smaller, ignore right half
		else
		{
			r = m - 1;
		}
	}

	// if we reach here, then element was
	// not present
	return -1;
}


int main(void)
{
	int arr[] = { 10, 12, 13, 16, 18, 19, 20, 21, 22, 23, 24, 33, 35, 42, 47 };
	int x = 19;
	int n = sizeof(arr) / sizeof(arr[0]);

	// Function call
	int result = LinearSearch(arr, n, x);
	//int result = BinarySearch(arr, 0, n - 1, x);
	//int result = BinarySearch_Recursive(arr, 0, n - 1, x);
	//int index = interpolationSearch(arr, 0, n - 1, x);

	(result == -1)
		? printf("Element is not present in array")
		: printf("Element is present at index %d", result);

	return 0;
}
