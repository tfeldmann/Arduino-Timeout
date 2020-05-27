#include <timeout.h>

const int PIN_LED = 13;
const int PIN_BTN = 12;

Timeout heartbeat;

void setup()
{
    pinMode(PIN_LED, OUTPUT);
    pinMode(PIN_BTN, INPUT);

    heartbeat.prepare(1000);
}

void loop()
{
    if (digitalRead(PIN_BTN))
    {
        heartbeat.reset();
    }

    digitalWrite(PIN_LED, heartbeat.time_over());
}
