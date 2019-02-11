#include "Job.h"
#include "Arduino.h"

#ifndef SOMETHING_DEF
#define SOMETHING_DEF

class Something : public Job
{
  private:
    byte jobId;

  public:
    Something(byte, JobType**, byte jobTypesAmmount);
    virtual ~Something();
    void Update();
    void Start();
};

#endif
