// task.h

#ifndef TASK_H
#define TASK_H

#include <iostream>
#include <string>
using namespace std;
/**
 * @struct Task
 * @brief Represents a single process or task in the scheduler.
 *
 * This structure acts like a Process Control Block (PCB). It holds all
 * essential information about a task, including its identity, execution state,
 * and performance metrics. These tasks are organized in a circular linked list
 * by the scheduler.
 *
 * The Task struct is the fundamental unit of work in the scheduler. It is
 * designed to be a lightweight representation of a process, containing only
 * the information necessary for the scheduler to do its job.
 */
struct Task {
  int id;      // Unique identifier for the task.
  string name; // A human-readable name for the task.

  int burst_time;     // The original, total CPU time required by the task.
  int remaining_time; // The CPU time still needed for the task to complete.

  int arrival_time;    // The simulation time when the task was added to the
                       // queue.
  int completion_time; // The simulation time when the task finished execution.
  int waiting_time;    // Total time the task spent in the ready queue, waiting
                       // for its turn.
  int turnaround_time; // Total time from arrival to completion.

  Task *next; // Pointer to the next task in the circular linked list.

  /**
   * @brief Constructor for the Task struct.
   * @param pid A unique integer ID for the task.
   * @param pname The name of the task.
   * @param ptime The total CPU burst time required.
   * @param arrival The simulation time when the task arrives.
   */
  Task(int pid, string pname, int ptime, int arrival)
      : id(pid), name(pname), burst_time(ptime), remaining_time(ptime),
        arrival_time(arrival), completion_time(0), waiting_time(0),
        turnaround_time(0), next(nullptr) {}
};

#endif
