#include <timeout.h>

const int LED_PIN = 13;
Timeout timeout;

void setup()
{
  pinMode(LED_PIN, OUTPUT);
  timeout.start(2000);
}

void loop()
{
  digitalWrite(LED_PIN, timeout.time_over());
}
