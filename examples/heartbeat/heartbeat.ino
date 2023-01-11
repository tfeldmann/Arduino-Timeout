#include <Timeout.h>

const int LED_PIN = 13;
const int BUTTON_PIN = 12;

Timeout heartbeat;

void setup()
{
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);
}

void loop()
{
  if (digitalRead(BUTTON_PIN)) {
    heartbeat.start(1000);
  }
  digitalWrite(LED_PIN, !heartbeat.time_over());
}
