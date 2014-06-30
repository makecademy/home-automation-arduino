// Hardware parameters
type = 'serial';
address = '/dev/cu.usbserial-A702LF8B';

setInterval(function() {

  // Get sensor data
  json_data = send(type, address, '/digital/8');

  // Get sensor ID
  var sensorID = json_data.id;
  
  // Update display  
  if (json_data.return_value == 0){
    $("#display_" + sensorID).css("background-color","gray");    
  }
  else {
    $("#display_" + sensorID).css("background-color","orange");  
  }  

}, 1000);