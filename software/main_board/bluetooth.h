#ifndef BLUETOOTH_H
#define BLUETOOTH_H


#include "BluetoothSerial.h"

class BlueTooth {
private:
    
    BluetoothSerial SerialBT;

    char deviceName[];

public:

    BlueTooth();


};


#endif
