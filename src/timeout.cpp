#include "timeout.h"

Timeout::Timeout()
    : force_timeout_(true)
    , duration_(0)
    , last_reset_(0)
{
}

Timeout::Timeout(unsigned long duration)
    : force_timeout_(true)
    , duration_(duration)
    , last_reset_(0)
{
}

void Timeout::prepare(unsigned long duration)
{
    duration_ = duration;
    force_timeout_ = true;
}

void Timeout::start()
{
    if (duration_ == 0) {
        force_timeout_ = true;
    } else {
        last_reset_ = millis();
        force_timeout_ = false;
    }
}

void Timeout::start(unsigned long duration)
{
    duration_ = duration;
    start();
}

bool Timeout::time_over()
{
    return (force_timeout_ || ((millis() - last_reset_) >= duration_));
}

void Timeout::expire()
{
    force_timeout_ = true;
}

bool Timeout::periodic()
{
    bool result = time_over();
    if (result)
        start();
    return result;
}
