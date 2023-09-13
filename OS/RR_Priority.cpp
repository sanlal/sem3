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

    float avgWaitingTime = totalWaitingTime / n;
    float avgTurnaroundTime = totalTurnaroundTime / n;

    cout << "Average waiting time: " << avgWaitingTime << endl;
    cout << "Average turn around time: " << avgTurnaroundTime << endl;

    return 0;
}

/*
Enter the total number of processes: 5
Enter Arrival time, Burst time, and Priority for all processes:
0 4 3
0 8 2
0 5 2
0 7 1
0 3 3
Enter the value of time quantum: 2
Process{4}      :       7       :       0
Process{3}      :       16      :       11
Process{2}      :       20      :       12
Process{5}      :       25      :       22
Process{1}      :       27      :       23
Average waiting time: 13.6
Average turn around time: 19
*/
























/*
Enter the total number of processes: 5
Enter Arrival time, Burst time, and Priority for all processes:
0 4 3
0 5 2
0 8 3
0 7 1
0 3 1
Enter the value of time quantum: 2
Process{5}      :       7       :       4
Process{4}      :       10      :       3
Process{2}      :       15      :       10
Process{1}      :       21      :       17
Process{3}      :       27      :       19
Average waiting time: 10.6
Average turn around time: 16
*/












//#include <iostream>
//#include <vector>
//#include <queue>
//#include <algorithm>
//
//using namespace std;
//
//struct Process {
//    int id;
//    int arrivalTime;
//    int burstTime;
//    int remainingTime;
//    int priority;
//};
//
//bool compareArrival(const Process &a, const Process &b) {
//    return a.arrivalTime < b.arrivalTime;
//}
//
//bool comparePriority(const Process &a, const Process &b) {
//    if (a.priority != b.priority)
//        return a.priority > b.priority;
//    return a.arrivalTime > b.arrivalTime; // If priority is same, use Round Robin based on Quantime Time
//}
//
//int main() {
//    int i, n, time = 0, remain, time_quantum;
//
//    float totalWaitingTime = 0;
//    float totalTurnaroundTime = 0;
//
//    cout << "Enter the total number of processes: ";
//    cin >> n;
//
//    remain = n;
//
//    vector<Process> processes;
//    priority_queue<Process, vector<Process>, decltype(&comparePriority)> pq(comparePriority);
//
//    cout << "Enter Arrival time, Burst time, and Priority for all processes:" << endl;
//    for (i = 0; i < n; i++) {
//        Process p;
//        p.id = i + 1;
//        cin >> p.arrivalTime >> p.burstTime >> p.priority;
//        p.remainingTime = p.burstTime;
//        processes.push_back(p);
//    }
//
//    cout << "Enter the value of time quantum: ";
//    cin >> time_quantum;
//
//    sort(processes.begin(), processes.end(), compareArrival);
//
//    cout << "\nProcess\t:Turnaround Time:Waiting Time\n\n";
//
//    i = 0; // index for iterating through processes
//    while (remain != 0) {
//        if (pq.empty() && processes[i].arrivalTime > time) {
//            time = processes[i].arrivalTime; // Move time forward to the next arrived process
//        }
//
//        // Add newly arrived processes to the priority queue
//        while (i < n && processes[i].arrivalTime <= time) {
//            pq.push(processes[i]);
//            i++;
//        }
//
//        if (!pq.empty()) {
//            Process current = pq.top();
//            pq.pop();
//
//            int executionTime = min(current.remainingTime, time_quantum);
//
//            // Process execution
//            current.remainingTime -= executionTime;
//            time += executionTime;
//
//            if (current.remainingTime == 0) {
//                remain--;
//                totalTurnaroundTime += time - current.arrivalTime;
//                totalWaitingTime += time - current.arrivalTime - current.burstTime;
//
//                printf("Process{%d}\t:\t%d\t:\t%d\n", current.id, time - current.arrivalTime, time - current.arrivalTime - current.burstTime);
//            } else {
//                pq.push(current); // Push back to the queue for further execution
//            }
//        } else {
//            time++; // No process in queue, simply increment time
//        }
//    }
//
//    float avgWaitingTime = totalWaitingTime / n;
//    float avgTurnaroundTime = totalTurnaroundTime / n;
//
//    cout << "Average waiting time: " << avgWaitingTime << endl;
//    cout << "Average turn around time: " << avgTurnaroundTime << endl;
//
//    return 0;
//}
//
