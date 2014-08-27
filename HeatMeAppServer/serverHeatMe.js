
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
/*
//guardar en la db
var pos = new Position({ latitud: '11', longitud: '22'});
pos.save(function(err){

    if (err) // ...
        console.log('Error recording position');
    else
        console.log('Position recorded');

});

var pos = new Position({ latitud: '11', longitud: '22'});
pos.save(function(err){

    if (err) // ...
        console.log('Error recording position');
    else
        console.log('Position recorded');

    Position.find({"date": {'$gte': new Date('3/1/2014'), '$lt': new Date('3/16/2015')}}).sort({date: 'asc'}).exec(function(err, docs){
        console.log(docs);
    });

});
*/
//</PRUEBA>

app.post('/locationUpdate', function(req, res){

    console.log('POST /locationUpdate');

    console.log(req.body.latitud);
    console.log(req.body.longitud);

    //guardar en la db
    var pos = new Position({ latitud: req.body.latitud, longitud: req.body.longitud });
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

    //NECESITO LAS FECHAS, SIEMPRE.

    /*
    var params = urlpars.query.match(/fDesde=(.+)&fHasta=(.+)/);

    var fDesde= params[1];
    var fHasta= params[2];

    console.log(fDesde);
    console.log(fHasta);
    */

    Position.find({"date": {'$gte': new Date('3/1/2014'), '$lt': new Date('3/16/2015')}}).sort({date: 'asc'}).exec(function(err, docs){
        
        console.log('<SENDING>');
        
        res.setHeader('Content-Type', 'application/json');
        res.setHeader("Access-Control-Allow-Origin", "*");

        var ret = [];
        for (var i=0; i<docs.length; i++)
        ret.push({  latitud: docs[i].latitud,
                    longitud: docs[i].longitud
                });

        console.log(ret);
        res.json(ret);
        
        console.log('</SENDING>');

    });

});
