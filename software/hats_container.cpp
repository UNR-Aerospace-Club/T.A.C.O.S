#include "hats_container.h"
#include "hats/hatABC.h"


HatsContainer::HatsContainer(uint8_t selectPins[5]) {
    for (int i = 0; i < 5; i++) {
        this->selectPins[i] = selectPins[i];
    }
}

void HatsContainer::addHat(HatABC* hat) {
    HatABC* tmp = hatArray;
    while (tmp->nextHat != nullptr) {
        tmp = tmp->nextHat;
    }
    tmp->nextHat = hat;
}

HatABC* HatsContainer::getHat(HatTypes hatType) {
    HatABC* tmp = hatArray;
    while (tmp->nextHat != nullptr) {
        if (tmp->hatID == hatType) {
            return tmp;
        }
    }
    return nullptr;
}


// the duplicate implimentation is kinda annoying but idk how else to do this
void HatsContainer::select(HatTypes hatType) {
    uint8_t tmp = hatType;
    for (int i = 0; i < 5; i++) {
        selectPins[i] = tmp % 2;
        tmp /= 2;
    }
}

void HatsContainer::select(uint8_t byte) {
    uint8_t tmp = byte;
    for (int i = 0; i < 5; i++) {
        selectPins[i] = tmp % 2;
        tmp /= 2;
    }
}


