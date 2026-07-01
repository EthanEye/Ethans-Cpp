Ethan Eye
CS 370 
HW5 

Description:
Implements three CPU scheduling algorithms:
- First Come First Serve (FCFS)  Non-preemptive
- Shortest Job First (SJF) Preemptive
- Priority Scheduling Preemptive

Usage:
make
./Scheduler Input.csv

Input Format:
CSV file with: ProcessID, Arrival Time, Burst Duration, Priority

Output:
Average Turnaround Time, Average Waiting Time, and Throughput
for each scheduling algorithm.