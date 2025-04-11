#include <LiquidCrystal.h>
#include <Servo.h>

int seconds = 0;
int p9= 9;

int p10 = 10;

int val;

Servo arm1;
Servo arm2;
LiquidCrystal lcd_1(12, 11, 5, 4, 3, 2);

void setup()
{
  pinMode(p9, OUTPUT);
  pinMode(p10,INPUT);
  lcd_1.begin(16, 2); // Set up the number of columns and rows on the LCD.
  arm1.attach(7);
  arm2.attach(8);
  // Print a message to the LCD.
  lcd_1.print("hello world!");
}

void loop()
{
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting
  // begins with 0):
  lcd_1.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd_1.print(seconds);
  
  val = digitalRead(p10);
  
  if (val==HIGH){
	digitalWrite(p9,HIGH);
  }
  else{
  digitalWrite(p9,LOW);
  }
  
  delay(1000); // Wait for 1000 millisecond(s)
  seconds += 1;
  
  forward();
  
  
}

void forward()
{
  arm1.write(180);
  arm2.write(180);
  
  arm1.write(0);
  arm2.write(0);
}

