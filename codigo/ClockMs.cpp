#include "Arduino.h"
// ClockMs.cpp

#include "ClockMs.h"

void ClockMs::init(void) {
  mLastMs = millis();
}

bool ClockMs::ms_passed(void) {
  unsigned long now = millis();

  if (now - mLastMs >= 1) {
    mLastMs = now;
    return true;
  }

  return false;
}

unsigned long ClockMs::pending_ticks() {
  unsigned long now = millis();
  unsigned long delta = mLastMs - now;

  if (delta > 0) {
    mLastMs += delta;
  }

  return delta;
}
