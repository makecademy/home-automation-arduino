var devices = [];

$.get('/devices', function( json_data ) {
  devices = json_data;
});

$(document).ready(function() {

  function updateSensors() {
    
    // Update light level and status
    $.get('/' + devices[0].name + '/light', function(json_data) {

      console.log(json_data.light);

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

      $.get('/' + devices[0].name + '/temperature', function(json_data) {
        $("#temperatureDisplay").html("Temperature: " + json_data.temperature + "°C");
        
        $.get('/' + devices[0].name + '/humidity', function(json_data) {
          $("#humidityDisplay").html("Humidity: " + json_data.humidity + "%");
        });
      });
    });
  }

  setTimeout(updateSensors, 500);
  setInterval(updateSensors, 5000);

});