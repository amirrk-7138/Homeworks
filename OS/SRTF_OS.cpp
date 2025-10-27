#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

struct Process {
    string pid;
    int at;
    int et;
    int remaining;
    int end;
    int wt;
};

void srtf_with_quantum(vector<Process> &p, int quantum) {
    int n = p.size();
    int time = 0;
    int completed = 0;
    vector<string> gantt; 

    for (auto &proc : p) {
        proc.remaining = proc.et;
        proc.end = 0;
    }

    while (completed < n) {
        vector<int> available;

        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && p[i].remaining > 0)
                available.push_back(i);
        }

        if (!available.empty()) {
            int current = available[0];
            for (int i : available) {
                if (p[i].remaining < p[current].remaining)
                    current = i;
            }

            gantt.push_back(p[current].pid);

            int run_time = min(p[current].remaining, quantum);
            p[current].remaining -= run_time;
            time += run_time;

            if (p[current].remaining == 0) {
                p[current].end = time;
                completed++;
            }
        } else {
            gantt.push_back("idle");
            time++;
        }
    }

    double total_wt = 0;
    for (auto &proc : p) {
        int turnaround = proc.end - proc.at;
        proc.wt = turnaround - proc.et;
        total_wt += proc.wt;
    }

    double avg_wt = total_wt / n;

    cout << "\nSRTF Algorithm Results with Quantum:\n";
    cout << "PID\tAT\tET\tEnd\tWT\n";
    for (auto &proc : p) {
        cout << proc.pid << "\t" << proc.at << "\t" << proc.et << "\t"
             << proc.end << "\t" << proc.wt << "\n";
    }

    cout << fixed << setprecision(2);
    cout << "\nAverage Waiting Time (WT): " << avg_wt << "\n";

    cout << "\nGantt Chart:\n";
    for (size_t i = 0; i < gantt.size(); i++) {
        cout << gantt[i];
        if (i != gantt.size() - 1) cout << " → ";
    }
    cout << "\n";
}

int main() {
    vector<Process> processes;
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        Process proc;
        cout << "\nProcess " << i + 1 << ":\n";
        cout << "Process name (PID): ";
        cin >> proc.pid;
        cout << "Arrival time (AT): ";
        cin >> proc.at;
        cout << "Execution time (ET): ";
        cin >> proc.et;
        processes.push_back(proc);
    }

    int quantum;
    cout << "\nEnter Quantum (Q): ";
    cin >> quantum;

    srtf_with_quantum(processes, quantum);

    return 0;
}
