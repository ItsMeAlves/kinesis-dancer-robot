/*
 * Kinesis Dancer Robot
 * Main code to receive differentials and integrate movement
 */

//Include files
#include <DynamixelSerial1.h>
#include "../Joint/Joint.cpp"
#include "../BodyRelation/BodyRelation.cpp"

//Define XBEE serial interface
#define XBEE Serial3
#define XBEE_RATE 57600

//Define array sizes
#define NUM_TRACKED_JOINTS 4
#define NUM_RELATIONS 4

//Define Dynamixel data
#define DYNAMIXEL_RATE 1000000 
#define DYNAMIXEL_CONTROL 9

//Define String usage constants
#define SERIAL_TIMEOUT 3
#define FIELD_SEP ','
#define LINE_SEP ';'

//Define general pins
#define LED 13

//Create body control arrays
Joint* differentials[NUM_TRACKED_JOINTS];
BodyRelation* bodyRelations[NUM_RELATIONS];
bool readyToMove = false;

void setup() {
    //Start communication with XBEE module
    XBEE.begin(XBEE_RATE);
    XBEE.setTimeout(SERIAL_TIMEOUT);
    pinMode(LED, OUTPUT);
    pinMode(12, OUTPUT);

    //Start Dynamixel control usage
    Dynamixel.begin(DYNAMIXEL_RATE, DYNAMIXEL_CONTROL);

    //Initialize differentials array
    for(int i = 0; i < NUM_TRACKED_JOINTS; i++) {
        differentials[i] = NULL;
    }
    //Initialize bodyRelations array
    for(int i = 0; i < NUM_RELATIONS; i++) {
        bodyRelations[i] = NULL;
    }

    //Sample body relations added for testing purposes
    float mapper[3] = {0,5,0};
    float mapper2[3] = {0,2,0};
    bodyRelations[0] = new BodyRelation("ElbowRight", 10, 1, mapper);
    bodyRelations[1] = new BodyRelation("WristRight", 13, 1, mapper2);
}

//Main loop
void loop() {
    digitalWrite(LED, LOW);
    //Whenever it has data available, it executes some tasks    
    if(readyToMove) {
        //Move robot and then clean data
        move();
        cleanDifferentials();
        // Then, wait more data to move again
        readyToMove = false;
    }
}

// Whenever data comes into Serial3 interface, it gets fired
void serialEvent3() {
    digitalWrite(LED, HIGH);

    // So it reads all data available and signs movement readiness
    while(XBEE.available() > 0) {
        //Receive differentials data from Serial interface
        receiveData(XBEE.readString(), differentials);
        readyToMove = true;
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
void move() {
    for(int i = 0; i < NUM_RELATIONS; i++) {
        if(bodyRelations[i] == NULL)
            continue;

        int index = searchInDifferentials(bodyRelations[i]->jointType());
        
        if(index != -1) {
            analogWrite(12, 100);
            int id = bodyRelations[i]->motor();
            //Sample position calculation, for testing purposes
            int position = 512 + (400 * differentials[i]->y());  
            Dynamixel.move(id, position);
        }
    }
    digitalWrite(12, LOW);
}

//Function to clean unused joints
void cleanDifferentials() {
    for(int i = 0; i < NUM_TRACKED_JOINTS; i++) {
        if(differentials[i] == NULL)
            continue;

        delete differentials[i];
        differentials[i] = NULL;
    }
}

//Search a joint in differentials array by its type
int searchInDifferentials(String jointType) {
    int index = -1;

    for(int i = 0; i < NUM_TRACKED_JOINTS; i++) {
        if(differentials[i] == NULL)
            continue;

        if(jointType.equals(differentials[i]->getType())) {
            index = i;
            break;
        }
    }

    return index;
}