#include "ClockMs.h"
#include "Executor.h"

#include "TaskLED.h"
#include "TaskBoton.h"
#include "TaskSensor.h"
#include "TaskMotor.h"
#include "TaskController.h"

ClockMs clock; // counts ms between calls
Executor executor;

// Defino mis tareas
TaskLED led_arranque(10); // PB2
TaskBoton boton_largada(9); // PB1
TaskSensor sensor1(17); // PC3
TaskSensor sensor2(16); // PC2
TaskSensor sensor3(15); // PC1
TaskSensor sensor4(14); // PC0
TaskMotor motor_izq(5); // PD5
TaskMotor motor_der(6); // PD6


controller_contexto contexto = {
  .led_arranque = &led_arranque,
  .boton_largada = &boton_largada,
  .sensores = {&sensor1, &sensor2, &sensor3, &sensor4},
  .motor_izq = &motor_izq,
  .motor_der = &motor_der
};
TaskController controlador(&contexto, 10); // corre cada 10ms

void setup() {
  // Agrego las tarreas al ejecutor
  executor.addTask(&led_arranque);
  executor.addTask(&boton_largada);
  executor.addTask(&sensor1);
  executor.addTask(&sensor2);
  executor.addTask(&sensor3);
  executor.addTask(&sensor4);
  executor.addTask(&motor_izq);
  executor.addTask(&motor_der);

  executor.addTask(&controlador);

  Serial.begin(115200);

  clock.init();
  executor.init();
}

void loop() {
  unsigned long ticks = clock.pending_ticks();
  executor.increaseTicks(ticks);

  executor.update();
}
