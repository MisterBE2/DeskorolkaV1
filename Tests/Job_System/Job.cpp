#include "Job.h"
#include "Arduino.h"
#include "limits.h"

// Job Infinite

bool JobInfiniteType::Finished()
{
  return false;
}

void JobInfiniteType::Step() {}
bool JobInfiniteType::Allow() { return true; }

String JobInfiniteType::ToString()
{
  return "JobInfiniteType";
}

// Job Finite

JobFiniteType::JobFiniteType(unsigned int maxSteps)
{
  JobFiniteType::maxSteps = maxSteps;
  JobFiniteType::currentStep = 0;
}

bool JobFiniteType::Finished()
{
  // Serial.print("Current step: ");
  // Serial.print(JobFiniteType::currentStep);
  // Serial.print("\t");

  // Serial.print("Max steps: ");
  // Serial.print(JobFiniteType::maxSteps);
  // Serial.print("\t");

  if (JobFiniteType::currentStep >= JobFiniteType::maxSteps)
    return true;

  return false;
}

bool JobFiniteType::Allow() { return true; }

void JobFiniteType::Step()
{
  if (JobFiniteType::currentStep < JobFiniteType::maxSteps)
    JobFiniteType::currentStep++;
}

String JobFiniteType::ToString()
{
  return "JobFiniteType";
}

// Job Time

JobTimeType::JobTimeType(unsigned int duration)
{
  JobTimeType::duration = duration;
  JobTimeType::start = millis();
}

bool JobTimeType::Finished()
{
  long curr = millis();

  // Serial.print("Current time: ");
  // Serial.print(curr);
  // Serial.print("\t");

  // Serial.print("Start: ");
  // Serial.print(JobTimeType::start);
  // Serial.print("\t");

  // Serial.print("Duration: ");
  // Serial.print(JobTimeType::duration);
  // Serial.print("\t");

  // Serial.print("End: ");
  // Serial.print(JobTimeType::duration + JobTimeType::start);
  // Serial.println("\t");

  if (curr >= JobTimeType::start)
  {
    if (curr >= (JobTimeType::start + JobTimeType::duration))
      return true;
  }
  else
  {
    long reminder = ULONG_MAX - JobTimeType::start;
    reminder -= JobTimeType::duration;

    if (curr >= reminder)
      return true;
  }

  return false;
}

bool JobTimeType::Allow() { return true; }

void JobTimeType::Step() {}

String JobTimeType::ToString()
{
  return "JobTimeType";
}

// Job Time Interval

JobTimeIntervalType::JobTimeIntervalType(unsigned int interval)
{
  JobTimeIntervalType::interval = interval;
  JobTimeIntervalType::lastTime = millis();
  JobTimeIntervalType::laggedTrigger = false;
}

bool JobTimeIntervalType::Finished()
{
  return false;
}

bool JobTimeIntervalType::Allow()
{
  if (JobTimeIntervalType::laggedTrigger)
    return true;

  if (millis() >= (JobTimeIntervalType::lastTime + JobTimeIntervalType::interval))
  {
    JobTimeIntervalType::laggedTrigger = true;
    JobTimeIntervalType::lastTime = millis();
    return true;
  }

  return false;
}

void JobTimeIntervalType::Step()
{
  JobTimeIntervalType::laggedTrigger = false;
}

String JobTimeIntervalType::ToString()
{
  return "JobTimeIntervalType";
}

// Job

bool Job::Finished()
{
  for (int i = 0; i < Job::jobTypesAmmount; i++)
  {
    if (Job::types[i] != nullptr)
    {
      if (Job::types[i]->Finished())
        return true;
    }
  }

  return false;
}

bool Job::Allow()
{
  bool allAllow = true;
  for (int i = 0; i < Job::jobTypesAmmount; i++)
  {
    if (Job::types[i] != nullptr)
    {
      if (!Job::types[i]->Allow())
      {
        allAllow = false;
        break;
      }
    }
  }

  return allAllow;
}

void Job::Step()
{
  for (int i = 0; i < Job::jobTypesAmmount; i++)
  {
    if (Job::types[i] != nullptr)
    {
      Job::types[i]->Step();
    }
  }
}

Job::~Job()
{
  for (int i = 0; i < Job::jobTypesAmmount; i++)
  {
    if (Job::types[i] != nullptr)
    {
      delete Job::types[i];
    }
  }
}