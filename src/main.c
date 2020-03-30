#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "../header/misc.h"
#include "../header/lab1.h"

//compile and run: gcc main.c misc.c lab1.c -o main %% ./main

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
