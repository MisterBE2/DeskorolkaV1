
#include "Joystick.h"
#include "Arduino.h"

Joystick::Joystick(unsigned int _PIN_ANALOG, unsigned int _PIN_BUTTON)
{
    PIN_ANALOG = _PIN_ANALOG;
    PIN_BUTTON = _PIN_BUTTON;
    MAX_VAL = 1024;
    MIN_VAL = 0;
}

Joystick::Joystick(unsigned int _PIN_ANALOG, unsigned int _PIN_BUTTON, unsigned int _MAX_VAL, unsigned int MAX_VAL)
{
    PIN_ANALOG = _PIN_ANALOG;
    PIN_BUTTON = _PIN_BUTTON;
    MAX_VAL = _MAX_VAL;
    MIN_VAL = _MAX_VAL;
}

int Joystick::getValue()
{
    int curVal = analogRead(PIN_ANALOG);
    return map(curVal, MIN_VAL, MAX_VAL, 0, 1024);
}