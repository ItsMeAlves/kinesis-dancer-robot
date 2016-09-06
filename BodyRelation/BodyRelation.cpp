#include "Arduino.h"
#include "BodyRelation.h"

BodyRelation::BodyRelation(String j, int pin, int direction, float* mapper) {
    _jointType = j;
    _motorPin = pin;
    _direction = (direction / abs(direction));
    _coordinateMapper = mapper;
};

String BodyRelation::getJointType() {
    return _jointType;
};

int BodyRelation::motor() {
    return _motorPin;
};

int* BodyRelation::direction() {
    return _direction;
};

float* BodyRelation::mapper() {
    return _coordinateMapper;
}