#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

class Process {
public:
    int pid;   // process id
    int at;    // arrival time
    int bt;    // burst time
    int wt=0;  // waiting time
    int tat=0; // turnaround time
    int ct=0;  // completion time

    Process(int p, int a, int b) : pid(p), at(a), bt(b) {}
};

float average(const vector<int>& v) {
    return accumulate(v.begin(), v.end(), 0.0) / v.size();
}

float median(vector<int> v) {
    sort(v.begin(), v.end());
    int n = v.size();
    if (n % 2 == 0)
        return (v[n/2 - 1] + v[n/2]) / 2.0;
    return v[n/2];
}

int recommendedTimeQuantum(const vector<int>& bt) {
    return (average(bt) + median(bt)) / 2;
}

/* ---------------- ROUND ROBIN ---------------- */
void roundRobin(vector<Process>& p, int n, int tq) {
    int time = 0, done = 0;
    vector<int> rt(n);

    for (int i = 0; i < n; i++)
        rt[i] = p[i].bt;

    while (done < n) {
        bool exec = false;

        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && rt[i] > 0) {
                exec = true;

                if (rt[i] > tq) {
                    time += tq;
                    rt[i] -= tq;
                } else {
                    time += rt[i];
                    rt[i] = 0;

                    p[i].ct  = time;
                    p[i].tat = p[i].ct - p[i].at;
                    p[i].wt  = p[i].tat - p[i].bt;
                    done++;
                }
            }
        }
        if (!exec) time++;
    }
}

/* ---------------- SJF (NON-PREEMPTIVE) ---------------- */
void sjf(vector<Process>& p, int n) {
    sort(p.begin(), p.end(), [](Process &a, Process &b) {
        return a.bt < b.bt;
    });

    int time = 0;
    for (int i = 0; i < n; i++) {
        if (time < p[i].at)
            time = p[i].at;

        time += p[i].bt;
        p[i].ct  = time;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt  = p[i].tat - p[i].bt;
    }
}

/* ---------------- SRTF ---------------- */
void srtf(vector<Process>& p, int n) {
    vector<int> rt(n);
    for (int i = 0; i < n; i++)
        rt[i] = p[i].bt;

    int time = 0, done = 0;

    while (done < n) {
        int idx = -1;

        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && rt[i] > 0) {
                if (idx == -1 || rt[i] < rt[idx])
                    idx = i;
            }
        }

        if (idx == -1) {
            time++;
            continue;
        }

        rt[idx]--;
        time++;

        if (rt[idx] == 0) {
            p[idx].ct  = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt  = p[idx].tat - p[idx].bt;
            done++;
        }
    }
}

/* ---------------- DISPLAY ---------------- */
void displayTable(const vector<Process>& p) {
    cout << "\npid\tat\tbt\twt\ttat\tct\n";

    float avgWT = 0, avgTAT = 0;

    for (auto &x : p) {
        cout << x.pid << "\t"
             << x.at  << "\t"
             << x.bt  << "\t"
             << x.wt  << "\t"
             << x.tat << "\t"
             << x.ct  << "\n";

        avgWT  += x.wt;
        avgTAT += x.tat;
    }

    cout << "\navg wt  = " << avgWT / p.size();
    cout << "\navg tat = " << avgTAT / p.size() << "\n";
}

int main() {
    vector<int> at = {4,2,3,6,1,5,8,7};
    vector<int> bt = {53,43,18,16,44,73,99,27};

    int n = at.size();
    vector<Process> p;

    for (int i = 0; i < n; i++)
        p.emplace_back(i, at[i], bt[i]);

    int tq = recommendedTimeQuantum(bt);
    cout << "recommended tq = " << tq << "\n";

    auto rr = p;
    roundRobin(rr, n, tq);
    cout << "\nRR:\n";
    displayTable(rr);

    auto sjfP = p;
    sjf(sjfP, n);
    cout << "\nSJF:\n";
    displayTable(sjfP);

    auto srtfP = p;
    srtf(srtfP, n);
    cout << "\nSRTF:\n";
    displayTable(srtfP);

    return 0;
}
