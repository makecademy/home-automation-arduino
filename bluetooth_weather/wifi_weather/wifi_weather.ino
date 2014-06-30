// Code to measure data & display it on the LCD screen

// Libraries
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include "DHT.h"
#include <Adafruit_CC3000.h>
#include <SPI.h>
#include <CC3000_MDNS.h>
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

// These are the pins for the CC3000 chip if you are using a breakout board
#define ADAFRUIT_CC3000_IRQ   3
#define ADAFRUIT_CC3000_VBAT  5
#define ADAFRUIT_CC3000_CS    10

// Create CC3000 instance
Adafruit_CC3000 cc3000 = Adafruit_CC3000(ADAFRUIT_CC3000_CS, ADAFRUIT_CC3000_IRQ, ADAFRUIT_CC3000_VBAT,
                                         SPI_CLOCK_DIV2);

// Your WiFi SSID and password                                         
#define WLAN_SSID       "KrakowskiePrzedm51m.15(flat15)"
#define WLAN_PASS       "KrK51flat15_1944_15"
#define WLAN_SECURITY   WLAN_SEC_WPA2

// The port to listen for incoming TCP connections 
#define LISTEN_PORT           80

// Server instance
Adafruit_CC3000_Server restServer(LISTEN_PORT);

// DNS responder instance
MDNSResponder mdns;

// Variables to be exposed to the API
int temperature;
int humidity;
int light;

void setup()
{
  // Expose variables to REST API
  rest.variable("temperature",&temperature);
  rest.variable("humidity",&humidity);
  rest.variable("light",&light);
  
  // Initialize the lcd 
  lcd.init();
  lcd.backlight();
  
  // Init DHT
  dht.begin();
  
  // Set up CC3000 and get connected to the wireless network.
  if (!cc3000.begin())
  {
    while(1);
  }
  
  if (!cc3000.connectToAP(WLAN_SSID, WLAN_PASS, WLAN_SECURITY)) {
    while(1);
  }
  while (!cc3000.checkDHCP())
  {
    delay(100);
  }
  
  // Start multicast DNS responder
  if (!mdns.begin("arduino", cc3000)) {
    while(1); 
  }
   
  // Start server
  restServer.begin();
}


void loop()
{
  
  // Measure from DHT
  temperature = (int)dht.readTemperature();
  humidity = (int)dht.readHumidity();
  
  // Measure light level
  float sensor_reading = analogRead(A0);
  light = (int)(sensor_reading/1024*100);
  
  // Handle any multicast DNS requests
  mdns.update();
  
  // Handle REST calls
  Adafruit_CC3000_ClientRef client = restServer.available();
  rest.handle(client);
  
  // Display temperature
  print_lcd("Temperature :", temperature, 0);
  
   // Display humidity
  print_lcd("Humidity :", humidity, 1);
  
   // Display light level
  print_lcd("Light", light, 2);
  
}

void print_lcd(String name, int value, int line) {
  lcd.setCursor(1,line);
  lcd.print(name);
  lcd.print(value);
}
