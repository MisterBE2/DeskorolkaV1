#include <Arduino.h>
#include "Data.h"
#ifndef JOY_DEF
#define JOY_DEF

class Joystick {
    public:
        unsigned int MAX_VAL, MIN_VAL; 
        byte PIN_ANALOG, PIN_BUTTON, HIS;
        Joystick();
        Joystick(byte, byte);
        Joystick(byte, byte, unsigned int, unsigned int, unsigned int);
        Joystick(DataStruct);
        int GetValue();
        int GetValueQuad();
        int GetValueRaw();
        String ToString();

    private:
        void SetData(byte, byte, unsigned int, unsigned int, unsigned int);
};

#endif
