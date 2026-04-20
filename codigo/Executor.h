// Executor.h

#ifndef EXECUTOR__H_
#define EXECUTOR__H_

#define N_TASKS 5

#include <Arduino.h>
#include "Task.h"

class Executor {
  public:
    Executor(void);
    void addTask(Task * task);
    void increaseTicks(unsigned long ticks);
    void init(void);
    void update(void);

  private:
    Task * mTasks[N_TASKS];
    size_t mTasksSize;
};

#endif
