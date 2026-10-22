// TaskMotor.cpp
#include "Arduino.h"
#include "TaskMotor.h"
#include "utils.h"

void TaskMotor::init(void) {
  mState = ST_MOTOR_OFF;
  mEvent = EV_MOTOR_IDLE;
  mVel = 0;
  pinMode(mPinAdelante, OUTPUT);
  pinMode(mPinAtras, OUTPUT);
  analogWrite(mPinAdelante, 0);
  analogWrite(mPinAtras, 0);
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

void TaskMotor::_encenderPWM(void) {
  int vel = mInvertido ? -mVel : mVel;

  // Siempre pongo primero en 0 el pin del sentido que se apaga, así los dos
  // pines nunca tienen PWM a la vez.
  if (vel >= 0) {
    analogWrite(mPinAtras, 0);
    analogWrite(mPinAdelante, vel);
  } else {
    analogWrite(mPinAdelante, 0);
    analogWrite(mPinAtras, -vel);
  }
}

void TaskMotor::_apagarPWM(void) {
  // Pongo mVel en 0 para que al volver a encender el motor no arranque
  // con la última velocidad de la corrida anterior.
  mVel = 0;
  // Ambos pines en 0 con el enable en alto: freno activo.
  analogWrite(mPinAdelante, 0);
  analogWrite(mPinAtras, 0);
}
