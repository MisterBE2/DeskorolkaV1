#include "Data.h"
#include <Arduino.h>
#include <EEPROM.h>

Data::Data()
{
    Data::Get();
}

void Data::Save(DataStruct data)
{
    for (unsigned int t = 0; t < sizeof(data); t++)
        EEPROM.write(DATA_START + t, *((char *)&data + t));
}

DataStruct Data::Get()
{
    if (Data::loaded == false)
    {
        DataStruct data;
        if (EEPROM.read(DATA_START + 0) == DATA_VER[0] &&
            EEPROM.read(DATA_START + 1) == DATA_VER[1])
        {
            for (unsigned int t = 0; t < sizeof(data); t++)
                *((char *)&data + t) = EEPROM.read(DATA_START + t);

            Data::data = data;
            Data::loaded == true;
            return data;
        }
        else
            return Data::def;
    }
    return Data::data;
}

String Data::ToString()
{
    DataStruct Loaded = Data::Get();

    String data;
    data += "VER : ";
    data += Loaded.VER;
    data += "\n\r";
    data += "PIN_ANALOG : ";
    data += Loaded.PIN_ANALOG;
    data += "\n\r";
    data += "PIN_BUTTON : ";
    data += Loaded.PIN_BUTTON;
    data += "\n\r";
    data += "MIN_VAL : ";
    data += Loaded.MIN_VAL;
    data += "\n\r";
    data += "MAX_VAL : ";
    data += Loaded.MAX_VAL;
    data += "\n\r";
    data += "HIS : ";
    data += Loaded.HIS;
    data += "\n\r";
    data += "JOY_INTERPOLATION : ";
    data += Loaded.joyVal;
    data += "\n\r";

    return data;
}