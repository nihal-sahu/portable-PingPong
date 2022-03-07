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
  lcd.clear();
  lcd.setCursor(0, 0);
  
  if (slaveReceive == 0)
    lcd.print("Press the blue button to start.");
  else if (slaveReceive == 1)
    lcd.print("Green is in the lead!");
  else if (slaveReceive == 2)
    lcd.print("Yellow is in the lead!");
  else if (slaveReceive == 3)
    lcd.print("Yellow gained a point!");
  else if (slaveReceive == 4)
    lcd.print("Green gained a point!");
  else if (slaveReceive == 5)
    lcd.print("Game over! Press black button to restart");
  else if (slaveReceive == 6)
    lcd.print("Score is tied.");

  lcd.scrollDisplayRight();
}
