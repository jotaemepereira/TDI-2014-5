package com.example.heatmeapp;

import java.io.IOException;
import java.util.List;
import java.util.Locale;

import android.app.Service;
import android.content.Context;
import android.content.Intent;
import android.location.Geocoder;
import android.location.Location;
import android.location.LocationManager;
import android.os.IBinder;
import android.widget.Toast;
import android.location.Address;

public class LocalizationService extends Service {

	private double latitude;
	private double longitude;
	String address = "";   

		
	@Override
	public IBinder onBind(Intent arg0) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public int onStartCommand(Intent intent, int flags, int startId) {
		// TODO Auto-generated method stub
		getPosition();
		return START_STICKY;
	}

	public void getPosition() {
		LocationManager lm = (LocationManager)getSystemService(Context.LOCATION_SERVICE);
		Location gpsLocation = lm.getLastKnownLocation(LocationManager.NETWORK_PROVIDER);

		// Obtenengo longitud y latitud
		longitude = gpsLocation.getLongitude();
		latitude = gpsLocation.getLatitude();

		Geocoder geocoder = new Geocoder(this, Locale.getDefault());
		List<Address> addresses = null;
		try {
			addresses = geocoder.getFromLocation(latitude, longitude, 1);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		if (!addresses.isEmpty()) {                                                  
			Address addr = addresses.get(0);                                           
			// address = addr.toString();
			for (int i=0; i<addr.getMaxAddressLineIndex(); i++) {
				address += addr.getAddressLine(i) + "\n";
			}
			address = address.replaceAll("null","");
		}
		else {
			address = "[ No se encontraron direcciones ]";                
		}
		
		Toast.makeText(getApplicationContext(), address, Toast.LENGTH_LONG).show();
	}
}
