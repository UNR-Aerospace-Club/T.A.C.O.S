#ifndef HATS_CONTAINER_H
#define HATS_CONTAINER_H

#include "hats/hatABC.h"
#include "hats/dummyhat.h"

#define UNIQUE_HAT_COUNT 6


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
    uint8_t* selectPins;
    // 1 pin used for data return
    uint8_t selectReturn;
    // 16 data pins
    uint8_t* pwmPins;

    // pointer to the first hat in the linked list
    HatABC* headHat = nullptr;

    HatTypes selectedHat;

    bool* destructData(uint8_t num, int numIndicies=5);

    // make my life easer so I dont have to wrire send function twice
    void sendData(uint8_t data);

public:

    HatsContainer(
        uint8_t* selectPins,
        uint8_t* pwmPins,
        uint8_t* serialPins,
        uint8_t selectReturn);

    void addHat(HatABC* hat);
    HatABC* getHat(HatTypes hatType);

    // detect and automatically add connected hats
    int scanConnectedHats();

    // these will select the given hat
    bool select(HatTypes hatType);

    // sends 16 bits of data to the data pins
    void sendData(uint16_t data);

    void sendBit(uint8_t pin, bool data);

    HatTypes getSelectedHat();

    

};

#endif
