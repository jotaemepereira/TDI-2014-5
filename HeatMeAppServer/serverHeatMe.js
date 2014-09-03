
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

var Position = mongoose.model('Position', { latitud: String, longitud: String, timestamp: String, tipo: String });


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
    console.log(req.body.timestamp);
    console.log(req.body.tipo);

    //guardar en la db
    var pos = new Position({ latitud: req.body.latitud, longitud: req.body.longitud, timestamp: req.body.timestamp, tipo: req.body.tipo });
    pos.save(function(err){

        if (err){
            console.log('Error recording position');
            res.send('OK');
        }
        else{
            console.log('Position recorded');
            res.send('BAD');
        };  

    });

});

app.get('/getHeatMap', function(req, res){

    console.log('GET /getHeatMap');

    var urlpars = url.parse(req.url,false,true);

    //NECESITO LAS FECHAS, SIEMPRE.

    if ((/hDesde=(.+)&hHasta=(.+)/).test(urlpars.query)){

        var params = urlpars.query.match(/hDesde=(.+)&hHasta=(.+)/);

        var hDesde= params[1];
        var hHasta= params[2];

        console.log('Rango');
        console.log(hDesde);
        console.log(hHasta);

        Position.find({"timestamp": {'$gte': hDesde, '$lt': hHasta}}).sort({date: 'asc'}).exec(function(err, docs){
            
            console.log('<SENDING>');
            
            res.setHeader('Content-Type', 'application/json');
            res.setHeader("Access-Control-Allow-Origin", "*");

            //console.log(docs);

            /*
            var ret = [];

            for (var i=0; i<docs.length; i++){

                console.log(ret[docs[i].timestamp]);
                if (ret[docs[i].timestamp]==undefined)
                    ret[docs[i].timestamp] = [];

                ret[docs[i].timestamp].push({ latitud: docs[i].latitud,
                                              longitud: docs[i].longitud
                                            });

            };
            */

            console.log(docs);
            res.json(docs);
            
            console.log('</SENDING>');

        });

    };

    if ((/hExacta=(.+)/).test(urlpars.query)){

        var params = urlpars.query.match(/hExacta=(.+)/);

        var hExacta= params[1];

        console.log('hExacta');
        console.log(hExacta);

        Position.find({"timestamp": hExacta}).sort({date: 'asc'}).exec(function(err, docs){
            
            console.log('<SENDING>');
            
            res.setHeader('Content-Type', 'application/json');
            res.setHeader("Access-Control-Allow-Origin", "*");

            /*
            var ret = [];
            for (var i=0; i<docs.length; i++)
            ret.push({  latitud: docs[i].latitud,
                        longitud: docs[i].longitud
                    });

            */

            console.log(docs);
            res.json(docs);
            
            console.log('</SENDING>');

        });
        
    };
    

});
