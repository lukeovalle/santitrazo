#include "ClockMs.h"
#include "Executor.h"
#include "LED.h"

ClockMs clock; // counts ms between calls
Executor executor;

LED led(LED_BUILTIN); // Led de la placa

void setup() {
  Serial.begin(9600);

  clock.init();
  executor.init();
}

void loop() {
  unsigned long ticks = clock.pending_ticks();
  executor.increaseTicks(ticks);

  executor.update();

  led.turnOn();
  Serial.print("Led state: ");
  Serial.println(led.getState());

  delay(2000);

  led.turnOff();
  Serial.print("Led state: ");
  Serial.println(led.getState());

  delay(2000);
}
