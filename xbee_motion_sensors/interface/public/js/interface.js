$(document).ready(function() {

  $.get('/devices', function( devices ) {

    // Set inputs
    for (i = 0; i < devices.length; i++){

      // Get device
      var device = devices[i];

      // Set input
      $.get('/' + device.name + '/mode/8/i');

    }

    setInterval(function() {

      for (i = 0; i < devices.length; i++){

        // Get device
        var device = devices[i];

        // Get data
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

    }, 2000);

  });

});