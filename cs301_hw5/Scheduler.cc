// Scheduler.cc

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <numeric>
#include <climits>

class Process
{
public:
    int id;
    int arrival;
    int burst;
    int priority;
};

// turn around is total time process was waiting and executing - >waiting time is total time process was waiting
// -> throughput is number of processes completed per unit time

class FCFS
{
public:
    void schedule(std::vector<Process> &processes)
    {
        std::vector<double> turn_arounds;
        std::vector<double> wait_times;
        sort_by_arrival(processes);

        int currentTime = 0;
        double turnaround = 0;
        double completion = 0;
        double waiting = 0;

        for (const Process &p : processes)
        {
            if (currentTime < p.arrival)
                currentTime = p.arrival;
            currentTime += p.burst;
            completion = currentTime;
            turnaround = completion - p.arrival;
            turn_arounds.push_back(turnaround);
            waiting = turnaround - p.burst;
            wait_times.push_back(waiting);
        }
        double throughput = static_cast<double>(processes.size()) / currentTime;

        std::cout << "Average Turnaround Time: " << std::accumulate(turn_arounds.begin(), turn_arounds.end(), 0.0) / turn_arounds.size() << std::endl;

        std::cout << "Average Waiting Time: " << std::accumulate(wait_times.begin(), wait_times.end(), 0.0) / wait_times.size() << std::endl;

        std::cout << "Throughput: " << throughput << std::endl;
    }

    void sort_by_arrival(std::vector<Process> &processes)
    {
        std::sort(processes.begin(), processes.end(),
                  [](const Process &a, const Process &b)
                  {
                      if (a.arrival == b.arrival)
                          return a.id < b.id;
                      return a.arrival < b.arrival;
                  });
    }
};

class SJFP
{
public:
    void schedule(std::vector<Process> &processes)
    {
        // every tick of the clock look at all processes that have arrived and pick the one with the shortest remaining time.
        // run it for a tick, then repeat. If a new process arrives with a shorter remaining time, preempt the current process
        // and run the new one.
        std::vector<int> remaining(processes.size());
        for (size_t i = 0; i < processes.size(); i++)
        {
            remaining[i] = processes[i].burst;
        }

        double totalTurnaround = 0.0;
        double totalWaiting = 0.0;
        int currentTime = 0;
        int completed = 0;

        while (static_cast<size_t>(completed) < processes.size())
        {
            int shortest = -1;
            int minBurst = INT_MAX;
            for (size_t i = 0; i < processes.size(); i++)
            {
                // checks has it arrived, is it not finished, and is it the shortest remaining time
                if (processes[i].arrival <= currentTime &&
                    remaining[i] > 0 &&
                    remaining[i] < minBurst)
                {
                    minBurst = remaining[i];
                    shortest = static_cast<int>(i);
                }
            }
            // if no process is ready to run, increment time and jump back to the start of the loop
            if (shortest == -1)
            {
                currentTime++;
                continue;
            }
            // run the shortest process for one tick
            remaining[shortest]--;
            currentTime++;
            // if the process is completed, calculate turnaround and waiting time
            if (remaining[shortest] == 0)
            {
                completed++;
                double turnaround = currentTime - processes[shortest].arrival;
                double waiting = turnaround - processes[shortest].burst;
                totalTurnaround += turnaround;
                totalWaiting += waiting;
            }
        }

        double avgTurnaround = totalTurnaround / processes.size();
        double avgWaiting = totalWaiting / processes.size();
        double throughput = static_cast<double>(processes.size()) / currentTime;

        std::cout << "Average Turnaround Time: " << avgTurnaround << "\n";
        std::cout << "Average Waiting Time: " << avgWaiting << "\n";
        std::cout << "Throughput: " << throughput << "\n";
    }
};
// Works similarly to SJFP, but instead of picking the shortest remaining time, it picks the highest priority (lowest number) process that has arrived and is not finished.
// If a new process arrives with a higher priority than the currently running process, preempt the current process and run the new one.

class PriorityScheduler
{
public:
    void schedule(std::vector<Process> &processes)
    {
        std::vector<int> remaining(processes.size());
        for (size_t i = 0; i < processes.size(); i++)
        {
            remaining[i] = processes[i].burst;
        }

        double totalTurnaround = 0.0;
        double totalWaiting = 0.0;
        int currentTime = 0;
        int completed = 0;

        while (static_cast<size_t>(completed) < processes.size())
        {
            int shortest = -1;
            int minPriority = INT_MAX;
            for (size_t i = 0; i < processes.size(); i++)
            {
                // checks has it arrived, is it not finished, and is it the highest priority
                if (processes[i].arrival <= currentTime &&
                    remaining[i] > 0 &&
                    processes[i].priority < minPriority)
                {
                    minPriority = processes[i].priority;
                    shortest = static_cast<int>(i);
                }
            }
            // if no process is ready to run, increment time and jump back to the start of the loop
            if (shortest == -1)
            {
                currentTime++;
                continue;
            }
            // run the shortest process for one tick
            remaining[shortest]--;
            currentTime++;
            // if the process is completed, calculate turnaround and waiting time
            if (remaining[shortest] == 0)
            {
                completed++;
                double turnaround = currentTime - processes[shortest].arrival;
                double waiting = turnaround - processes[shortest].burst;
                totalTurnaround += turnaround;
                totalWaiting += waiting;
            }
        }

        double avgTurnaround = totalTurnaround / processes.size();
        double avgWaiting = totalWaiting / processes.size();
        double throughput = static_cast<double>(processes.size()) / currentTime;

        std::cout << "Average Turnaround Time: " << avgTurnaround << "\n";
        std::cout << "Average Waiting Time: " << avgWaiting << "\n";
        std::cout << "Throughput: " << throughput << "\n";
    }
};

int run(std::vector<Process> processes)
{
    std::cout << " --- FCFS ---\n";
    FCFS fcfs;
    fcfs.schedule(processes);

    std::cout << " --- SJFP ---\n";
    SJFP sjfp;
    sjfp.schedule(processes);

    std::cout << " --- Priority ---\n";
    PriorityScheduler prsh;
    prsh.schedule(processes);
    return 0;
}

int main(int argc, char *argv[])
{

    // ifstream opens file for reading
    std::ifstream file(argv[1]);
    if (!file.is_open() || argc < 2)
    {
        std::cerr << "Error: invalid file specified" << std::endl;
        return 1;
    }
    std::string line;
    std::vector<Process> processes;

    while (std::getline(file, line))
    {
        std::stringstream stream(line);
        std::string token;

        std::getline(stream, token, ',');
        int id = std::stoi(token);

        std::getline(stream, token, ',');
        int arrival = std::stoi(token);

        std::getline(stream, token, ',');
        int burst = std::stoi(token);

        std::getline(stream, token, ',');
        int priority = std::stoi(token);

        processes.push_back({id, arrival, burst, priority});
    }

    file.close();
    return run(processes);
}
