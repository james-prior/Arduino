//#include <Wire.h> 
#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7); // LCD Shield

const byte backLightpin = 5; 
const byte contrast_pin = 6;



void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  lcd.print("Hello World!");
  
}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.setCursor(0,1);
  lcd.print(millis() / 1000);
}
