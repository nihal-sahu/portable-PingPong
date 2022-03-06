#include<SPI.h>

#define SS PA4


void setup (void)
{
Serial.begin(115200);
pinMode(SS, OUTPUT);
SPI.begin();
SPI.setClockDivider(SPI_CLOCK_DIV64);
digitalWrite(SS, HIGH);
}

void loop(void)
{
int masterSend, masterReceive;

masterSend = 55;

digitalWrite(SS, LOW);

masterReceive = SPI.transfer(masterSend);
Serial.println(masterReceive);
delay(100);

}
