#ifndef TASK_H
#define TASK_H

#include <string>

// Process Control Block (PCB) in an OS  ==> to manage a information
struct Task {
  int id;
  std::string name;

  int burst_time;
  int remaining_time;

  /*
   Metrics for analysis
   Waiting Time (WT): The total time a process spent in the ready queue waiting
   for the CPU. Turnaround Time (TAT): The total time from submission to
   completion (Completion Time - Arrival Time).
   */
  int arrival_time;
  int completion_time;
  int waiting_time;
  int turnaround_time;

  Task *next;

  Task(int pid, std::string pname, int ptime, int arrival)
      : id(pid), name(pname), burst_time(ptime), remaining_time(ptime),
        arrival_time(arrival), completion_time(0), waiting_time(0),
        turnaround_time(0), next(nullptr) {}
};

#endif
