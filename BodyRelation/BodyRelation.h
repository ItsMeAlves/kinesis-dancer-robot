#ifndef BodyRelation_h
#define BodyRelation_h

#include "Arduino.h"

#define X_INDEX 0
#define Y_INDEX 1
#define Z_INDEX 2

class BodyRelation {
    public:
        BodyRelation(String j, int pin, int direction, float* mapper);
        String getJointType();
        int motor();
        int direction();
        float* mapper();
    private:
        String _jointType;
        int _motorPin;
        int _direction;
        float* _coordinateMapper;
};

#endif