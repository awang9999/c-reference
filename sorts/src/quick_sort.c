#include <stdio.h>
#include <stdbool.h>
#include "quick_sort.h"

// This quicksort algorithm is based on Tony Hoare's original partition
// algorithm. This was coded based off of the pseudocode provided on the
// Wikipedia page for quick sort.

// Invariant of partition is that low <= pivot < high and that the elements of
// the array to the left of the pivot <= the pivot and that the elements to the
// right of the pivot >= the pivot.
int partition(int *arr, int l, int h)
{
    int pivot = arr[((h + l) / 2)];
    int i = l;
    int j = h;

    while (true)
    {
        while (arr[i] < pivot)
        {
            i++;
        }
        while (arr[j] > pivot)
        {
            j--;
        }
        if (i >= j)
        {
            return j;
        }

        int tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
    }
}

void quick_helper(int *arr, int l, int h)
{
    //Recursive case when low < high
    if (l < h)
    {
        // pivot is chosen as median of low and high index
        int p = partition(arr, l, h); // partition() ensures low <= p < high
        // Recursively sort sub partitions of the array
        quick_helper(arr, l, p);
        quick_helper(arr, p + 1, h);
    }
}

void quick_sort(int *arr, int sz)
{
    quick_helper(arr, 0, sz - 1);
}