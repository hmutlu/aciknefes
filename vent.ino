/*
  LiquidCrystal Library - Hello World

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch prints "Hello World!" to the LCD
 and shows the time.

  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystal
 */

// include the library code:
#include <LiquidCrystal.h>
#include <Stepper.h>


// initialize the LiquidCrystal library with the numbers of the interface pins
// RS, E, D4, D5, D6, D7
LiquidCrystal lcd(12, 11, 10, 9, 8, 7);
int bmp = 12;
int bmp_min = 12;
int bmp_max = 26;
const int bmp_pin = 2;
int ieratio = 2;
int ieratio_min = 1;
int ieration_max = 4;
const int ieration_pin = 3;
const int alarm_pin = 6;
const int sensor_trigPin = 4;
const int sensor_echoPin = 3;
bool alarm_armed = true;
const int alarm_reset_pin = A0;
long int alarm_ack_time = millis();
int alarm_wait_time_msec = 5000;
long int last_time_show_pressure = millis();
int show_pressure_and_thr_switch = 2000;
bool show_pressure = true;
long int last_time_rotate_in_one_direction = millis();
int rotate_time_in_one_direction = 4000;
int rotDirection = 0;

#define enA 5
#define in1 4
#define in2 3





void setup() {
 
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("BMP=");
  lcd.print(bmp);
  lcd.setCursor(8, 0);
  lcd.print("I/E=1:");
  lcd.print(ieratio);
  lcd.setCursor(0, 1);
  lcd.print("TD=0");
  lcd.setCursor(8, 1);
  lcd.print("TH=0");

  pinMode(alarm_reset_pin, INPUT);
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  rotDirection = 0;

}

void loop() {


  int bmp_pot_read = analogRead(bmp_pin);

  //motor speed
  int pwmOutput = map(bmp_pot_read, 0, 1023, 0 , 255);
  analogWrite(enA, pwmOutput);




  // Calculate BMP
  bmp = 12 + max(0,bmp_pot_read - 20)/64;

  if(bmp>25 && alarm_armed)
  {
    tone(alarm_pin, 500);
  } else
  {
    noTone(alarm_pin);
  }

  if (digitalRead(alarm_reset_pin) == HIGH)
  {
    alarm_armed = false;
    alarm_ack_time = millis();
  }

  if (millis() - alarm_ack_time > alarm_wait_time_msec)
  {
    alarm_armed = true;
  }
  

   
  // Print current values to the LCD.
  lcd.setCursor(0, 0);
  lcd.print("BMP=");
  lcd.print(bmp);
  lcd.setCursor(8, 0);
  lcd.print("I/E=1:");
  lcd.print(ieratio);
  lcd.setCursor(0, 1);
  lcd.print("TD=0");
  lcd.setCursor(8, 1);

  if ((millis() - last_time_show_pressure) > show_pressure_and_thr_switch )
  {

    last_time_show_pressure =  millis();
    
    if(show_pressure)
         show_pressure = false;
    else  
         show_pressure = true; 
  }
    
  if(show_pressure)
    lcd.print("Press");
  else
    lcd.print("TH=0 ");
  


    // If button is pressed - change rotation direction
  if ((millis() - last_time_rotate_in_one_direction) > rotate_time_in_one_direction ) 
  {
     
    last_time_rotate_in_one_direction =  millis();
    if(rotDirection == 1)
    {
        rotDirection = 0;
        delay(20);
    }
    else
    {
        rotDirection = 1;
        delay(20); 
    } 

  }

  if(rotDirection == 1)
    {
        digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
    }
    else
    {

        digitalWrite(in1, HIGH);
       digitalWrite(in2, LOW);
      
    }

  }

 


 
