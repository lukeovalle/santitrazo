// Executor.cpp

#include "Executor.h"

Executor::Executor() {
  mTasksSize = 0;
}

void addTask(Task * task) {
  
}


void Executor::increaseTicks(unsigned long ticks) {
  for (size_t i = 0; i < mTasksSize; i++) {
    Task * task = mTasks[i];
    
    task->addTicks(ticks);
  }
}

void Executor::init() {
  for (size_t i = 0; i < mTasksSize; i++) {
    Task * task = mTasks[i];

    task->init();
  }
}

// Ejecuta las tareas según la cantidad de ticks acumulados
void Executor::update() {
  for (size_t i = 0; i < mTasksSize; i++) {
    Task * task = mTasks[i];

    while (task->pendingTicks() > 0) {
      task->consumeTick();
      task->update();
    }
  }
}
