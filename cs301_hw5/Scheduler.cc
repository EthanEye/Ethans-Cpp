// Scheduler.cc

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

class Process {
public:
    int id;
    int arrival;
    int burst;
    int priority;
    // etc.
};

class FCFS {
public:
    void schedule(std::vector<Process>& processes) {
        (void)processes;
    }
};

class SJF {
public:
    void schedule(std::vector<Process>& processes) {
        (void)processes;
    }
};

class PriorityScheduler {
public:
    void schedule(std::vector<Process>& processes) {
        (void)processes;
    }
};

int main(int argc, char* argv[]) {

    if (argc < 2) {
        std::cerr << "Usage: ./Scheduler <input_file>" << std::endl;
        return 1;
    }
    // ifstream opens file for reading
    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file!" << std::endl;
        return 1;
    }

    std::string line;
    // read line by line until end of file
    while (std::getline(file, line)) {
        std::cout << line << std::endl;
    }

    file.close();
    return 0;
}