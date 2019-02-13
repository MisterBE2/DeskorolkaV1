#include "Arduino.h"

#ifndef JOB_DEF
#define JOB_DEF

// Defines interface for Decorator Pattern
class JobType
{
public:
  virtual bool Finished() = 0;
  virtual void Step() = 0;
  virtual bool Allow() = 0;
  virtual String ToString() = 0;
};

// A decorator which allows task to always run
class JobInfiniteType : public JobType
{
public:
  // Retruns true when job is done
  bool Finished();

  // Returns true
  bool Allow();

  // Does nothing
  void Step();

  // Retruns object description as String
  String ToString();
};

// A decorator which allows task to run for finite ammount of cycles
class JobFiniteType : public JobType
{
private:
  unsigned int currentStep;
  unsigned int maxSteps;

public:
  // Param @maxSteps defines for how may loops/steps job is allowed to run
  JobFiniteType(unsigned int);

  // Retruns true when job is done
  bool Finished();
  // Returns true

  bool Allow();
  // Forwards internal parameters
  void Step();

  // Retruns object description as String
  String ToString();
};

// A decorator which allows tak to run for specified time
class JobTimeType : public JobType
{
private:
  unsigned int duration;
  unsigned long start;

public:
  // Param @duration defines for how long in milliseconds job is allowed to run
  JobTimeType(unsigned int);

  // Retruns true when job is done
  bool Finished();

  // Returns true
  bool Allow();

  // Does nothing
  void Step();

  // Retruns object description as String
  String ToString();
};

// A decorator which allows tak to run for specified time
class JobTimeIntervalType : public JobType
{
private:
  unsigned int interval;
  unsigned long lastTime;
  bool laggedTrigger;

public:
  // Param @interval defines interval of time in milliseconds after which job is allowed to run
  JobTimeIntervalType(unsigned int);

  // Retruns true when job is done
  bool Finished();

  // Retruns true when interval passes
  bool Allow();

  // Does nothing
  void Step();

  // Retruns object description as String
  String ToString();
};

// Interface which defines a task
class Job
{
public:
  virtual void Update() = 0;
  virtual void Start() = 0;
  virtual ~Job();

  // Retruns true when one of JobTypes are done
  virtual bool Finished();

  // Retruns true when all JobTypes allows task to run
  virtual bool Allow();

  // Setps all JobTypes
  virtual void Step();

protected:
  byte jobTypesAmmount;
  JobType **types;
};

#endif
