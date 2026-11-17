#include <stdio.h>

struct Process {
    int id;
    int burst_time;
    int waiting_time;
    int turnaround_time;
};

void findWaitingTime(struct Process proc[], int n) {
    proc[0].waiting_time = 0;
    for (int i = 1; i < n; i++) {
        proc[i].waiting_time = proc[i-1].waiting_time + proc[i-1].burst_time;
    }
}

void findTurnaroundTime(struct Process proc[], int n) {
    for (int i = 0; i < n; i++) {
        proc[i].turnaround_time = proc[i].burst_time + proc[i].waiting_time;
    }
}

int main() {
    struct Process proc[] = {{1, 10}, {2, 5}, {3, 8}};
    int n = sizeof(proc) / sizeof(proc[0]);
    findWaitingTime(proc, n);
    findTurnaroundTime(proc, n);
    printf("Processes  Burst time  Waiting time  Turnaround time\n");
    for (int i = 0; i < n; i++) {
        printf("  %d \t\t %d \t\t %d \t\t %d\n", proc[i].id, proc[i].burst_time,
               proc[i].waiting_time, proc[i].turnaround_time);
    }
    return 0;
}
