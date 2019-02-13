#include <SPI.h>
#include "RF24.h"
#include <Servo.h>
#include <Adafruit_NeoPixel.h>

RF24 radio(6, 7);
Servo myservo;
Adafruit_NeoPixel led = Adafruit_NeoPixel(1, 9);

byte add[][6] = {"Reciver"};

unsigned long lastTime = 0;
unsigned long lastTimeMinus = 0;

void setup()
{
    led.begin();
    led.setPixelColor(0, 255, 255, 255);
    led.show();

    radio.begin();
    radio.setPALevel(RF24_PA_MAX);

    radio.openReadingPipe(1, add[0]);
    radio.startListening();

    myservo.attach(3);
    Serial.begin(115200);
    Serial.println("Hello!");
}

int val = 0;
unsigned long last = 0;
bool lampOn = false;

void loop()
{
    // if (radio.available())
    // {
    //     radio.read(&val, sizeof(val));
    //     Serial.print("Recived: ");
    //     Serial.println(val);
    //     myservo.writeMicroseconds(val);
    //     last = millis();
    //     lampOn = true;
    //     led.setPixelColor(0, 255, 255, 255);
    //     led.show();
    // }

    // if (millis() >= (last + 1000) && lampOn)
    // {
    //     lampOn = false;
    //     led.setPixelColor(0, 0, 0, 0);
    //     led.show();
    // }

    if (radio.available())
    {
        radio.read(&val, sizeof(val));
        if (val > 1024)
            val = 1024;
        else if (val < -1024)
            val = 1024;

        lastTimeMinus = lastTime = millis();
    }

    if (millis() >= (lastTime + 100))
    {
        if (millis() >= (lastTimeMinus + 2))
        {
            if (val > -1024)
                val--;
            lastTimeMinus = millis();
        }
    }

    if (val > 55)
    {
        int ledVal = map(val, 55, 1024, 0, 255);
        led.setPixelColor(0, ledVal, ledVal, ledVal);
        led.show();

        int signal = map(val, 55, 1024, 900, 2000);
        myservo.writeMicroseconds(signal);
        // Serial.println(signal);
        // delay(2);
    }
    else
    {
        int ledVal = map(val, -1024, 54, 255, 0);
        led.setPixelColor(0, ledVal, 0, 0);
        led.show();

        int signal = map(val, -1024, 54, 750, 800);
        myservo.writeMicroseconds(signal);
        // Serial.println(signal);
        // delay(2);
    }
}
