// TaskSensor.cpp

#include "TaskSensor.h"

void TaskSensor::init(void) {
  mState = ST_SENSOR_OFF;
  mEvent = EV_SENSOR_IDLE;
}

void TaskSensor::update(void) {
  _statechart();
}


void TaskSensor::_statechart(void) {
  switch (mState) {
  case ST_SENSOR_OFF:
    break;

  default:
    break;
  }
}
