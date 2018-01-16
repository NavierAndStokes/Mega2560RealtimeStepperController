// THis sketch first waits for any 1 byte start signal, and sends the signal back.
// The sketch then waits for at least 6 bytes of binary data and replies with the data in string form

byte inByte = 0;         // incoming serial byte

void setup()
{
  // start serial port at 9600 bps:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  establishContact();  // send a byte to establish contact until receiver responds
}

void loop()
{
  // if we get 6 bytes, read them
  if (Serial.available() >= 6) {
    // get incoming byte:
    for(int i = 0; i<6; i++)
    {
      inByte = Serial.read();
      Serial.print(inByte);
      Serial.print(' ');
    }
    Serial.println();
  }
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
