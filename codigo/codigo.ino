#include "ClockMs.h"
#include "Executor.h"

#include "TaskLED.h"
#include "TaskBoton.h"
#include "TaskController.h"

ClockMs clock; // counts ms between calls
Executor executor;

// Defino mis tareas
TaskLED led_arranque(LED_BUILTIN); // PB5
TaskBoton boton_largada(9); // PB1

controller_contexto contexto = {
  .led_arranque = &led_arranque,
  .boton_largada = &boton_largada,
};
TaskController controlador(&contexto);

void setup() {
  // Agrego las tarreas al ejecutor
  executor.addTask(&led_arranque);
  executor.addTask(&controlador);

  Serial.begin(9600);

  clock.init();
  executor.init();
}

void loop() {
  unsigned long ticks = clock.pending_ticks();
  executor.increaseTicks(ticks);

  executor.update();
}
