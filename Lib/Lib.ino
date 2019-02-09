#include "Data.h"
#include "Joystick.h"

Joystick *joy;
Data data;

void setup()
{
    Serial.begin(115200);
    joy = new Joystick(data.Load());

    Serial.print(data.ToString());

    delay(2000);
}

void loop()
{
    int val;
    switch (data.Load().joyVal)
    {
        case raw:
            val = joy->GetValueRaw();
            break;

        case quad:
            val = joy->GetValueQuad();
            break;

        case center:
            val = joy->GetValue();
            break;
    }

    Serial.println(val);
}