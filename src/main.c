#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define t_qua 4
#define qua 10
#define rr "Round Robin"
#define fcfs "First Come First Serve"
#define sjf "Shortest Job First"
#define srtf "Shortest Remaining Time First"

int compare_incr(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

void waiting_time(int *bt, int *wt, int *at, char *type)
{
    wt[0] = 0;
    if (strcmp(type, srtf) == 0)
        waiting_time_srtf(bt, wt, at);
    else if (strcmp(type, rr) == 0)
        waiting_time_rr(bt, wt, at);
    else if (strcmp(type, sjf) == 0)
    {
        qsort(bt, qua, sizeof(int), compare_incr);
        waiting_time_sjf(bt, wt);
    }
    else
        waiting_time_sjf(bt, wt);
}

void waiting_time_sjf(int *bt, int *wt)
{
    for (int i = 1; i < qua; i++)
        wt[i] = bt[i - 1] + wt[i - 1];
}

void waiting_time_srtf(int *bt, int *wt, int *at)
{
    int min, min_i = 0, done = 0, cur_t = 0, found = 0, fin_t = 0, tempt[qua];

    for (int i = 0; i < qua; i++)
        tempt[i] = bt[i];

    while (done != qua)
    {
        min = __INT_MAX__;
        for (int i = 0; i < qua; i++)
            if (tempt[i] > 0 && tempt[i] < min && at[i] <= cur_t)
            {
                min_i = i;
                min = tempt[i];
                found = 1;
            }
        if (found == 0)
        {
            cur_t++;
            continue;
        }
        tempt[min_i]--;
        if (tempt[min_i] == 0)
        {
            done++;
            found = 0;
            fin_t = cur_t + 1;
            wt[min_i] = fin_t - bt[min_i] - at[min_i];
            if (wt[min_i] < 0)
                wt[min_i] = 0;
        }
        cur_t++;
    }
}

void waiting_time_rr(int *bt, int *wt, int *at)
{
    int tempt[qua], done = 0, cur_t = 0, min = __INT_MAX__;
    float quant;
    for (int i = 0; i < qua; i++)
    {
        tempt[i] = bt[i];
        if (tempt[i] < min)
            min = tempt[i];
    }

    quant = min * 0.6;

    while (done != 1)
    {
        done = 1;
        for (int i = 0; i < qua; i++)
        {
            if (tempt[i] > 0)
            {
                done = 0;
                if (tempt[i] > quant)
                {
                    cur_t += quant;
                    tempt[i] -= quant;
                }
                else
                {
                    cur_t += tempt[i];
                    wt[i] = cur_t - bt[i];
                    tempt[i] = 0;
                }
            }
        }
    }
}

int avg_wait(int *wt)
{
    int avg = 0;
    for (int i = 0; i < qua; i++)
        avg += wt[i];
    avg /= qua;
    return avg;
}

int print_avg(int *bt, int *wt, int *at, char *type)
{
    int avg;

    printf("№\tburst\twait\tarrival\n");
    for (int i = 0; i < qua; i++)
        printf("%d\t%d\t%d\t%d\n", i, bt[i], wt[i], at[i]);

    avg = avg_wait(wt);

    printf("average waiting time for %s: %d\n\n", type, avg);

    return avg;
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

int main()
{
    int bt[qua];                    //burst time array
    int at[qua];                    //arrival time array
    int wt[qua];                    //waiting time array
    int avgs[t_qua] = {0, 0, 0, 0}; //average waiting time of all algorithms
    char *types[] = {fcfs, sjf, srtf, rr};
    int min = __INT_MAX__;
    int min_i = 0;

    randomize_arr(bt, 25); //randomize burst time
    randomize_arr(at, 25); //randomize arrival time

    for (int i = 0; i < t_qua; i++)
    {
        //create temp arrays
        int tempbt[qua];
        int tempat[qua];
        //copy original values to temp array
        copy(bt, tempbt);
        copy(at, tempat);

        printf("%s:\n", types[i]);
        waiting_time(bt, wt, at, types[i]);
        avgs[i] = print_avg(bt, wt, at, types[i]);
    }

    //find minimum
    for (int i = 0; i < t_qua; i++)
        if (avgs[i] < min)
        {
            min = avgs[i];
            min_i = i;
        }
    printf("Smallest waiting time = %d: %s\n\n", avgs[min_i], types[min_i]);

    return 0;
}
