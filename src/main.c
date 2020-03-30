#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define t_qua 4
#define qua 10

// fcfs, sjf, srtf, rr

void waiting_time(int *bt, int *wt, int *at, char *type)
{
    wt[0] = 0;
    if (strcmp(type, "srtf") == 0)
        waiting_time_srtf(bt, wt, at);
    else if (strcmp(type, "rr") == 0)
        waiting_time_rr(bt, wt, at);
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
    int tempt[qua], done = 0, cur_t = 0, quant = 0, min = __INT_MAX__;

    for (int i = 0; i < qua; i++)
    {
        tempt[i] = bt[i];
        if (tempt[i] < min)
            min = tempt[i];
    }
    quant = 2;
    // quant = ceil(min / 2);

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

int compare_incr(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

void fcfs(int *bt, int *wt, int *at, int *avgs)
{
    char *type = "fcfs";

    printf("First Come First Serve:\n");

    waiting_time(bt, wt, at, type);

    avgs[0] = print_avg(bt, wt, at, type);
}

void sjf(int *bt, int *wt, int *at, int *avgs)
{
    char *type = "sjf";

    printf("Shortest Job First:\n");
    qsort(bt, qua, sizeof(int), compare_incr); //sort

    waiting_time(bt, wt, at, type);

    avgs[1] = print_avg(bt, wt, at, type);
}

void srtf(int *bt, int *wt, int *at, int *avgs)
{
    char *type = "srtf";

    printf("Shortest Remaining Time First:\n");

    waiting_time(bt, wt, at, type);

    avgs[2] = print_avg(bt, wt, at, type);
}

void rr(int *bt, int *wt, int *at, int *avgs)
{
    char *type = "rr";
    printf("Round Robin:\n");

    waiting_time(bt, wt, at, type);

    avgs[3] = print_avg(bt, wt, at, type);
}
void copy(int *arr, int *other)
{

    for (int i = 0; i < qua; i++)
        other[i] = arr[i];
}
int main()
{
    int bt[qua];                    //burst time array
    int wt[qua];                    //waiting time array
    int at[qua];                    //arrival time array
    int avgs[t_qua] = {0, 0, 0, 0}; //average waiting time of all algorithms
    int min = __INT_MAX__;

    randomize_arr(bt, 25); //randomize burst time
    randomize_arr(at, 25); //randomize arrival time
    int tempbt_srtf[qua], tempbt_rr[qua];

    copy(bt, tempbt_srtf);
    copy(bt, tempbt_rr);

    fcfs(bt, wt, at, avgs);
    sjf(bt, wt, at, avgs);
    srtf(tempbt_srtf, wt, at, avgs);
    rr(tempbt_rr, wt, at, avgs);

    for (int i = 0; i < t_qua; i++)
        if (avgs[i] < min)
            min = avgs[i];

    printf("The least time taken: %d\n", min);

    return 0;
}
