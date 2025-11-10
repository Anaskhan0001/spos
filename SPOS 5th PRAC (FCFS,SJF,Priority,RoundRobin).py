# CPU Scheduling Simulation

class Process:
    def __init__(self, pid, arrival_time, burst_time, priority=None):
        self.pid = pid
        self.arrival_time = arrival_time
        self.burst_time = burst_time
        self.remaining_time = burst_time
        self.priority = priority
        self.completion_time = 0
        self.waiting_time = 0
        self.turnaround_time = 0

def fcfs(processes):
    processes.sort(key=lambda x: x.arrival_time)
    current_time = 0
    for process in processes:
        if current_time < process.arrival_time:
            current_time = process.arrival_time
        process.completion_time = current_time + process.burst_time
        process.turnaround_time = process.completion_time - process.arrival_time
        process.waiting_time = process.turnaround_time - process.burst_time
        current_time += process.burst_time

def sjf_preemptive(processes):
    processes.sort(key=lambda x: x.arrival_time)
    current_time = 0
    completed = 0
    n = len(processes)
    while completed < n:
        available = [p for p in processes if p.arrival_time <= current_time and p.remaining_time > 0]
        if available:
            available.sort(key=lambda x: x.remaining_time)
            current_process = available[0]
            current_process.remaining_time -= 1
            current_time += 1
            if current_process.remaining_time == 0:
                current_process.completion_time = current_time
                current_process.turnaround_time = current_process.completion_time - current_process.arrival_time
                current_process.waiting_time = current_process.turnaround_time - current_process.burst_time
                completed += 1
        else:
            current_time += 1

def priority_non_preemptive(processes):
    processes.sort(key=lambda x: (x.arrival_time, x.priority))
    current_time = 0
    for process in processes:
        if current_time < process.arrival_time:
            current_time = process.arrival_time
        process.completion_time = current_time + process.burst_time
        process.turnaround_time = process.completion_time - process.arrival_time
        process.waiting_time = process.turnaround_time - process.burst_time
        current_time += process.burst_time

def round_robin(processes, time_quantum):
    queue = [p for p in processes]
    current_time = 0
    while queue:
        process = queue.pop(0)
        if process.arrival_time > current_time:
            current_time = process.arrival_time
        if process.remaining_time <= time_quantum:
            current_time += process.remaining_time
            process.completion_time = current_time
            process.remaining_time = 0
            process.turnaround_time = process.completion_time - process.arrival_time
            process.waiting_time = process.turnaround_time - process.burst_time
        else:
            current_time += time_quantum
            process.remaining_time -= time_quantum
            queue.append(process)

def display_results(processes):
    print(f"{'PID':<10}{'Arrival':<10}{'Burst':<10}{'Priority':<10}{'Completion':<15}{'Turnaround':<15}{'Waiting':<10}")
    for process in processes:
        print(f"{process.pid:<10}{process.arrival_time:<10}{process.burst_time:<10}{process.priority if process.priority else '-':<10}"
              f"{process.completion_time:<15}{process.turnaround_time:<15}{process.waiting_time:<10}")

# Main Program
if __name__ == "__main__":
    processes = [
        Process(1, 0, 8, 2),
        Process(2, 1, 4, 1),
        Process(3, 2, 9, 4),
        Process(4, 3, 5, 3)
    ]

    print("First-Come, First-Serve (FCFS):")
    fcfs(processes)
    display_results(processes)

    print("\nShortest Job First (SJF Preemptive):")
    for process in processes:
        process.remaining_time = process.burst_time  # Reset for re-use
    sjf_preemptive(processes)
    display_results(processes)

    print("\nPriority Scheduling (Non-Preemptive):")
    priority_non_preemptive(processes)
    display_results(processes)

    print("\nRound Robin (Preemptive, Time Quantum = 3):")
    for process in processes:
        process.remaining_time = process.burst_time  # Reset for re-use
    round_robin(processes, time_quantum=3)
    display_results(processes)
