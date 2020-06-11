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
    int queue[qua] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int less = 0;
    int more = 0;
    int same = 0;
    int dir = 0; // direction. 0 = undefined; -1 = left, 1 = right
    int currpos = head;
    int min = get_min_dist(arr, head);

    dir = arr[min] > head ? 1 : -1;
    for (int i = 0; i < qua; i++) // how many times move to the left
    {
        if (arr[i] < head)
            less++;
        else if (arr[i] > head)
            more++;
        else if (arr[i] == head)
            same++;
    }
    // first we need to build the queue

    int tmp = head;
    for (int i = 0; i < qua;)
    {
        min = get_min_dist(arr, tmp); //get closest to curret head
        switch (dir)
        {
        case -1:
            if (less > 0)
            {
                if (arr[min] > head)
                {
                    dir *= -1;
                    break;
                }
                if (arr[min] == head)
                {
                    dir = 0;
                    break;
                }
                queue[i] = arr[min]; // add to queue
                tmp = arr[min];      // move current head
                arr[min] = -1;       // destroy element
                less--;
                i++;
            }
            else if (less <= 0)
                dir *= -1;
            break;
        case 1:
            if (more > 0)
            {
                if (arr[min] < head)
                {
                    dir *= -1;
                    break;
                }
                if (arr[min] == head)
                {
                    dir = 0;
                    break;
                }
                queue[i] = arr[min]; // add to queue
                tmp = arr[min];      // move current head
                arr[min] = -1;       // destroy element
                more--;
                i++;
            }
            else if (more <= 0)
                dir *= -1;
            break;
        case 0:
            if (same > 0)
            {
                if (arr[min] < head)
                {
                    dir = -1;
                    break;
                }
                if (arr[min] > head)
                {
                    dir = 1;
                    break;
                }
                queue[i] = arr[min]; // add to queue
                tmp = arr[min];      // move current head
                arr[min] = -1;       // destroy element
                same--;
                i++;
            }
            else if (same <= 0)
                dir = -1;
            break;
        }
    }

    return get_fcfs(queue, head);
}

int get_cscan(int *arr, int head)
{
    return get_scan(arr, head);
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
