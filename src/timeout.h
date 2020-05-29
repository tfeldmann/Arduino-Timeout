#pragma once
#include <Arduino.h>

class Timeout
{
public:
    Timeout();
    void prepare(unsigned long duration); // setup duration but don't start (time_over=1)
    void start(unsigned long duration);   // setup duration and start the timer
    bool time_over();                     // return true if time ran out
    void reset();                         // wind up to last known duration
    void expire();                        // runs out the timer so time_over() is true
    bool periodic();                      // returns a single true when time runs out and
                                          // then resets itself

private:
    bool force_timeout_;
    unsigned long duration_;
    unsigned long last_reset_;
};
