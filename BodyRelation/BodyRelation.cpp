#include "Arduino.h"
#include "BodyRelation.h"

BodyRelation::BodyRelation(String j, int pin, int direction, float* mapper) {
    int i = X_INDEX;
    _jointType = j;
    _motorPin = pin;
    _coordinateMapper = mapper;
    if(direction != 0) {
        _direction = (direction / abs(direction));
    }
    else {
        direction = 1;
    }
};

String BodyRelation::getJointType() {
    return _jointType;
};

int BodyRelation::motor() {
    return _motorPin;
};

int BodyRelation::direction() {
    return _direction;
};

float* BodyRelation::mapper() {
    return _coordinateMapper;
}