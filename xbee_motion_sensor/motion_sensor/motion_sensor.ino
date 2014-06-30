// Libraries
#include <SPI.h>
#include <aREST.h>

// Motion sensor ID
String xbee_id = "1";

// Create ArduREST instance
aREST rest = aREST();

void setup() {
  
  // Start Serial
  Serial.begin(9600);
  
  // Give name and ID to device
  rest.set_id(xbee_id);
}

void loop() {
  
  // Handle REST calls
  rest.handle(Serial);
  
}
