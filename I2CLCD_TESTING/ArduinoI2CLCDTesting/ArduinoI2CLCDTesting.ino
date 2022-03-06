#include<SPI.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);
volatile boolean received;
volatile char slaveReceive, slaveSend;

void setup()
{
  Serial.begin(9600);

  pinMode(MISO, OUTPUT);
  SPCR |= _BV(SPE);
  received = false;
  SPI.attachInterrupt();
  
  //lcd setup
  lcd.init();
  lcd.backlight();
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
  
  lcd.setCursor(0, 0);
  lcd.print("Data: ");
  
  if(received == true)
  {
    Serial.println(int(slaveReceive));
    lcd.print(int(slaveReceive));
    delay(250);
    received = false;
}
}
