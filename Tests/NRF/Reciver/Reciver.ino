#include <SPI.h> //Call SPI library so you can communicate with the nRF24L01+
#include <nRF24L01.h> //nRF2401 libarary found at https://github.com/tmrh20/RF24/
#include <RF24.h> //nRF2401 libarary found at https://github.com/tmrh20/RF24/

const int pinCE = 6; //This pin is used to set the nRF24 to standby (0) or active mode (1)
const int pinCSN = 7; //This pin is used to tell the nRF24 whether the SPI communication is a command or message to send out
int gotByte = 0; //used to store payload from transmit module
volatile int count = 0; //tracks the number of interrupts from IRQ
int pCount = 0; //tracks what last count value was so know when count has been updated
RF24 wirelessSPI(pinCE, pinCSN); // Declare object from nRF24 library (Create your wireless SPI)
const uint64_t pAddress = 0xB00B1E5000LL;  //Create a pipe addresses for the 2 nodes to communicate over, the "LL" is for LongLong type

void setup()   {
  Serial.begin(115200);
  Serial.println("Hello!");
  delay(5000);

  wirelessSPI.begin();  //Start the nRF24 module
  // Ensure autoACK is enabled so rec sends ack packet to let you know it got the transmit packet payload
  //allows you to include payload on ack packet
  wirelessSPI.maskIRQ(1, 1, 0);             //mask all IRQ triggers except for receive (1 is mask, 0 is no mask)
  wirelessSPI.setPALevel(RF24_PA_LOW); //Set power level to low, won't work well at higher levels (interfer with receiver)
  wirelessSPI.openReadingPipe(1, pAddress);     //open pipe o for recieving meassages with pipe address
  wirelessSPI.startListening();                 // Start listening for messages
  attachInterrupt(1, interruptFunction, FALLING);  //Create interrupt: 0 for pin 2 or 1 for pin 3, the name of the interrupt function or ISR, and condition to trigger interrupt
}

void loop() {
}

//This is the function called when the interrupt occurs (pin 2 goes high)
//this is often referred to as the interrupt service routine or ISR
//This cannot take any input arguments or return anything
void interruptFunction() {
  int val;
  if (wirelessSPI.available())
  {
    wirelessSPI.read( &val, sizeof(val) );
    Serial.println(val);
  }

}
