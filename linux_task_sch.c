//task schdeuler round robin
#include <stdio.h>
#include <stdlib.h>

#define MAX_TASKS 3
#define TIME_QUANTUM 2   /* each task gets 2 units per turn */

typedef struct {
    int  id;
    int  burst_time;     /* total CPU time needed */
    int  remaining_time;
} Task;

void round_robin_scheduler(Task tasks[], int n)
{
    int time = 0;
    int done  = 0;

    printf("Scheduling (Round-Robin, quantum=%d):\n", TIME_QUANTUM);

    while (done < n) {
        done = 0;
        for (int i = 0; i < n; i++) {
            if (tasks[i].remaining_time <= 0) {
                done++;
                continue;
            }

            int run = (tasks[i].remaining_time >= TIME_QUANTUM)
                      ? TIME_QUANTUM
                      : tasks[i].remaining_time;

            printf("  t=%d  Task%d runs for %d units\n",
                   time, tasks[i].id, run);

            tasks[i].remaining_time -= run;
            time += run;

            if (tasks[i].remaining_time == 0)
                printf("  Task%d FINISHED at t=%d\n", tasks[i].id, time);
        }
    }
}

int main(void)
{
    Task tasks[MAX_TASKS] = {
        {1, 6, 6},
        {2, 4, 4},
        {3, 8, 8},
    };

    round_robin_scheduler(tasks, MAX_TASKS);
    return 0;
}