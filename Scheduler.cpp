#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "task.h"
#include <vector>

class RoundRobinScheduler {
private:
  Task *head;       // Current task in the circle
  Task *tail;       // Last task (links back to head)
  int time_quantum; // Time slice per turn
  int current_time; // Global simulation clock
  int task_counter; // To assign unique IDs

  // We store completed tasks here to print a final report later
  // independent of the running linked list.
  std::vector<Task> completed_history;

  // Internal helper to remove a node from the circular list
  void removeTask(Task *&current, Task *&prev);

public:
  RoundRobinScheduler(int quantum);
  ~RoundRobinScheduler(); // Destructor to clean up any remaining nodes

  void addTask(std::string name, int time);
  void run();
  void printMetrics();
};

#endif
