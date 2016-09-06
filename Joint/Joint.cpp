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

Joint* Joint::fromString(String src, char separator) {
    String type = src.substring(0, src.indexOf(separator));
    src = src.substring(src.indexOf(separator) + 1);

    int xIndex = src.indexOf(separator);
    int yIndex = src.indexOf(separator, xIndex + 1);
    int zIndex = src.indexOf(separator, yIndex + 1);

    float x = src.substring(0, xIndex).toFloat();
    float y = src.substring(xIndex + 1, yIndex).toFloat();
    float z = src.substring(yIndex + 1, zIndex).toFloat();

    Joint* j = new Joint(type, x, y, z);
    return j;
}