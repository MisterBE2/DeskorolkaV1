#include "Something.h"

Something::Something(byte jobId, JobType ** types, byte jobTypesAmmount)
{
  Something::jobId = jobId;
  Something::types = types;
  Something::jobTypesAmmount = jobTypesAmmount;
  Serial.print("[");
  Serial.print(Something::jobId);
  Serial.print("] sc, ");
}

Something::~Something()
{
  Serial.print("[");
  Serial.print(Something::jobId);
  Serial.print("] sd, ");
}

void Something::Update()
{
  Serial.print("[");
  Serial.print(Something::jobId);
  Serial.print("] su, ");
}

void Something::Start()
{
  Serial.print("[");
  Serial.print(Something::jobId);
  Serial.print("] ss, ");
}
