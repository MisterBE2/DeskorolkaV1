#include "RF24.h"
#include "nRF24L01.h"

#ifndef CON_DEF
#define CON_DEF

enum _e_connectorRole {sender, reciver, transciver};

class Connector 
{
  public:
    Connector(byte, byte, _e_connectorRole);
    void Send(String);
    //String Recive();

  private:
    byte CN, CSN;
    RF24 con;
    _e_connectorRole role;
    const uint64_t pAddress = 0xB00B1E5000LL;
    void (*dataInOut)();
};


#endif