#ifndef BodyRelation_h
#define BodyRelation_h

#include "Arduino.h"

class BodyRelation {
    public:
        BodyRelation(String j, int pin, int* mapper);
        String getJointType();
        int motor();
        int* coordinateMapper();
    private:
        String _jointType;
        int _motorPin;
        int* _coordinateMapper;
};

#endif