#define qua 10

#define fcfs "First Come First Serve"
#define rr "Round Robin"
#define sjf "Shortest Job First"
#define srtf "Shortest Remaining Time First"

#define sstf "Shortest Seek Time First"
#define scan "SCAN"
#define cscan "C-SCAN"

int compare_incr(const void *a, const void *b);

int get_min_dist(int *arr, int head);

int get_min(int *arr);

void randomize_arr(int *arr, int uplim);

void copy(int *from, int *to);
