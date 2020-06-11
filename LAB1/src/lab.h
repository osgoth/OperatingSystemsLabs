#define t_qua 4

int *waiting_time_rr(int *bt, int *wt, int *at);
int *waiting_time_srtf(int *bt, int *wt, int *at);
int *waiting_time_sjf(int *bt, int *wt);
int *waiting_time(int *bt, int *wt, int *at, char *type);

int print_avg(int *bt, int *wt, int *at, char *type);

int avg_wait(int *wt);