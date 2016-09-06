/*
 * Kinesis Router
 * It gets data from USB and TX it via XBEE module
 */

#include <SoftwareSerial.h>

#define XBEE_RX 6
#define XBEE_TX 7
#define KINESIS_BAUDRATE 9600
#define XBEE_BAUDRATE 9600
#define SERIAL_TIMEOUT 4

SoftwareSerial xbee(XBEE_RX, XBEE_TX);

void setup() {
    Serial.begin(KINESIS_BAUDRATE);
    Serial.setTimeout(SERIAL_TIMEOUT);
    xbee.begin(XBEE_BAUDRATE);
}

void loop() {
    while(Serial.available() > 0) {
        String source = Serial.readString();
        xbee.write(source);
    }
}