// Scheduler.cc

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>

class Process
{
public:
    int id;
    int arrival;
    int burst;
    int priority;
};

class FCFS
{
public:
    void schedule(std::vector<Process> &processes)
    {
        (void)processes;
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

