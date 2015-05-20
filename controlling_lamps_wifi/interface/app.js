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

// Serve interface
app.get('/', function(req, res){
  res.render('interface');
});

// Start server
app.listen(port);
console.log("Listening on port " + port);