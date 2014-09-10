package com.example.heatmeapp;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.ImageView;
public class CustomList extends ArrayAdapter<String>{
	private final Activity context;
	private final Integer[] imageId;
	
	public CustomList(Activity context,
			String[] web, Integer[] imageId) {
		super(context, R.layout.list_single, web);
		this.context = context;
		this.imageId = imageId;
	}
	
	@Override
    public View getDropDownView(int position, View convertView,ViewGroup parent) {
        return getCustomView(position, convertView, parent);
    }

    @Override
    public View getView(int position, View convertView, ViewGroup parent) {
       return getCustomView(position, convertView, parent);
    }
    
	@SuppressLint("InflateParams") public View getCustomView(int position, View view, ViewGroup parent) {
		LayoutInflater inflater = context.getLayoutInflater();
		View rowView= inflater.inflate(R.layout.list_single, null, true);
		ImageView imageView = (ImageView) rowView.findViewById(R.id.img);
		imageView.setImageResource(imageId[position]);
		return rowView;
	}
}
