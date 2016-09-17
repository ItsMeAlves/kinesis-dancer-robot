#include "Arduino.h"
#include "BodyRelation.h"

BodyRelation::BodyRelation(String j, int id, int direction, float xMultiplier, float yMultiplier, float zMultiplier) {
    _jointType = j;
    _motorId = id;
    _direction = direction;
    _xMultiplier = xMultiplier;
    _yMultiplier = yMultiplier;
    _zMultiplier = zMultiplier;
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

float BodyRelation::xMultiplier() {
    return _xMultiplier;
}
float BodyRelation::yMultiplier() {
    return _yMultiplier;
}
float BodyRelation::zMultiplier() {
    return _zMultiplier;
}

String BodyRelation::toString() {
    return _jointType + " " + _motorId + " " + _direction;
}