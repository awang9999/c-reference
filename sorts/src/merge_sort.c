#include <stdio.h>
#include "merge_sort.h"

/**
 * This code is based on the Geeksforgeeks.org article about merge sort.
 */

void merge(int *arr, int l, int m, int r)
{
    // Calculate work array sizes
    int s1 = m - l + 1;
    int s2 = r - m;
    // Create work arrays
    int left[s1];
    int right[s2];
    // Copy values into work arrays
    for (int n = 0; n < s1; n++)
    {
        left[n] = arr[l + n];
    }
    for (int p = 0; p < s2; p++)
    {
        right[p] = arr[m + 1 + p];
    }
    int i = 0; // index of first sub array
    int j = 0; // index of second sub array
    int k = l; // index of result array
    // Merge the sub arrays back into the result
    while (i < s1 && j < s2)
    {
        if (left[i] < right[j])
        {
            arr[k] = left[i];
            i++;
        }
        else
        {
            arr[k] = right[j];
            j++;
        }
        k++;
    }
    // Copy the rest of the left and right sub arrays if needed
    while (i < s1)
    {
        arr[k] = left[i];
        i++;
        k++;
    }
    while (j < s2)
    {
        arr[k] = right[j];
        j++;
        k++;
    }
    return;
}

void merge_helper(int *arr, int l, int r)
{
    if (l < r)
    {
        int m = l + ((r - l) / 2);

        merge_helper(arr, l, m);
        merge_helper(arr, m + 1, r);
        merge(arr, l, m, r);
    }
    return;
}

void merge_sort(int *arr, int sz)
{
    merge_helper(arr, 0, sz - 1);
    return;
}