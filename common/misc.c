#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>

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

int get_min_pos(int *arr, int n)
{
    int min = INT_MAX;
    int min_i = -1;
    for (int i = 0; i < n; i++)
        if (arr[i] < min)
        {
            min = arr[i];
            min_i = i;
        }
    return min_i;
}
int get_pos(int *arr, int el, int n)
{
    for (int i = 0; i < n; i++)
        if (el == arr[i])
            return i;
    return -1;
}

int arr_contains(int *arr, int el)
{
    for (int i = 0; i < qua; i++)
        if (arr[i] == el)
            return 1;
    return 0;
}

char *arr_string(int *arr)
{

    char *str[512] = {"[ "};
    char buff[5] = "";

    for (int i = 0; i < 5; i++)
    {
        char c[sizeof(int)];
        snprintf(c, sizeof(int), "%d", arr[i]);
        str[i] = (char *)malloc(sizeof(c));
        strcpy(str[i], c);
    }

    char *ptr = str;

    return ptr;
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
