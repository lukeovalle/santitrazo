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

void TaskLED::encender() {
  mEvent = EV_LED_TURN_ON;
}

void TaskLED::apagar() {
  mEvent = EV_LED_TURN_OFF;
}

void TaskLED::_statechart() {
  switch(mState) {
  case ST_LED_OFF:
    if (mEvent == EV_LED_TURN_ON) {
      digitalWrite(mPin, HIGH);

      Serial.print("BOTON ");
      Serial.print(mPin);
      Serial.println(": HIGH");
      mState = ST_LED_ON;
      mEvent = EV_LED_IDLE;
    }
    break;

  case ST_LED_ON:
    if (mEvent == EV_LED_TURN_OFF) {
      digitalWrite(mPin, LOW);

      Serial.print("BOTON ");
      Serial.print(mPin);
      Serial.println(": LOW");
      mState = ST_LED_OFF;
      mEvent = EV_LED_IDLE;
    }
    break;

  default:
    break;
  }
}
