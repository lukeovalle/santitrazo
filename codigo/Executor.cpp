// Executor.cpp

#include "Executor.h"

Executor::Executor() {
  mTasksSize = 0;
}

// Devuelve false (y no agrega nada) si ya se alcanzó N_TASKS, para no
// escribir fuera del arreglo mTasks.
bool Executor::addTask(Task * task) {
  if (task == nullptr || mTasksSize >= N_TASKS)
    return false;

  mTasks[mTasksSize++] = task;
  return true;
}

void Executor::increaseTicks(unsigned long ticks) {
  for (size_t i = 0; i < mTasksSize; i++) {
    mTasks[i]->addTicks(ticks);
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
      task->run();
    }
  }
}
