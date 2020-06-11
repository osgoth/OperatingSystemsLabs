#include <limits.h>
#include <stdlib.h>

#include "misc.h"

int compare_incr(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

int get_min_dist(int *arr, int head)
{
    int min = INT_MAX;
    int min_i = -1;
    for (int i = 0; i < qua; i++)
        if (arr[i] > 0)
        {
            int bbs = abs(head - arr[i]);
            if (bbs < min)
            {
                min = bbs;
                min_i = i;
            }
        }
    return min_i;
}

int get_min_pos(int *arr)
{
    int min = INT_MAX;
    int min_i = -1;
    for (int i = 0; i < qua; i++)
        if (arr[i] < min)
        {
            min = arr[i];
            min_i = i;
        }
    return min_i;
}

void randomize_arr(int *arr, int uplim)
{
    for (int i = 0; i < qua; i++)
        arr[i] = rand() / (RAND_MAX / (uplim + 1) + 1);
}

void copy(int *from, int *to)
{
    for (int i = 0; i < qua; i++)
        to[i] = from[i];
}