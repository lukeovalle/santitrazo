// TaskMotor.cpp
#include <float.h>
#include "Arduino.h"
#include "TaskMotor.h"
#include "utils.h"

void TaskMotor::init(void) {
  mState = ST_MOTOR_OFF;
  mEvent = EV_MOTOR_IDLE;
  mVel = 0;
  pinMode(mPin, OUTPUT);
}

void TaskMotor::update(void) {
  _statechart();
}

void TaskMotor::apagar(void) {
  mEvent = EV_MOTOR_TURN_OFF;
}

void TaskMotor::encender(void) {
  mEvent = EV_MOTOR_TURN_ON;
}

void TaskMotor::cambiarVelocidad(int vel) {
  mEvent = EV_MOTOR_CHANGE_VELOCITY;
  mVel = CLAMP(vel, 0, 255);
}

void TaskMotor::_statechart(void) {
  switch (mState) {
  case ST_MOTOR_OFF:
    if (mEvent == EV_MOTOR_TURN_ON) {
      _encenderPWM();
      mState = ST_MOTOR_ON;
    };
    break;

  case ST_MOTOR_ON:
    if (mEvent == EV_MOTOR_TURN_OFF) {
      _apagarPWM();
      mState = ST_MOTOR_OFF;
    } else if (mEvent == EV_MOTOR_CHANGE_VELOCITY) {
      _encenderPWM();
    }
    break;

  default:
    mState = ST_MOTOR_OFF;
    _apagarPWM();
    break;
  }

  mEvent = EV_MOTOR_IDLE;
}

void TaskMotor::_encenderPWM(void) {
  analogWrite(mPin, mVel);
}

void TaskMotor::_apagarPWM(void) {
  analogWrite(mPin, 0);
}
