
var express = require('express');
var url = require('url');

var app = express();

app.use(express.urlencoded());

var bodyParser = require('body-parser');

app.use(bodyParser.urlencoded());

var server = app.listen(8080, function(){
    console.log('heatMe is listening on port %d', server.address().port);
});

app.post('/locationUpdate', function(req, res){

    console.log('POST /locationUpdate');

    console.log(req.body.timestamp);
    console.log(req.body.latitud);
    console.log(req.body.longitud);

    //guardar en la db



});


app.get('/getHeatMap', function(req, res){

    console.log('GET /getHeatMap');

    console.log(req.body.timestamp);
    console.log(req.body.latitud);
    console.log(req.body.longitud);

    console.log(req.url);
    var urlpars = url.parse(req.url,false,true);

    var params = urlpars.query.match(/timestamp=(.+)&latitud=(.+)&longitud=(.+)/) ;

    var timestamp = params[1];
    var latitud= params[2];
    var longitud= params[3];

    console.log(timestamp);
    console.log(latitud);
    console.log(longitud);


    //guardar en la db



});
