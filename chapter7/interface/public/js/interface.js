// Hardware parameters
wifi_address = 'arduino.local';

xbee_address = '/dev/cu.usbserial-A702LF8B';

setInterval(function() {
  
  json_data = send('serial', xbee_address, '/temperature');
  if (json_data.temperature){
     $("#xbeeTempDisplay").html("Temperature: " + json_data.temperature + "°C");    
  }

  json_data = send('serial', xbee_address, '/humidity');
  if (json_data.humidity){
    $("#xbeeHumDisplay").html("Humidity: " + json_data.humidity + "%");    
  }

  json_data = send('serial', xbee_address, '/light');
  if (json_data.light){
    $("#xbeeLightDisplay").html("Light: " + json_data.light + "%");    
  }

  if (json_data.connected == 1){
    $("#xbeeStatus").html("Online");
    $("#xbeeStatus").css("color","green");    
  }
  else {
    $("#xbeeStatus").html("Offline");
    $("#xbeeStatus").css("color","red");     
  }

}, 2000);

// Function to control the lamp
function buttonClick(clicked_id){

  if (clicked_id == "1"){
    send('wifi', wifi_address, "/digital/8/1");  
  } 

  if (clicked_id == "2"){
    send('wifi', wifi_address, "/digital/8/0");  
  }

}