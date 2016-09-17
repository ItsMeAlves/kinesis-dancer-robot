/*
 * Kinesis Dancer Robot
 * Main code to receive differentials and integrate movement
 */

//Include files
#include <DynamixelSerial1.h>
#include "../Joint/Joint.cpp"
#include "../BodyRelation/BodyRelation.cpp"

//Define standard serial interface
#define SERIAL Serial
#define SERIAL_RATE 57600
#define SERIAL_EVENT serialEvent

//Define array sizes
#define NUM_TRACKED_JOINTS 4
#define NUM_RELATIONS 4

//Define Dynamixel data
#define DYNAMIXEL_RATE 1000000 
#define DYNAMIXEL_CONTROL 9
#define MOVEMENT_MULTIPLIER 100
#define RIGHT RIGTH  //Fix library typo

//Define String usage constants
#define SERIAL_TIMEOUT 3
#define FIELD_SEP ','
#define LINE_SEP ';'

//Define general pins
#define LED 13

//Create body control arrays
Joint* differentials[NUM_TRACKED_JOINTS];
BodyRelation* bodyRelations[NUM_RELATIONS];

// Set global variables
bool readyToMove = false;

void setup() {
    //Start communication with SERIAL module
    SERIAL.begin(SERIAL_RATE);
    SERIAL.setTimeout(SERIAL_TIMEOUT);
    Serial.begin(9600);
    pinMode(LED, OUTPUT);
    pinMode(12, OUTPUT);

    //Start Dynamixel control usage
    Dynamixel.begin(DYNAMIXEL_RATE, DYNAMIXEL_CONTROL);

    //Initialize differentials array
    for(int i = 0; i < NUM_TRACKED_JOINTS; i++) {
        differentials[i] = NULL;
    }
    
    //Sample body relations added for testing purposes
    provideBodyRelationsTo(bodyRelations);

    for(int i = 0; i < NUM_RELATIONS; i++) {
        int id = bodyRelations[i]->motor();
        Dynamixel.setEndless(id, OFF);
        Dynamixel.ledStatus(id, ON);
    }
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
void SERIAL_EVENT() {
    digitalWrite(LED, HIGH);

    // So it reads all data available and signs movement readiness
    while(SERIAL.available() > 0) {
        //Receive differentials data from Serial interface
        receiveData(SERIAL.readString(), differentials);
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
            analogWrite(12, 100);   // LED used during testing 
            BodyRelation* relation = bodyRelations[i];
            
            int id = relation->motor();
            int direction = relation->direction();
            
            float x = differentials[i]->x() * relation->xMultiplier();
            float y = differentials[i]->y() * relation->yMultiplier();
            float z = differentials[i]->z() * relation->zMultiplier();
            
            //Sample speed calculation, for testing purposes
            int speed = MOVEMENT_MULTIPLIER * (x + y + z);  

            if(speed < 0) {
                if(direction == LEFT)
                    direction = RIGHT;
                else
                    direction = LEFT;
            }

            Dynamixel.turn(id, direction, speed);
            digitalWrite(12, LOW);
        }
    }
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