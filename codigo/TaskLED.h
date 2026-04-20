// TaskLED.h

#ifndef TASK_LED__H_
#define TASK_LED__H_

#include "LED.h"
#include "Task.h"

class TaskLED : public Task {
  public:
    TaskLED(int pin) : led(pin) {}
    void init(void) override;
    void update(void) override;

  private:
    LED led;
};

#endif
