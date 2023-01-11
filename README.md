# Timeout library for Arduino

![tests](https://github.com/tfeldmann/Arduino-Timeout/workflows/tests/badge.svg)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/tfeldmann/library/Timeout.svg)](https://registry.platformio.org/libraries/tfeldmann/Timeout)

The ideal library for heartbeats, timeouts and repeated timers. Easier to use than your kitchen timer.

_This is a library I use in almost all of my projects. It is fully unit-tested and works on all platforms (AVR, SAM, ESP...) that support the arduino core._

## Quickstart

### Example 1: A simple timeout

The LED will turn off after 2 seconds.

```cpp
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
```

### Example 2: As a heartbeat detection

Connect a button to pin 12.
Press the button to turn on the LED.
Failing to press the button for more than one second switches off the LED.

```cpp
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
```

### Example 3: A periodic timer

Toggles the LED every 200 milliseconds.

```cpp
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
```

## Full API

`Timeout` instances have the following methods:

```cpp
// set the timer to `time_ms` and start ticking
void start(uint32_t time_ms);

// returns a single true when time runs out and then resets to `time_ms`.
bool periodic(uint32_t time_ms);

// pause and resume the timer
void pause();
void resume();

// runs out the timer so `time_over()` returns true
void expire();

// returns whether the time ran out
bool time_over();

// returns whether the timer is paused
bool is_paused();

// returns the milliseconds until the timer runs out
uint32_t time_left_ms();
```
