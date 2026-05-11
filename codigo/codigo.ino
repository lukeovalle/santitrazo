#include "ClockMs.h"
#include "Executor.h"
#include "TaskLED.h"

ClockMs clock; // counts ms between calls
Executor executor;

// Defino mis tareas
TaskLED led_arranque(LED_BUILTIN);

void setup() {
  // Agrego las tarreas al ejecutor
  executor.addTask(&led_arranque);

  Serial.begin(9600);

  clock.init();
  executor.init();
}

void loop() {
  unsigned long ticks = clock.pending_ticks();
  executor.increaseTicks(ticks);

  executor.update();
}
