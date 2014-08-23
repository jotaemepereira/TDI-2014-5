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

	map = new google.maps.Map(document.getElementById('map_canvas'), {
		center: sanFrancisco,
		zoom: 15,
		mapTypeId: google.maps.MapTypeId.SATELLITE
	});
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
    $( "#date_field" ).datepicker();
});
