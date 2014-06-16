window.onload = function() {
    $.get("/api", {type: 'wifi', target: 'arduino.local', command: "/mode/6/o"} );
}

setInterval(function() {

    $.get('/api', {type: 'wifi', target: 'arduino.local', command: "/temperature"}, function( data ) {
        json_data = jQuery.parseJSON(data);
        if (json_data.temperature){
            $("#wifiTempDisplay").html("Temperature: " + json_data.temperature);    
        }
        if (json_data.connected == 1){
            $("#wifiStatus").html("Online");
            $("#wifiStatus").css("color","green");    
        }
        else {
            $("#wifiStatus").html("Offline");
            $("#wifiStatus").css("color","red");     
        }
    });

}, 5000);

// Function to control LEDs
function buttonClick(clicked_id){

    if (clicked_id == "1"){
        $.get( '/api', {
        type: 'wifi', target: 'arduino.local', command: "/digital/6/1"} );  
    } 

    if (clicked_id == "2"){
        $.get( '/api', {
        type: 'wifi', target: 'arduino.local', command: "/digital/6/0"} );  
    } 

}