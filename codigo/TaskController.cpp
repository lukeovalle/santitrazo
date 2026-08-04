// TaskController.cpp

#include <HardwareSerial.h>
#include "TaskController.h"
#include "utils.h"
#include "TaskLED.h"
#include "TaskBoton.h"
#include "TaskSensor.h"
#include "TaskMotor.h"

static int ticks = 100;

void TaskController::init(void) {
  mState = ST_CONTROLLER_INIT;
  mEvent = EV_CONTROLLER_IDLE;
  mBotonAnterior = false;
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
  case ST_CONTROLLER_INIT:
    if (mEvent == EV_CONTROLLER_BUTTON_PRESSED) {
      mTareas->led_arranque->encender();
      mTareas->motor_izq->encender();
      mTareas->motor_der->encender();
      mState = ST_CONTROLLER_RUNNING;
    }
    break;

  case ST_CONTROLLER_RUNNING:
    if (mEvent == EV_CONTROLLER_BUTTON_PRESSED) {
      mTareas->led_arranque->apagar();
      mTareas->motor_izq->apagar();
      mTareas->motor_der->apagar();
      mState = ST_CONTROLLER_INIT;
      break;
    }

    // Lógica del PID
    int pid = _calcularPID();

    int vel_max = 255; // valor máximo 255

    if (pid > 0) {
      mTareas->motor_izq->cambiarVelocidad(vel_max);
      mTareas->motor_der->cambiarVelocidad(vel_max - pid);
    } else if (pid < 0) {
      mTareas->motor_izq->cambiarVelocidad(vel_max + pid);
      mTareas->motor_der->cambiarVelocidad(vel_max);
    } else {
      mTareas->motor_izq->cambiarVelocidad(vel_max);
      mTareas->motor_der->cambiarVelocidad(vel_max);
    }

    break;

  default:
    mState = ST_CONTROLLER_INIT;
    break;
  }

  mEvent = EV_CONTROLLER_IDLE;
}

int TaskController::_calcularPID(void) {
  const float k_prop = 1.5,
              k_dif = 10,
              k_inte = 1e-3;

  float error = _calcular_error();

  // parte proporcional
  float prop = k_prop * error;

  // parte integral
  mAcumIntegralError += error;
  mAcumIntegralError = CLAMP(mAcumIntegralError, -1e3, 1e3);
  float integral = k_inte * mAcumIntegralError;

  // parte diferencial
  // podría dividir por un dt pero asumo que es constante y "está incluído " en k_dif
  float de_dt = (error - mPrevError);
  float diferencial = k_dif * de_dt;

  ticks--;
  if (!ticks) {
    Serial.print(prop);
    Serial.print(",");
    Serial.print(integral);
    Serial.print(",");
    Serial.println(diferencial);
    ticks = 100;
  }

  mPrevError = error;
  return (int)(prop + integral + diferencial);
}

float TaskController::_calcular_error(void) {
  const float sensores[] = { -200, -100, 100, 200 }; // Pesos de cada sensor
  float suma = 0;
  float activos = 0;

  for (int i = 0; i < TAM_SENSORES; i++) {
    int activo = mTareas->sensores[i]->estaActivo();
    suma += sensores[i] * activo; // multiplico por 1 si está activo y 0 si no
    activos += activo;
  }

  // si no se leyeron sensores, uso el último valor así sigue doblando hasta volver a la línea
  if (activos == 0)
    return mPrevError;

  return suma / activos; // promedio
}
