#include<LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);  // sets the interfacing pins

void setup()
{
  lcd.begin(16, 2);  // initializes the 16x2 LCD
  lcd.print("hello! world");
}



void loop()
{
  lcd.print("hello! world");
  delay(100);
}
