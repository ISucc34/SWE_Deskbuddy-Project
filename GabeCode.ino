#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT11.h>
#include <Servo.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
DHT11 dht11(2); // DHT11 on D2

// Declare servos
Servo servo1; // First servo (e.g., left leg)
Servo servo2; // Second servo (e.g., right leg)

void setup() {
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);

  // Attach servos
  servo1.attach(A1); // Servo 1 on A1
  servo2.attach(10); // Servo 2 on D10

  // Set initial servo positions
  servo1.write(90); // Center position
  servo2.write(90);

  lcd.setCursor(0, 0);
  lcd.print("TARS Online");
}

void loop() {
  int temperature = 0;
  int humidity = 0;
  int result = dht11.readTemperatureHumidity(temperature, humidity);

  if (result == 0) {
    // Serial output for debugging
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print(" °C\tHumidity: ");
    Serial.print(humidity);
    Serial.println(" %");

    // Display on LCD
    lcd.setCursor(0, 1); // Second line
    lcd.print("T:"); // Temperature label
    lcd.print(temperature);
    lcd.print("C H:"); // Humidity label
    lcd.print(humidity);
    lcd.print("%  "); // Clear extra characters

    // Servo movement based on temperature (placeholder for walking)
    if (temperature > 30) { // If hot, move servos
      servo1.write(120); // Simulate step
      servo2.write(60);
      delay(500);
      servo1.write(90); // Return to center
      servo2.write(90);
    }
  } else {
    Serial.println(DHT11::getErrorString(result));
    lcd.setCursor(0, 1);
    lcd.print("Sensor Error ");
  }

  delay(2000); // Delay for readability
}
