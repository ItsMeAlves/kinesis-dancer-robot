//xico.ino
#include "Joint/Joint.cpp"
#include "BodyRelation/BodyRelation.cpp"

#define NUM_TRACKED_JOINTS 4
#define NUM_RELATIONS 4
#define SERIAL_TIMEOUT 5
#define FIELD_SEP ','
#define LINE_SEP ';'

int led = 13;

Joint* differentials[NUM_TRACKED_JOINTS];
BodyRelation* bodyRelations[NUM_RELATIONS];

void receiveData(String src, Joint** dest);
void move(Joint** diffs, BodyRelation** body);
void cleanDifferentials();

void setup() {
    Serial.begin(9600);
    Serial.setTimeout(SERIAL_TIMEOUT);
    pinMode(led, OUTPUT);

    for(int i = 0; i < NUM_TRACKED_JOINTS; i++) {
        differentials[i] = NULL;
    }
}

void loop() {
    digitalWrite(led, LOW);

    while(Serial.available() > 0) {
        digitalWrite(led, HIGH);
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
    // TODO: write logic
}

void cleanDifferentials() {
    for(int i = 0; i < NUM_TRACKED_JOINTS; i++) {
        delete differentials[i];
        differentials[i] = NULL;
    }
}