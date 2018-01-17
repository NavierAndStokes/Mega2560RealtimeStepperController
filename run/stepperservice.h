#ifndef stepperservice_h
#define stepperservice_h
#include "pinout.h"
#include "circularbuffer.h"
#include "Arduino.h"

/**
USES TIMER 1 TO GENERATE PROCESS SETEPPING SIGNALS FROM A CRICULAR BUFFER, DATA MUST BE ADDED TO THE CIRCULAR BUFFER IN REAL TIME
*/

//TEMPORARY ARRAY FOR DATA TRANSFER
byte tmp[6];

void disableStepperService(){
TIMSK1 &= ~(1 << OCIE1A);
}

void enableStepperService(){
OCR1A = 250; // compare match register A for timer 1: 16MHz/64/1000Hz
TCNT1  = 0;  //Reset count variable to 0.
TIMSK1 |= (1 << OCIE1A); // enable timer compare interrupt  TCNTn will be compared to OCRnA
}

void setupStepperService(void) { //    PB4:7 become unavailable!.
  noInterrupts();           // disable all interrupts
  //See pag 154 in the datasheet and up for Timer descriptions:
  TCCR1A = 0; //clear control register A and B
  TCCR1B = 0;
  // TCCR1B |= (1 << WGM12);   // CTC mode (see pag 144 datasheet)
  TCCR1B = 0;  // Normal mode (In normal mode B and C compare are available, see pag 144-145 datasheet)
  TCCR1B |= (1 << CS11)|(1 << CS10);  // 64 prescaler  (see TCCRnB table in the datasheet) TABLE 17-6 page 157:
  enableStepperService();
  interrupts();             // enable all interrupts
}

//A Services: running @ 1000HZ
ISR(TIMER1_COMPA_vect)          // timer compare interrupt service routine
{
  //OCR1A = TCNT1 + 250; //1 ms  ->1000Hz
  OCR1A += 80; //0.32 ms  ->3125Hz
  //If there is anything in the buffer, push it into the pin outputs
  if(popFromCircularBuffer(tmp))
  {
	//SET THE DIRECTIONS:
	setDirections(tmp[0],tmp[1],tmp[2]);
	//SET B INTERRUPT TO START THE PULSES 20 µs INTO THE FUTURE
	OCR1B = TCNT1 + 5; //20 µs
	//ENABLE B INTERRUPT
	TIMSK1 |= (1 << OCIE1B);
  }
}

//B Services: USED TO START THE PULSES
ISR(TIMER1_COMPB_vect) {
	//DISABLE B INTERRUPT
	TIMSK1 &= ~(1 << OCIE1B);
    //CODE TO START THE PULSES
	startPulses(tmp[3],tmp[4],tmp[5]);
	//SET C INTERRUPT TO 20 µs INTO THE FUTURE
	OCR1C = TCNT1 + 5; //20 µs
	//ENABLE C INTERRUPT
	TIMSK1 |= (1 << OCIE1C);
}

//C Services: USED TO END THE PULSES
ISR(TIMER1_COMPC_vect) {
	//DISABLE C INTERRUPT
	TIMSK1 &= ~(1 << OCIE1C);
    //CODE TO END THE PULSES
	endPulses();
}

# endif
