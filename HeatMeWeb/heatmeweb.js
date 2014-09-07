var map;
var heatmap = null;

function initialize() 
{
	var montevideo = new google.maps.LatLng(-34.8730281, -56.1500187);

	var styleArray = [
	{
		featureType: "all",
		stylers: [
		  { hue: "#808080" },
		  { saturation: -100 }
		]
	},
	{
		featureType: "road",
		elementType: "geometry",
		stylers: [
		  { hue: "#B3FFFB" },
		  { saturation: 50 },
		]
	},
	{
		featureType: "road.arterial",
		elementType: "geometry",
		stylers: [
		  { hue: "#00ffee" },
		  { saturation: 100 },
		]
	},
	{
		featureType: "road.highway",
		elementType: "geometry",
		stylers: [
		  { hue: "#00B3A7" },
		  { saturation: 30 },
		]
	},
	{
		featureType: "poi.business",
		elementType: "labels",
		stylers: [
		  { visibility: "off" }
		]
	}];

	map = new google.maps.Map(document.getElementById('map_canvas'), {
		center: montevideo,
		zoom: 12,
		mapTypeId: google.maps.MapTypeId.ROADMAP
	});
	map.setOptions({styles: styleArray});
	obtenerPuntosDeCalor();
}

function runHeatmap() 
{
    var pointArray = new google.maps.MVCArray(heatmapData);
    if (!heatmap) {
        heatmap = new google.maps.visualization.HeatmapLayer({
            data: pointArray,
            map: map
        });
    } else {
        heatmap.setData(pointArray);
    }
}
google.maps.event.addDomListener(window, 'load', initialize);

$(document).ready(function()
{
	var date = new Date();
	var h = date.getHours();
	var m = date.getMinutes()
	$('#date_field').val((date.getMonth() + 1) + '/' + date.getDate() + '/' + date.getFullYear());
	parseFloat(h) < 10 ? ($('#hora').text('0' + h), $('#hours_field').val('0' + h)) : ($('#hora').text(h), $('#hours_field').val(h));
	parseFloat(m) < 10 ? ($('#min').text('0' + m), $('#minutes_field').val('0' + m)) : ($('#min').text(m), $('#minutes_field').val(m));
})

$(function() {
    $("#date_field").datepicker();
    $("#date_field").change(obtenerPuntosDeCalor);
    $("#hours_field").change(obtenerPuntosDeCalor);
    $("#minutes_field").change(obtenerPuntosDeCalor);
    $("#play").click(verMovimientoDelDia);
    $("#next").click(function()
    	{
    		var currentDate = $("#date_field").datepicker( "getDate" );
    		$("#date_field").datepicker("setDate", new Date(currentDate.getTime() + (24 * 60 * 60 * 1000)));
    		obtenerPuntosDeCalor();
    	});
    $("#prev").click(function()
    	{
    		var currentDate = $("#date_field").datepicker( "getDate" );
    		$("#date_field").datepicker("setDate", new Date(currentDate.getTime() - (24 * 60 * 60 * 1000)));
    		obtenerPuntosDeCalor();
    	});
    $("#tipo_select").change(cambiarMedioTransporte);
});

function obtenerPuntosDeCalor() 
{
	//162.248.53.11:8080
	var timestamp = $( "#date_field" ).datepicker( "getDate" );
	timestamp.setHours($('#hours_field').val());
	timestamp.setMinutes($('#minutes_field').val());
	var transporte = $("#tipo_select").val();
	console.log('timestamp --> ' + timestamp);
	var d = new Date();	
	$.ajax({
		type : "GET",
		url: 'http://162.248.53.11:8080/getHeatMap',
		data: "hExacta=" + timestamp.getTime() + "&tipo=" + transporte,
		contentType: 'application/x-www-form-urlencoded',
		dataType: 'json',
	}).done(function(userData){
		//console.log('Success getHeatMap: ' + JSON.stringify(userData));
		var heatpoints = [];
		userData.forEach(function(point){
			heatpoints.push(new google.maps.LatLng(parseFloat(point.latitud), parseFloat(point.longitud)));
		})
		var pointArray = new google.maps.MVCArray(heatpoints);
		//map.panTo(new google.maps.LatLng(heatpoints[heatpoints.length - 1].k, heatpoints[heatpoints.length - 1].B));
		if (!heatmap) {
		    heatmap = new google.maps.visualization.HeatmapLayer({
		        data: pointArray,
		        map: map
		    });
		} else {
		    heatmap.setData(pointArray);
		}
	}).progress(function(jqXHR, textStatus) {
		console.log('progress: ' + textStatus);
	}).fail(function(jqXHR, textStatus) {
		console.log('Error getHeatMap: ' + textStatus);
	});
}

function cambiarMedioTransporte()
{
	var tipo = $('#tipo_select').val();
	if (tipo !== '4')
		$('#tipo_img').attr('src', 'assets/images/tipo' + tipo +'.png');
	obtenerPuntosDeCalor();
}

function verMovimientoDelDia()
{
	var hDesde = $( "#date_field" ).datepicker( "getDate" );
	var hHasta = $( "#date_field" ).datepicker( "getDate" );
	var tipo = $('#tipo_select').val();
	hDesde.setHours(0);
	hDesde.setMinutes(1);
	hHasta.setHours(23);
	hHasta.setMinutes(59);

	$.ajax({
		type : "GET",
		url: 'http://162.248.53.11:8080/getHeatMap',
		data: "hDesde=" + hDesde.getTime() + "&hHasta=" + hHasta.getTime() + "&tipo=" + tipo,
		contentType: 'application/x-www-form-urlencoded',
		dataType: 'json',
	}).done(function(response){
		var heatpoints = [];
		for (var i=0; i<response.length; i++){
		   if ( !heatpoints[response[i].timestamp] ) ///  si esa celda no esta creada la creo vacia
		   {
	   			var d = new Date(parseFloat(response[i].timestamp));
				//console.log(d);
		        heatpoints[response[i].timestamp] = [];
		   }
		   //inserto en la celda del timestamp los datos correspondientes
		   heatpoints[response[i].timestamp].push([response[i].latitud, response[i].longitud]);
		};
		//console.log(heatpoints);
		var pointArray = [];
		if (!heatmap) {
		    heatmap = new google.maps.visualization.HeatmapLayer({
		        data: pointArray,
		        map: map
		    });
		}
		var i = 10;
		for (var timestamp in heatpoints){
            (function(timestamp){
            	//console.log(heatpoints[timestamp]);
            	setTimeout(moveCity, i, heatpoints[timestamp], timestamp); 
				i += 100;
            })(timestamp);
        };
        //map.panTo(new google.maps.LatLng(-34.8970141,-56.06299));
		
	}).progress(function(jqXHR, textStatus) {
		console.log('Error getHeatMap: ' + textStatus);
	}).fail(function(jqXHR, textStatus) {
		console.log('Error getHeatMap: ' + textStatus);
	});
}

function moveCity(puntos, timestamp){
	var hora = $( "#hora" );
	var min = $( "#min" );
	var d = new Date(parseFloat(timestamp));
	var heatpoints = [];
	puntos.forEach(function(point){
		heatpoints.push(new google.maps.LatLng(parseFloat(point[0]), parseFloat(point[1])));
	})
	var pointArray = new google.maps.MVCArray(heatpoints);
	heatmap.setData(pointArray);
	var h = d.getHours();
	var m = d.getMinutes()
	parseFloat(h) < 10 ? hora.text('0' + h) : hora.text(h);
	parseFloat(m) < 10 ? min.text('0' + m) : min.text(m);
}

