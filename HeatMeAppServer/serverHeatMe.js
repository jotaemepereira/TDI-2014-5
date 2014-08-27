
var express     = require('express');
var url         = require('url');
var bodyParser  = require('body-parser');
var mongo       = require('mongodb');
var mongoose    = require('mongoose');

var app = express();

app.use(express.urlencoded());

app.use(bodyParser.urlencoded());

var server = app.listen(8080, function(){
    console.log('heatMe is listening on port %d', server.address().port);
});

mongoose.connect('mongodb://localhost/heatMe');

var Position = mongoose.model('Position', { latitud: String, longitud: String, date:  { type: Date, default: Date.now } });


//<PRUEBA>

//guardar en la db
var pos = new Position({ latitud: '11', longitud: '22'/*, timestamp: req.body.timestamp */});
pos.save(function(err){

    if (err) // ...
        console.log('Error recording position');
    else
        console.log('Position recorded');

    Position.find({"date": {'$gte': new Date('3/1/2014'), '$lt': new Date('3/16/2015')}}, function(err, docs){
        console.log(docs);
    });

});

//</PRUEBA>

app.post('/locationUpdate', function(req, res){

    console.log('POST /locationUpdate');

    //console.log(req.body.timestamp);
    console.log(req.body.latitud);
    console.log(req.body.longitud);

    //guardar en la db
    var pos = new Position({ latitud: req.body.latitud, longitud: req.body.longitud/*, timestamp: req.body.timestamp */});
    pos.save(function(err){

        if (err) // ...
            console.log('Error recording position');
        else
            console.log('Position recorded');

    });

});

app.get('/getHeatMap', function(req, res){

    console.log('GET /getHeatMap');

    var urlpars = url.parse(req.url,false,true);

    var params = urlpars.query.match(/timestamp=(.+)&latitud=(.+)&longitud=(.+)/);

    var timestamp = params[1];
    var latitud= params[2];
    var longitud= params[3];

    console.log(timestamp);
    console.log(latitud);
    console.log(longitud);

    Position.find({"date": {'$gte': new Date('3/1/2014'), '$lt': new Date('3/16/2015')}}, function(err, docs){
        console.log(docs);
    });

});
