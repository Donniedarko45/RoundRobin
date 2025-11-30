#include "scheduler.h"

using namespace std;

// To compile: g++ main.cpp scheduler.cpp -o scheduler
// To run: ./scheduler

/**
 * @brief The main entry point of the program.
 *
 * This program simulates a Round Robin CPU scheduling algorithm. It creates a
 * scheduler, adds a few tasks to it, runs the simulation, and then prints the
 * performance metrics.
 *
 * @return 0 on successful execution.
 */
int main() {
  // 1. Initialize Scheduler with a Time Quantum of 20ms
  RoundRobinScheduler cpu(20);

  // 2. Load Tasks (Name, Burst Time)
  // Simulating a mix of CPU-bound and I/O-bound tasks
  cpu.addTask("Chrome_Tab1", 50);  // Long task
  cpu.addTask("Spotify_Core", 30); // Medium task
  cpu.addTask("Notepad", 10);      // Short task (completes in 1 turn)
  cpu.addTask("VS_Code", 85);      // Very long task

  // 3. Start the OS Simulation
  cpu.run();

  // 4. Analyze Performance
  cpu.printMetrics();

  return 0;
}
