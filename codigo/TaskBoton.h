// TaskBoton.h

#ifndef TASK_BOTON__H_
#define TASK_BOTON__H_

#include "Task.h"

typedef enum {
  ST_BOTON_PRESSED,
  ST_BOTON_PRESSING,
  ST_BOTON_RELEASED,
  ST_BOTON_RELEASING
} task_boton_st_t;

typedef enum {
  EV_BOTON_IDLE,
  EV_BOTON_PRESSING,
  EV_BOTON_RELEASING
} task_boton_ev_t;

class TaskBoton : public Task {
  public:
    TaskBoton(int pin) : mPin(pin) {}
    void init(void) override;
    void update(void) override;
    void setEvento(task_boton_ev_t ev);

  private:
    int mPin;
    task_boton_st_t mState;
    task_boton_ev_t mEvent;
    void _statechart(void);
};

#endif
