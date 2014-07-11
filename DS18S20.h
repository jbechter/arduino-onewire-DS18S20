/*
 *   DS18S20.h
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

#ifndef DS18S20_h
#define DS18S20_h

#include <Arduino.h>
#include <OneWire.h>

#define DS18S20_TEMPERATURE_CONVERSION_COMMAND 0x44
#define DS18S20_READ_SCRATCHPAD_COMMAND 0xbe
#define DS18S20_TEMPERATURE_CONVERSION_DELAY 750


class DS18S20 {
    public:
        DS18S20(OneWire *ow, uint8_t *address);
        void begin();
        void update();
        double getTemperature();
        unsigned long getTimestamp();
        boolean isError();
    private:
        OneWire *_ow;
        uint8_t *_address;
        double _temperature;
        unsigned long _timestamp;
        boolean _error;
};

#endif
