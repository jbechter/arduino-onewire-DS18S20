/*
 *   DS18S20Temperature
 *
 *   This example demonstrates the use of the DS18S20 library and the  using the Arduino
 *   OneWire library to read temperature values from a Dallas Semiconductor DS18S20.
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

#include <Arduino.h>
#include <OneWire.h>
#include <DS18S20.h>

// define the Arduino digital I/O pin to be used for the 1-Wire network here
const uint8_t ONE_WIRE_PIN = 2;

// define the 1-Wire address of the DS18S20 temperature sensor here
uint8_t DS18S20_address[] = { 0x10, 0xc9, 0x5d, 0xe1, 0x01, 0x08, 0x00, 0x90 };

OneWire ow(ONE_WIRE_PIN);
DS18S20 ds18S20(&ow, DS18S20_address);

void setup() {
    Serial.begin(9600);
    ds18S20.begin();
}

void loop() {
    ds18S20.update();
    if (ds18S20.isError()) {
        Serial.println("Error reading temperature");
    } else {
        Serial.print("Temperature = ");
        Serial.print(ds18S20.getTemperature(), 1);
        Serial.print("C (");
        Serial.print(ds18S20.getTemperature() * 9.0 / 5.0 + 32.0, 1);
        Serial.println("F)");
    }
    delay(500);
}
