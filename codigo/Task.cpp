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

void Task::run(void) {
  mPeriodCount++;
  if (mPeriodCount >= mPeriodTicks) {
    mPeriodCount = 0;
    update();
  }
}
