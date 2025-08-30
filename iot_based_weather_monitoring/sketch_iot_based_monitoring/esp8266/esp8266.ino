#include "ThingSpeak.h"
#include <ESP8266WiFi.h>

//-------  WI-FI details ----------//
char ssid[] = "Haider"; // SSID here
char pass[]  = "786786786"; // Password here
//--------------------------------//

//-----------  Channel details ----------------//
unsigned long Channel_ID = 2890263; // Your Channel ID
const char * myWriteAPIKey = "YI4513NI3MM5G73U"; //Your write API key
//-------------------------------------------//

const int Field_Humidity = 1;
const int Field_DHT_Temp = 2;
const int Field_BMP_Temp = 3;
const int Field_Pressure = 4;
const int Field_Altitude = 5;
const int Field_Rain = 6;

WiFiClient client;

float humidity = 0;
float dhtTemp = 0;
float bmpTemp = 0;
float pressure = 0;
float altitude = 0;
int rainValue = 0;

void setup()
{
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client); 
  client.connect("175.107.205.117", 80);
  connectWiFi();
}

void loop()
{
  connectWiFi(); // Ensure WiFi is connected
  
  if (Serial.available() > 0)
  {
    delay(100);
    while (Serial.available() > 0)
    {
      String receivedData = Serial.readStringUntil('\n'); // Read full serial line

      if (receivedData.startsWith("*") && receivedData.endsWith("#"))
      {
        receivedData.remove(0, 1); // Remove '*' at the start
        receivedData.remove(receivedData.length() - 1, 1); // Remove '#' at the end
        Serial.print("Raw Serial Data: ");
        Serial.println(receivedData);

        // Split values from received data
        sscanf(receivedData.c_str(), "%f,%f,%f,%f,%f,%d", &humidity, &dhtTemp, &bmpTemp, &pressure, &altitude, &rainValue);
        
        // Debugging output
        Serial.println("Received Data:");
        Serial.print("Humidity: "); Serial.println(humidity);
        Serial.print("DHT Temp: "); Serial.println(dhtTemp);
        Serial.print("BMP Temp: "); Serial.println(bmpTemp);
        Serial.print("Pressure: "); Serial.println(pressure);
        Serial.print("Altitude: "); Serial.println(altitude);
        Serial.print("Rain Sensor Value: "); Serial.println(rainValue);
      }
    }
  }

  uploadToThingSpeak();
}

void connectWiFi()
{
  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.print("Connecting to WiFi");
    WiFi.begin(ssid, pass);
    
    int retries = 20;
    while (WiFi.status() != WL_CONNECTED && retries-- > 0)
    {
      delay(1000);
      Serial.print(".");
    }
    
    if (WiFi.status() == WL_CONNECTED)
      Serial.println("\nWiFi Connected!");
    else
      Serial.println("\nWiFi Connection Failed!");
  }
}

void uploadToThingSpeak()
{
    if (!client.connect("175.107.205.117", 80)) {
    Serial.println("Failed to connect to ThingSpeak IP");
  }

  Serial.println("Uploading Data to ThingSpeak...");

  ThingSpeak.setField(Field_Humidity, humidity);
  ThingSpeak.setField(Field_DHT_Temp, dhtTemp);
  ThingSpeak.setField(Field_BMP_Temp, bmpTemp);
  ThingSpeak.setField(Field_Pressure, pressure);
  ThingSpeak.setField(Field_Altitude, altitude);
  ThingSpeak.setField(Field_Rain, rainValue);

  int response = ThingSpeak.writeFields(Channel_ID, myWriteAPIKey);

  if (response == 200)
    Serial.println("Upload Successful!");
  else {
    Serial.print("Upload Failed. HTTP Error Code: ");
    Serial.println(response);

    // Print the connection status too
    Serial.print("WiFi status: ");
    Serial.println(WiFi.status());
    Serial.print("Local IP: ");
    Serial.println(WiFi.localIP());
  }

  delay(15000);
}
