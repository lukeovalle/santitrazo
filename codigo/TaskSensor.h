// TaskSensor.h

#ifndef TASK_SENSOR__H_
#define TASK_SENSOR__H_

#include "Task.h"

#define SENSOR_VENTANA 13

typedef enum {
  ST_SENSOR_OFF,
  ST_SENSOR_ON
} task_sensor_st_t;

typedef enum {
  EV_SENSOR_IDLE,
  EV_SENSOR_HIGH,
  EV_SENSOR_LOW
} task_sensor_ev_t;

class TaskSensor : public Task {
  public:
    TaskSensor(int pin) : mPin(pin) {}
    void init(void) override;
    void update(void) override;
    bool estaActivo(void);
    float nivelActividad(void); // fracción [0, 1] promedio de las últimas N mediciones

  private:
    int mPin;
    task_sensor_st_t mState;
    task_sensor_ev_t mEvent;
    void _statechart(void);

    uint8_t mBuffer[SENSOR_VENTANA] = { 0 };
    uint8_t mIndice = 0;
    uint8_t mSuma = 0;
};

#endif
