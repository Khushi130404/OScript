#include <stdio.h>

typedef struct {
    int id;         // Process ID
    int burstTime;  // Remaining Burst Time
    int waitTime;   // Wait Time
    int turnAround; // Turnaround Time
} Process;

void roundRobinScheduling(Process processes[], int n, int quantum) {
    int time = 0, remaining = n;
    
    printf("\nProcess Execution Order:\n");

    while (remaining > 0) {
        for (int i = 0; i < n; i++) {
            if (processes[i].burstTime > 0) {
                printf("[ Time %d ] -> Process P%d executes\n", time, processes[i].id);

                int execTime = (processes[i].burstTime > quantum) ? quantum : processes[i].burstTime;
                time += execTime;
                processes[i].burstTime -= execTime;

                if (processes[i].burstTime == 0) {
                    remaining--;
                    processes[i].turnAround = time;
                    processes[i].waitTime = processes[i].turnAround - processes[i].burstTime;
                }
            }
        }
    }

    printf("\nProcess Completion Times:\n");
    printf("PID\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\n", processes[i].id, processes[i].turnAround, processes[i].waitTime);
    }
}

int main() {
    int n, quantum;
    
    printf("Enter number of processes: ");
    scanf("%d", &n);
    
    Process processes[n];
    
    printf("Enter burst times for %d processes:\n", n);
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("P%d: ", processes[i].id);
        scanf("%d", &processes[i].burstTime);
    }
    
    printf("Enter time quantum: ");
    scanf("%d", &quantum);

    roundRobinScheduling(processes, n, quantum);
    
    return 0;
}

// PS D:\OScript>  & 'c:\Users\Khushi\.vscode\extensions\ms-vscode.cpptools-1.23.6-win32-x64\debugAdapters\bin\WindowsDebugLauncher.exe' '--stdin=Microsoft-MIEngine-In-h2u3hxmo.1ah' '--stdout=Microsoft-MIEngine-Out-40mizlnq.q5b' '--stderr=Microsoft-MIEngine-Error-5jk4yok3.gax' '--pid=Microsoft-MIEngine-Pid-2qtg41z4.c5y' '--dbgExe=C:\MinGW\bin\gdb.exe' '--interpreter=mi' 

// [Running] cd "d:\OScript\Assignment4\" && gcc pr_5.c -o pr_5 && "d:\OScript\Assignment4\"pr_5
// Process Execution Order:
// [ Time 0 ] -> Process P1 executes
// [ Time 3 ] -> Process P2 executes
// [ Time 6 ] -> Process P3 executes
// [ Time 9 ] -> Process P1 executes
// [ Time 12 ] -> Process P3 executes
// [ Time 15 ] -> Process P1 executes
// [ Time 18 ] -> Process P3 executes

// Process Completion Times:
// PID     Turnaround Time   Waiting Time
// P1      15               7
// P2      6                2
// P3      18               9
