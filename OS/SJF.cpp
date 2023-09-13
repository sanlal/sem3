#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX_N = 50; // Define a reasonable maximum number of processes

struct Process {
    int id;
    int AT;
    int ET;
    int ST;
    int FT;
    int TAT;
    int WT;
};

bool compareByExecutionTime(const Process &a, const Process &b) {
    return a.ET < b.ET;
}

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> processes(n);
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        cout << "Enter Arrival Time and Execution time for P" << i + 1 << ": ";
        cin >> processes[i].AT >> processes[i].ET;
    }

    sort(processes.begin(), processes.end(), compareByExecutionTime);

    processes[0].ST = processes[0].AT;
    processes[0].FT = processes[0].ST + processes[0].ET;
    processes[0].TAT = processes[0].FT - processes[0].AT;
    processes[0].WT = processes[0].TAT - processes[0].ET;

    for (int i = 1; i < n; i++) {
        processes[i].ST = max(processes[i].AT, processes[i - 1].FT);
        processes[i].FT = processes[i].ST + processes[i].ET;
        processes[i].TAT = processes[i].FT - processes[i].AT;
        processes[i].WT = processes[i].TAT - processes[i].ET;
    }

    // Print Gantt Chart and other information
    char ch = 222;
    for (int i = 0; i < 100; i++) {
        cout << ch;
    }
    cout << endl;
    cout << "\t\t\t\t GANTT CHART \n";
    for (int i = 0; i < 100; i++) {
        cout << ch;
    }
    cout << endl << endl;

    cout << "P \t AT \t ET \t ST \t FT \t TAT \t WT \t" << endl;
    for (int j = 0; j < n; j++) {
        cout << "P" << processes[j].id << "\t" << processes[j].AT << "\t" << processes[j].ET << "\t"
             << processes[j].ST << "\t" << processes[j].FT << "\t" << processes[j].TAT << "\t" << processes[j].WT;
        cout << endl;
    }
    cout << endl;
    for (int i = 0; i < 100; i++) {
        cout << ch;
    }
    cout << endl << endl;
    cout << endl << endl;

    float A_TAT = 0;
    float AWT = 0;
    for (int i = 0; i < n; i++) {
        A_TAT += processes[i].TAT;
        AWT += processes[i].WT;
    }
    cout << "Average Turn Around Time (A_TAT):  " << A_TAT / n << endl;
    cout << "Average Waiting Time (AWT):  " << AWT / n << endl;

    return 0;
}







//#include <iostream>
//using namespace std;
//
//int main() {
//    int n;
//    cout << "Enter n: ";
//    cin >> n;
//
//    int AT[n];
//    int ET[n];
//    for (int i = 0; i < n; i++) {
//        cout << "Enter Arrival Time and Execution time for P" << i + 1 << " : ";
//        cin >> AT[i] >> ET[i];
//    }
//
//    for (int i = 0; i < n - 1; i++) {
//        for (int j = i + 1; j < n; j++) {
//            if (ET[i] > ET[j]) {
//                swap(AT[i], AT[j]);
//                swap(ET[i], ET[j]);
//            }
//        }
//    }
//
//    int ST[n]; // Start Time
//    ST[0] = AT[0];
//    for (int i = 1; i < n; i++) {
//        ST[i] = max(AT[i], ST[i - 1] + ET[i - 1]);
//    }
//
//    int FT[n]; // Finish Time
//    for (int i = 0; i < n; i++) {
//        FT[i] = ST[i] + ET[i];
//    }
//
//    int TAT[n]; // Turn Around Time
//    for (int i = 0; i < n; i++) {
//        TAT[i] = FT[i] - AT[i];
//    }
//
//    int WT[n]; // Waiting Time
//    for (int i = 0; i < n; i++) {
//        WT[i] = TAT[i] - ET[i];
//    }
//
//    cout << endl;
//    char ch = 222;
//    for (int i = 0; i < 100; i++) {
//        cout << ch;
//    }
//    cout << endl;
//    cout << "\t\t\t\t GANTT CHART \n";
//    for (int i = 0; i < 100; i++) {
//        cout << ch;
//    }
//    cout << endl << endl;
//
//    cout << "P \t AT \t ET \t ST \t FT \t TAT \t WT \t" << endl;
//    for (int j = 0; j < n; j++) {
//        cout << "P" << j + 1 << "\t" << AT[j] << "\t" << ET[j] << "\t" << ST[j] << "\t" << FT[j] << "\t" << TAT[j] << "\t" << WT[j];
//        cout << endl;
//    }
//    cout << endl;
//    for (int i = 0; i < 100; i++) {
//        cout << ch;
//    }
//    cout << endl << endl;
//    cout << endl << endl;
//
//    float A_TAT = 0;
//    for (int i = 0; i < n; i++) {
//        A_TAT += TAT[i];
//    }
//    cout << "Average Turn Around Time (A_TAT)::  " << A_TAT / n << endl;
//
//    float AWT = 0;
//    for (int i = 0; i < n; i++) {
//        AWT += WT[i];
//    }
//    cout << "Average Waiting Time (AWT)::  " << AWT / n << endl;
//    
//    
//}
