# Timeout

This is a library I use in almost all of my projects. It is fully unit-tested, production-ready and works on all platforms (AVR, SAM, ESP...) that support the arduino core.

## Examples

### Example 1: A simple timeout

The LED will turn on after 2 seconds.

```arduino
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
```

### Example 2: As a heartbeat detection

Connect a button to pin 12.
Press the button to turn on the LED.
Failing to press the button for more than one second switches off the LED.

```arduino
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
```

### Example 3: A periodic timer

Toggles the LED every 200 milliseconds.

```arduino
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
```

## Full API

Include it like this:
```arduino
#include <timeout.h>

Timeout t;

void setup() {
    // your setup here
}

void loop() {
    // your loop here
}
```

The `Timeout` instance `t` has the following methods:
```cpp
// setup duration but don't start (time_over() will return true)
// then call `reset()` somewhere else in your code to start the timer.
void prepare(unsigned long duration); 

// setup duration and start the timer (time_over() is false
// for the next `duration` milliseconds)
void start(unsigned long duration);   

// return true if time ran out without reset
bool time_over();

// reset the timer
void reset();

// wind the timer forward so time_over() is true
void expire();

// returns a single true when time runs out then resets itself
bool periodic();
```

