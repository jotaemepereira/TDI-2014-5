var map;
var heatmap = null;
var pointArray = [];
var gradient = null;
var gradientTodos = ['rgba(0, 255, 255, 0)', 'rgba(0, 255, 255, 1)', 'rgba(0, 127, 255, 1)', 'rgba(0, 90, 179, 1)', 'rgba(0, 50, 95, 1)', 'rgba(0, 37, 79, 1)'];
var gradientBondi = ['rgba(226, 226, 0, 0)', 'rgba(226, 226, 0, 1)', 'rgba(142, 142, 0, 1)', 'rgba(142, 104, 0, 1)', 'rgba(142, 59, 0, 1)', 'rgba(142, 26, 0, 1)', 'rgba(187, 19, 0, 1)'];
var gradientAuto = ['rgba(152, 240, 0, 0)', 'rgba(152, 240, 0, 1)', 'rgba(112, 177, 0, 1)', 'rgba(0, 119, 16, 1)', 'rgba(0, 134, 100, 1)', 'rgba(0, 134, 127, 1)', 'rgba(0, 208, 219, 1)'];
var gradientBici = null;
var gradientCaminando = ['rgba(255, 186, 251, 0)', 'rgba(255, 186, 251, 1)', 'rgba(254, 138, 246, 1)', 'rgba(218, 30, 114, 1)', 'rgba(190, 10, 10, 1)', 'rgba(105, 0, 0, 1)'];

function initialize() 
{
	var montevideo = new google.maps.LatLng(-34.8968678,-56.1182457);

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
		zoom: 13,
		mapTypeId: google.maps.MapTypeId.ROADMAP
	});
	map.setOptions({styles: styleArray});
	heatmap = new google.maps.visualization.HeatmapLayer({
        data: pointArray,
        map: map,
        radius: 25,
        maxIntensity: 1
    });
	obtenerPuntosDeCalor();
}

google.maps.event.addDomListener(window, 'load', initialize);

$(document).ready(function()
{
	$("#spinner").hide();
	var date = new Date();
	var h = date.getHours();
	var m = date.getMinutes()
	$('#date_field').val((date.getMonth() + 1) + '/' + date.getDate() + '/' + date.getFullYear());
	parseFloat(h) < 10 ? $('#hours_field').val('0' + h) : $('#hours_field').val(h);
	parseFloat(m) < 10 ? $('#minutes_field').val('0' + m) : $('#minutes_field').val(m);
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
	var h = $('#hours_field').val();
	var m = $('#minutes_field').val();
	parseFloat(h) < 10 && h.length < 2 ? $('#hora').text('0' + h) : $('#hora').text(h);
	parseFloat(m) < 10 && m.length < 2 ? $('#min').text('0' + m) : $('#min').text(m);

	var timestamp = $( "#date_field" ).datepicker( "getDate" );
	timestamp.setHours(h);
	timestamp.setMinutes(m);
	
	var transporte = $("#tipo_select").val();
	switch(transporte) {
	    case '0':
	        gradient = gradientCaminando;
	        break;
	    case '1':
	        gradient = gradientBici;
	        break;
	    case '2':
	    	gradient = gradientAuto;
	    	break;
	    case '3':
	    	gradient = gradientBondi;
		    break;
	    default:
	        gradient = gradientTodos;
	}
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
		pointArray = new google.maps.MVCArray(heatpoints);
		//map.panTo(new google.maps.LatLng(heatpoints[heatpoints.length - 1].k, heatpoints[heatpoints.length - 1].B));
		/*if (!heatmap) {
		    heatmap = new google.maps.visualization.HeatmapLayer({
		        data: pointArray,
		        map: map,
		        gradient: ['rgba(0, 255, 255, 0)', 'rgba(0, 255, 255, 1)', 'rgba(0, 191, 255, 1)', 'rgba(0, 127, 255, 1)', 'rgba(0, 90, 179, 1)', 'rgba(0, 50, 95, 1)'],
		        radius: 23
		    });
		} else {*/
		heatmap.setData(pointArray);
		heatmap.set('gradient', gradient);
		//}
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
	$("#spinner").show();
	var hDesde = $( "#date_field" ).datepicker( "getDate" );
	var hHasta = $( "#date_field" ).datepicker( "getDate" );
	var tipo = $('#tipo_select').val();
	hDesde.setHours(6);
	hDesde.setMinutes(30);
	hHasta.setHours(20);
	hHasta.setMinutes(00);

	$.ajax({
		type : "GET",
		url: 'http://162.248.53.11:8080/getHeatMap',
		data: "hDesde=" + hDesde.getTime() + "&hHasta=" + hHasta.getTime() + "&tipo=" + tipo,
		contentType: 'application/x-www-form-urlencoded',
		dataType: 'json',
	}).done(function(response){
		$("#spinner").hide();
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
		/*if (!heatmap) {
		    heatmap = new google.maps.visualization.HeatmapLayer({
		        data: pointArray,
		        map: map,
		        radius: 23
		    });
		}*/
		var i = 10;
		for (var timestamp in heatpoints){
            (function(timestamp){
            	//console.log(heatpoints[timestamp]);
            	setTimeout(moveCity, i, heatpoints[timestamp], timestamp); 
				i += 200;
            })(timestamp);
        };
        //map.panTo(new google.maps.LatLng(-34.8970141,-56.06299));
		
	}).fail(function(jqXHR, textStatus) {
		$("#spinner").hide();
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
	pointArray = new google.maps.MVCArray(heatpoints);
	heatmap.setData(pointArray);
	var h = d.getHours();
	var m = d.getMinutes()
	parseFloat(h) < 10 ? hora.text('0' + h) : hora.text(h);
	parseFloat(m) < 10 ? min.text('0' + m) : min.text(m);
}

