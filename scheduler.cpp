
#include "scheduler.h"
#include <iomanip>
#include <iostream>
using namespace std;
/**
 * @brief Construct a new Round Robin Scheduler:: Round Robin Scheduler object
 *
 * @param quantum The time quantum for the scheduler.
 */
RoundRobinScheduler::RoundRobinScheduler(int quantum)
    : head(nullptr), tail(nullptr), time_quantum(quantum), current_time(0),
      task_counter(0) {}

/**
 * @brief Destroy the Round Robin Scheduler:: Round Robin Scheduler object
 *
 * This destructor is responsible for cleaning up any remaining tasks in the
 * scheduler. It iterates through the circular linked list and deletes each
 * task, one by one.
 */
RoundRobinScheduler::~RoundRobinScheduler() {
  if (!head) {
    return;
  }
  Task *current = head;
  do {
    Task *temp = current;
    current = current->next;
    delete temp;
  } while (current != head);
}

/**
 * @brief Adds a new task to the scheduler's circular queue.
 *
 * @param name The name of the task.
 * @param time The burst time of the task.
 */
void RoundRobinScheduler::addTask(std::string name, int time) {
  Task *newTask = new Task(++task_counter, name, time, current_time);
  if (!head) {
    head = newTask;
    tail = newTask;
    newTask->next = head;
  } else {
    tail->next = newTask;
    tail = newTask;
    tail->next = head;
  }
}

/**
 * @brief Starts the scheduling simulation and runs until all tasks are
 * completed.
 *
 * This is the core of the scheduler. It iterates through the tasks and
 * simulates the round-robin execution. It continues until all tasks have been
 * completed.
 */
void RoundRobinScheduler::run() {
  if (!head) {
    return;
  }

  Task *current = head;
  Task *prev = tail;

  cout << " Round Robin Scheduler Simulation " << endl;

  while (head) {
    int time_slice = (current->remaining_time > time_quantum)
                         ? time_quantum
                         : current->remaining_time;

    cout << "Time " << current_time << ": Executing task " << current->name
         << " for " << time_slice
         << "ms (remaining: " << current->remaining_time - time_slice << "ms)"
         << std::endl;

    current->remaining_time -= time_slice;
    current_time += time_slice;

    if (current->remaining_time <= 0) {
      current->completion_time = current_time;
      current->turnaround_time =
          current->completion_time - current->arrival_time;
      current->waiting_time = current->turnaround_time - current->burst_time;

      completed_history.push_back(*current);

      Task *next_task = current->next;
      removeTask(current, prev);
      current = next_task;
      if (head == nullptr)
        break;

    } else {
      prev = current;
      current = current->next;
    }
  }
  cout << "Simulation Complete " << endl;
}

/**
 * @brief Internal helper function to safely remove a task from the circular
 * list.
 *
 * @param current The task to be removed.
 * @param prev The task before the one to be removed.
 */
void RoundRobinScheduler::removeTask(Task *&current, Task *&prev) {
  if (!head)
    return;

  if (head == tail) { // Only one task
    delete head;
    head = nullptr;
    tail = nullptr;
    current = nullptr;
  } else {
    if (current == head) {
      head = head->next;
    }
    if (current == tail) {
      tail = prev;
    }
    prev->next = current->next;
    delete current;
  }
}

/**
 * @brief Prints performance metrics (like waiting time, turnaround time) for
 * all completed tasks.
 *
 * This function is responsible for printing a summary of the performance of the
 * scheduler. It prints the waiting time, turnaround time, and burst time for
 * each task, as well as the average waiting time and average turnaround time.
 */
void RoundRobinScheduler::printMetrics() {
  if (completed_history.empty()) {
    cout << "No tasks were executed." << std::endl;
    return;
  }

  float avg_waiting_time = 0;
  float avg_turnaround_time = 0;

  cout << "\nPerformance Metrics" << std::endl;
  cout << std::left << std::setw(5) << "ID" << std::setw(15) << "Name"
       << std::setw(15) << "Burst Time" << std::setw(15) << "Waiting Time"
       << std::setw(20) << "Turnaround Time" << std::endl;

  for (const auto &task : completed_history) {
    cout << std::left << std::setw(5) << task.id << std::setw(15) << task.name
         << std::setw(15) << task.burst_time << std::setw(15)
         << task.waiting_time << std::setw(20) << task.turnaround_time
         << std::endl;
    avg_waiting_time += task.waiting_time;
    avg_turnaround_time += task.turnaround_time;
  }

  avg_waiting_time /= completed_history.size();
  avg_turnaround_time /= completed_history.size();

  cout << "\nAverage Waiting Time: " << avg_waiting_time << "ms" << std::endl;
  cout << "Average Turnaround Time: " << avg_turnaround_time << "ms"
       << std::endl;
}
