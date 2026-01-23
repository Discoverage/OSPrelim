#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;
class Process {
public:
    int pid;        // Process ID
    int at;         // Arrival Time
    int bt;         // Burst Time
    int wt = 0;     // Waiting Time
    int tat = 0;    // Turnaround Time
    int ct = 0;     // Completion Time

    Process(int p, int a, int b) : pid(p), at(a), bt(b) {}
};

float average(const vector<int>& v) {
    return accumulate(v.begin(), v.end(), 0.0) / v.size();
}

float median(vector<int>& v) {
    sort(v.begin(), v.end());
    if (v.size() % 2 == 0)
        return (v[v.size() / 2 - 1] + v[v.size() / 2]) / 2.0;
    else
        return v[v.size() / 2];
}

// Function to calculate the recommended time quantum
int recommendedTimeQuantum(const vector<int>& burstTimes) {
    vector<int> sortedBurstTimes = burstTimes;
    float avg = average(sortedBurstTimes);
    float med = median(sortedBurstTimes);
    return static_cast<int>((avg + med) / 2);  // You can also choose to return avg or med based on preference
}

// Round Robin Scheduling
void roundRobin(vector<Process>& processes, int n, int tq) {
    int time = 0, complete = 0;
    vector<int> rt(n);
    for (int i = 0; i < n; i++) rt[i] = processes[i].bt;

    while (complete < n) {
        bool executed = false;
        for (int i = 0; i < n; i++) {
            if (rt[i] > 0) {
                executed = true;
                if (rt[i] > tq) {
                    time += tq;
                    rt[i] -= tq;
                } else {
                    time += rt[i];
                    processes[i].wt = time - processes[i].bt - processes[i].at;
                    processes[i].tat = time - processes[i].at;
                    rt[i] = 0;
                    complete++;
                }
            }
        }
        if (!executed) time++;  // If no process was executed, increase time
    }
}

// Shortest Job First (SJF) Scheduling
void sjf(vector<Process>& processes, int n) {
    sort(processes.begin(), processes.end(), [](Process& p1, Process& p2) {
        return p1.bt < p2.bt;  // Sort by burst time
    });

    int time = 0;
    for (int i = 0; i < n; i++) {
        if (i == 0) {
            processes[i].wt = 0;
            processes[i].tat = processes[i].bt;
        } else {
            processes[i].wt = time - processes[i].at;
            processes[i].tat = processes[i].wt + processes[i].bt;
        }
        time += processes[i].bt;
    }
}

// Shortest Remaining Time First (SRTF) Scheduling
void srtf(vector<Process>& processes, int n) {
    int time = 0, complete = 0;
    vector<int> rt(n);
    for (int i = 0; i < n; i++) rt[i] = processes[i].bt;

    while (complete < n) {
        int smallest = -1;
        for (int i = 0; i < n; i++) {
            if (processes[i].at <= time && rt[i] > 0) {
                if (smallest == -1 || rt[i] < rt[smallest])
                    smallest = i;
            }
        }

        if (smallest == -1) {
            time++;
            continue;
        }

        rt[smallest]--;
        time++;

        if (rt[smallest] == 0) {
            processes[smallest].wt = time - processes[smallest].bt - processes[smallest].at;
            processes[smallest].tat = time - processes[smallest].at;
            complete++;
        }
    }
}

void displayTable(const vector<Process>& processes) {
    cout << "\nPROCESS\tARRIVAL TIME\tBURST TIME\tWAITING TIME\tTURNAROUND TIME\tCOMPLETION TIME\n";
    for (const auto& p : processes) {
        cout << p.pid << "\t" << p.at << "\t\t" << p.bt << "\t\t" << p.wt << "\t\t" << p.tat << "\t\t" << p.ct << "\n";
    }

    // Calculating averages
    float avgWT = 0, avgTAT = 0;
    for (const auto& p : processes) {
        avgWT += p.wt;
        avgTAT += p.tat;
    }

    cout << "\nAverage Waiting Time: " << avgWT / processes.size();
    cout << "\nAverage Turnaround Time: " << avgTAT / processes.size() << "\n";
}

int main() {
    vector<int> arrivalTimes = {4, 2, 3, 6, 1, 5, 8, 7};
    vector<int> burstTimes = {53, 43, 18, 16, 44, 73, 99, 27};

    int n = arrivalTimes.size();
    vector<Process> processes;

    for (int i = 0; i < n; i++) {
        processes.push_back(Process(i, arrivalTimes[i], burstTimes[i]));
    }

   
    int tq = recommendedTimeQuantum(burstTimes);
    cout << "Recommended Time Quantum: " << tq << "\n";

  
    vector<Process> rrProcesses = processes;
    roundRobin(rrProcesses, n, tq);
    cout << "\nRound Robin Scheduling Results:\n";
    displayTable(rrProcesses);

  
    vector<Process> sjfProcesses = processes;
    sjf(sjfProcesses, n);
    cout << "\nShortest Job First Scheduling Results:\n";
    displayTable(sjfProcesses);


    vector<Process> srtfProcesses = processes;
    srtf(srtfProcesses, n);
    cout << "\nShortest Remaining Time First Scheduling Results:\n";
    displayTable(srtfProcesses);

    return 0;
}
