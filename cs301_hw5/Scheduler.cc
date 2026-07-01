// Scheduler.cc

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <numeric>

class Process
{
public:
    int id;
    int arrival;
    int burst;
    int priority;
};

// turn around is total time process was waiting and executing
// waiting time is total time process was waiting
// throughput is number of processes completed per unit time

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

        std::cout << "Average Turnaround Time: " << 
        std::accumulate(turn_arounds.begin(), turn_arounds.end(), 0.0) / turn_arounds.size() << std::endl;
        std::cout << "Average Waiting Time: " << 
        std::accumulate(wait_times.begin(), wait_times.end(), 0.0) / wait_times.size() << std::endl;
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
        (void)processes;
    }
};

class PriorityScheduler
{
public:
    void schedule(std::vector<Process> &processes)
    {
        (void)processes;
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
