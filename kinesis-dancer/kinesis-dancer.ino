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
#define SERIAL_RATE 115200
#define SERIAL_EVENT serialEvent

//Define array sizes
#define NUM_TRACKED_JOINTS 6
#define NUM_RELATIONS 7

//Define Dynamixel data
#define DYNAMIXEL_RATE 1000000 
#define DYNAMIXEL_CONTROL 2
#define MOVEMENT_MULTIPLIER 250
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
    moveToDefaultPosition();
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
        SERIAL.println("OK");
    }
}

// Whenever data comes into Serial interface, it gets fired
void SERIAL_EVENT() {
    digitalWrite(LED, HIGH);

    // So it reads all data available and signs movement readiness
    while(SERIAL.available() > 0) {
        //Receive differentials data from Serial interface
        String src = SERIAL.readString();

        if(src.equals("RESTART")) {
            moveToDefaultPosition();
            SERIAL.println("OK");
        }
        else {
            receiveData(src, differentials);
            readyToMove = true;
        }
    }
}

//Function to move to default position, made by relations offsets
void moveToDefaultPosition() {
    for(int i = 0; i < NUM_RELATIONS; i++) {
        if(bodyRelations[i] == NULL)
            continue;

        int id = bodyRelations[i]->motor();
        int pos = bodyRelations[i]->offset();
        Dynamixel.setEndless(id, OFF);
        Dynamixel.ledStatus(id, ON);

        Dynamixel.move(id, pos);
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
        int indexEnemy = -1;

        if(bodyRelations[i]->hasAnEnemy()) {
            indexEnemy = searchInDifferentials(bodyRelations[i]->enemy());
        }
        
        if(index != -1) {
            BodyRelation* relation = bodyRelations[i];
            Joint* enemy = NULL;

            if(indexEnemy != -1) {
                enemy = differentials[indexEnemy];
            }

            int id = relation->motor();
            int pos = calculatePosition(differentials[index], enemy, relation);

            Dynamixel.move(id, pos);
        }
    }
}

int calculatePosition(Joint* j, Joint* e, BodyRelation* r) {
    float x = j->x() * r->xMultiplier();
    float y = j->y() * r->yMultiplier();
    float z = j->z() * r->zMultiplier();

    float xEnemy = 0;
    float yEnemy = 0;
    float zEnemy = 0;

    if(e != NULL) {
        xEnemy = e->x() * r->xMultiplier();
        yEnemy = e->y() * r->yMultiplier();
        zEnemy = e->z() * r->zMultiplier();
    }

    int offset = r->offset();
    float speed = MOVEMENT_MULTIPLIER * 
        ((x - xEnemy) + (y - yEnemy) + (z - zEnemy));

    return offset + speed;
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