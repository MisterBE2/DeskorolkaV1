#include "Core.h"

Core core;

void setup()
{
    core.Begin();
}

void loop()
{
    core.Update();

    // if (Serial.available())
    // {
    //     int val = Serial.readStringUntil('\n').toInt();
    //     Serial.print("Sending: ");
    //     Serial.println(val);
    //     radio.write(&val, sizeof(val));
    // }
}
