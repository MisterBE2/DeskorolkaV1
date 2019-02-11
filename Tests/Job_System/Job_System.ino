#include "Job.h"
#include "Something.h"

Job *job;

void setup()
{
  Serial.begin(115200);
  Serial.println("------------Start------------");
  delay(3000);

  JobType *types[] = {new JobFiniteType(4)};
  job = new Something(0, types, 1);
  job->Start();
}

unsigned long loops = 0;

void loop()
{
  if (job->Finished())
  {
    Serial.println();
    Serial.print("[");
    Serial.print(0);
    Serial.println("] F");
    delete job;

    //jobs[i] = nullptr;

    JobType *types[] = {new JobFiniteType(3)};
    job = new Something(0, types, 1);
    job->Start();
    
    Serial.println();

    loops++;
    Serial.print("Loop: ");
    Serial.println(loops);
  }
  else
  {
    if (job->Allow())
    {
      job->Update();
      job->Step();
    }
  }
}
