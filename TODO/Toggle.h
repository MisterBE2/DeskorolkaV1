#include "Job.h"
#ifndef TOGGLE_DEF
#define TOGGLE_DEF

class Toggle : public Job
{
  public:
    Toggle(byte, bool *, unsigned int *, byte);
    void Start();
    void Update();
    bool Finnished();
    void Step();
    bool Allow();

  private:
    unsigned int currentStep;
    bool *step;
    unsigned int *duration;
    byte length;
    byte pin;
};

#endif