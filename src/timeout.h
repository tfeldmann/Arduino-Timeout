#pragma once
#include <Arduino.h>

class Timeout {
public:
    Timeout();
    Timeout(unsigned long duration);

    // setup duration but don't start (time_over() stays true)
    void prepare(unsigned long duration);

    // start the timer with the prepared duration
    void start();

    // setup duration and start the timer
    void start(unsigned long duration);

    // return true if time ran out
    bool time_over();

    // runs out the timer so time_over() is true
    void expire();

    // returns a single true when time runs out and then resets itself
    bool periodic();

private:
    bool force_timeout_;
    unsigned long duration_;
    unsigned long last_reset_;
};
