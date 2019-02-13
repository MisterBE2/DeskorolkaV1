#include "Buzzer.h"
#include "Core.h"

Buzzer::Buzzer(unsigned int *melody, byte *melodyDurations, byte melodyLength)
{
    Buzzer::melody = melody;
    Buzzer::melodyDurations = melodyDurations;
    Buzzer::melodyLength = melodyLength;
    Buzzer::currentNote = 0;
    Buzzer::isPause = false;
}

void Buzzer::Start()
{
    Buzzer::currentNote = 0;
    JobType *type[] = {new JobTimeType(1300 / Buzzer::melodyDurations[0])};
    Buzzer::types = type;
    Buzzer::jobTypesAmmount = 1;
    int noteDuration = 1000 / Buzzer::melodyDurations[0];
    tone(_PIN_BUZZER, Buzzer::melody[0], noteDuration);
}

void Buzzer::Update()
{
    // if (isPause)
    //     noTone(_PIN_BUZZER);
    // else
    //     tone(_PIN_BUZZER, Buzzer::melody[Buzzer::currentNote], (1000 / Buzzer::melodyDurations[Buzzer::currentNote]));
}

void Buzzer::Step()
{
    // Buzzer::isPause = !Buzzer::isPause;
    // if (!Buzzer::isPause)
    // {
    //     JobType *type[] = {new JobTimeType((1000 / Buzzer::melodyDurations[Buzzer::currentNote]) * 1.30)};
    //     Buzzer::types = type;
    // }
    // else if (Buzzer::currentNote < Buzzer::melodyLength)
    // {
    //     Buzzer::currentNote++;
    //     JobType *type[] = {new JobTimeType((1000 / Buzzer::melodyDurations[Buzzer::currentNote]))};
    //     Buzzer::types = type;
    // }
}

bool Buzzer::Finished()
{
    if (Buzzer::currentNote >= Buzzer::melodyLength)
        return true;

    return false;
}

bool Buzzer::Allow()
{
    if ((Job::Finished() && (Buzzer::currentNote <= Buzzer::melodyLength)) || Buzzer::currentNote == 0)
        return true;

    return false;
}