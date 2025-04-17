#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT11.h>
#include <Servo.h> // Add Servo library

LiquidCrystal_I2C lcd(0x27, 16, 2);
DHT11 dht11(2); // Pin D2 for DHT11

// Declare two servos
Servo servo1; // For one leg
Servo servo2; // For the other leg

void setup() {
  lcd.init();
  lcd.backlight();
  Serial.begin(9600); // Already used for DHT11 debugging, also for Python later

  // Attach servos to pins
  servo1.attach(9); // Pin D9 for Servo 1
  servo2.attach(10); // Pin D10 for Servo 2

  // Initial servo positions
  servo1.write(90); // Center position (0-180 degrees)
  servo2.write(90);

  lcd.setCursor(0, 0);
  lcd.print("TARS Online");
}

void loop() {
  int temperature = 0;
  int humidity = 0;
  int result = dht11.readTemperatureHumidity(temperature, humidity);

  if (result == 0) {
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print(" °C\tHumidity: ");
    Serial.print(humidity);
    Serial.println(" %");

    // Display humidity on LCD
    lcd.setCursor(0, 1);
    lcd.print("Hum: ");
    lcd.print(humidity);
    lcd.print("%    "); // Clear extra characters

    // Move servos based on temperature (example logic)
    if (temperature > 30) { // If too hot, "react"
      servo1.write(120); // Move one leg
      servo2.write(60);  // Move other leg (opposite direction)
      delay(500); // Hold position briefly
      servo1.write(90); // Return to center
      servo2.write(90);
    }
  } else {
    Serial.println(DHT11::getErrorString(result));
    lcd.setCursor(0, 1);
    lcd.print("Sensor Error ");
  }

  delay(2000); // Slow down loop for readability
}
