// TaskMotor.cpp

#include "TaskMotor.h"

void TaskMotor::init(void) {
  mState = ST_MOTOR_OFF;
  mEvent = EV_MOTOR_IDLE;
}

void TaskMotor::update(void) {
  _statechart();
}


void TaskMotor::_statechart(void) {
  switch (mState) {
  case ST_MOTOR_OFF:
    break;

  default:
    break;
  }
}
