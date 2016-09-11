/*
 * Kinesis Router
 * It gets data from USB and TX it via XBEE module
 */

//Import Libraries
#include <SoftwareSerial.h>

//Define useful constants
#define XBEE_RX 6               // xbee RX pin, which means its DOUT pin
#define XBEE_TX 7               // xbee TX pin, which means its DIN pin
#define KINESIS_BAUDRATE 57600   // Baudrate to bind to USB communication
#define XBEE_BAUDRATE 57600      // Baudrate to bind to XBEE messages
#define SERIAL_TIMEOUT 3        // Timeout for reading strings cycle

// Creates a serial interface communication to XBEE module
bool dataReady = false;
String source;
SoftwareSerial xbee(XBEE_RX, XBEE_TX);

// Time to set all communication definitions
void setup() {
    Serial.begin(KINESIS_BAUDRATE);
    Serial.setTimeout(SERIAL_TIMEOUT);
    xbee.begin(XBEE_BAUDRATE);
}

// Main loop, where it executes the router feature
void loop() {
    // Whenever data is ready to be used, it is sent through XBEE module
    if(dataReady) {
        xbee.print(source);
        dataReady = false;

        //Telling Kinesis that's okay to receive data again!
        Serial.println("OK");
    }
    // That's all, folks!
}

// Any data received is stored into source variable
// It also signs that data storage is ready to use
void serialEvent() {
    while(Serial.available() > 0) {
        source = Serial.readString();
        dataReady = true;
    }
}