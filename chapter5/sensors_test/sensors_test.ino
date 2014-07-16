// Code to measure data and print it on the Serial monitor

// Libraries
#include "DHT.h"

// DHT sensor
#define DHTPIN 7 
#define DHTTYPE DHT11

// DHT instance
DHT dht(DHTPIN, DHTTYPE);

void setup()
{
  // Initialize the Serial port
  Serial.begin(9600);
  
  // Init DHT
  dht.begin();
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
  Serial.print("Temperature: ");
  Serial.print((int)temperature);
  Serial.println(" C");
  
   // Display humidity
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println("%");
  
  // Display light level
  Serial.print("Light: ");
  Serial.print(light);
  Serial.println("%");
  Serial.println("");
  
  // Wait 500 ms
  delay(500);
  
}
