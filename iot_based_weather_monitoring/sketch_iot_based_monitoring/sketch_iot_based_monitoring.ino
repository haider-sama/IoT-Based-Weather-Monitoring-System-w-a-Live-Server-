#include <Wire.h>                    
#include <LiquidCrystal_I2C.h>        
#include <dht.h>                      
#include <Adafruit_BMP085.h>         
#include <SoftwareSerial.h>

#define RED_LED_PIN 5      // Red LED pin (Failure)
#define YELLOW_LED_PIN 6   // Yellow LED pin (Caution)
#define GREEN_LED_PIN 7    // Green LED pin (OK)

#define DHTPIN 2                      // DHT11 sensor pin
#define RAIN_SENSOR_PIN A0             // Rain sensor pin

LiquidCrystal_I2C lcd(0x27, 16, 2);   // Initialize I2C LCD
dht DHT;                              // Create DHT object
Adafruit_BMP085 bmp;                  // Create BMP180 object

SoftwareSerial espSerial(5, 6);

float humidity;    
float temperature; 
float pressure;    
float altitude;    
int rainValue = 0;
String rainStatus = "No Rain";

// Define threshold values
float HUMIDITY_THRESHOLD = 85.0;    // Humidity threshold for warning
float TEMPERATURE_THRESHOLD = 35.0; // Temperature threshold for warning
float PRESSURE_THRESHOLD = 2980.0;   // Pressure threshold for warning (in hPa)
int RAIN_THRESHOLD = 2600;           // Rain sensor threshold for heavy rain

void setup() {
  Serial.begin(9600);   // Start Serial communication
  espSerial.begin(9600);
  Serial.println("Serial Communication Initialized");
  lcd.begin(16, 2);     // Initialize LCD
  lcd.backlight();      // Turn ON LCD backlight

  lcd.setCursor(1, 0);
  lcd.print("Hello!");
  lcd.setCursor(0, 1);
  lcd.print(" Weather Monitor ");
  delay(1000);
  lcd.clear();
  
  // Initialize BMP180 sensor
  if (!bmp.begin()) {
    Serial.println("BMP180 sensor not found!");
    lcd.setCursor(0, 0);
    lcd.print("BMP180 Error!");
    while (1);
  }

    // Initialize LED pins
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(YELLOW_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
}

void loop() {
  Serial.println("Loop Running...");
  delay(1000);
  // Read temperature and humidity from DHT11
  DHT.read11(DHTPIN);
  humidity = DHT.humidity;
  temperature = DHT.temperature;

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("DHT Sensor Error!");
    delay(1000);
    return;
  }

  // Read values from BMP180
  float bmpTemp = bmp.readTemperature();
  pressure = bmp.readPressure() / 100.0; // Convert to hPa
  altitude = bmp.readAltitude();  

  // Read rain sensor
  // Read analog value (0-1023)
   // Read and average rain sensor
  int rainSum = 0;
  for (int i = 0; i < 10; i++) {
    rainSum += analogRead(RAIN_SENSOR_PIN);
    delay(5);
  }
  rainValue = rainSum / 10;

    // Determine rain status
  if (rainValue > 600) {
    rainStatus = "No Rain";
  } else if (rainValue > 300) {
    rainStatus = "Light Rain";
  } else {
    rainStatus = "Heavy Rain";
  }

    // Check if any sensor value exceeds the threshold
  if (humidity > HUMIDITY_THRESHOLD || temperature > TEMPERATURE_THRESHOLD || pressure > PRESSURE_THRESHOLD || rainValue > RAIN_THRESHOLD) {
    // System in warning state or failure
    digitalWrite(RED_LED_PIN, HIGH);   // Turn on Red LED (Failure)
    digitalWrite(YELLOW_LED_PIN, LOW); // Turn off Yellow LED
    digitalWrite(GREEN_LED_PIN, LOW);  // Turn off Green LED
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Warning! Check System");
  }
  else if (rainValue > 300 || humidity > 60.0 || temperature > 30.0) {
    // System in caution state
    digitalWrite(RED_LED_PIN, LOW);    // Turn off Red LED
    digitalWrite(YELLOW_LED_PIN, HIGH); // Turn on Yellow LED (Caution)
    digitalWrite(GREEN_LED_PIN, LOW);  // Turn off Green LED
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Caution! Abnormal");
  } else {
    // System is OK
    digitalWrite(RED_LED_PIN, LOW);    // Turn off Red LED
    digitalWrite(YELLOW_LED_PIN, LOW); // Turn off Yellow LED
    digitalWrite(GREEN_LED_PIN, HIGH); // Turn on Green LED (OK)
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("System OK");
  }


  // Print values to Serial Monitor
  Serial.println("----- Weather Data -----");
  Serial.print("Humidity: "); Serial.println(humidity);
  Serial.print("DHT Temp: "); Serial.println(temperature);
  Serial.print("BMP180 Temp: "); Serial.println(bmpTemp);
  Serial.print("Pressure: "); Serial.println(pressure);
  Serial.print("Altitude: "); Serial.println(altitude);
  Serial.print("Rain Value: "); Serial.print(rainValue); Serial.print(" - "); Serial.println(rainStatus);
  Serial.println("----------------------------");

  // Display on LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Humidity: ");
  lcd.print(humidity);
  lcd.print(" %");
  delay(2000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("DHT Temp: ");
  lcd.print(temperature);
  lcd.print((char)223);
  lcd.print("C");
  delay(2000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("BMP Temp: ");
  lcd.print(bmpTemp);
  lcd.print((char)223);
  lcd.print("C");
  delay(2000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Pressure: ");
  lcd.print(pressure);
  lcd.print(" hPa");
  delay(2000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Altitude: ");
  lcd.print(altitude);
  lcd.print(" m");
  delay(2000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Rain: ");
  lcd.print(rainStatus);
  delay(2000);

  lcd.clear();
  delay(2000);

}
