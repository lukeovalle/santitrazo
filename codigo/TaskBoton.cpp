// TaskBoton.cpp

#include "TaskBoton.h"

void TaskBoton::init(void) {
  mState = ST_BOTON_RELEASED;
  mEvent = EV_BOTON_IDLE;
}

void TaskBoton::update(void) {
  _statechart();
}


void TaskBoton::_statechart(void) {
  switch (mState) {
  case ST_BOTON_RELEASED:
    break;

  default:
    break;
  }
}
