// C++ Program to implement Round Robin
// Scheduling CPU Algorithm

#include <iostream>

/*at = Arrival time,
bt = Burst time,
time_quantum= Quantum time
tat = Turn around time,
wt = Waiting time*/

using namespace std;

int main()
{
    int i, n, time, remain, temps = 0, time_quantum;

    int wt = 0, tat = 0;

    cout << "Enter the total number of process=" << endl;
    cin >> n;

    remain = n;
    // assigning the number of process to remain variable

    int at[n];
    int bt[n];
    int rt[n];

    cout << "Enter the Arrival time, Burst time for All the processes" << endl;
    for (i = 0; i < n; i++)
    {
        cout << "Arrival time for process " << i + 1 << endl;
        cin >> at[i];
        cout << "Burst time for process " << i + 1 << endl;
        cin >> bt[i];
        rt[i] = bt[i];
    }

    cout << "Enter the value of time QUANTUM:" << endl;
    cin >> time_quantum;

    cout << "\n\nProcess\t:Turnaround Time:Waiting Time\n\n";
    for (time = 0, i = 0; remain != 0;)
    {
        if (rt[i] <= time_quantum && rt[i] > 0)
        {
            time += rt[i];

            rt[i] = 0;
            temps = 1;
        }

        else if (rt[i] > 0)
        {
            rt[i] -= time_quantum;

            time += time_quantum;
        }

        if (rt[i] == 0 && temps == 1)
        {
            remain--;
            // Desplaying the result of wating, turn around time:
            printf("Process{%d}\t:\t%d\t:\t%d\n", i + 1, time - at[i], time - at[i] - bt[i]);
            cout << endl;

            wt += time - at[i] - bt[i];
            tat += time - at[i];
            temps = 0;
        }

        if (i == n - 1)
            i = 0;
        else if (at[i + 1] <= time)
            i++;
        else
            i = 0;
    }

    cout << "Average waiting time " << wt * 1.0 / n << endl;
    cout << "Average turn around time " << tat * 1.0 / n << endl;
    ;

    return 0;
}

/*
Enter the total number of process=
3
Enter the Arrival time, Burst time for All the processes
Arrival time for process 1
0
Burst time for process 1
3
Arrival time for process 2
1
Burst time for process 2
1
Arrival time for process 3
1
Burst time for process 3
5
Enter the value of time QUANTUM:
2


Process :Turnaround Time:Waiting Time

Process{2}      :       2       :       1

Process{1}      :       6       :       3

Process{3}      :       8       :       3

Average waiting time 2.33333
Average turn around time 5.33333
*/