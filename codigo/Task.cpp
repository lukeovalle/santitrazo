// Task.cpp

#include "Task.h"

void Task::addTicks(unsigned long ticks) {
  mTick += ticks;
}

void Task::consumeTick() {
  mTick--;
}

unsigned long Task::pendingTicks() { 
  return mTick;
}
