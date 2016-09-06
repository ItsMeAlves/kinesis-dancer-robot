#include "Arduino.h"
#include "BodyRelation.h"

BodyRelation::BodyRelation(String j, int pin, int* mapper) {
    _jointType = j;
    _motorPin = pin;
    _coordinateMapper = mapper;
};

String BodyRelation::getJointType() {
    return _jointType;
};

int BodyRelation::motor() {
    return _motorPin;
};

int* BodyRelation::coordinateMapper() {
    return _coordinateMapper;
};