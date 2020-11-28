#include "insertion_sort.h"

void insertion_sort(int *arr, int sz)
{
    for (int i = 0; i < sz - 1; i++)
    {
        int sorted = i;
        int j = i + 1;
        int curr = arr[j];
        while (curr < arr[sorted] && j > 0)
        {
            arr[j] = arr[j - 1];
            j--;
            sorted--;
        }
        arr[j] = curr;
    }
    return;
}