#include <timeout.h>

const int PIN_LED = 13;
Timeout timeout;

void setup()
{
    pinMode(PIN_LED, OUTPUT);
    timeout.start(2000);
}

void loop()
{
    digitalWrite(PIN_LED, timeout.time_over());
}
