#include "Core.h"
#include "Arduino.h"
#include "Pitches.h"
#include <avr/sleep.h>

void Core::Begin()
{
    pinMode(_PIN_JOYSTICK_BUTTON, INPUT_PULLUP);
    pinMode(_PIN_LED, OUTPUT);
    pinMode(_PIN_BUZZER, OUTPUT);
    pinMode(_PIN_RESTART, OUTPUT);
    pinMode(_PIN_RF_POWER, OUTPUT);

    digitalWrite(_PIN_RF_POWER, HIGH);
    digitalWrite(_PIN_LED, LOW);
    digitalWrite(_PIN_BUZZER, LOW);
    digitalWrite(_PIN_RESTART, HIGH);

    Core::joy = new Joystick(A7, 3, 535, 985, 55);

    Core::radio = new RF24(_PIN_RF_CE, _PIN_RF_CSN);
    Core::radio->begin();
    Core::radio->setPALevel(RF24_PA_LOW);

    Core::radio->openWritingPipe(Core::add);
    Core::radio->stopListening();

    if (Core::debug)
    {
        Serial.begin(115200);
        Serial.println("Hello!");
    }

    Core::WelcomeSound();
}

void Core::WelcomeSound()
{
    bool ledState = false;
    int melody[] = {
        NOTE_G4, NOTE_G4, NOTE_G5};

    int noteDurations[] = {
        8, 8, 4};

    for (int thisNote = 0; thisNote < 3; thisNote++)
    {
        digitalWrite(_PIN_LED, ledState);
        int noteDuration = 1000 / noteDurations[thisNote];
        tone(_PIN_BUZZER, melody[thisNote], noteDuration);

        int pauseBetweenNotes = noteDuration * 1.30;
        delay(pauseBetweenNotes);

        noTone(_PIN_BUZZER);
        ledState = !ledState;
    }

    digitalWrite(_PIN_LED, LOW);
}

void Core::SleepSound()
{
    bool ledState = false;
    int melody[] = {
        NOTE_G4, NOTE_G4};

    int noteDurations[] = {
        8, 8};

    for (int thisNote = 0; thisNote < 2; thisNote++)
    {
        digitalWrite(_PIN_LED, ledState);
        int noteDuration = 1000 / noteDurations[thisNote];
        tone(_PIN_BUZZER, melody[thisNote], noteDuration);

        int pauseBetweenNotes = noteDuration * 1.30;
        delay(pauseBetweenNotes);

        noTone(_PIN_BUZZER);
        ledState = !ledState;
    }

    digitalWrite(_PIN_LED, LOW);
}

int Core::GetVal()
{
    return Core::joy->GetValueQuad();
}

void Core::Update()
{
    int val = Core::GetVal();

    if (val != 0)
        Core::lastTime = millis();

    if (Core::debug)
        Serial.println(val);

    Core::radio->write(&val, sizeof(val));

    if (millis() >= (Core::lastTime + _TIME_TO_SLEEP))
        Core::Sleep();
}

void Core::Restart()
{
    digitalWrite(_PIN_RESTART, LOW);
}

void WakeUP()
{
    //Does nothing, is needed for interrupt to work
}

void Core::Sleep()
{
    Core::SleepSound();

    digitalWrite(_PIN_RF_POWER, LOW);

    sleep_enable();
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    attachInterrupt(1, WakeUP, LOW);
    sleep_mode();
    sleep_disable();
    detachInterrupt(1);
    Core::Restart();
}
