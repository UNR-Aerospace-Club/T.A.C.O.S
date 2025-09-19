#ifndef HAT_ABC_H
#define HAT_ABC_H

#include "Arduino.h"

class HatABC {
private:

    // the 5 bit sequence for this unique hat - last 3 bits are always 0
    const static uint8_t hatID;

    // the 8 pwm compatible data pins
    uint8_t dataPWM[8];
    // the 8 serial communication data pins
    uint8_t dataSerial[8];

public:

};

#endif
