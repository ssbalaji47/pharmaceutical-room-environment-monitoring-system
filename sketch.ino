#include <DHT.h>
#include <LiquidCrystal_I2C.h>

#define DHT_PIN 8 // Pin to which DHT22 sensor is connected
#define BUZZER_PIN 7 // Pin to which the buzzer is connected
#define DHT_TYPE DHT22 // Change to DHT11 if using DHT11 sensor
DHT dht(DHT_PIN, DHT_TYPE);

// Initialize the LCD with the I2C address (0x27 or 0x3F)
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Address, Columns, Rows

void setup() {
  lcd.begin(16, 2); // Initialize the LCD with 16 columns and 2 rows
  dht.begin(); // Initialize the DHT sensor
  lcd.backlight(); 
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(9, OUTPUT);//red led
  pinMode(10, OUTPUT);//Green led
  
  // Display initial labels on the LCD
  lcd.print("Temp:"); 
  lcd.setCursor(0, 1);
  lcd.print("Humidity:");
}

void loop() {
  // Read temperature and humidity from DHT sensor
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  
  // Display the readings on the LCD
  lcd.setCursor(6, 0);
  lcd.print(temperature, 1);
  lcd.print("C");
  lcd.setCursor(9, 1);
  lcd.print(humidity, 1);
  lcd.print("%");

  // Check if humidity is within the desired range
  if (humidity > 15.0 && humidity <= 25.0 ) {
    digitalWrite(BUZZER_PIN, LOW);
  } else {
    digitalWrite(BUZZER_PIN, HIGH);
  }

  // Check if temperature is within the desired range
  if (temperature > 15.0 && temperature <= 25.0 ) {
    digitalWrite(10, HIGH);
    digitalWrite(9, LOW);
  } else {
    digitalWrite(10, LOW);
    digitalWrite(9, HIGH);
  }

  delay(2000); // Delay to avoid overloading the display
}

