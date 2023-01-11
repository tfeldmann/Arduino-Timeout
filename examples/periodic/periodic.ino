#include <Timeout.h>

const int LED_PIN = 13;
bool led_on = false;

Timeout timer;

void setup()
{
  pinMode(LED_PIN, OUTPUT);
}

void loop()
{
  if (timer.periodic(200)) {
    led_on = !led_on;
    digitalWrite(LED_PIN, led_on);
  }
}
