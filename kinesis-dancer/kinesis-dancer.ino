/*
 * Kinesis Dancer Robot
 * Main code to receive differentials and integrate movement
 */

//Include files
#include <DynamixelSerial.h>
#include "../Joint/Joint.cpp"
#include "../BodyRelation/BodyRelation.cpp"

//Define XBEE serial interface
#define XBEE Serial

//Define array sizes
#define NUM_TRACKED_JOINTS 4
#define NUM_RELATIONS 4

//Define Dynamixel data
#define DYNAMIXEL_RATE 1000000
#define DYNAMIXEL_CONTROL 9

//Define String usage constants
#define SERIAL_TIMEOUT 4
#define FIELD_SEP ','
#define LINE_SEP ';'

//Define general pins
#define LED 13

//Create body control arrays
Joint* differentials[NUM_TRACKED_JOINTS];
BodyRelation* bodyRelations[NUM_RELATIONS];

void setup() {
    //Start communication with XBEE module
    XBEE.begin(9600);
    XBEE.setTimeout(SERIAL_TIMEOUT);
    pinMode(LED, OUTPUT);

    //Start Dynamixel control usage
    Dynamixel.begin(DYNAMIXEL_RATE, DYNAMIXEL_CONTROL);

    //Initialize differentials array
    for(int i = 0; i < NUM_TRACKED_JOINTS; i++) {
        differentials[i] = NULL;
    }
}

//Main loop
void loop() {
    digitalWrite(LED, LOW);

    //Whenever it has data available, it executes some tasks
    while(XBEE.available() > 0) {
        digitalWrite(LED, HIGH);

        //Receive differentials data from Serial interface
        receiveData(XBEE.readString(), differentials);

        //Move robot and then clean data
        move(differentials, bodyRelations);
        cleanDifferentials();
    }
}

//Function to jointify data received and store it into dest
void receiveData(String src, Joint** dest) {
    int i = 0;
    int begin = 0;
    int end = src.indexOf(LINE_SEP);

    //When there is data, we read it!
    while(end != -1) {
        dest[i] = Joint::fromString(
            src.substring(begin, end), 
            FIELD_SEP);

        i += 1;
        begin = end + 1;
        end = src.indexOf(LINE_SEP, begin);
    }
}

//Function to move using body relations data
void move(Joint** diffs, BodyRelation** body) {
    for(int i = 0; i < NUM_RELATIONS; i++) {
        Joint* j = searchInDifferentials(body[i]->getJointType());
        if(j != NULL) {
            int pin = body[i]->motor();
            int position = 0; // TODO: make calculations
            int speed = 0; // TODO: make calculations
            Dynamixel.moveSpeed(pin, position, speed);
        }
    }
}

//Function to clean unused joints
void cleanDifferentials() {
    for(int i = 0; i < NUM_TRACKED_JOINTS; i++) {
        delete differentials[i];
        differentials[i] = NULL;
    }
}

//Search a joint in differentials array by its type
Joint* searchInDifferentials(String jointType) {
    Joint* j = NULL;

    for(int i = 0; i < NUM_TRACKED_JOINTS; i++) {
        if(jointType.equals(differentials[i]->getType())) {
            j = differentials[i];
            break;
        }
    }

    return j;
}