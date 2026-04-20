// LED.cpp

#include "LED.h"

LED::LED(int pin) {
  mPin  = pin;
  mState = LOW;
  pinMode(mPin, OUTPUT);
}

void LED::turnOn() {
  mState = HIGH;
  _writePin();
}

void LED::turnOff() {
  mState = LOW;
  _writePin();
}

int LED::getState() {
  return mState;
}

void LED::_writePin(void) {
  digitalWrite(mPin, mState);
}
