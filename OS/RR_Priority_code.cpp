#include <algorithm>
#include <deque>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

using namespace std;
// Process structure
struct Process {
    int pid;
    int arrivalTime;
    int priority;
    int burstTime;
    int tempBurstTime;
    int startingTime;
    int finishingTime;
    int turnAroundTime;
    int waitingTime;
    bool init;
};

class PriorityCompare {
  public:
    bool operator()(Process& a, Process& b) {
        if (a.priority == b.priority)
            return a.pid > b.pid;
        return a.priority > b.priority;
    }
};

bool compare(Process& p1, Process& p2) {
    return p1.arrivalTime < p2.arrivalTime;
}

class PriorityPreemptive {
  private:
    queue<Process> mProcessList; // Initially store all processes in queue.
    // Store running processes.
    priority_queue<Process, vector<Process>, PriorityCompare> mRunningProcessList;
    vector<pair<int, int>> mGantChart; // <pid, time>
    vector<Process> mFinishedProcesses;

    int mTimeCounter; // Running time counter.
    int mTimeQuantum; // Time limit for each process.

  public:
    PriorityPreemptive(vector<Process>&);
    void scheduleProcess();
    void print();
    void printGanttChart();
};

PriorityPreemptive::PriorityPreemptive(vector<Process>& processList) {
    // Sort process based on arrival time.
    sort(processList.begin(), processList.end(), compare);

    // Load all processes to queue.
    for (Process& process : processList)
        mProcessList.push(process);

    mTimeCounter = 0;
    mTimeQuantum = 1; // 1 second.
}

void PriorityPreemptive::scheduleProcess() {
    // Keep scheduling until all processes are processed.
    while (!mProcessList.empty() || !mRunningProcessList.empty()) {
        // If arrivalTime is equal to mTimeCounter then load process into running Queue.
        while (mTimeCounter == mProcessList.front().arrivalTime) {
            mRunningProcessList.push(mProcessList.front());
            mProcessList.pop();
        }

        if (!mRunningProcessList.empty()) {
            // Fetch least burst time process into currentProcess
            Process currentProcess = mRunningProcessList.top();
            mRunningProcessList.pop();

            currentProcess.tempBurstTime -= mTimeQuantum; // Process for time quantum.

            // Update starting time if required
            if (currentProcess.init == false) {
                currentProcess.startingTime = mTimeCounter;
                currentProcess.init = true;
            }

            if (currentProcess.tempBurstTime == 0) {
                currentProcess.finishingTime = mTimeCounter + 1; // Update finishing time.
                mFinishedProcesses.push_back(currentProcess);
            } else {
                mRunningProcessList.push(currentProcess);
            }

            mGantChart.push_back({currentProcess.pid, mTimeCounter}); // Push process to gant chart.
        }

        ++mTimeCounter;
    }

    // Update Finished processes table
    for (auto& p : mFinishedProcesses) {
        p.turnAroundTime = p.finishingTime - p.arrivalTime;
        p.waitingTime = p.turnAroundTime - p.burstTime;
    }
}

void PriorityPreemptive::print() {
    scheduleProcess();
    cout << "P\tAT\tPr\tBT\tST\tFT\tTAT\tWT\n";

    int waitingTime = 0;
    int turnAroundTime = 0;
    for (auto& p : mFinishedProcesses) {
        cout << p.pid << '\t';
        cout << p.arrivalTime << '\t';
        cout << p.priority << '\t';
        cout << p.burstTime << '\t';
        cout << p.startingTime << '\t';
        cout << p.finishingTime << '\t';
        cout << p.turnAroundTime << '\t';
        cout << p.waitingTime << '\n';

        waitingTime += p.waitingTime;
        turnAroundTime += p.turnAroundTime;
    }

    cout << endl;

    cout << "Average waiting time: " << double(waitingTime) / mFinishedProcesses.size() << endl;
    cout << "Average turn around time: " << double(turnAroundTime) / mFinishedProcesses.size() << endl;
    cout << endl;

    printGanttChart();
}

void PriorityPreemptive::printGanttChart() {
    cout << "Process: ";
    for (auto& p : mGantChart) {
        cout << p.first << '\t';
    }
    cout << endl;

    cout << "Time   : ";
    for (auto& p : mGantChart) {
        cout << p.second << '\t';
    }
    cout << endl;
}

int main() {
    // vector<Process> processList = {
    //     {1, 0, 4, 4},
    //     {2, 0, 3, 3},
    //     {3, 1, 1, 1},
    //     {4, 2, 4, 4},
    //     {5, 1, 2, 2},
    //     {6, 4, 6, 6},
    // };

    vector<Process> processList = {
        {1, 0, 1, 10, 10},
        {2, 1, 2, 9, 9},
        {0, 2, 1, 5, 5},
        {4, 3, 3, 4, 4},
        {5, 40, 5, 4, 4},
    };

    PriorityPreemptive(processList).print();

    return 0;
}