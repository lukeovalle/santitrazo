// TaskController.cpp

#include "TaskController.h"

void TaskController::init(void) {
  mState = ST_CONTROLLER_INIT;
  mEvent = EV_CONTROLLER_IDLE;
}

void TaskController::update(void) {
  _statechart();
}


void TaskController::_statechart(void) {
  switch (mState) {
  case ST_CONTROLLER_INIT:
    break;

  default:
    break;
  }
}
