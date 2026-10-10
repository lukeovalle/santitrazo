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

// Motor con puente H (L298N) manejado con DOS pines PWM, uno por sentido, y el
// enable (ENA/ENB) siempre en alto (jumper puesto o cable a 5 V).
//   vel > 0: PWM en pinAdelante, pinAtras = 0
//   vel < 0: PWM en pinAtras,    pinAdelante = 0
//   vel = 0: ambos pines en 0 (IN1 = IN2 = LOW con enable alto) => FRENO ACTIVO
// Como la parte "apagada" del PWM también es freno (no rueda libre), el torque
// cambia de forma continua al pasar por vel = 0: no hay salto entre 0 y +-1.
// Los dos pines tienen que ser pines con PWM (en el 328P: 3, 5, 6, 9, 10, 11).
// Si el motor gira al revés de lo esperado, pasar invertido = true (o
// intercambiar los cables del motor).
class TaskMotor : public Task {
  public:
    TaskMotor(int pinAdelante, int pinAtras, bool invertido = false)
      : mPinAdelante(pinAdelante), mPinAtras(pinAtras), mInvertido(invertido) {}
    void init(void) override;
    void update(void) override;
    void apagar(void);
    void encender(void);
    // vel en [-255, 255]: el signo elige el sentido de giro, el módulo es el PWM.
    void cambiarVelocidad(int vel);

  private:
    int mPinAdelante;
    int mPinAtras;
    bool mInvertido;
    int mVel;
    task_motor_st_t mState;
    task_motor_ev_t mEvent;
    void _statechart(void);
    void _encenderPWM(void);
    void _apagarPWM(void);
};

#endif
