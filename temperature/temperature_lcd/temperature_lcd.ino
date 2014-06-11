// Code to measure data & display it on the LCD screen

// Libraries
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include "DHT.h"

// DHT sensor
#define DHTPIN 7 
#define DHTTYPE DHT11

// LCD display instance
LiquidCrystal_I2C lcd(0x27,20,4); 

// DHT instance
DHT dht(DHTPIN, DHTTYPE);

void setup()
{
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
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  
  // Measure light level
  float sensor_reading = analogRead(A0);
  float light = sensor_reading/1024*100;
  
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
