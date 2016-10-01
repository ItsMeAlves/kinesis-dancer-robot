#include "Arduino.h"
#include "BodyRelation.h"

BodyRelation::BodyRelation(String j, int id, int offset, float xMultiplier, float yMultiplier, float zMultiplier) {
    _jointType = j;
    _motorId = id;
    _offset = offset;
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

int BodyRelation::offset() {
    return _offset;
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
    return _jointType + " " + _motorId + " " + _offset;
}