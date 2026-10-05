// TaskMotor.cpp
#include "Arduino.h"
#include "TaskMotor.h"
#include "utils.h"

void TaskMotor::init(void) {
  mState = ST_MOTOR_OFF;
  mEvent = EV_MOTOR_IDLE;
  mVel = 0;
  pinMode(mPinPwm, OUTPUT);
  pinMode(mPinIn1, OUTPUT);
  pinMode(mPinIn2, OUTPUT);
  digitalWrite(mPinIn1, LOW);
  digitalWrite(mPinIn2, LOW);
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
  mVel = CLAMP(vel, -255, 255);
}

void TaskMotor::_statechart(void) {
  switch (mState) {
  case ST_MOTOR_OFF:
    if (mEvent == EV_MOTOR_TURN_ON) {
      _encenderPWM();
      mState = ST_MOTOR_ON;
    }
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

void TaskMotor::_setDireccion(bool adelante) {
  if (mInvertido)
    adelante = !adelante;

  digitalWrite(mPinIn1, adelante ? HIGH : LOW);
  digitalWrite(mPinIn2, adelante ? LOW : HIGH);
}

void TaskMotor::_encenderPWM(void) {
  _setDireccion(mVel >= 0);
  analogWrite(mPinPwm, mVel >= 0 ? mVel : -mVel);
}

void TaskMotor::_apagarPWM(void) {
  // Pongo mVel en 0 para que al volver a encender el motor no arranque
  // con la última velocidad de la corrida anterior.
  mVel = 0;
  analogWrite(mPinPwm, 0);
  digitalWrite(mPinIn1, LOW);
  digitalWrite(mPinIn2, LOW);
}
