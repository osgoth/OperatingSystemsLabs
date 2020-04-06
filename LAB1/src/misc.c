#include "../header/misc.h"

int compare_incr(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

void randomize_arr(int *arr, int uplim)
{
    for (int i = 0; i < qua; i++)
        arr[i] = rand() % (uplim * 2) + uplim;
}

void copy(int *from, int *to)
{
    for (int i = 0; i < qua; i++)
        to[i] = from[i];
}