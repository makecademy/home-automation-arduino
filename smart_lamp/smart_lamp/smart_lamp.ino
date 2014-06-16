// Code for the smart lamp project

// Libraries
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Relay state
const int relay_pin = 8;
boolean relay_state = false;

// LCD display instance
LiquidCrystal_I2C lcd(0x27,20,4); 

// Define measurement variables
float amplitude_current;
float effective_value;
float effective_voltage = 230; // Set voltage to 230V (Europe) or 110V (US)
float effective_power;
float zero_sensor;

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
  
  // Set relay pin to output
  pinMode(relay_pin,OUTPUT);
  
  // Calibrate sensor with null current
  zero_sensor = getSensorValue(A1);
  
  // Clear LCD
  delay(2000);
  lcd.clear();
}

void loop()
{
  // Measure light level
  float sensor_reading = analogRead(A0);
  float light = (sensor_reading/1024*100);
  
  // Perform power measurement
  float sensor_value = getSensorValue(A1);
    
  // Convert to current
  amplitude_current = (float)(sensor_value-zero_sensor)/1024*5/185*1000000;
  effective_value = amplitude_current/1.414;
  effective_power = abs(effective_value*effective_voltage/1000);
  
  // Switch relay accordingly
  // If the light level is more than 75 %, switch the lights off
  if (light > 75) {
    digitalWrite(relay_pin, LOW);
    relay_state = false;
  }
  // If the light level is less than 50 %, switch the lights off
  if (light < 50) {
    digitalWrite(relay_pin, HIGH);
    relay_state = true;
  }
  
  // Update LCD screen
  
  // Display relay state
  lcd.setCursor(1,0);
  lcd.print("Relay: ");
  if (relay_state) {lcd.print("On ");}
  else {lcd.print("Off");}
  
  // Display energy consumption
  lcd.setCursor(1,1);
  lcd.print("Power: ");
  lcd.print(effective_power);
  lcd.print("W");
  
  // Display light level
  lcd.setCursor(1,2);
  lcd.print("Light: ");
  lcd.print(light);
  lcd.print("%");
  
  // Wait 500 ms
  delay(500);
  
}

// Get the reading from the current sensor
float getSensorValue(int pin)
{
  int sensorValue;
  float avgSensor = 0;
  int nb_measurements = 100;
  for (int i = 0; i < nb_measurements; i++) {
    sensorValue = analogRead(pin);
    avgSensor = avgSensor + float(sensorValue);
  }	  
  avgSensor = avgSensor/float(nb_measurements);
  return avgSensor;
}
