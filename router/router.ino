/*
 * Kinesis Router
 * It gets data from USB and TX it via XBEE module
 */

//Import Libraries
#include <SoftwareSerial.h>

//Define useful constants
#define XBEE_RX 6               // xbee RX pin, which means its DOUT pin
#define XBEE_TX 7               // xbee TX pin, which means its DIN pin
#define KINESIS_BAUDRATE 9600   // Baudrate to bind to USB communication
#define XBEE_BAUDRATE 9600      // Baudrate to bind to XBEE messages
#define SERIAL_TIMEOUT 4        // Timeout for reading strings cycle

// Creates a serial interface communication to XBEE module
SoftwareSerial xbee(XBEE_RX, XBEE_TX);

// Time to set all communication definitions
void setup() {
    Serial.begin(KINESIS_BAUDRATE);
    Serial.setTimeout(SERIAL_TIMEOUT);
    xbee.begin(XBEE_BAUDRATE);
}

// Main loop, where it executes the router feature
void loop() {
    // Whenever the board receives data from USB
    // it stores data available and send it through XBEE
    
    while(Serial.available() > 0) {
        String source = Serial.readString();
        xbee.println(source);
    }
    // That's all, folks!
}