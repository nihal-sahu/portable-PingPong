#include<SPI.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

void displayData();

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
  

  
  if(received == true)
  {
    Serial.println(int(slaveReceive));
    displayData();
    delay(250);
    received = false;
  }
}

void displayData()
{
  lcd.setCursor(0, 0);
  lcd.print("Data: ");
  lcd.print(int(slaveReceive));
}
