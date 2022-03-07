#include<SPI.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

void display_data();

LiquidCrystal_I2C lcd(0x27,20,4);
volatile boolean received;
volatile char slaveReceive, slaveSend;
int greenStatus = 0, yellowStatus = 0;

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
  lcd.print("test");
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

      display_data();
}

void display_data()
{
  lcd.setCursor(0, 0);
  if (slaveReceive == 1)
    lcd.print("Green!");
  else if (slaveReceive == 2)
    lcd.print("Yellow!");
}
