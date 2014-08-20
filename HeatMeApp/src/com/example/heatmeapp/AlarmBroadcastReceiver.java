package com.example.heatmeapp;

import android.app.AlarmManager;
import android.app.PendingIntent;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.os.PowerManager;
public class AlarmBroadcastReceiver extends BroadcastReceiver {


	final public static String ONE_TIME = "onetime";
	 
	 @Override
	 public void onReceive(Context context, Intent intent) {
	   PowerManager pm = (PowerManager) context.getSystemService(Context.POWER_SERVICE);
	         PowerManager.WakeLock wl = pm.newWakeLock(PowerManager.PARTIAL_WAKE_LOCK, "YOUR TAG");
	         //Acquire the lock
	        
	         wl.acquire();
	         Bundle extras = intent.getExtras();
	          
	         if(extras != null && extras.getBoolean(ONE_TIME, Boolean.FALSE)){
	        	 
	         } 
	         
	         Intent i = new Intent(context, LocalizationService.class);
	         context.startService(i);
	         
	         //Release the lock
	         wl.release();
	 }
	 
	 public void SetAlarm(Context context)
	    {
	        AlarmManager am=(AlarmManager)context.getSystemService(Context.ALARM_SERVICE);
	        Intent intent = new Intent(context, AlarmBroadcastReceiver.class);
	        intent.putExtra(ONE_TIME, Boolean.FALSE);
	        PendingIntent pi = PendingIntent.getBroadcast(context, 0, intent, 0);
	        //After 5 seconds
	        am.setRepeating(AlarmManager.RTC_WAKEUP, System.currentTimeMillis(), 1000 * 10 , pi); 
	    }
	 
	 

}
