#include "lab.h"
#include "../../common/misc.h"

int *waiting_time_sjf(int *bt, int *wt)
{
    for (int i = 1; i < qua; i++)
        wt[i] = bt[i - 1] + wt[i - 1];
    return wt;
}

int *waiting_time_srtf(int *bt, int *wt, int *at)
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
    return wt;
}

int *waiting_time_rr(int *bt, int *wt, int *at)
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
    return wt;
}

int avg_wait(int *wt)
{
    int avg = 0;
    for (int i = 0; i < qua; i++)
        avg += wt[i];
    avg /= qua;
    return avg;
}

int get_avg(int *bt, int *wt, int *at, char *type)
{
    int avg;

    avg = avg_wait(wt);

    return avg;
}

int *waiting_time(int *bt, int *wt, int *at, char *type)
{
    wt[0] = 0;
    if (strcmp(type, srtf) == 0)
        return waiting_time_srtf(bt, wt, at);
    else if (strcmp(type, rr) == 0)
        return waiting_time_rr(bt, wt, at);
    else if (strcmp(type, sjf) == 0)
    {
        qsort(bt, qua, sizeof(int), compare_incr);
        return waiting_time_sjf(bt, wt);
    }
    else
        return waiting_time_sjf(bt, wt);
}