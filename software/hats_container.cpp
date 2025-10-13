#include "hats_container.h"
#include "hats/hatABC.h"

HatsContainer::HatsContainer(
        uint8_t* selectPins,
        uint8_t* pwmPins,
        uint8_t* serialPins,
        uint8_t selectReturn): selectReturn(selectReturn) {
    // this is intentional 
    // we want to read and edit the actual pins that are passed in
    this->selectPins = selectPins;
    this->pwmPins = pwmPins;
    this->serialPins = serialPins;
}

void HatsContainer::addHat(HatABC* hat) {
    HatABC* tmp = headHat;
    while (tmp->nextHat != nullptr) {
        tmp = tmp->nextHat;
    }
    tmp->nextHat = hat;
}

HatABC* HatsContainer::getHat(HatTypes hatType) {
    HatABC* tmp = headHat;
    while (tmp->nextHat != nullptr) {
        if (tmp->hatID == hatType) {
            return tmp;
        }
        tmp = tmp->nextHat;
    }
    return nullptr;
}

int HatsContainer::scanConnectedHats() {
    for (uint8_t hat = DUMMY; hat < UNIQUE_HAT_COUNT; hat++) {
        select(hat);
        delay(10);
        if (digitalRead(selectReturn)) {
            switch(hat) {
            case DUMMY:
                // idk if this works the way I think it does
                addHat((HatABC*) new DummyHat());
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
            }
        }
    }
}

bool HatsContainer::select(HatTypes hatType) {
    // sets the select pins to the hat type
    bool* pinout = destructData(selectPins, hatType,5);
   
    for (int i = 0; i < 5; i++) {
        digitalWrite(selectPins[i], pinout[4-i] ? HIGH : LOW);
    }

    // this check is kinda cumbersome but it'll be nice to know
    if (getHat(hatType) != nullptr) {
        selectedHat = hatType;
        return true;
    }
    return false;
}




// this works cause its a pointer
void HatsContainer::sendData(uint8_t data, bool* pins) {
    bool bits[8];
    destructData(bits, data);
    for (int i = 0; i < 8; i++) {
        pins[i] = bits[i];
    }
}

void HatsContainer::sendPWM(uint8_t data) {
    sendData(data, pwmPins);
}

void HatsContainer::sendSerial(uint8_t data) {
    sendData(data, selectPins);
}

HatTypes HatsContainer::getSelectedHat() {return selectedHat;}
