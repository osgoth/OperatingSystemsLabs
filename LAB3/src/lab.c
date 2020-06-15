#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#include "lab.h"
#include "../../common/misc.h"

int get_fault(int *arr, char *type)
{
    if (strcmp(type, fifo) == 0)
        return get_fifo(arr);
    else if (strcmp(type, opt) == 0)
        return get_opt(arr);
    else if (strcmp(type, lru) == 0)
        return get_lru(arr);
    else if (strcmp(type, alru) == 0)
        return get_alru(arr);
    else
        return INT_MIN;
}

int get_fifo(int *arr)
{
    int fault = 0;
    int mem[PAGE_SLOT] = {0, 0, 0, 0};
    char buff[5] = "";

    for (int i = 0, j = 0; i < qua; i++)
    {
        if (!arr_contains(mem, arr[i]))
        {
            if (j == PAGE_SLOT)
                j = 0;
            mem[j++] = arr[i];
            fault++;
        }
    }
    return fault;
}

int find_furthest(int *mem, int *refs, int pos)
{
    int max = INT_MIN;
    int max_i = -1;
    for (int i = 0; i < PAGE_SLOT; i++)
    {
        int last = -1;
        for (int j = qua; j > pos; j--)
            if (refs[i] == mem[i])
            {
                last = j;
                break;
            }
        if (last == -1)
            return i;
        else if (max < last)
        {
            max = last;
            max_i = i;
        }
        return max_i;
    }
}

int get_opt(int *arr)
{
    int faults = 0;
    int mem[PAGE_SLOT];

    for (int i = 0, j = 0; i < qua; i++)
        if (!arr_contains(mem, arr[i]))
            if (j != PAGE_SLOT)
            {
                mem[j++] = arr[i];
                faults++;
            }
            else
            {
                mem[find_furthest(mem, arr, i)] = arr[i];
                faults++;
            }

    return faults;
}

int get_lru(int *arr)
{
    int faults = 0;
    int mem[PAGE_SLOT] = {-1, -1, -1, -1};
    int ctrs[PAGE_SLOT] = {0, 0, 0, 0};

    for (int i = 0, j = 0; i < qua; i++)
        if (!arr_contains(mem, arr[i]))
            if (j != PAGE_SLOT)
            {
                ctrs[j]++;
                mem[j++] = arr[i];
                faults++;
            }
            else
            {
                int min_i = get_min_pos(ctrs, PAGE_SLOT);
                mem[min_i] = arr[i];
                ctrs[min_i] = 1;
                faults++;
            }
        else
            ctrs[get_pos(mem, arr[i], PAGE_SLOT)]++;

    return faults;
}

int get_alru(int *arr)
{
    int faults = 0;
    int mem[PAGE_SLOT] = {-1, -1, -1, -1};
    int ctrs[PAGE_SLOT] = {0, 0, 0, 0};
    for (int i = 0, j = 0, k = 0; i < qua; i++)
        if (!arr_contains(mem, arr[i]))
            if (j != PAGE_SLOT)
            {
                ctrs[j] = 1;
                mem[j++] = arr[i];
                faults++;
            }
            else
            {
                while (ctrs[k] != 0)
                {
                    if (k == PAGE_SLOT)
                        k = 0;
                    ctrs[k++] = 0;
                }
                mem[k] = arr[i];
                ctrs[k] = 1;
                faults++;
            }

    return faults;
}
