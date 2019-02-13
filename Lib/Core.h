#ifndef CORE_DEF
#define CORE_DEF

#define _PIN_JOYSTICK A7
#define _PIN_JOYSTICK_BUTTON 3
#define _PIN_LED 2
#define _PIN_BUZZER 9
#define _PIN_RESTART 4
#define _PIN_RF_CE 6
#define _PIN_RF_CSN 7

class Core
{
    public:
    static const bool debug = false;
    static void Begin();
};

#endif