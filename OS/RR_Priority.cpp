#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int priority;
};

bool compareArrival(const Process &a, const Process &b) {
    return a.arrivalTime < b.arrivalTime;
}

bool comparePriority(const Process &a, const Process &b) {
    return a.priority > b.priority;
}

int main() {
    int i, n, time = 0, remain, temps = 0, time_quantum;

    int wt = 0, tat = 0;

    cout << "Enter the total number of processes: ";
    cin >> n;

    remain = n;

    vector<Process> processes;
    priority_queue<Process, vector<Process>, decltype(&comparePriority)> pq(comparePriority);

    cout << "Enter Arrival time, Burst time, and Priority for all processes:" << endl;
    for (i = 0; i < n; i++) {
        Process p;
        p.id = i + 1;
        cin >> p.arrivalTime >> p.burstTime >> p.priority;
        p.remainingTime = p.burstTime;
        processes.push_back(p);
    }

    cout << "Enter the value of time quantum: ";
    cin >> time_quantum;

    sort(processes.begin(), processes.end(), compareArrival);

    cout << "\nProcess\t:Turnaround Time:Waiting Time\n\n";

    i = 0; // index for iterating through processes
    while (remain != 0) {
        if (pq.empty() && processes[i].arrivalTime > time) {
            time = processes[i].arrivalTime; // Move time forward to the next arrived process
        }

        // Add newly arrived processes to the priority queue
        while (i < n && processes[i].arrivalTime <= time) {
            pq.push(processes[i]);
            i++;
        }

        if (!pq.empty()) {
            Process current = pq.top();
            pq.pop();

            // Process execution (similar to Round Robin)
            if (current.remainingTime <= time_quantum) {
                time += current.remainingTime;
                current.remainingTime = 0;
                // ... (update waiting and turnaround times)
                remain--;

                wt += time - current.arrivalTime - current.burstTime;
                tat += time - current.arrivalTime;

                printf("Process{%d}\t:\t%d\t:\t%d\n", current.id, time - current.arrivalTime, time - current.arrivalTime - current.burstTime);
            } else {
                time += time_quantum;
                current.remainingTime -= time_quantum;
                pq.push(current); // Push back to the queue for further execution
            }
        } else {
            time++; // No process in queue, simply increment time
        }
    }

    cout << "Average waiting time: " << wt * 1.0 / n << endl;
    cout << "Average turn around time: " << tat * 1.0 / n << endl;

    return 0;
}
