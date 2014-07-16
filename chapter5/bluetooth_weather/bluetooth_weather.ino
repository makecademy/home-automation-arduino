// Code to measure data & make it accessible via 

// Libraries
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include "DHT.h"
#include <aREST.h>

// DHT sensor
#define DHTPIN 7 
#define DHTTYPE DHT11

// LCD display instance
LiquidCrystal_I2C lcd(0x27,20,4); 

// DHT instance
DHT dht(DHTPIN, DHTTYPE);

// Create aREST instance
aREST rest = aREST();

// Variables to be exposed to the API
int temperature;
int humidity;
int light;

void setup()
{
  // Start Serial
  Serial.begin(115200);
  
  // Expose variables to REST API
  rest.variable("temperature",&temperature);
  rest.variable("humidity",&humidity);
  rest.variable("light",&light);
  
  // Set device name & ID
  rest.set_id("1");
  rest.set_name("weather_station");
  
  // Initialize the lcd 
  lcd.init();
  
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(1,0);
  lcd.print("Hello !");
  lcd.setCursor(1,1);
  lcd.print("Initializing ...");
  
  // Init DHT
  dht.begin();
  
  // Clear LCD
  delay(2000);
  lcd.clear();
}


void loop()
{
  
  // Measure from DHT
  temperature = (int)dht.readTemperature();
  humidity = (int)dht.readHumidity();
  
  // Measure light level
  float sensor_reading = analogRead(A0);
  light = (int)(sensor_reading/1024*100);
  
  // Handle REST calls
  rest.handle(Serial);
  
  // Display temperature
  lcd.setCursor(1,0);
  lcd.print("Temperature: ");
  lcd.print((int)temperature);
  lcd.print((char)223);
  lcd.print("C");
  
   // Display humidity
  lcd.setCursor(1,1);
  lcd.print("Humidity: ");
  lcd.print(humidity);
  lcd.print("%");
  
   // Display light level
  lcd.setCursor(1,2);
  lcd.print("Light: ");
  lcd.print(light);
  lcd.print("%");
  
  // Wait 100 ms
  delay(100);
  
}
