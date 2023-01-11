#include <Timeout.h>

const int LED_PIN = 13;
Timeout timer;

void setup()
{
  pinMode(LED_PIN, OUTPUT);
  timer.start(2000);
}

void loop()
{
  digitalWrite(LED_PIN, !timer.time_over());
}
