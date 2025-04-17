#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT11.h>


LiquidCrystal_I2C lcd(0x27, 16, 2);  



DHT11 dht11(2); // pin into d2 (out)

void setup() {
  lcd.init(); //SDA is pin a4. SCL in pin a5. VCC is 5v, GND is ground
  lcd.backlight();  // Turn on the backlight
  lcd.setCursor(0, 0);
  lcd.print("Hello, LCD12C!");
}

void loop() {
  // Nothing here

  int temperature = 0;
  int humidity = 0;
  int result = dht11.readTemperatureHumidity(temperature, humidity);

if (result == 0) {
        Serial.print("Temperature: ");
        Serial.print(temperature);
        Serial.print(" °C\tHumidity: ");
        Serial.print(humidity);
        Serial.println(" %");

        lcd.print(humidity);

    } 
    else {
        // Print error message based on the error code.
        Serial.println(DHT11::getErrorString(result));
    }
}