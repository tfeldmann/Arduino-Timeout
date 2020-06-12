# Minimal Timeout for Arduino

![Unit tests](https://github.com/tfeldmann/Arduino-Timeout/workflows/Unit%20tests/badge.svg)
![Compile examples](https://github.com/tfeldmann/Arduino-Timeout/workflows/Compile%20examples/badge.svg)

The ideal library for heartbeats, timeouts and repeated timers. Easier to use than your kitchen timer.

*This is a library I use in almost all of my projects. It is fully unit-tested, production-ready and works on all platforms (AVR, SAM, ESP...) that support the arduino core.*


## Quickstart

### Example 1: A simple timeout

The LED will turn on after 2 seconds.

```cpp
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
```


### Example 2: As a heartbeat detection

Connect a button to pin 12.
Press the button to turn on the LED.
Failing to press the button for more than one second switches off the LED.

```cpp
#include <timeout.h>

const int LED_PIN = 13;
const int BUTTON_PIN = 12;

Timeout heartbeat;

void setup()
{
    pinMode(LED_PIN, OUTPUT);
    pinMode(BUTTON_PIN, INPUT);

    heartbeat.prepare(1000);
}

void loop()
{
    if (digitalRead(BUTTON_PIN))
    {
        heartbeat.reset();
    }

    digitalWrite(LED_PIN, heartbeat.time_over());
}
```


### Example 3: A periodic timer

Toggles the LED every 200 milliseconds.

```cpp
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
```


## Full API

`Timeout` instances have the following methods:
```cpp
// setup duration but don't start (time_over() will return true)
// then call `reset()` somewhere else in your code to start the timer.
void prepare(unsigned long duration);

// setup duration and start the timer (time_over() is false
// for the next `duration` milliseconds)
void start(unsigned long duration);

// returns true if time ran out, false otherwise
bool time_over();

// winds up the timer to last known duration
void reset();

// runs out the timer so time_over() is true
void expire();

// returns a single true when time runs out then automatically resets itself
bool periodic();
```

