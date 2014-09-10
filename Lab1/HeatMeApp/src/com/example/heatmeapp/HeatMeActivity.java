package com.example.heatmeapp;

import android.app.AlertDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.location.Location;
import android.location.LocationListener;
import android.location.LocationManager;
import android.os.Bundle;
import android.provider.Settings;
import android.support.v4.app.FragmentActivity;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.Spinner;
import android.widget.Toast;

import com.google.android.gms.maps.CameraUpdateFactory;
import com.google.android.gms.maps.GoogleMap;
import com.google.android.gms.maps.SupportMapFragment;
import com.google.android.gms.maps.model.BitmapDescriptorFactory;
import com.google.android.gms.maps.model.LatLng;
import com.google.android.gms.maps.model.MarkerOptions;


public class HeatMeActivity extends FragmentActivity {

	private AlarmBroadcastReceiver alarm ;
	GoogleMap map;
	LocationManager lm;
	public static final String BROADCAST = "PACKAGE_NAME.android.action.broadcast";

	Spinner list;
	String[] web = {
			"Omnibus",
			"Bicicleta",
			"Auto"
	} ;
	Integer[] imageId = {
			R.drawable.bus,
			R.drawable.bike,
			R.drawable.walk
	};


	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_heat_me);
		alarm = new AlarmBroadcastReceiver();
		CustomList adapter = new
				CustomList(HeatMeActivity.this, web, imageId);
		list=(Spinner)findViewById(R.id.spinner1);
		list.setAdapter(adapter);
		Button btn = (Button) findViewById(R.id.button1);
		btn.setOnClickListener(new OnClickListener() {

			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub

				//Iniciar servicio directo
				//Intent i = new Intent(HeatMeActivity.this, LocalizationService.class);      
				//HeatMeActivity.this.startService(i);  

				//Comenzar el broadcast receiver para iniciar el servicio cada tanto
				startRepeatingTimer();
			}
		});

		lm = (LocationManager) getSystemService(Context.LOCATION_SERVICE);

		SupportMapFragment mapFragment = (SupportMapFragment) getSupportFragmentManager()
				.findFragmentById(R.id.map);

		map = mapFragment.getMap();

		map.setMyLocationEnabled(true);

		LocationListener ll = new LocationListener() {



			@Override
			public void onStatusChanged(String provider, int status,
					Bundle extras) {
				// TODO Auto-generated method stub

			}

			@Override
			public void onProviderEnabled(String provider) {
				// TODO Auto-generated method stub

			}

			@Override
			public void onProviderDisabled(String provider) {
				// TODO Auto-generated method stub
				//showSettingsAlert();

			}

			@Override
			public void onLocationChanged(Location location) {

				//Limpio viejos marks que hayan quedado
				map.clear();

				map.addMarker(new MarkerOptions()
				.position(
						new LatLng(location.getLatitude(), location
								.getLongitude()))
								.title("Estoy aqui")
								.icon(BitmapDescriptorFactory
										.defaultMarker(BitmapDescriptorFactory.HUE_AZURE)));

				map.animateCamera(CameraUpdateFactory.newLatLngZoom(new LatLng(
						location.getLatitude(), location.getLongitude()), 15.0f));

			}
		};

		lm.requestLocationUpdates(LocationManager.GPS_PROVIDER, 60*1000, 0, ll);
	}


	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.heat_me, menu);
		return true;
	}

	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
		// Handle action bar item clicks here. The action bar will
		// automatically handle clicks on the Home/Up button, so long
		// as you specify a parent activity in AndroidManifest.xml.
		int id = item.getItemId();
		if (id == R.id.action_settings) {
			return true;
		}
		return super.onOptionsItemSelected(item);
	}

	public void startRepeatingTimer() {
        Context context = this.getApplicationContext();
        if(alarm != null){
         alarm.SetAlarm(context);
        }else{
         Toast.makeText(context, "Alarm is null", Toast.LENGTH_SHORT).show();
        }
       }

	public void showSettingsAlert(){
		AlertDialog.Builder alertDialog = new AlertDialog.Builder(getBaseContext());

		// Setting Dialog Title
		alertDialog.setTitle("GPS is settings");

		// Setting Dialog Message
		alertDialog.setMessage("GPS is not enabled. Do you want to go to settings menu?");

		// On pressing Settings button
		alertDialog.setPositiveButton("Settings", new DialogInterface.OnClickListener() {
			public void onClick(DialogInterface dialog,int which) {
				Intent intent = new Intent(Settings.ACTION_LOCATION_SOURCE_SETTINGS);
				startActivity(intent);
			}
		});

		// on pressing cancel button
		alertDialog.setNegativeButton("Cancel", new DialogInterface.OnClickListener() {
			public void onClick(DialogInterface dialog, int which) {
				dialog.cancel();
			}
		});

		// Showing Alert Message
		alertDialog.show();
	}


}
