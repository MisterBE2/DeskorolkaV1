#include "Connector.h"
#include "RF24.h"
#include "nRF24L01.h"
#include <SPI.h>
#include <avr/sleep.h>

Connector::Connector(byte CN, byte CSN, _e_connectorRole role, )
{
    Connector::con = new RF24(CN, CSN);
    Connector::role = role;
    Connector::con.begin();                            //Start the nRF24 module
    Connector::con.setAutoAck(1);                      // Ensure autoACK is enabled so rec sends ack packet to let you know it got the transmit packet payload
    Connector::con.enableAckPayload();                 //allows you to include payload on ack packet
    Connector::con.maskIRQ(1, 1, 0);                   //mask all IRQ triggers except for receive (1 is mask, 0 is no mask)
    Connector::con.setPALevel(RF24_PA_LOW);            //Set power level to low, won't work well at higher levels (interfer with receiver)
    Connector::con.openReadingPipe(1, Connector::pAddress);       //open pipe o for recieving meassages with pipe address
    Connector::con.startListening();                   // Start listening for messages
    attachInterrupt(1, interruptFunction, FALLING);    //Create interrupt: 0 for pin 2 or 1 for pin 3, the name of the interrupt function or ISR, and condition to trigger interrupt
}

void Connector::Send(String data)
{
}
