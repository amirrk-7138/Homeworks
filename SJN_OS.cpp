//@Amirrk-7138

#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

struct Process {
    int id;
    float arrival, execute, average, turnaround, service;
    bool done = false;
};

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;
    vector<Process> p(n);

    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        cout << "\nProcess " << p[i].id << " Arrival Time: ";
        cin >> p[i].arrival;
        cout << "Execute Time: ";
        cin >> p[i].execute;
    }

    float time = 0, totalAvg = 0, totalTurn = 0;
    int doneCount = 0;

    while (doneCount < n) {
        int idx = -1;
        float minExec = 1e9;

        for (int i = 0; i < n; i++)
            if (!p[i].done && p[i].arrival <= time && p[i].execute < minExec)
                minExec = p[i].execute, idx = i;

        if (idx == -1) { time++; continue; }

        p[idx].service = time;
        p[idx].average = time - p[idx].arrival;
        time += p[idx].execute;
        p[idx].turnaround = time - p[idx].arrival;
        p[idx].done = true;
        doneCount++;

        cout << "Process " << p[idx].id
             << " ran (" << p[idx].execute << " units) "
             << "from " << p[idx].service
             << " to " << time << endl;
    }

    cout << "\n--- Results ---\n"
         << setw(10) << "PID"
         << setw(10) << "Arrival"
         << setw(10) << "Exec"
         << setw(10) << "Service"
         << setw(10) << "Average"
         << setw(10) << "Turn" << endl;

    for (auto &x : p) {
        totalAvg += x.average;
        totalTurn += x.turnaround;
        cout << setw(10) << x.id
             << setw(10) << x.arrival
             << setw(10) << x.execute
             << setw(10) << x.service
             << setw(10) << x.average
             << setw(10) << x.turnaround << endl;
    }

    cout << "\nAvg(Average): " << totalAvg / n
         << "\nAvg(Turnaround): " << totalTurn / n << endl;
}
