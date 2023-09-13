#include<iostream>
using namespace std;

int main()
{
	// Arrays to store arrival time, burst time, and copy of burst time
    int a[10], b[10], x[10]; 
    
    // Arrays to store various process-related times and priorities
    int waiting[10], turnaround[10], completion[10], p[10]; 
    
    int i, j, smallest, count = 0, time, n; // Loop control and temporary variables
    double avg = 0, tt = 0, end; // Variables to calculate average times
    
    // Read the number of processes
    cout << "\nEnter the number of Processes: ";
    cin >> n; 

    // Loop to read arrival times of processes
    for (i = 0; i < n; i++)
    {
        cout << "\nEnter arrival time of process: ";
        cin >> a[i];
    }

    // Loop to read burst times of processes
    for (i = 0; i < n; i++)
    {
        cout << "\nEnter burst time of process: ";
        cin >> b[i];
    }

    // Loop to read priorities of processes
    for (i = 0; i < n; i++)
    {
        cout << "\nEnter priority of process: ";
        cin >> p[i];
    }

    // Store the burst times in another array for later reference
    for (i = 0; i < n; i++)
        x[i] = b[i];

    p[9] = -1; // Initialize a dummy priority for comparison

    // Main scheduling loop
    for (time = 0; count != n; time++)
    {
        smallest = 9; // Initialize index of the smallest priority process

        // Find the process with highest priority that has arrived and is not completed
        for (i = 0; i < n; i++)
        {
            if (a[i] <= time && p[i] > p[smallest] && b[i] > 0)
                smallest = i;
        }

        b[smallest]--; // Decrement the burst time of the selected process

        // If the burst time of the selected process becomes 0, it's completed
        if (b[smallest] == 0)
        {
            count++; // Increment the count of completed processes
            end = time + 1;
            completion[smallest] = end;
            waiting[smallest] = end - a[smallest] - x[smallest];
            turnaround[smallest] = end - a[smallest];
        }
    }

    // Print table header
    cout << "Process" << "\t" << "Burst-time" << "\t" << "Arrival-time" << "\t" << "Priority" << "\t" << "Finish-time" << "\t" << "Turnaround-time" << "\t" << "Waiting-time" << endl;

    // Print process details and calculate averages
    for (i = 0; i < n; i++)
    {
        cout << "p" << i + 1 << "\t\t" << x[i] << "\t\t" << a[i] << "\t\t" << p[i] << "\t\t" << completion[i] << "\t\t" << turnaround[i] << "\t\t" << waiting[i] << endl;
        avg = avg + waiting[i];
        tt = tt + turnaround[i];
    }

    // Print average turnaround and waiting times
    cout << "  Average Turnaround time =" << tt / n << endl;
    cout << "\n\nAverage waiting time =" << avg / n << endl;

} // End of the program
