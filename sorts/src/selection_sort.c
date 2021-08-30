#include "selection_sort.h"

void selection_sort(int *arr, int sz)
{
    for (int i = 0; i < sz; i++)
    {
        int min = arr[i];
        int min_index = i;
        for (int j = i + 1; j < sz; j++)
        {
            if (arr[j] < min)
            {
                min = arr[j];
                min_index = j;
            }
        }
        arr[min_index] = arr[i];
        arr[i] = min;
    }
    return;
}