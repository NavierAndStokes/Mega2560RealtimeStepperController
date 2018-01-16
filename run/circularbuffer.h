#ifndef circularbuffer_h
#define circularbuffer_h
#define BUFFER_SIZE 1000
#include "Arduino.h"

byte CircularBuffer[BUFFER_SIZE][6];
volatile unsigned int IndexStart = 0;
volatile unsigned int IndexEnd = 0;
volatile unsigned int NbItemsInBuffer = 0;

inline unsigned int itemsInCircularBuffer(void)
{
	return NbItemsInBuffer;
}
//RETURN HOW MANY SPACES ARE IN THE 
inline unsigned int availableSpaceInCircularBuffer(void)
{
	return BUFFER_SIZE - NbItemsInBuffer;
}

inline void advanceEndIndex()
{
	if(IndexEnd == BUFFER_SIZE)
	{
		IndexEnd = 0;
	}
	else
	{
		IndexEnd++;
	}
}

inline void advanceStartIndex()
{
	if(IndexStart == BUFFER_SIZE)
	{
		IndexStart = 0;
	}
	else
	{
		IndexStart++;
	}
}

inline bool pushToCircularBuffer(byte the6Bytes[])
{
	if(NbItemsInBuffer < BUFFER_SIZE)
	{
		CircularBuffer[IndexEnd][0] = the6Bytes[0];
		CircularBuffer[IndexEnd][1] = the6Bytes[1];
		CircularBuffer[IndexEnd][2] = the6Bytes[2];
		CircularBuffer[IndexEnd][3] = the6Bytes[3];
		CircularBuffer[IndexEnd][4] = the6Bytes[4];
		CircularBuffer[IndexEnd][5] = the6Bytes[5];
		advanceEndIndex();
		NbItemsInBuffer++;
		return true;
	}
	else
	{
		return false;
	}
}

inline bool popFromCircularBuffer(byte the6Bytes[])
{
	if(NbItemsInBuffer)
	{
		the6Bytes[0] = CircularBuffer[IndexStart][0];
		the6Bytes[1] = CircularBuffer[IndexStart][1];
		the6Bytes[2] = CircularBuffer[IndexStart][2];
		the6Bytes[3] = CircularBuffer[IndexStart][3];
		the6Bytes[4] = CircularBuffer[IndexStart][4];
		the6Bytes[5] = CircularBuffer[IndexStart][5];
		advanceStartIndex();
		NbItemsInBuffer--;
		return true;
	}
	else
	{
		return false;
	}
}


#endif
