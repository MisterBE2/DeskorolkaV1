#include <SPI.h>
#include "RF24.h"
#include "Joystick.h"

#ifndef CORE_DEF
#define CORE_DEF

#define _PIN_JOYSTICK A7
#define _PIN_JOYSTICK_BUTTON 3
#define _PIN_LED 2
#define _PIN_BUZZER 9
#define _PIN_RESTART 4
#define _PIN_RF_CE 6
#define _PIN_RF_CSN 7
#define _PIN_RF_POWER 5
#define _TIME_TO_SLEEP 20000

void WakeUP();

class Core
{
  public:
    bool debug = false;
    void Begin();
    void WelcomeSound();
    void SleepSound();
    int GetVal();
    void Update();
    void Sleep();
    void Restart();

  private:
    unsigned long lastTime = 0;
    Joystick *joy;
    RF24 *radio;
    byte * add = "Reciver";
};

#endif