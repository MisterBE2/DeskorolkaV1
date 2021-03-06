#include "Core.h"
#include "Job.h"
#include "Toggle.h"

Job *job;

void setup()
{
    Serial.begin(115200);
    Serial.println("Start");

    job = new Toggle(_PIN_LED, step, duration, 10);
    job->Start();
    Serial.println("End Start");
}

void loop()
{
    if (job != nullptr)
    {
        if (job->Finished())
        {
            delete job;
            job = nullptr;
            Serial.println("Finished");
        }
        else if (job->Allow())
        {
            Serial.println("Update");
            job->Update();
            job->Step();
        }
    }
}