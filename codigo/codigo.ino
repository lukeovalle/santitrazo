#include "LED.h"

LED led(LED_BUILTIN); // Led de la placa

void setup() {
  Serial.begin(9600);

}

void loop() {
  led.turnOn();
  Serial.print("Led state: ");
  Serial.println(led.getState());

  delay(2000);

  led.turnOff();
  Serial.print("Led state: ");
  Serial.println(led.getState());

  delay(2000);
}
