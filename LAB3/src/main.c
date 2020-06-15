#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "../../common/misc.h"
#include "lab.h"

int main()
{
    int seq[qua];                   // request sequence
    int avgs[t_qua] = {0, 0, 0, 0}; //average waiting time of all algorithms
    char *types[] = {fifo, opt, lru, alru};

    int min_i = 0;
    int sim_qua = 0;

    printf("How many simulations would you like to go through?\n>>> ");
    scanf("%d", &sim_qua);
    int bbs = abs(-20);
    for (int j = 0; j < sim_qua; j++)
    {
        randomize_arr(seq, 10); // randomize request sequence time

        for (int i = 0; i < t_qua; i++)
        {
            int tempseq[qua];   // create temp arrays
            copy(seq, tempseq); // copy original values to temp array
            avgs[i] += get_fault(tempseq, types[i]);
        }
    }
    for (int i = 0; i < t_qua; i++)
        avgs[i] /= sim_qua;
    for (int i = 0; i < t_qua; i++)
        if (avgs[i] < avgs[min_i])
            min_i = i;

    for (int i = 0; i < t_qua; i++)
        printf("Average faults quantity = %d: %s\n", avgs[i], types[i]);

    printf("Smallest = %d: %s\n", avgs[min_i], types[min_i]);
    printf("Page slots = %d\n", PAGE_SLOT);
    return 0;
}
