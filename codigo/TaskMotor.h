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

// Motor con puente H: un pin PWM (enable) y dos pines de dirección (IN1, IN2).
//   adelante: IN1 = HIGH, IN2 = LOW
//   atrás:    IN1 = LOW,  IN2 = HIGH
// Si el motor gira al revés de lo esperado, pasar invertido = true (o
// intercambiar los cables del motor).
class TaskMotor : public Task {
  public:
    TaskMotor(int pinPwm, int pinIn1, int pinIn2, bool invertido = false)
      : mPinPwm(pinPwm), mPinIn1(pinIn1), mPinIn2(pinIn2), mInvertido(invertido) {}
    void init(void) override;
    void update(void) override;
    void apagar(void);
    void encender(void);
    // vel en [-255, 255]: el signo elige el sentido de giro, el módulo es el PWM.
    void cambiarVelocidad(int vel);

  private:
    int mPinPwm;
    int mPinIn1;
    int mPinIn2;
    bool mInvertido;
    int mVel;
    task_motor_st_t mState;
    task_motor_ev_t mEvent;
    void _statechart(void);
    void _encenderPWM(void);
    void _apagarPWM(void);
    void _setDireccion(bool adelante);
};

#endif
