var devices = [];

$.get('/devices', function( json_data ) {
  devices = json_data;
});

$(document).ready(function() {

  // Update sensors and repeat every 5 seconds
  setTimeout(updateSensors, 500);
  setInterval(updateSensors, 5000);

  // Function to control the lamp
  $('#1').click(function(){
    $.get('/' + devices[0].name + '/digital/8/1');
  });

  $('#2').click(function(){
    $.get('/' + devices[0].name + '/digital/8/0');
  });

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

});