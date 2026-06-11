// TaskController.h

#ifndef TASK_CONTROLLER__H_
#define TASK_CONTROLLER__H_

#include "Task.h"

// declaraciones de clases a usar
class TaskLED;
class TaskBoton;


typedef enum {
  ST_CONTROLLER_INIT,
} task_controller_st_t;

typedef enum {
  EV_CONTROLLER_IDLE,
} task_controller_ev_t;

// Estructura de contexto
typedef struct {
  TaskLED * led_arranque;
  TaskBoton * boton_largada;
} controller_contexto;



class TaskController : public Task {
  public:
    TaskController(controller_contexto * contexto) : mTareas(contexto) {}
    void init(void) override;
    void update(void) override;
    

  private:
    controller_contexto * mTareas;
    task_controller_st_t mState;
    task_controller_ev_t mEvent;
    void _statechart(void);
};


#endif
