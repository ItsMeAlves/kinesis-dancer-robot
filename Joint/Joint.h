#ifndef Joint_h
#define Joint_h

#include "Arduino.h"

class Joint {
    private:
        String _type;
        float _x, _y, _z;
    public:
        Joint(String type, float x, float y, float z);
        String toString();
        String getType();
        float x();
        float y();
        float z();
};

#endif