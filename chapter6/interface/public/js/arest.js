// Standard function for the aREST API

// Send command via node-aREST
function send(type, target, command, speed) {

  // Default speed
  if (typeof speed === 'undefined') {
    speed = 9600;
  }
   
  // Send command
  $.ajax({
    type: 'GET',
    url: '/send',
    async: false,
    data: {type: type, target: target, command: command, speed: speed},
    success: function( data ) {
      json_data = jQuery.parseJSON(data);
    }
  });
  
  // Return answer
  return json_data;
}