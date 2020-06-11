#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lab.h"
#include "../../common/misc.h"

void move_head(int *currpos, int *dist, int *head, int *seek, int *next)
{
    *currpos = *next;
    *dist = (*currpos - *head) >= 0 ? (*currpos - *head) : (*currpos - *head) * -1;
    *seek += *dist;
    *head = *currpos;
}

int schedule(int *arr, int head, char *type)
{
    if (strcmp(type, fcfs) == 0)
        return get_fcfs(arr, head);
    else if (strcmp(type, scan) == 0)
        return get_scan(arr, head);
    else if (strcmp(type, cscan) == 0)
        return get_cscan(arr, head);
    else if (strcmp(type, sstf) == 0)
        return get_sstf(arr, head);
    else
        return INT_MIN;
}

int get_fcfs(int *arr, int head)
{
    int seek = 0;
    int dist = 0;
    int currpos = head;

    for (int i = 0; i < qua; i++)
        move_head(&currpos, &dist, &head, &seek, &arr[i]);

    return seek;
}

int get_scan(int *arr, int head)
{
    int more = 0;
    int less = 0;
    int currpos = head;
    int dist = 0;
    int seek = 0;

    for (int i = 0; i < qua; i++)
        if (head > arr[i])
            less++;
        else if (head < arr[i])
            more++;

    int before[less + 1];
    int after[more + 1];

    for (int i = 0, j = 0; i < qua; i++)
        if (arr[i] < head)
            before[j++] = arr[i];
    before[less] = 0;

    for (int i = 0, j = 0; i < qua; i++)
        if (arr[i] > head)
            after[j++] = arr[i];
    after[more] = 199;

    qsort(before, less + 1, sizeof(int), compare_incr);
    qsort(after, more + 1, sizeof(int), compare_incr);

    for (int i = 0; i < more; i++)
        move_head(&currpos, &dist, &head, &seek, &after[i]);
    for (int i = less; i > 0; i--)
        move_head(&currpos, &dist, &head, &seek, &before[i]);

    return seek;
}

int get_cscan(int *arr, int head)
{
    int more = 0;
    int less = 0;
    int currpos = head;
    int dist = 0;
    int seek = 0;

    for (int i = 0; i < qua; i++)
        if (head > arr[i])
            less++;
        else if (head < arr[i])
            more++;

    int before[less + 1];
    int after[more + 1];

    for (int i = 0, j = 0; i < qua; i++)
        if (arr[i] < head)
            before[j++] = arr[i];
    before[less] = 0;

    for (int i = 0, j = 0; i < qua; i++)
        if (arr[i] > head)
            after[j++] = arr[i];
    after[more] = 199;

    qsort(before, less + 1, sizeof(int), compare_incr);
    qsort(after, more + 1, sizeof(int), compare_incr);

    for (int i = 0; i < more; i++)
        move_head(&currpos, &dist, &head, &seek, &after[i]);
    for (int i = 0; i < less; i++)
        move_head(&currpos, &dist, &head, &seek, &before[i]);

    return seek;
}

int get_sstf(int *arr, int head)
{
    int seek = 0;
    int dist = 0;
    int currpos = head;
    int nearest_i = 0;

    for (int i = 0; i < qua; i++)
    {
        nearest_i = get_min_dist(arr, head);
        move_head(&currpos, &dist, &head, &seek, &arr[nearest_i]);
        arr[nearest_i] = -1;
    }
    return seek;
}
