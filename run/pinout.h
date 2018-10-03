#ifndef pinout_h
#define pinout_h

//PORTS F, K, A WILL BE USED FOR STEPPING THE MOTORS
void setupOutputs(void)
{
	//SET PORTS F, K, A, C, L, H AS OUTPUTS
	DDRF  = 0xFF;
	DDRK  = 0xFF;
	DDRA  = 0xFF;

	DDRC  = 0xFF;
	DDRL  = 0xFF;
	DDRH  = 0xFF;

	//WRITE 0 TO ALL OUTPUTS
	PORTF  = 0x00;
	PORTK  = 0x00;
	PORTA  = 0x00;

	PORTC  = 0x00;
	PORTL  = 0x00;
	PORTH  = 0x00;
}

inline void endPulses(void)
{
	PORTF  = 0x00;
	PORTK  = 0x00;
	PORTA  = 0x00;
}

inline void startPulses(const byte& portF, const byte& portK, const byte& portA)
{
	PORTF = portF;
	PORTK = portK;
	PORTA = portA;
}

inline void setDirections(const byte& portC, const byte& portL, const byte& portH)
{
	PORTC = portC;
	PORTL = portL;
	PORTH = portH;
}

# endif
