$(document).ready(function() {

  $.get('/devices', function( devices ) {

    // Update sensors and repeat every 5 seconds
    setTimeout(updateSensors, 500);
    setInterval(updateSensors, 5000);

    // Function to control the lamp
    $('#lamp1').click(function(){
      $.get('/' + devices[0].name + '/digital/8/1');
    });

    $('#lamp2').click(function(){
      $.get('/' + devices[0].name + '/digital/8/0');
    });

    // Update lamp sensors
    function updateSensors(){

      // Update light level
      $.get('/' + devices[0].name + '/light', function(json_data) {

        $("#lightDisplay").html("Light level: " + json_data.light + " %");    

        // Update status
        if (json_data.connected == 1){
          $("#status").html("Lamp Online");
          $("#status").css("color","green");    
        }
        else {
          $("#status").html("Lamp Offline");
          $("#status").css("color","red");     
        }

        // Update power
        $.get('/' + devices[0].name + '/power', function(json_data) {
          $("#powerDisplay").html("Power: " + json_data.power + " W");  
        });

      });
    }

    // Set inputs for motion sensors
    for (i = 0; i < devices.length; i++){

      // Get device
      var device = devices[i];

      // Set input
      if (device.type == 'xbee'){
         $.get('/' + device.name + '/mode/8/i');
      }
     
    }

    setInterval(function() {

      for (i = 0; i < devices.length; i++){

        // Get device
        var device = devices[i];

        // Get data
        if (device.type == 'xbee'){
          $.get('/' + device.name + '/digital/8', function(json_data) {

            // Update display  
            if (json_data.return_value == 0){
              $("#" + json_data.id).html("No motion");
              $("#" + json_data.id).css("color","red");    
            }
            else {
              $("#" + json_data.id).html("Motion detected");
              $("#" + json_data.id).css("color","green");  
            }  
          });
        }
        
      }

    }, 2000);
    
  });

});