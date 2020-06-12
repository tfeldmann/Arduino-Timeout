#include <timeout.h>

const int LED_PIN = 13;
bool led_on = false;

Timeout timer;

void setup()
{
  pinMode(LED_PIN, OUTPUT);
  timer.start(200);
}

void loop()
{
  if (timer.periodic())
  {
    led_on = !led_on;
    digitalWrite(LED_PIN, led_on);
  }
}
