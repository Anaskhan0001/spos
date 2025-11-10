#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

// Define the Process class
class Process {
public:
    string pid;             // Process ID (e.g., P1, P2, P3, etc.)
    int arrival_time;       // Time when process arrives
    int burst_time;         // CPU burst time required to complete the process
    int completion_time;    // Time when process completes
    int turnaround_time;    // Turnaround time = Completion time - Arrival time
    int waiting_time;       // Waiting time = Turnaround time - Burst time

    // Constructor
    Process(string id, int arrival, int burst)
        : pid(id), arrival_time(arrival), burst_time(burst), completion_time(0), turnaround_time(0), waiting_time(0) {}
};

// Function to calculate and print SJF scheduling
void sjf_scheduling(vector<Process>& processes) {
    int n = processes.size();
    int current_time = 0;              // Current time starts at 0
    int completed_processes = 0;
    int total_waiting_time = 0;
    int total_turnaround_time = 0;

    // Sort processes by arrival time first, then by burst time (in case of tie in arrival time)
    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        if (a.arrival_time == b.arrival_time) {
            return a.burst_time < b.burst_time;  // If arrival times are the same, sort by burst time
        }
        return a.arrival_time < b.arrival_time;
    });

    // Process scheduling loop
    while (completed_processes < n) {
        // Find the process with the shortest burst time among the ready processes
        Process* current_process = nullptr;

        // Check for processes that have arrived and are not yet completed
        for (auto& p : processes) {
            if (p.arrival_time <= current_time && p.completion_time == 0) {
                if (current_process == nullptr || p.burst_time < current_process->burst_time) {
                    current_process = &p;
                }
            }
        }

        // If no process is ready (i.e., we are idle), jump to the next arrival time
        if (current_process == nullptr) {
            current_time++;
            continue;
        }

        // Set the completion time, waiting time, and turnaround time
        current_process->completion_time = current_time + current_process->burst_time;
        current_process->turnaround_time = current_process->completion_time - current_process->arrival_time;
        current_process->waiting_time = current_process->turnaround_time - current_process->burst_time;

        // Update total waiting time and total turnaround time
        total_waiting_time += current_process->waiting_time;
        total_turnaround_time += current_process->turnaround_time;

        // Update current time
        current_time = current_process->completion_time;

        // Mark this process as completed
        completed_processes++;
    }

    // Print results
    cout << "Process ID\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n";
    for (const auto& p : processes) {
        cout << p.pid << "\t\t" << p.arrival_time << "\t\t" << p.burst_time << "\t\t"
             << p.completion_time << "\t\t" << p.turnaround_time << "\t\t" << p.waiting_time << endl;
    }

    // Calculate and print average waiting time and turnaround time
    cout << "\nAverage Waiting Time: " << (float)total_waiting_time / n << endl;
    cout << "Average Turnaround Time: " << (float)total_turnaround_time / n << endl;
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes;
    int arrival_time, burst_time;

    // User input for process details (only arrival time and burst time)
    for (int i = 0; i < n; ++i) {
        cout << "Enter details for Process " << i + 1 << ":\n";
        cout << "Arrival Time: ";
        cin >> arrival_time;
        cout << "Burst Time: ";
        cin >> burst_time;

        // Assign process ID dynamically as P1, P2, P3, etc.
        string pid = "P" + to_string(i + 1);

        // Add the process to the list
        processes.push_back(Process(pid, arrival_time, burst_time));
    }

    // Call the SJF scheduling function
    sjf_scheduling(processes);

    return 0;
}
