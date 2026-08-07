#include "Arduino.h"
// TaskSensor.cpp

#include "TaskSensor.h"

void TaskSensor::init(void) {
  mState = ST_SENSOR_OFF;
  mEvent = EV_SENSOR_IDLE;

  pinMode(mPin, INPUT);
}

void TaskSensor::update(void) {
  uint8_t lectura = (digitalRead(mPin) == HIGH) ? 1 : 0;

  // cola circular con las últimas mediciones
  mSuma -= mBuffer[mIndice];
  mBuffer[mIndice] = lectura;
  mSuma += lectura;
  mIndice = (mIndice + 1) % SENSOR_VENTANA;

  mEvent = lectura ? EV_SENSOR_HIGH : EV_SENSOR_LOW;

  _statechart();
}

bool TaskSensor::estaActivo(void) {
  return mState == ST_SENSOR_ON;
}

float TaskSensor::nivelActividad(void) {
  return (float)mSuma  / SENSOR_VENTANA;
}

void TaskSensor::_statechart(void) {
  switch (mState) {
  case ST_SENSOR_OFF:
    if (mEvent == EV_SENSOR_HIGH)
      mState = ST_SENSOR_ON;
    break;

  case ST_SENSOR_ON:
    if (mEvent == EV_SENSOR_LOW)
      mState = ST_SENSOR_OFF;
    break;

  default:
    mState = ST_SENSOR_OFF;
    break;
  }

  mEvent = EV_SENSOR_IDLE;
}
