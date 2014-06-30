// Simple motion sensor
int sensor_pin = 8;

void setup() {
  Serial.begin(9600);
}

void loop() {
  
  // Read sensor data
  int sensor_state = digitalRead(sensor_pin);
  
  // Print data
  Serial.print("Motion sensor state: ");
  Serial.println(sensor_state);
  delay(100);
}
