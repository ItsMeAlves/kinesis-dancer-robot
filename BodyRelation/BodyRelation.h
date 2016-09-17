#ifndef BodyRelation_h
#define BodyRelation_h

#include "Arduino.h"

#define X_INDEX 0
#define Y_INDEX 1
#define Z_INDEX 2

class BodyRelation {
    public:
        BodyRelation(String j, int id, int direction, float xMultiplier, float yMultiplier, float zMultiplier);
        String jointType();
        int motor();
        int direction();
        float xMultiplier();
        float yMultiplier();
        float zMultiplier();
        String toString();
    private:
        String _jointType;
        int _motorId;
        int _direction;
        float _xMultiplier;
        float _yMultiplier;
        float _zMultiplier;
};

#endif