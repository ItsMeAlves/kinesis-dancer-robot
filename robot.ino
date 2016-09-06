/*
 * Kinesis Dancer Robot
 * Main code to receive differentials and integrate movement
 */

#include <DynamixelSerial.h>
#include "Joint/Joint.cpp"
#include "BodyRelation/BodyRelation.cpp"

#define DYNAMIXEL_RATE 1000000
#define NUM_TRACKED_JOINTS 4
#define DYNAMIXEL_CONTROL 9
#define SERIAL_TIMEOUT 5
#define NUM_RELATIONS 4
#define FIELD_SEP ','
#define LINE_SEP ';'
#define LED 13;

Joint* differentials[NUM_TRACKED_JOINTS];
BodyRelation* bodyRelations[NUM_RELATIONS];

void receiveData(String src, Joint** dest);
void move(Joint** diffs, BodyRelation** body);
void cleanDifferentials();

void setup() {
    Serial.begin(9600);
    Serial.setTimeout(SERIAL_TIMEOUT);
    pinMode(LED, OUTPUT);

    Dynamixel.begin(DYNAMIXEL_RATE, DYNAMIXEL_CONTROL);

    for(int i = 0; i < NUM_TRACKED_JOINTS; i++) {
        differentials[i] = NULL;
    }
}

void loop() {
    digitalWrite(LED, LOW);

    while(Serial.available() > 0) {
        digitalWrite(LED, HIGH);
        receiveData(Serial.readString(), differentials);
        move(differentials, bodyRelations);
        cleanDifferentials();
    }
}

void receiveData(String src, Joint** dest) {
    int i = 0;
    int begin = 0;
    int end = src.indexOf(LINE_SEP);

    while(end != -1) {
        dest[i] = Joint::fromString(
            src.substring(begin, end), 
            FIELD_SEP);

        i += 1;
        begin = end + 1;
        end = src.indexOf(LINE_SEP, begin);
    }
}

void move(Joint** diffs, BodyRelation** body) {
    for(int i = 0; i < NUM_RELATIONS; i++) {
        Joint* j = searchInDifferentials(body[i].getJointType());
        if(j != NULL) {
            int pin = body[i];
            int position = 0; // TODO: make calculations
            int speed = 0; // TODO: make calculations
            Dynamixel.moveSpeed(pin, position, speed);
        }
    }
}

void cleanDifferentials() {
    for(int i = 0; i < NUM_TRACKED_JOINTS; i++) {
        delete differentials[i];
        differentials[i] = NULL;
    }
}

Joint* searchInDifferentials(String jointType) {
    Joint* j = NULL;

    for(int i = 0; i < NUM_TRACKED_JOINTS; i++) {
        if(jointType.equals(differentials[i].getType())) {
            j = differentials[i];
            break;
        }
    }

    return j;
}