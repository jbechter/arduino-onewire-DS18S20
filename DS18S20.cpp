/*
 *   DS18S20.cpp
 *
 *   by Joe Bechter
 *
 *   (C) 2012, bechter.com
 *
 *   All files, software, schematics and designs are provided as-is with no warranty.
 *   All files, software, schematics and designs are for experimental/hobby use.
 *   Under no circumstances should any part be used for critical systems where safety,
 *   life or property depends upon it. You are responsible for all use.
 *   You are free to use, modify, derive or otherwise extend for your own non-commercial purposes provided
 *       1. No part of this software or design may be used to cause injury or death to humans or animals.
 *       2. Use is non-commercial.
 *       3. Credit is given to the author (i.e. portions © bechter.com), and provide a link to the original source.
 *
 */

#include "DS18S20.h"


DS18S20::DS18S20(OneWire *ow, uint8_t *address) {
    _ow = ow;
    _address = address;
}

void DS18S20::begin() {
    _temperature = 0.0;
    _error = true;
    _timestamp = 0;
}

void DS18S20::update() {
    uint8_t data[9];

    _timestamp = millis();
    _ow->reset();
    _ow->select(_address);
    _ow->write(DS18S20_TEMPERATURE_CONVERSION_COMMAND, 0);
    delay(DS18S20_TEMPERATURE_CONVERSION_DELAY);
    _ow->reset();
    _ow->select(_address);
    _ow->write(DS18S20_READ_SCRATCHPAD_COMMAND, 0);
    for (int i = 0; i < 9; i++) {
        data[i] = _ow->read();
    }
    uint8_t lsb = data[0];
    uint8_t msb = data[1];
    int16_t temp = (msb << 8) + lsb;
    uint8_t sign = temp & 0x8000;
    if (sign) {
        temp = (temp ^ 0xffff) + 1;
    }
    _temperature = (double)temp / 2.0 + 0.05;
    if (sign) {
       _temperature = 0.0 - _temperature;
    }
    _error = data[8] != _ow->crc8(data, 8);
}

double DS18S20::getTemperature() {
    return _temperature;
}

boolean DS18S20::isError() {
    return _error;
}

unsigned long DS18S20::getTimestamp() {
    return _timestamp;
}
