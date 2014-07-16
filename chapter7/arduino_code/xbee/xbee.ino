// Code to measure data & make it accessible via 

// Libraries
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include "DHT.h"
#include <aREST.h>

// DHT sensor
#define DHTPIN 7 
#define DHTTYPE DHT11

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
  Serial.begin(9600);
  
  // Expose variables to REST API
  rest.variable("temperature",&temperature);
  rest.variable("humidity",&humidity);
  rest.variable("light",&light);
  
  // Set device name & ID
  rest.set_id("1");
  rest.set_name("weather_station");

  // Init DHT
  dht.begin();
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
  
}
