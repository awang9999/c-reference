#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "selection_sort.h"
#include "insertion_sort.h"

void print_arr(int *arr, int sz)
{
    printf("[");
    for (int i = 0; i < sz - 1; i++)
    {
        printf("%d, ", arr[i]);
    }
    printf("%d]\n", arr[sz - 1]);
    return;
}

int *random_array(int n)
{
    int *arr = malloc(sizeof(int) * n);
    // Fill array
    for (int i = 0; i < n; i++)
    {
        arr[i] = i;
    }
    // Shuffle array
    for (int i = 0; i < n; i++)
    {
        int r = rand() % n;
        int tmp = arr[i];
        arr[i] = arr[r];
        arr[r] = tmp;
    }

    return arr;
}

int main()
{
    srand(time(0));

    int sz = 15;
    int *arr_orig = random_array(sz);
    printf("Random Array (Size = %d): ", sz);
    print_arr(arr_orig, sz);

    printf("Selection Sort: ");
    int *selection_cpy = malloc(sizeof(int) * sz);
    memcpy(selection_cpy, arr_orig, sz * sizeof(int));
    selection_sort(selection_cpy, sz);
    print_arr(selection_cpy, sz);

    printf("Insertion Sort: ");
    int *insertion_cpy = malloc(sizeof(int) * sz);
    memcpy(insertion_cpy, arr_orig, sz * sizeof(int));
    insertion_sort(insertion_cpy, sz);
    print_arr(insertion_cpy, sz);

    return EXIT_SUCCESS;
}