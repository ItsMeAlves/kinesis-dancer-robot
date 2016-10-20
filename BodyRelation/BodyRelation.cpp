#include "Arduino.h"
#include "BodyRelation.h"

BodyRelation::BodyRelation(String j, int id, int offset, 
    float xMultiplier, float yMultiplier, float zMultiplier, String enemy) {
    _jointType = j;
    _motorId = id;
    _offset = offset;
    _xMultiplier = xMultiplier;
    _yMultiplier = yMultiplier;
    _zMultiplier = zMultiplier;
    _enemy = enemy;
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

String BodyRelation::enemy() {
    return _enemy;
}

bool BodyRelation::hasAnEnemy() {
    return !_enemy.equals("*");
}

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