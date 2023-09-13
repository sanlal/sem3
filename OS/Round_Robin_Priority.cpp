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
    if (a.priority != b.priority)
        return a.priority > b.priority;
    return a.arrivalTime > b.arrivalTime; // Use '>' instead of '<' for Round Robin
}

int main() {
    int n, time = 0, remain;

    float totalWaitingTime = 0;
    float totalTurnaroundTime = 0;

    cout << "Enter the total number of processes: ";
    cin >> n;

    remain = n;

    vector<Process> processes;
    priority_queue<Process, vector<Process>, decltype(&comparePriority)> pq(comparePriority);

    cout << "Enter Arrival time, Burst time, and Priority for all processes:" << endl;
    for (int i = 0; i < n; i++) {
        Process p;
        p.id = i + 1;
        cin >> p.arrivalTime >> p.burstTime >> p.priority;
        p.remainingTime = p.burstTime;
        processes.push_back(p);
    }

    cout << "Enter the value of time quantum: ";
    int time_quantum;
    cin >> time_quantum;

    sort(processes.begin(), processes.end(), compareArrival);

    int i = 0; // Index for iterating through processes

    // Initialize variables for Gantt chart
    vector<int> ganttProcess;
    vector<int> ganttTime;

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

            int executionTime = min(current.remainingTime, time_quantum);

            // Process execution
            current.remainingTime -= executionTime;
            time += executionTime;

            // Update Gantt chart
            ganttProcess.push_back(current.id);
            ganttTime.push_back(time);

            if (current.remainingTime == 0) {
                remain--;
                totalTurnaroundTime += time - current.arrivalTime;
                totalWaitingTime += time - current.arrivalTime - current.burstTime;

                printf("Process{%d}\t:\t%d\t:\t%d\n", current.id, time - current.arrivalTime, time - current.arrivalTime - current.burstTime);
            } else {
                pq.push(current); // Push back to the queue for further execution
            }
        } else {
            time++; // No process in queue, simply increment time
        }
    }
    
    
    
// Print Gantt chart
cout << "Gantt Chart:" << endl;
cout << " ";
for (int i = 0; i < ganttTime.size(); i++) {
    cout << "P" << ganttProcess[i] << " ";
}
cout << endl;
cout << ganttTime[0] << " ";
for (int i = 1; i < ganttTime.size(); i++) {
    if (ganttProcess[i] != ganttProcess[i - 1]) {
        cout << "|" << ganttTime[i] << " ";
    }
}
cout << "|" << time << "|" << endl; // Add the final time to the Gantt chart
    

//    // Print Gantt chart
//    cout << "Gantt Chart:" << endl;
//    cout << " ";
//    for (int i = 0; i < ganttTime.size(); i++) {
//        cout << "P" << ganttProcess[i] << " ";
//    }
//    cout << endl;
//    cout << ganttTime[0] << " ";
//    for (int i = 1; i < ganttTime.size(); i++) {
//        if (ganttProcess[i] != ganttProcess[i - 1]) {
//            cout << "|" << ganttTime[i] << " ";
//        }
//    }
//    cout << "|" << endl;

    float avgWaitingTime = totalWaitingTime / n;
    float avgTurnaroundTime = totalTurnaroundTime / n;

    cout << "\n\nAverage waiting time: " << avgWaitingTime << endl;
    cout << "Average turnaround time: " << avgTurnaroundTime << endl;

    return 0;
}
