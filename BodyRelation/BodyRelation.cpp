#include "Arduino.h"
#include "BodyRelation.h"

BodyRelation::BodyRelation(String j, int id, int direction, float* multiplier) {
    _jointType = j;
    _motorId = id;
    _multiplier = multiplier;
    if(direction != 0) {
        _direction = (direction / abs(direction));
    }
    else {
        direction = 1;
    }
};

String BodyRelation::jointType() {
    return _jointType;
};

int BodyRelation::motor() {
    return _motorId;
};

int BodyRelation::direction() {
    return _direction;
};

float* BodyRelation::multiplier() {
    return _multiplier;
}

String BodyRelation::toString() {
    return _jointType + " " + _motorId + " " + _direction;
}