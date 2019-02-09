#include "Data.h"
#include <Arduino.h>
#include <EEPROM.h>

void Data::Save(DataStruct data)
{
    for (unsigned int t = 0; t < sizeof(data); t++)
        EEPROM.write(DATA_START + t, *((char *)&data + t));
}

DataStruct Data::Load()
{
    DataStruct data;
    if (EEPROM.read(DATA_START + 0) == DATA_VER[0] &&
        EEPROM.read(DATA_START + 1) == DATA_VER[1])
        for (unsigned int t = 0; t < sizeof(data); t++)
            *((char *)&data + t) = EEPROM.read(DATA_START + t);
    else
        data = Data::def;

    return data;
}

String Data::ToString()
{
    DataStruct loaded = Data::Load();

    String data;
    data += "VER : ";
    data += loaded.VER;
    data += "\n\r";
    data += "PIN_ANALOG : ";
    data += loaded.PIN_ANALOG;
    data += "\n\r";
    data += "PIN_BUTTON : ";
    data += loaded.PIN_BUTTON;
    data += "\n\r";
    data += "MIN_VAL : ";
    data += loaded.MIN_VAL;
    data += "\n\r";
    data += "MAX_VAL : ";
    data += loaded.MAX_VAL;
    data += "\n\r";
    data += "HIS : ";
    data += loaded.HIS;
    data += "\n\r";
    data += "JOY_INTERPOLATION : ";
    data += loaded.joyVal;
    data += "\n\r";

    return data;
}