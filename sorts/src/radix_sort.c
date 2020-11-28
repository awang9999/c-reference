#include <stdio.h>
#include "radix_sort.h"

int get_max(int *arr, int sz)
{
    int max = arr[0];
    for (int i = 0; i < sz; i++)
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }
    return max;
}

void radix_sort(int *arr, int sz)
{

    int digitPlace = 1;
    int result[sz];
    int max_num = get_max(arr, sz);
    int i;

    // Run this loop until all the digits are exhausted.
    while (max_num / digitPlace > 0)
    {
        int count[10] = {0};

        for (i = 0; i < sz; i++)
        {
            count[(arr[i] / digitPlace) % 10]++;
        }

        for (i = 1; i < 10; i++)
        {
            count[i] += count[i - 1];
        }

        for (i = sz - 1; i >= 0; i--)
        {
            result[count[(arr[i] / digitPlace) % 10] - 1] = arr[i];
            count[(arr[i] / digitPlace) % 10]--;
        }

        for (i = 0; i < sz; i++)
        {
            arr[i] = result[i];
        }

        digitPlace *= 10;
    }
}