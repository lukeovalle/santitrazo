// TaskController.cpp

#include "TaskController.h"
#include "TaskLED.h"
#include "TaskBoton.h"

void TaskController::init(void) {
  mState = ST_CONTROLLER_INIT;
  mEvent = EV_CONTROLLER_IDLE;
}

void TaskController::update(void) {
  if (mTareas->boton_largada->estaPresionado()) {
    mTareas->led_arranque->encender();
  } else {
    mTareas->led_arranque->apagar();
  }

  _statechart();
}


void TaskController::_statechart(void) {
  switch (mState) {
  case ST_CONTROLLER_INIT:
    break;

  default:
    mState = ST_CONTROLLER_INIT;
    break;
  }
}
