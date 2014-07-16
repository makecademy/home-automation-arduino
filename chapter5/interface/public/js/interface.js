// Hardware parameters
type = 'serial';
address = '/dev/cu.AdafruitEZ-Link06d5-SPP';
speed = 115200;

setInterval(function() {

  // Update light level
  json_data = send(type, address, '/light', speed);
  $("#lightDisplay").html("Light level: " + json_data.light + "%");    

  // Update status
  if (json_data.connected == 1){
    $("#status").html("Station Online");
    $("#status").css("color","green");    
  }
  else {
    $("#status").html("Station Offline");
    $("#status").css("color","red");     
  }

  // Update temperature
  json_data = send(type, address, '/temperature', speed);
  $("#temperatureDisplay").html("Temperature: " + json_data.temperature + "°C");

  // Update humidity
  json_data = send(type, address, '/humidity', speed);
  $("#humidityDisplay").html("Humidity: " + json_data.humidity + "%");

}, 10000);