#define qua 10

#define fcfs "First Come First Serve"

#define rr "Round Robin"
#define sjf "Shortest Job First"
#define srtf "Shortest Remaining Time First"

#define sstf "Shortest Seek Time First"
#define scan "SCAN"
#define cscan "C-SCAN"

#define fifo "First In First Out"
#define opt "Optimal Page Replacement"
#define lru "Least Recently Used"
#define alru "Second Chance"

int get_min_pos(int *arr, int n);
int arr_contains(int *arr, int el);
int get_pos(int *arr, int el, int n);
int compare_incr(const void *a, const void *b);
int get_min_dist(int *arr, int head);
void randomize_arr(int *arr, int uplim);
void copy(int *from, int *to);