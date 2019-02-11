#ifndef CORE_DEF
#define CORE_DEF

#define JOYSTICK_PIN A7
#define JOYSTICK_BUTTON_PIN 3
#define LED_PIN 2
#define BUZZER_PIN 9
#define RESTART_PIN 4
#define RF_CE_PIN 6
#define RF_CSN_PIN 7

class Core
{
    public:
    static const bool debug = false;
};

#endif