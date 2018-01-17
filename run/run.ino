//usage:
//put all files in the same sketch folder, include the following files
#include "circularbuffer.h"
#include "pinout.h"
#include "stepperservice.h"

//PORTS F, K AND A ARE USED FOR THE PULSES,
//PORTS C, L, AND H ARE USED FOR THE DIRECTIONS

/*The buffer can hold up to 1000 output 6-byte datasets (can be modified within circularbuffer.h)
Outputs are executed at a rate of 3125 Hz as long as the buffer isn't empty, it first sets the directions, 
then waits 20 µs and writes the pulses, then waits another 20 µs to end the pulses, pulse durations, delays and frequencies can be set within (stepperservice.h)
*/

byte IncomingData[6]; // first 3 bytes for ports F, K, A (for pulses), last 3 bytes for ports C, L, H
uint8_t Counter = 100;
//within the setup function call:
void setup()
{
  setupOutputs();
  setupStepperService(); //Step execution starts automatically
    // start serial port at 230400 bps:
  Serial.begin(230400);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  establishContact();  // send a byte to establish contact until receiver responds
}


//within the main loop do:
void loop()
{
    // if we get 6 bytes, read them
  if (Serial.available() >= 6) {
    Counter++;
    // get incoming byte:
    for(int i = 0; i<6; i++)
    {
      IncomingData[i] = Serial.read();
      Serial.print(IncomingData[i]);
      Serial.print(' ');
    }
      //check if there is space in the buffer, and add the data to the buffer
      if(availableSpaceInCircularBuffer() > 0)
      {
        pushToCircularBuffer(IncomingData);
      }
<<<<<<< HEAD
    Serial.print("B");
    Serial.print(itemsInCircularBuffer());
    Serial.println();
//    if (Counter >= 100)
//    {
//      Counter = 0;
//      Serial.print("B");
//      Serial.print(itemsInCircularBuffer());
//      Serial.println();
//    }
=======
    //Send status after each 200 data parts
    if (Counter == 200)
    {
      Counter = 0;
      Serial.print('[');
      for(int i = 0; i<6; i++)
      {
        Serial.print(IncomingData[i]);
        if(i == 5) continue;
        Serial.print(", ");
      }
      Serial.print(']');
      Serial.print(" B");
      Serial.print(itemsInCircularBuffer());
      Serial.println();
    }
>>>>>>> upgraded to 3125Hz, mirror every 200th data point
  }
  // to check how many items remain in the executionbuffer use:
  //itemsInCircularBuffer();
  
  //To start/stop the stepper execution use:
  //enableStepperService()
  //disableStepperService()
}


void establishContact() {
  //Wait for start signal
  while (Serial.available() <= 0) {
    delay(300);
  }
  //Read the start signal
  char signal = Serial.read();
  //Reply
  Serial.write(signal);   // reply with signal
}

