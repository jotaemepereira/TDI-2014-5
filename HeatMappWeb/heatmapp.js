var map;
var heatmap = null;
var heatmapData = [
	new google.maps.LatLng(37.782, -122.447),
	new google.maps.LatLng(37.782, -122.445),
	new google.maps.LatLng(37.782, -122.443),
	new google.maps.LatLng(37.782, -122.441),
	new google.maps.LatLng(37.782, -122.439),
	new google.maps.LatLng(37.782, -122.437),
	new google.maps.LatLng(37.782, -122.435),
	new google.maps.LatLng(37.785, -122.447),
	new google.maps.LatLng(37.785, -122.445),
	new google.maps.LatLng(37.785, -122.443),
	new google.maps.LatLng(37.785, -122.441),
	new google.maps.LatLng(37.785, -122.439),
	new google.maps.LatLng(37.785, -122.437),
	new google.maps.LatLng(37.785, -122.435)
];

function initialize() 
{
	var sanFrancisco = new google.maps.LatLng(37.784546, -122.443523);

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
		center: sanFrancisco,
		zoom: 12,
		mapTypeId: google.maps.MapTypeId.ROADMAP
	});
	map.setOptions({styles: styleArray});
	runHeatmap();
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
	$('#hours_field').val(date.getHours());
	$('#minutes_field').val(date.getMinutes());
	$('#date_field').val((date.getMonth() + 1) + '/' + date.getDate() + '/' + date.getFullYear());
})

$(function() {
    $("#date_field").datepicker();
    $("#date_field").change(obtenerPuntosDeCalor);
    $("#hours_field").change(obtenerPuntosDeCalor);
    $("#minutes_field").change(obtenerPuntosDeCalor);
    $("#play").click(function()
    	{
    		
    	});
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
	console.log('timestamp --> ' + timestamp);
	$.ajax({
		type : "GET",
		url: 'http://localhost:8080/getHeatMap',
		data: "timestamp=" + timestamp.getTime(),
		contentType: 'application/x-www-form-urlencoded',
		dataType: 'json',
	}).done(function(userData){
		console.log('Success getHeatMap: ' + JSON.stringify(userData));
		var heatpoints = [];
		userData.forEach(function(point){
			heatpoints.push(new google.maps.LatLng(parseFloat(point.latitud), parseFloat(point.longitud)));
		})
		var pointArray = new google.maps.MVCArray(heatpoints);
		map.setCenter(new google.maps.LatLng(heatpoints[heatpoints.length - 1].k, heatpoints[heatpoints.length - 1].B));
		if (!heatmap) {
		    heatmap = new google.maps.visualization.HeatmapLayer({
		        data: pointArray,
		        map: map
		    });
		} else {
		    heatmap.setData(pointArray);
		}
	}).fail(function(jqXHR, textStatus) {
		console.log('Error getHeatMap: ' + textStatus);
	});
	/*$.ajax({
		type : "POST",
		url: 'http://localhost:8080/locationUpdate',
		data: "timestamp=" + timestamp,
		contentType: 'application/x-www-form-urlencoded',
		dataType: 'json',
	}).done(function(userData){
		 console.log('Success: ' + JSON.stringify(data));
	}).fail(function(jqXHR, textStatus) {
		console.log('Error: ' + error.message);
	}); */

}

function signinCallback(authResult) 
{
	if (authResult['access_token']) 
	{
		// Autorizado correctamente
		// Oculta el botón de inicio de sesión ahora que el usuario está autorizado, por ejemplo:
		document.getElementById('google_sign_in').setAttribute('style', 'display: none');
	} 
	else if (authResult['error']) 
	{
		// Se ha producido un error.
		// Posibles códigos de error:
		//   "access_denied": el usuario ha denegado el acceso a la aplicación.
		//   "immediate_failed": no se ha podido dar acceso al usuario de forma automática.
		console.log('There was an error: ' + authResult['error']);
	}
}

function cambiarMedioTransporte()
{
	var tipo = $('#tipo_select').val();
	$('#tipo_img').attr('src', 'assets/images/tipo' + tipo +'.png');
}

