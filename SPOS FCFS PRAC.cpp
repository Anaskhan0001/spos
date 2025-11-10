#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Define a structure to hold process information
struct Process {
    string id;          // Process ID (now in "P1", "P2", etc. format)
    int arrivalTime;    // Arrival Time of the process
    int burstTime;      // Burst Time (Time required for execution)
    int completionTime;
    int turnAroundTime;
    int waitingTime;
};

// Function to calculate completion time, turn around time, and waiting time
void findCompletionTimes(vector<Process>& processes) {
    int n = processes.size();
    int currentTime = 0;

    for (int i = 0; i < n; i++) {
        // Completion Time = max(Current Time, Arrival Time) + Burst Time
        processes[i].completionTime = max(currentTime, processes[i].arrivalTime) + processes[i].burstTime;
        currentTime = processes[i].completionTime;

        // Turnaround Time = Completion Time - Arrival Time
        processes[i].turnAroundTime = processes[i].completionTime - processes[i].arrivalTime;

        // Waiting Time = Turnaround Time - Burst Time
        processes[i].waitingTime = processes[i].turnAroundTime - processes[i].burstTime;
    }
}

// Function to print the process table with completion time, turn around time, and waiting time
void printProcessTable(const vector<Process>& processes) {
    cout << "Process ID | Arrival Time | Burst Time | Completion Time | Turnaround Time | Waiting Time" << endl;
    for (const auto& p : processes) {
        cout << p.id << "\t\t" << p.arrivalTime << "\t\t" << p.burstTime 
             << "\t\t" << p.completionTime << "\t\t" << p.turnAroundTime 
             << "\t\t" << p.waitingTime << endl;
    }
}

int main() {
    // Define number of processes
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);

    // Input for all processes
    for (int i = 0; i < n; i++) {
        processes[i].id = "P" + to_string(i + 1);  // Process ID in format P1, P2, P3, etc.
        cout << "Enter arrival time for " << processes[i].id << ": ";
        cin >> processes[i].arrivalTime;
        cout << "Enter burst time for " << processes[i].id << ": ";
        cin >> processes[i].burstTime;
    }

    // Sort the processes based on arrival time (in case they arrive at the same time)
    sort(processes.begin(), processes.end(), [](Process& p1, Process& p2) {
        return p1.arrivalTime < p2.arrivalTime;
    });

    // Calculate the completion time, turn around time, and waiting time
    findCompletionTimes(processes);

    // Print the final results
    printProcessTable(processes);

    // Calculate and print average waiting time and average turnaround time
    double avgWaitingTime = 0, avgTurnAroundTime = 0;
    for (const auto& p : processes) {
        avgWaitingTime += p.waitingTime;
        avgTurnAroundTime += p.turnAroundTime;
    }

    avgWaitingTime /= n;
    avgTurnAroundTime /= n;

    cout << "\nAverage Waiting Time: " << avgWaitingTime << endl;
    cout << "Average Turnaround Time: " << avgTurnAroundTime << endl;

    return 0;
}