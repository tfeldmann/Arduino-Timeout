#include "timeout.h"

Timeout::Timeout()
{
    force_timeout_ = true;
    duration_ = 0;
    last_reset_ = 0;
}

void Timeout::prepare(unsigned long duration)
{
    duration_ = duration;
    force_timeout_ = true;
}

void Timeout::start(unsigned long duration)
{
    duration_ = duration;
    reset();
}

bool Timeout::time_over()
{
    return (force_timeout_ || ((millis() - last_reset_) >= duration_));
}

void Timeout::reset()
{
    if (duration_ == 0)
    {
        force_timeout_ = true;
    }
    else
    {
        last_reset_ = millis();
        force_timeout_ = false;
    }
}

void Timeout::expire()
{
    force_timeout_ = true;
}

bool Timeout::periodic()
{
    bool result = time_over();
    if (result)
        reset();
    return result;
}
