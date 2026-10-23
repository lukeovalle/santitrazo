#include "ClockMs.h"
#include "Executor.h"

#include "TaskLED.h"
#include "TaskBoton.h"
#include "TaskSensor.h"
#include "TaskMotor.h"
#include "TaskController.h"

#include "config.h"

ClockMs reloj; // contar ms entre llamados
Executor executor;

// Defino mis tareas
TaskLED led_arranque(10); // PB2
TaskBoton boton_largada(9); // PB1
TaskSensor sensor1(17); // PC3
TaskSensor sensor2(16); // PC2
TaskSensor sensor3(15); // PC1
TaskSensor sensor4(14); // PC0
// Motores: TaskMotor(pin PWM adelante, pin PWM atrás). ENA y ENB van siempre en
// alto (jumper puesto). Los cuatro pines tienen que tener PWM.
// Pines de la placa actual: los que ya tenían PWM (PD5 y PD6, pines 11 y 12 del
// DIP-28) quedan como "adelante"; los IN que antes iban a tierra pasan a PD3
// (pin 5) y PB3 (pin 17, compartido con MOSI del ICSP) como "atrás".
TaskMotor motor_izq(5, 3);  // adelante PD5 (pin 11), atrás PD3 (pin 5)
TaskMotor motor_der(6, 11); // adelante PD6 (pin 12), atrás PB3 (pin 17)


controller_contexto contexto = {
  .led_arranque = &led_arranque,
  .boton_largada = &boton_largada,
  .sensores = {&sensor1, &sensor2, &sensor3, &sensor4},
  .motor_izq = &motor_izq,
  .motor_der = &motor_der
};
TaskController controlador(&contexto, CONTROL_PERIODO_MS); // corre cada 10ms

void setup() {
  // Agrego las tareas al ejecutor
  executor.addTask(&led_arranque);
  executor.addTask(&boton_largada);
  executor.addTask(&sensor1);
  executor.addTask(&sensor2);
  executor.addTask(&sensor3);
  executor.addTask(&sensor4);
  executor.addTask(&motor_izq);
  executor.addTask(&motor_der);

  executor.addTask(&controlador);

  reloj.init();
  executor.init();
}

void loop() {
  unsigned long ticks = reloj.pending_ticks();
  executor.increaseTicks(ticks);

  executor.update();
}
