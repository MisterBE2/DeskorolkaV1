#include "Toggle.h"

Toggle::Toggle(byte pin, bool *step, unsigned int *duration, byte length)
{
    Toggle::pin = pin;
    Toggle::currentStep = 0;
    Toggle::length = length;
    Toggle::step = step;
    Toggle::duration = duration;
}

void Toggle::Start()
{
    JobType *jobType[] = {new JobTimeType(duration[0])};
    Toggle::types = jobType;
}

void Toggle::Update()
{
    digitalWrite(Toggle::pin, Toggle::step[Toggle::currentStep]);
}

bool Toggle::Finnished()
{
    if (Toggle::currentStep >= Toggle::length)
        return true;

    return false;
}

void Toggle::Step()
{
    JobType *jobType[] = {new JobTimeType(duration[Toggle::currentStep])};
    Toggle::types = jobType;

    if (Toggle::currentStep < Toggle::duration)
        Toggle::currentStep++;
}

bool Toggle::Allow()
{
    if (Job::Finished() && Toggle::currentStep < Toggle::length)
        return true;

    return false;
}