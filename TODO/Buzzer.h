#include "Job.h"

#ifndef BUZZER_DEF
#define BUZZER_DEF

class Buzzer : public Job
{
  public:
    Buzzer(unsigned int *, byte *, byte);
    void Update();
    void Start();
    bool Finished();
    bool Allow();
    void Step();

  private:
    unsigned int *melody;
    byte *melodyDurations;
    byte melodyLength;
    byte currentNote;
    bool isPause;
};

#endif