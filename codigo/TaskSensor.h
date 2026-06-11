// TaskSensor.h

#ifndef TASK_SENSOR__H_
#define TASK_SENSOR__H_

#include "Task.h"

typedef enum {
  ST_SENSOR_OFF,
  ST_SENSOR_ON
} task_sensor_st_t;

typedef enum {
  EV_SENSOR_IDLE,
  EV_SENSOR_READ,
} task_sensor_ev_t;

class TaskSensor : public Task {
  public:
    TaskSensor(int pin) : mPin(pin) {}
    void init(void) override;
    void update(void) override;
    void setEvento(task_sensor_ev_t ev);

  private:
    int mPin;
    task_sensor_st_t mState;
    task_sensor_ev_t mEvent;
    void _statechart(void);
};

#endif
