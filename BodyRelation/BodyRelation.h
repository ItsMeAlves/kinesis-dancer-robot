#ifndef BodyRelation_h
#define BodyRelation_h

#include "Arduino.h"

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