
var express     = require('express');
var url         = require('url');
var bodyParser  = require('body-parser');
var mongo       = require('mongodb');
var mongoose    = require('mongoose');

var app = express();

app.use(express.urlencoded());

app.use(express.bodyParser());

//app.use(bodyParser.urlencoded());

var server = app.listen(8080, function(){
    console.log('heatMe is listening on port %d', server.address().port);
});

mongoose.connect('mongodb://localhost/heatMe');

var Position = mongoose.model('Position', { latitud: String, longitud: String, timestamp: String, tipo: String });

app.post('/locationUpdateTest', function(req, res){

    console.log('POST /locationUpdateTest');

    console.log(req.body.latitud);
    console.log(req.body.longitud);
    console.log(req.body.timestamp);
    console.log(new Date(parseFloat(req.body.timestamp)));
    console.log(req.body.tipo);

    //guardar en la db
    var pos = new Position({ latitud: req.body.latitud, longitud: req.body.longitud, timestamp: req.body.timestamp, tipo: req.body.tipo });
    pos.save(function(err){

        res.setHeader("Access-Control-Allow-Origin", "*");

        if (err){

            console.log('Error recording position');
            res.send('BAD');

        }
        else{

            console.log('Position recorded');
            res.send('OK');
            
        };  

    });

});

app.post('/locationUpdate', function(req, res){

    console.log('POST /locationUpdate');

    var ok = 0;
    
    res.setHeader("Access-Control-Allow-Origin", "*");

    for (var i=0; i<req.body.posiciones.length; i++){

        var pos = new Position({ latitud: req.body.posiciones[i].latitud, longitud: req.body.posiciones[i].longitud, timestamp: req.body.posiciones[i].timestamp, tipo: req.body.posiciones[i].tipo });
        pos.save(function(err){

            ok++;

            if (!err){

                if (ok==req.body.posiciones.length){
                    console.log('Positions recorded');
                    res.send('OK');
                };  

            }
            else{

                res.setHeader("Access-Control-Allow-Origin", "*");
                console.log('Error recording position');
                res.send('BAD');

            };

        });

    };

});

app.get('/getHeatMap', function(req, res){

    console.log('GET /getHeatMap');

    var urlpars = url.parse(req.url,false,true);

    if ((/hDesde=(.+)&hHasta=(.+)/).test(urlpars.query)){

        var params = urlpars.query.match(/hDesde=(.+)&hHasta=(.+)&tipo=(.+)/);

        var hDesde = params[1];
        var hHasta = params[2];
        var tipo = params [3];

        console.log('Rango');
        console.log(hDesde);
        console.log(hHasta);
        console.log(tipo);

        if (tipo=="4"){

            Position.find({"timestamp": {'$gte': hDesde, '$lt': hHasta}}).sort({date: 'asc'}).exec(function(err, docs){
                
                console.log('<SENDING>');
                
                res.setHeader('Content-Type', 'application/json');
                res.setHeader("Access-Control-Allow-Origin", "*");

                console.log(docs);
                res.json(docs);
                
                console.log('</SENDING>');

            });

        }
        else{

            Position.find({"timestamp": {'$gte': hDesde, '$lt': hHasta}, "tipo" : tipo}).sort({date: 'asc'}).exec(function(err, docs){
                
                console.log('<SENDING>');
                
                res.setHeader('Content-Type', 'application/json');
                res.setHeader("Access-Control-Allow-Origin", "*");

                console.log(docs);
                res.json(docs);
                
                console.log('</SENDING>');

            });

        };

    };

    if ((/hExacta=(.+)/).test(urlpars.query)){

        var params = urlpars.query.match(/hExacta=(.+)&tipo=(.+)/);

        var hExacta= params[1];
        var tipo = params [2];

        console.log('hExacta');

        console.log(hExacta);
        console.log(tipo);

        if (tipo=="4"){

            Position.find({"timestamp": hExacta}).sort({date: 'asc'}).exec(function(err, docs){
                
                console.log('<SENDING>');
                
                res.setHeader('Content-Type', 'application/json');
                res.setHeader("Access-Control-Allow-Origin", "*");

                console.log(docs);
                res.json(docs);
                
                console.log('</SENDING>');

            });

        }
        else{

            Position.find({"timestamp": hExacta, "tipo" : tipo}).sort({date: 'asc'}).exec(function(err, docs){
                
                console.log('<SENDING>');
                
                res.setHeader('Content-Type', 'application/json');
                res.setHeader("Access-Control-Allow-Origin", "*");

                console.log(docs);
                res.json(docs);
                
                console.log('</SENDING>');

            });  

        }
        
    };

});
