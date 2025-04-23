#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT11.h>
#include <Servo.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo myservo;

int D = 6;
DHT11 dht11(2); // pin into d2 (out)

void setup() {
  lcd.init(); //SDA is pin a4. SCL in pin a5. VCC is 5v, GND is ground
  lcd.backlight();  // Turn on the backlight
  lcd.setCursor(0, 0);
  lcd.print("Hello, LCD12C!");
  pinMode(D, INPUT);
  myservo.attach(A1);
  lcd.clear();
  Serial.begin(9600); // NEW: Initialize serial for Python communication
}

void loop() {
  int temperature = 0;
  int humidity = 0;
  int result = dht11.readTemperatureHumidity(temperature, humidity);
  myservo.write(humidity);
  lcd.setCursor(0, 0);
  //lcd.println(humidity);

  // NEW: Handle serial input from Python
  String incomingWord = "";
  while (Serial.available() > 0) {
    char inChar = Serial.read();
    if (inChar != '\n') {
      incomingWord += inChar;
    } else {
      lcd.setCursor(0, 1); // Second line
      lcd.print("                "); // Clear line
      lcd.setCursor(0, 1);
      lcd.print(incomingWord.substring(0, 16)); // Display up to 16 chars
    }
  }
}