// LED.h

#ifndef LED__H_
#define LED__H_

#include <Arduino.h>

class LED {
  public:
    LED(int pin);
    void turnOn();
    void turnOff();
    int getState();
    
  private:
    int mPin;
    unsigned char mState;
    void _writePin(void);
};


#endif
