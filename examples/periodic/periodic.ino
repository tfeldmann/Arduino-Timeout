#include <timeout.h>

const int PIN_LED = 13;
bool led_on = false;

Timeout timer;

void setup()
{
    pinMode(PIN_LED, OUTPUT);
    timer.start(200);
}

void loop()
{
    if (timer.periodic())
    {
        led_on = !led_on;
        digitalWrite(PIN_LED, led_on);
    }
}
