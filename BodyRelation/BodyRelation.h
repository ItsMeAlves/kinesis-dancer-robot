#ifndef BodyRelation_h
#define BodyRelation_h

#include "Arduino.h"

#define X_INDEX 0
#define Y_INDEX 1
#define Z_INDEX 2

class BodyRelation {
    public:
        BodyRelation(String j, int id, int offset, 
            float xMultiplier, float yMultiplier, float zMultiplier, String enemy);
        String jointType();
        int motor();
        int offset();
        float xMultiplier();
        float yMultiplier();
        float zMultiplier();
        String enemy();
        bool hasAnEnemy();
        String toString();
    private:
        String _jointType;
        int _motorId;
        int _offset;
        float _xMultiplier;
        float _yMultiplier;
        float _zMultiplier;
        String _enemy;
};

#endif