#ifndef DUMMYHAT_H
#define DUMMYHAT_H

#include "hatABC.h"

class DummyHat: protected HatABC {
private:

    // the 5 bit sequence for this unique hat - #1
    const static uint8_t hatID = 0b00000001;

public:

    

};


#endif
