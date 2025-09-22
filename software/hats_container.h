#ifndef HATS_CONTAINER_H
#define HATS_CONTAINER_H

#include "hats/hatABC.h"


enum HatTypes {
  DUMMY = 0b00001,
  SIMPLE_ROCKET = 0b00010,
  TELEMETRY = 0b00011,
  ACTIVE_AERO = 0b00100,
  LOW_RADIO = 0b00101,
  HIGH_RADIO = 0b00110
};


class HatsContainer {
private:

    // 5 pins that are used for data select
    uint8_t selectPins[5];

    // pointer to the first hat in the linked list
    HatABC* hatArray = nullptr;


public:

    HatsContainer(uint8_t selectPins[5]);

    void addHat(HatABC* hat);
    HatABC* getHat(HatTypes hatType);

    // these will select the given hat
    void select(uint8_t byte);
    void select(HatTypes hatType);

    // sends data to all 16 data pins, LSB is PWM, MSB is Serial
    void sendData(uint16_t data);
    
    // sends 8 bits of data to pwm compatible pins
    void sendPWM(uint8_t data);

    // sends 8 bits of data to the serial compatible pins
    void sendSerial(uint8_t data);
    

};

#endif
