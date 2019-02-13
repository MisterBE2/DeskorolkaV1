#include "Core.h"
#include "Arduino.h"

void Core::Begin()
{
    pinMode(_PIN_JOYSTICK_BUTTON, INPUT_PULLUP);
    pinMode(_PIN_LED, OUTPUT);
    pinMode(_PIN_BUZZER, OUTPUT);
    pinMode(_PIN_RESTART, OUTPUT);

    digitalWrite(_PIN_LED, LOW);
    digitalWrite(_PIN_BUZZER, LOW);
    digitalWrite(_PIN_RESTART, HIGH);
}