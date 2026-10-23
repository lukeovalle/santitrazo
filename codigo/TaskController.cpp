// TaskController.cpp

#include <Arduino.h>
#include "TaskController.h"
#include "utils.h"
#include "TaskLED.h"
#include "TaskBoton.h"
#include "TaskSensor.h"
#include "TaskMotor.h"

void TaskController::init(void) {
  mState = ST_CONTROLLER_INIT;
  mEvent = EV_CONTROLLER_IDLE;
  mBotonAnterior = false;
  _reiniciarPID();
}

// Borra la memoria del PID (integral y error previo) para que una corrida
// nueva no arrastre el estado de la anterior.
void TaskController::_reiniciarPID(void) {
  mPrevError = 0;
  mAcumIntegralError = 0;
  mTurboTicks = 0;
}

void TaskController::update(void) {
  // Veo si se apretó el botón y si antes no estaba presionado.
  bool boton = mTareas->boton_largada->estaPresionado();

  if (!mBotonAnterior && boton)
    mEvent = EV_CONTROLLER_BUTTON_PRESSED;

  mBotonAnterior = boton;

  _statechart();
}


void TaskController::_statechart(void) {
  switch (mState) {
  case ST_CONTROLLER_INIT: {
    if (mEvent == EV_CONTROLLER_BUTTON_PRESSED) {
      _reiniciarPID();
      mTareas->led_arranque->encender();
      mTareas->motor_izq->encender();
      mTareas->motor_der->encender();
      mState = ST_CONTROLLER_RUNNING;
    }
    break;
  }

  case ST_CONTROLLER_RUNNING: {
    if (mEvent == EV_CONTROLLER_BUTTON_PRESSED) {
      mTareas->led_arranque->apagar();
      mTareas->motor_izq->apagar();
      mTareas->motor_der->apagar();
      mState = ST_CONTROLLER_INIT;
      break;
    }

    // Lógica del PID
    int pid = _calcularPID();
    pid = CLAMP(pid, -PID_MAX, PID_MAX);
    
    // validaciones del turbo
    bool turboPrevio = mTurboTicks >= TURBO_TICKS_ENTRADA && mTurboTicks <= TURBO_TICKS_DURACION;
    float limite = turboPrevio ? TURBO_ERROR_SALIDA : TURBO_ERROR_ENTRADA;
    if (mLineaVisible && fabs(mPrevError) <= limite) { // solo entro al turbo en rectas
      if (mTurboTicks == TURBO_TICKS_DURACION)
        mTurboTicks++;
    } else {
      mTurboTicks = 0;
    }
    bool turbo = mTurboTicks >= TURBO_TICKS_ENTRADA && mTurboTicks <= TURBO_TICKS_DURACION;

    int vel_max = turbo ? VEL_TURBO : VEL_NORMAL;

    // pid > 0: la línea está a la derecha, frena el motor derecho.
    // pid < 0: la línea está a la izquierda, frena el motor izquierdo.
    // Uno suma y el otro resta; el CLAMP de TaskMotor::cambiarVelocidad()
    // mantiene cada velocidad en [-255, 255]. El motor que "suma" se queda en
    // el máximo y el que "resta" baja hasta 0 y después gira hacia atrás.
    // El caso extremo es |pid| >= 510: una rueda a +255 y la otra a -255,
    // o sea girar sobre el lugar a máxima velocidad.
    mTareas->motor_izq->cambiarVelocidad(vel_max + pid);
    mTareas->motor_der->cambiarVelocidad(vel_max - pid);

    break;
  }

  default: {
    mState = ST_CONTROLLER_INIT;
    break;
  }
  }

  mEvent = EV_CONTROLLER_IDLE;
}

int TaskController::_calcularPID(void) {
  float error = _calcular_error();

  // parte proporcional
  float prop = PID_KP * error;

  // parte integral
  mAcumIntegralError += error;
  mAcumIntegralError = CLAMP(mAcumIntegralError, -1e3, 1e3);
  float integral = PID_KI * mAcumIntegralError;

  // parte diferencial
  // podría dividir por un dt pero asumo que es constante y "está incluído " en PID_KD
  float de_dt = (error - mPrevError);
  float diferencial = PID_KD * de_dt;

  mPrevError = error;
  return (int)(prop + integral + diferencial);
}

float TaskController::_calcular_error(void) {
  static const float sensores[] = { -200, -100, 100, 200 }; // Pesos de cada sensor
  float suma = 0;
  float activos = 0;

  for (int i = 0; i < TAM_SENSORES; i++) {
    float activo = mTareas->sensores[i]->nivelActividad();
    suma += sensores[i] * activo; // multiplico por el valor sensado en rango [0, 1]
    activos += activo;
  }

  // si no se leyeron sensores, uso el último valor así sigue doblando hasta volver a la línea
  mLineaVisible = (activos >= 0.01f);
  if (!mLineaVisible)
    return mPrevError;

  return suma / activos; // promedio
}
