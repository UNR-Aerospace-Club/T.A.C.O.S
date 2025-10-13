#ifndef HAT_ABC_H
#define HAT_ABC_H

#include "Arduino.h"
#include "../hats_container.h"

class HatABC {
protected:

    // the 8 pwm compatible data pins
    uint8_t dataPWM[8];
    // the 8 serial communication data pins
    uint8_t dataSerial[8];

    

public:

    // the 5 bit sequence for this unique hat - last 3 bits are always 0
    const HatTypes hatID;

    HatABC* nextHat;

    HatABC();


};

#endif
