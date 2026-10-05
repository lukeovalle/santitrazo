// TaskController.cpp

#include <Arduino.h>
#include "TaskController.h"
#include "utils.h"
#include "TaskLED.h"
#include "TaskBoton.h"
#include "TaskSensor.h"
#include "TaskMotor.h"

static int ticks = 10;

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
      _reiniciarPID();
      mTareas->led_arranque->encender();
      mTareas->motor_izq->encender();
      mTareas->motor_der->encender();
      mState = ST_CONTROLLER_RUNNING;
    }
    break;

  case ST_CONTROLLER_RUNNING: {
    if (mEvent == EV_CONTROLLER_BUTTON_PRESSED) {
      mTareas->led_arranque->apagar();
      mTareas->motor_izq->apagar();
      mTareas->motor_der->apagar();
      mState = ST_CONTROLLER_INIT;
      break;
    }

    // Lógica del PID
    // _calcularPID() tiene efectos secundarios (integral, error previo), así que
    // se llama una sola vez: CLAMP es un macro y evalúa sus argumentos más de una vez.
    int pid = _calcularPID();
    pid = CLAMP(pid, -PID_MAX, PID_MAX);

    int vel_max = 255; // valor máximo 255

    // pid > 0: la línea está a la derecha, frena el motor derecho.
    // pid < 0: la línea está a la izquierda, frena el motor izquierdo.
    // Uno suma y el otro resta; el CLAMP de TaskMotor::cambiarVelocidad()
    // mantiene cada velocidad en [-255, 255]. El motor que "suma" se queda en
    // el máximo y el que "resta" baja hasta 0 (pid = 255) y después gira hacia
    // atrás. El caso extremo es |pid| >= 510: una rueda a +255 y la otra a -255,
    // o sea girar sobre el lugar a máxima velocidad.
    mTareas->motor_izq->cambiarVelocidad(vel_max + pid);
    mTareas->motor_der->cambiarVelocidad(vel_max - pid);

    break;
  }

  default:
    mState = ST_CONTROLLER_INIT;
    break;
  }

  mEvent = EV_CONTROLLER_IDLE;
}

int TaskController::_calcularPID(void) {
  const float k_prop = 1.3,
              k_dif = 13,
              k_inte = 1.3e-2;

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
    ticks = 10;
  }

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
  if (activos < 0.01f)
    return mPrevError;

  return suma / activos; // promedio
}
