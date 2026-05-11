// TaskLED.cpp

#include <Arduino.h>
#include "TaskLED.h"

void TaskLED::init() {
  mState = ST_LED_OFF;
  mEvent = EV_LED_IDLE;
}

void TaskLED::update() {
  _statechart();
}

void TaskLED::_statechart() {
  switch(mState) {
  case ST_LED_OFF:
    if (mEvent == EV_LED_TURN_ON) {
      digitalWrite(mPin, HIGH);
      mState = ST_LED_ON;
    }
    break;

  case ST_LED_ON:
    if (mEvent == EV_LED_TURN_OFF) {
      digitalWrite(mPin, LOW);
      mState = ST_LED_OFF;
    }
    break;

  default:
    break;
  }

}