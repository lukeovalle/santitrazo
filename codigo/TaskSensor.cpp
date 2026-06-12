#include "Arduino.h"
// TaskSensor.cpp

#include "TaskSensor.h"

void TaskSensor::init(void) {
  mState = ST_SENSOR_OFF;
  mEvent = EV_SENSOR_IDLE;

  pinMode(mPin, INPUT);
}

void TaskSensor::update(void) {
  mEvent = (digitalRead(mPin) == HIGH) ? EV_SENSOR_HIGH : EV_SENSOR_LOW;

  _statechart();
}

bool TaskSensor::estaActivo(void) {
  return mState == ST_SENSOR_ON;
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
