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
    int min_i = 0;
    int min_tot = 0;
    int sim_qua = 0;

    printf("How many simulations would you like to go through?\n>>> ");
    scanf("%d", &sim_qua);
    for (int j = 0; j < sim_qua; j++)
    {
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
            waiting_time(bt, wt, at, types[i]);
            avgs[i] += avg_wait(wt);
        }
    }
    for (int i = 0; i < t_qua; i++)
        avgs[i] /= sim_qua;
    for (int i = 0; i < t_qua; i++)
        if (avgs[i] < avgs[min_i])
            min_i = i;

    for (int i = 0; i < t_qua; i++)
        printf("Average waiting time = %d: %s\n", avgs[i], types[i]);

    printf("Smallest = %d: %s\n", avgs[min_i], types[min_i]);

    return 0;
}
