#include<SPI.h>



volatile boolean received;
volatile char slaveReceive, slaveSend;

void setup()
{
Serial.begin(9600);
pinMode(MISO, OUTPUT);


SPCR |= _BV(SPE);
received = false;

SPI.attachInterrupt();
}

/* SPI ISR */
ISR (SPI_STC_vect)
{
slaveReceive = SPDR;
received = true;
}

void loop()
{
slaveSend = 65;

SPDR = slaveSend;

if(received == true)
{
  Serial.println(int(slaveReceive));
  delay(250);
  received = false;
}
}
