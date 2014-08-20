package com.example.heatmeapp;

import android.support.v7.app.ActionBarActivity;
import android.content.Context;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.Toast;


public class HeatMeActivity extends ActionBarActivity {

	private AlarmBroadcastReceiver alarm ;
	
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_heat_me);
        alarm = new AlarmBroadcastReceiver();
        Button btn = (Button) findViewById(R.id.button1);
        btn.setOnClickListener(new OnClickListener() {
			
			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				//Intent i = new Intent(HeatMeActivity.this, LocalizationService.class);
				//i.putExtra("name", "SurvivingwithAndroid");       
				//HeatMeActivity.this.startService(i);  
				startRepeatingTimer();
			}
		});
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
}
