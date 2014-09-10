package com.example.heatmeapp;

import android.annotation.SuppressLint;
import android.app.AlarmManager;
import android.app.PendingIntent;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.os.PowerManager;
import android.widget.Toast;
@SuppressLint("Wakelock") public class AlarmBroadcastReceiver extends BroadcastReceiver {


	final public static String ONE_TIME = "onetime";
	public double latitud;
	public double longitud;

	@Override
	public void onReceive(Context context, Intent intent) { 
		PowerManager pm = (PowerManager) context.getSystemService(Context.POWER_SERVICE);
		PowerManager.WakeLock wl = pm.newWakeLock(PowerManager.PARTIAL_WAKE_LOCK, "YOUR TAG");
		
		//Acquire the lock
		wl.acquire();
		//Bundle extras = intent.getExtras();

		TestService gps = new TestService(context);
    	if (gps.canGetLocation()) {
    		Toast.makeText(context, Double.toString(gps.getLatitude()), Toast.LENGTH_SHORT).show();
    		latitud = gps.getLatitude();
    		Toast.makeText(context, Double.toString(gps.getLongitude()), Toast.LENGTH_SHORT).show();
    		longitud = gps.getLongitude();
    		//new sendData().doInBackground();
    		
    	}
		
        
		//Release the lock
		wl.release();
	}

	public void SetAlarm(Context context)
	{
		AlarmManager am=(AlarmManager)context.getSystemService(Context.ALARM_SERVICE);
		Intent intent = new Intent(context, AlarmBroadcastReceiver.class);
		intent.putExtra(ONE_TIME, Boolean.FALSE);
		PendingIntent pi = PendingIntent.getBroadcast(context, 0, intent, 0);
		//After 10 seconds
		am.setRepeating(AlarmManager.RTC_WAKEUP, System.currentTimeMillis(), 1000 * 60 , pi); 
	}
	
	public void CancelAlarm(Context context)
    {
        Intent intent = new Intent(context, AlarmBroadcastReceiver.class);
        PendingIntent sender = PendingIntent.getBroadcast(context, 0, intent, 0);
        AlarmManager alarmManager = (AlarmManager) context.getSystemService(Context.ALARM_SERVICE);
        alarmManager.cancel(sender);
    }

}
