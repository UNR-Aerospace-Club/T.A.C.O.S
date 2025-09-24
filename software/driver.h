#ifndef DRIVER_H
#define DRIVER_H

#include "hats/hatABC.h"
#include "hats/dummyhat.h"

#include "hats_container.h"

class Driver {
private:    
    bool dataSelect[5];
    bool dataPWM[8];
    bool dataSerial[8];

    HatsContainer* hatsContainer;

public:
    Driver();
    ~Driver();

    void main();

};

#endif
