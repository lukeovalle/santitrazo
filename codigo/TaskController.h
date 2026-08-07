// TaskController.h

#ifndef TASK_CONTROLLER__H_
#define TASK_CONTROLLER__H_

#include "Task.h"

#define TAM_SENSORES 4

// declaraciones de clases a usar
class TaskLED;
class TaskBoton;
class TaskSensor;
class TaskMotor;

typedef enum {
  ST_CONTROLLER_INIT,
  ST_CONTROLLER_RUNNING
} task_controller_st_t;

typedef enum {
  EV_CONTROLLER_IDLE,
  EV_CONTROLLER_BUTTON_PRESSED
} task_controller_ev_t;

// Estructura de contexto
typedef struct {
  TaskLED * led_arranque;
  TaskBoton * boton_largada;
  TaskSensor * sensores[TAM_SENSORES];
  TaskMotor * motor_izq;
  TaskMotor * motor_der;
} controller_contexto;



class TaskController : public Task {
  public:
    TaskController(controller_contexto * contexto, unsigned long periodTicks = 10) : Task(periodTicks), mTareas(contexto) {}
    void init(void) override;
    void update(void) override;
    

  private:
    controller_contexto * mTareas;
    bool mBotonAnterior = false;
    float mPrevError = 0;
    float mAcumIntegralError = 0;
    task_controller_st_t mState;
    task_controller_ev_t mEvent;
    void _statechart(void);
    int _calcularPID(void);
    float _calcular_error(void);
};


#endif
