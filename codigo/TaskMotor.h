// TaskMotor.h

#ifndef TASK_MOTOR__H_
#define TASK_MOTOR__H_

#include "Task.h"

typedef enum {
  ST_MOTOR_OFF,
  ST_MOTOR_ON
} task_motor_st_t;

typedef enum {
  EV_MOTOR_IDLE,
  EV_MOTOR_TURN_ON,
  EV_MOTOR_TURN_OFF,
  EV_MOTOR_CHANGE_VELOCITY,
} task_motor_ev_t;

class TaskMotor : public Task {
  public:
    TaskMotor(int pin) : mPin(pin) {}
    void init(void) override;
    void update(void) override;
    void setEvento(task_motor_ev_t ev);

  private:
    int mPin;
    task_motor_st_t mState;
    task_motor_ev_t mEvent;
    void _statechart(void);
};

#endif
