#include "Arduino.h"
#include "Joint.h"

Joint::Joint(String type, float x, float y, float z) {
    _type = type;
    _x = x;
    _y = y;
    _z = z;
};

String Joint::getType() {
    return _type;
};

String Joint::toString() {
    return _type + " " + _x + " " + _y + " " + _z;
}

float Joint::x() {
    return _x;
};

float Joint::y() {
    return _y;
};

float Joint::z() {
    return _z;
}