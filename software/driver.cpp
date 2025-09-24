#include "driver.h"

Driver::Driver() {
    hatsContainer = new HatsContainer(
                        dataSelect,
                        dataPWM,
                        dataSerial
                    );

}

Driver::~Driver() {
    delete hatsContainer;
}


void Driver::main() {
    switch(hatsContainer->getSelectedHat()) {
        case DUMMY:
            break;
        case SIMPLE_ROCKET:
            break;
        case TELEMETRY:
            break;
        case ACTIVE_AERO:
            break;
        case LOW_RADIO:
            break;
        case HIGH_RADIO:
            break;
        default:
            break;
    }
}
