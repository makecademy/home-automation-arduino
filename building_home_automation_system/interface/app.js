// Module
var express = require('express');
var app = express();

// Define port
var port = 3000;

// View engine
app.set('view engine', 'jade');

// Set public folder
app.use(express.static(__dirname + '/public'));

// Rest
var rest = require("arest")(app);
rest.addDevice('http','192.168.1.103');
rest.addDevice('xbee','/dev/tty.usbserial-A702LF8B');

// Serve interface
app.get('/', function(req, res){
  var devices = rest.getDevices();
  res.render('interface', {devices: devices});
});

// Start server
app.listen(port);
console.log("Listening on port " + port);