#include "hats_container.h"
#include "hats/hatABC.h"

HatsContainer::HatsContainer(
        bool* selectPins,
        bool* pwmPins,
        bool* serialPins) {
    // this is intentional 
    // we want to read and edit the actual pins that are passed in
    this->selectPins = selectPins;
    this->pwmPins = pwmPins;
    this->serialPins = serialPins;
}

bool* HatsContainer::destructData(bool* bits, uint8_t num, int numIndices) {
    uint8_t tmp = num;
    // this is kinda dank but it works
    // its because the /2 method gives us bits from LSB to MSB
    for (int i = 8 - 1; i >=0; i++) {
        bits[i <= numIndices ? i : 0] = tmp % 2;
        tmp /= 2;
    }
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


bool HatsContainer::select(HatTypes hatType) {
    // sets the select pins to the hat type
    destructData(selectPins, hatType,5);
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
