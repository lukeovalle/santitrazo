// LED.h

#ifndef LED__H_
#define LED__H_

#include <Arduino.h>

class LED {
  public:
    LED(int pin);
    void turnOn(void);
    void turnOff(void);
    int getState(void);
    
  private:
    int mPin;
    unsigned char mState;
    void _writePin(void);
};


#endif
