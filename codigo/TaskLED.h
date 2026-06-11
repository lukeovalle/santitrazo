// TaskLED.h

#ifndef TASK_LED__H_
#define TASK_LED__H_

#include "Task.h"

typedef enum {
  ST_LED_OFF,
  ST_LED_ON,
} task_LED_st_t;

typedef enum {
  EV_LED_IDLE,
  EV_LED_TURN_ON,
  EV_LED_TURN_OFF
} task_LED_ev_t;

class TaskLED : public Task {
  public:
    TaskLED(int pin) : mPin(pin) {}
    void init(void) override;
    void update(void) override;
    void encender(void);
    void apagar(void);

  private:
    int mPin;
    task_LED_st_t mState;
    task_LED_ev_t mEvent;
    void _statechart(void);
};

#endif
