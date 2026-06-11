// TaskLED.cpp

#include <Arduino.h>
#include "TaskLED.h"

void TaskLED::init() {
  mState = ST_LED_OFF;
  mEvent = EV_LED_IDLE;

  pinMode(mPin, OUTPUT);
}

void TaskLED::update() {
  _statechart();
}

void TaskLED::setEvento(task_LED_ev_t ev) {
  mEvent = ev;
}

void TaskLED::_statechart() {
  switch(mState) {
  case ST_LED_OFF:
    if (mEvent == EV_LED_TURN_ON) {
      digitalWrite(mPin, HIGH);
      mState = ST_LED_ON;
      mEvent = EV_LED_IDLE;
    }
    break;

  case ST_LED_ON:
    if (mEvent == EV_LED_TURN_OFF) {
      digitalWrite(mPin, LOW);
      mState = ST_LED_OFF;
      mEvent = EV_LED_IDLE;
    }
    break;

  default:
    break;
  }
}
