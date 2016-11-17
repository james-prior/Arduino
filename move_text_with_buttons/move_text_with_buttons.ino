//#include <Wire.h> 
#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7); // Create a new LiquidCrystal object and the arguments are:
//LiquidCrystal(rs, enable, d4, d5, d6, d7) 
//rs: the number of the Arduino pin that is connected to the RS pin on the LCD
//enable: the number of the Arduino pin that is connected to the enable pin on the LCD
//d0, d1, d2, d3, d4, d5, d6, d7: the numbers of the Arduino pins that are connected to
//the corresponding data pins on the LCD. d0, d1, d2, and d3 are optional; if omitted, 
//the LCD will be controlled using only the four data lines (d4, d5, d6, d7).


const byte backLightpin = 5; 
const byte contrast_pin = 6;
byte column = 0;
byte row = 0;
  int i = 0;
  String words[] = {"Hello", "Goodbye", "The Lost", "Wayne's", "What"};

/*-----( Declare Constants )-----*/
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

/*-----( Declare Variables )-----*/
int lcd_key       = 0;
int adc_key_in    = 0;
int adc_key_prev  = 0;

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  lcd.setCursor(column,row);

  lcd.print(words[i] + " World!");
}

void loop() {

  //set a timer to slow down my loop and check for same analog value 3x to confirm button press.
  // put your main code here, to run repeatedly:

  adc_key_prev = lcd_key ;       // Looking for changes
  lcd_key = read_LCD_buttons();  // read the buttons

  if (adc_key_prev != lcd_key)
  {
    lcd.clear();
    lcd.setCursor(column,row); 
    lcd.print(words[i] + " World!");         // Blank, display returned Analog value of button 
  }

switch (lcd_key)               // depending on which button was pushed, we perform an action
  {
  case btnRIGHT:
    {
      column++;
      delay(200);
      break;
    }
  case btnLEFT:
    {
      column--;
      delay(200);
      break;
    }
  case btnUP:
    {
      row = 0;
      break;
    }
  case btnDOWN:
    {
      row = 1;
      break;
    }
  case btnSELECT:
    {
      if (i < 4) {
        i++;
      }
      else {
        i = 0;
      }
      delay(200);
      break;
    }
  }/* --(end switch )-- */

}

int read_LCD_buttons()
{
  adc_key_in = analogRead(0);      // read the value from the sensor 
  delay(15); //switch debounce delay. Increase this delay if incorrect switch selections are returned.
  int k = (analogRead(0) - adc_key_in); //gives the button a slight range to allow for a little contact resistance noise
  if (5 < abs(k)) return btnNONE;  // double checks the keypress. If the two readings are not equal +/-k value after debounce delay, it tries again.
  // my buttons when read are centered at these valies: 0, 144, 329, 504, 741
  // we add approx 50 to those values and check to see if we are close
  if (adc_key_in > 1000) return btnNONE; // We make this the 1st option for speed reasons since it will be the most likely result
  if (adc_key_in < 50)   return btnRIGHT;  
  if (adc_key_in < 195)  return btnUP; 
  if (adc_key_in < 380)  return btnDOWN; 
  if (adc_key_in < 555)  return btnLEFT; 
  if (adc_key_in < 790)  return btnSELECT;   
  return btnNONE;  // when all others fail, return this...
}
