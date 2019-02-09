#include <Arduino.h>

#ifndef DATA_DEF
#define DATA_DEF 0

#define DATA_START 32
#define DATA_VER "d0"

enum joyVal_e
{
    raw,
    quad,
    center
};

struct DataStruct
{
    char VER[3];
    unsigned int MAX_VAL, MIN_VAL;
    byte PIN_ANALOG, PIN_BUTTON, HIS;
    joyVal_e joyVal;

} typedef DataStruct;

class Data
{
  public:
    Data();
    void Save(DataStruct);
    DataStruct Get();
    String ToString();

  private:
    bool loaded = false;
    DataStruct data;
    DataStruct def = {DATA_VER, 1024, 0, A7, 4, 50, quad};
};

#endif