// Hardware parameters
wifi_address = 'arduino.local';
xbee_address = '/dev/cu.usbserial-A702LF8B';

setInterval(function() {

  // Get sensor data
  json_data = send('serial', xbee_address, '/digital/8');

  // Get sensor ID
  var sensorID = json_data.id;
  
  // Update display  
  if (json_data.return_value == 0){
    $("#display_" + sensorID).css("background-color","gray");    
  }
  else {
    $("#display_" + sensorID).css("background-color","orange");  
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