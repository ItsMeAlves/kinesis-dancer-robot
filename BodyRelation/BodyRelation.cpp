#include "Arduino.h"
#include "BodyRelation.h"

BodyRelation::BodyRelation(String j, int id, int direction, float* mapper) {
    int i = X_INDEX;
    _jointType = j;
    _motorId = id;
    _coordinateMapper = mapper;
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

float* BodyRelation::mapper() {
    return _coordinateMapper;
}

String BodyRelation::toString() {
    return _jointType + " " + _motorId + " " + _direction;
}