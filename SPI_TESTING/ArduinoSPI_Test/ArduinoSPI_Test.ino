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
/* Value received from master STM32F103C8T6 is stored in variable slaveReceive */
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
