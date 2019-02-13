#include <Arduino.h>
#include <stdlib.h>
#include "Joystick.h"

Joystick::Joystick()
{
}

Joystick::Joystick(byte _PIN_ANALOG, byte _PIN_BUTTON, unsigned int _MIN_VAL, unsigned int _MAX_VAL, unsigned int _HIS)
{
    Joystick::SetData(_PIN_ANALOG, _PIN_BUTTON, _MIN_VAL, _MAX_VAL, _HIS);
}

Joystick::Joystick(byte _PIN_ANALOG, byte _PIN_BUTTON)
{
    Joystick::SetData(_PIN_ANALOG, _PIN_BUTTON, 0, 1024, 50);
}

// Joystick::Joystick(DataStruct data)
// {
//     Joystick::SetData(
//         data.PIN_ANALOG,
//         data.PIN_BUTTON,
//         data.MIN_VAL,
//         data.MAX_VAL,
//         data.HIS);
// }

void Joystick::SetData(byte _PIN_ANALOG, byte _PIN_BUTTON, unsigned int _MIN_VAL, unsigned int _MAX_VAL, unsigned int _HIS)
{
    PIN_ANALOG = _PIN_ANALOG;
    PIN_BUTTON = _PIN_BUTTON;
    MAX_VAL = _MAX_VAL;
    MIN_VAL = _MIN_VAL;
    HIS = _HIS;

    pinMode(PIN_BUTTON, INPUT_PULLUP);
}

int Joystick::GetValue()
{
    int curVal = analogRead(PIN_ANALOG);
    curVal = map(curVal, MIN_VAL, MAX_VAL, 0, 1024);

    if (abs(curVal) > HIS)
    {
        if (curVal > 1024)
            return 1024;
        else if (curVal < -1024)
            return -1024;
        return curVal;
    }
    else
        return 0;
}

int Joystick::GetValueRaw()
{
    return analogRead(PIN_ANALOG);
}

int Joystick::GetValueQuad()
{
    int rawVal = Joystick::GetValue();
    if (rawVal != 0)
    {
        float val = Joystick::GetValue() / 1024.0;
        val = val * val * val;

        // if (rawVal < 0)
        //     return -(val * 1024);

        return val * 1024;
    }

    return 0;
}

// int Joystick::GetValue(e_joyVal type)
// {
//     switch (type)
//     {
//     case raw:
//         return Joystick::GetValueRaw();
//         break;

//     case quad:
//         return Joystick::GetValueQuad();
//         break;

//     case center:
//         return Joystick::GetValue();
//         break;

//     default:
//         return 0;
//         break;
//     }
// }

String Joystick::ToString()
{
    String data;
    data += "PIN_ANALOG : ";
    data += PIN_ANALOG;
    data += "\n\r";
    data += "PIN_BUTTON : ";
    data += PIN_BUTTON;
    data += "\n\r";
    data += "MIN_VAL : ";
    data += MIN_VAL;
    data += "\n\r";
    data += "MAX_VAL : ";
    data += MAX_VAL;
    data += "\n\r";
    data += "HIS : ";
    data += HIS;
    data += "\n\r";
    return data;
}
