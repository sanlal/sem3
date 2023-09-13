#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "Enter n: ";
    cin >> n;

    int AT[n];
    int ET[n];
    for (int i = 0; i < n; i++) {
        cout << "Enter Arrival Time and Execution time for P" << i + 1 << " : ";
        cin >> AT[i] >> ET[i];
    }

    int ST[n]; // Start Time
    ST[0] = AT[0]; // Initialize the first element
    for (int i = 1; i < n; i++) {
        ST[i] = max(AT[i], ST[i - 1] + ET[i - 1]);
    }

    int FT[n]; // Finish Time
    for (int i = 0; i < n; i++) {
        FT[i] = ST[i] + ET[i];
    }

    int TAT[n]; // Turn Around Time
    for (int i = 0; i < n; i++) {
        TAT[i] = FT[i] - AT[i];
    }

    int WT[n]; // Waiting Time
    for (int i = 0; i < n; i++) {
        WT[i] = TAT[i] - ET[i];
    }

    cout << endl;
    char ch = 222;
    for (int i = 0; i < 100; i++) {
        cout << ch;
    }
    cout << endl;
    cout << "\t\t\t\t GAANT CHART \n";
    for (int i = 0; i < 100; i++) {
        cout << ch;
    }
    cout << endl << endl;

    cout << "P \t AT \t ET \t ST \t FT \t TAT \t WT \t" << endl;
    for (int j = 0; j < n; j++) {
        cout << "P" << j + 1 << "\t" << AT[j] << "\t" << ET[j] << "\t" << ST[j] << "\t" << FT[j] << "\t" << TAT[j] << "\t" << WT[j];
        cout << endl;
    }
    cout << endl;
    for (int i = 0; i < 100; i++) {
        cout << ch;
    }
    cout << endl << endl;
    cout << endl << endl;

    cout << "Average Turn Around Time (A_TAT)::  ";

    float A_TAT = 0;
    for (int i = 0; i < n; i++) {
        A_TAT += TAT[i];
    }
    cout << A_TAT / n << endl;

    cout << "Average Waiting Time (AWT)::  ";

    float AWT = 0;
    for (int i = 0; i < n; i++) {
        AWT += WT[i];
    }
    cout << AWT / n << endl;
}
