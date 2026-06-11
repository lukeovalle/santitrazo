#include "Arduino.h"
// TaskBoton.cpp

#include "TaskBoton.h"

void TaskBoton::init(void) {
  mState = ST_BOTON_RELEASED;
  mEvent = EV_BOTON_IDLE;

  pinMode(mPin, INPUT);
}

void TaskBoton::update(void) {
  if (digitalRead(mPin) == LOW) { // en 0V está apretado, en 5V está abierto
    mEvent = EV_BOTON_PRESSING;
  } else {
    mEvent = EV_BOTON_RELEASING;
  }

  _statechart();
}

bool TaskBoton::estaPresionado(void) {
  return mState == ST_BOTON_PRESSED;
}


void TaskBoton::_statechart(void) {
  switch (mState) {
  case ST_BOTON_RELEASED:
    if (mEvent == EV_BOTON_PRESSING) {
      mState = ST_BOTON_PRESSING;
      mTickCnt = mTickMax;
    }
    break;

  case ST_BOTON_PRESSING:
    if (mTickCnt > 0) {
      mTickCnt--;
    } else { // después del debouncing cambio a pressed o released
      mState = (mEvent == EV_BOTON_PRESSING) ? ST_BOTON_PRESSED : ST_BOTON_RELEASED;
    }
    break;

  case ST_BOTON_PRESSED:
    if (mEvent == EV_BOTON_RELEASING) {
      mState = ST_BOTON_RELEASING;
      mTickCnt = mTickMax;
    }
    break;

  case ST_BOTON_RELEASING:
    if (mTickCnt > 0) {
      mTickCnt--;
    } else {
      mState = (mEvent == EV_BOTON_RELEASING) ? ST_BOTON_RELEASED : ST_BOTON_PRESSED;
    }
    break;

  default:
    mState = ST_BOTON_RELEASED;
    break;
  }

  mEvent = EV_BOTON_IDLE;
}
