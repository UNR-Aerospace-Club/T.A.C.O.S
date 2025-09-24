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

    // 5 pins are used for data select
    bool* selectPins;
    // 8 pwm pins
    bool* pwmPins;
    // 8 serial pins
    bool* serialPins;

    // pointer to the first hat in the linked list
    HatABC* headHat = nullptr;

    HatTypes selectedHat;

    // returns an array of booleans that represent individual bits
    bool* destructData(bool* bits, uint8_t num,int numIndices=8);

    // make my life easer so I dont have to wrire send function twice
    void sendData(uint8_t data);

public:

    HatsContainer(
        bool* selectPins,
        bool* pwmPins,
        bool* serialPins);

    void addHat(HatABC* hat);
    HatABC* getHat(HatTypes hatType);

    // these will select the given hat
    bool select(HatTypes hatType);

    // sends 8 bits of data to pwm compatible pins
    void sendPWM(uint8_t data);

    // sends 8 bits of data to the serial compatible pins
    void sendSerial(uint8_t data);

    HatTypes getSelectedHat();
    

};

#endif
