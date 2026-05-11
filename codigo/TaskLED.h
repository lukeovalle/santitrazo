// TaskLED.h

#ifndef TASK_LED__H_
#define TASK_LED__H_

#include "Task.h"
#include "TaskLEDAttribute.h"

class TaskLED : public Task {
  public:
    TaskLED(int pin) : mPin(pin) {}
    void init(void) override;
    void update(void) override;

  private:
    int mPin;
    task_LED_st_t mState;
    task_LED_ev_t mEvent;
    void _statechart(void);
};

#endif
