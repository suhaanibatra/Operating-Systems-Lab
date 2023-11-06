#include <stdio.h>
#include <stdlib.h>

typedef struct Process {
    int process_no;
    int arrival_time;
    int burst_time;
    int priority;
    int waiting_time;
    int turnaround_time;
    int response_time;
} Process;

void fcfs(Process *processes, int n, int *total_waiting_time, int *total_turnaround_time);
void sjf(Process *processes, int n, int *total_waiting_time, int *total_turnaround_time);
void srtf(Process *processes, int n, int time_quantum, int *total_waiting_time, int *total_turnaround_time);
void rr(Process *processes, int n, int time_quantum, int *total_waiting_time, int *total_turnaround_time);
void non_preemptive_priority(Process *processes, int n, int *total_waiting_time, int *total_turnaround_time);
void preemptive_priority(Process *processes, int n, int time_quantum, int *total_waiting_time, int *total_turnaround_time);

int main() {
    int n, i, algorithm, time_quantum;
    Process *processes;
    int total_waiting_time = 0, total_turnaround_time = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    processes = (Process *)malloc(n * sizeof(Process));

    for (i = 0; i < n; i++) {
        printf("Enter process no., arrival time, burst time, and priority for process %d: ", i + 1);
        scanf("%d %d %d %d", &processes[i].process_no, &processes[i].arrival_time, &processes[i].burst_time, &processes[i].priority);
    }

    printf("Enter the algorithm to use (1 - FCFS, 2 - SJF, 3 - SRTF, 4 - RR, 5 - Non-Preemptive Priority, 6 - Preemptive Priority): ");
    scanf("%d", &algorithm);

    if (algorithm == 3 || algorithm == 4 || algorithm == 6) {
        printf("Enter the time quantum: ");
        scanf("%d", &time_quantum);
    }

    switch (algorithm) {
        case 1:
            fcfs(processes, n, &total_waiting_time, &total_turnaround_time);
            break;
        case 2:
            sjf(processes, n, &total_waiting_time, &total_turnaround_time);
            break;
        case 3:
            srtf(processes, n, time_quantum, &total_waiting_time, &total_turnaround_time);
            break;
        case 4:
            rr(processes, n, time_quantum, &total_waiting_time, &total_turnaround_time);
            break;
        case 5:
            non_preemptive_priority(processes, n, &total_waiting_time, &total_turnaround_time);
            break;
        case 6:
            preemptive_priority(processes, n, time_quantum, &total_waiting_time, &total_turnaround_time);
            break;
        default:
            printf("Invalid algorithm.\n");
            return 1;
    }

    printf("Process No.\tWaiting Time\tTurnaround Time\tResponse Time\n");
    for (i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\n", processes[i].process_no, processes[i].waiting_time, processes[i].turnaround_time, processes[i].response_time);
    }

    printf("Average Waiting Time: %.2f\n", (float)total_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_turnaround_time / n);

    return 0;
}

void fcfs(Process *processes, int n, int *total_waiting_time, int *total_turnaround_time) {
    int waiting_time = 0;
    int turnaround_time = 0;
    *total_waiting_time = 0;
    *total_turnaround_time = 0;

    for (int i = 0; i < n; i++) {
        waiting_time += turnaround_time - processes[i].arrival_time;
        turnaround_time += processes[i].burst_time;
        processes[i].waiting_time = waiting_time;
        processes[i].turnaround_time = turnaround_time - processes[i].arrival_time;
        processes[i].response_time = waiting_time;  // Response time is the same as waiting time

        *total_waiting_time += processes[i].waiting_time;
        *total_turnaround_time += processes[i].turnaround_time;
    }
}

void sjf(Process *processes, int n, int *total_waiting_time, int *total_turnaround_time) {
    // Sort the processes based on their burst times in ascending order
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].burst_time > processes[j + 1].burst_time) {
                // Swap the processes
                Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }

    int current_time = 0;
    *total_waiting_time = 0;
    *total_turnaround_time = 0;

    for (int i = 0; i < n; i++) {
        // Calculate waiting time for the current process
        processes[i].waiting_time = current_time;
        // Calculate response time for the current process (same as waiting time)
        processes[i].response_time = current_time;
        // Update current time to the completion time of the current process
        current_time += processes[i].burst_time;
        // Calculate turnaround time for the current process
        processes[i].turnaround_time = processes[i].waiting_time + processes[i].burst_time;
        // Update total waiting time and total turnaround time
        *total_waiting_time += processes[i].waiting_time;
        *total_turnaround_time += processes[i].turnaround_time;
    }
}

void srtf(Process *processes, int n, int time_quantum, int *total_waiting_time, int *total_turnaround_time) {
    // Implement SRTF scheduling algorithm here
}

void rr(Process *processes, int n, int time_quantum, int *total_waiting_time, int *total_turnaround_time) {
    // Implement RR scheduling algorithm here
}

void non_preemptive_priority(Process *processes, int n, int *total_waiting_time, int *total_turnaround_time) {
    // Implement non-preemptive priority scheduling algorithm here
}

void preemptive_priority(Process *processes, int n, int time_quantum, int *total_waiting_time, int *total_turnaround_time) {
    // Implement preemptive priority scheduling algorithm here
}

