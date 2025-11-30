// scheduler.h

#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "task.h"
#include <vector>
using namespace std;
/**
 * @class RoundRobinScheduler
 * @brief Simulates a Round Robin CPU scheduling algorithm.
 *
 * This class manages a circular linked list of tasks and executes them
 * in a round-robin fashion. Each task gets a fixed time quantum. If a task
 * is not completed in its turn, it is preempted and put back at the end of the
 * queue.
 *
 * The scheduler is designed to be a high-level abstraction of a real-world
 * operating system scheduler. It is responsible for managing the lifecycle of
 * tasks, from their creation to their completion.
 */
class RoundRobinScheduler {
private:
  Task *head;       // Pointer to the current task to be executed.
  Task *tail;       // Pointer to the last task, which links back to the head.
  int time_quantum; // The maximum time slice each task gets per turn.
  int current_time; // Global clock, simulating the passage of time.
  int task_counter; // Counter to assign a unique ID to each new task.

  // Stores a copy of tasks that have finished execution.
  // This is used for generating a final report without traversing the live
  // task list.
  vector<Task> completed_history;

  // Internal helper function to safely remove a task from the circular list.
  void removeTask(Task *&current, Task *&prev);

public:
  // Constructor: Initializes the scheduler with a specific time quantum.
  RoundRobinScheduler(int quantum);

  // Destructor: Cleans up dynamically allocated memory for any remaining tasks.
  ~RoundRobinScheduler();

  // Adds a new task to the scheduler's circular queue.
  void addTask(string name, int time);

  // Starts the scheduling simulation and runs until all tasks are completed.
  void run();

  // Prints performance metrics (like waiting time, turnaround time) for all
  // completed tasks.
  void printMetrics();
};

#endif
