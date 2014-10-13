import java.io.File;
import java.io.FileInputStream;
import java.io.InputStream;
import java.util.Map;
import org.apache.commons.io.IOUtils;
import processing.data.XML;
import controlP5.*;

ControlP5 cp5;
ArrayList branches = new ArrayList();
HashMap<String,ArrayList <Dato>> hm = new HashMap<String,ArrayList <Dato>>();
 
void setup(){
  
  size(800, 640);
  stroke(0, 150, 255, 65);
  for(int i = 0; i < 5; i++){branches.add(new Branch());}
  
  cp5 = new ControlP5(this);
  cp5.setControlFont(new ControlFont(createFont("Verdana", 10), 10));
  DropdownList droplist = cp5.addDropdownList("Select the Country or Area").setPosition(20, 35);

  XML xml = loadXML("data.xml");
  XML[] data = xml.getChildren("data");
  XML[] records = data[0].getChildren("record");
  XML[] fields;
  
  int j = 0;
  
  for (int i = 0; i < records.length; i++) {
    fields = records[i].getChildren("field");
    
    String country = fields[0].getContent();
    String year = fields[1].getContent();
    String value = fields[2].getContent();
    Dato d = new Dato();
    d.setYear(year);
    d.setValue(value);
    
    ArrayList <Dato> list = hm.get(country);
    if (list != null){
      list.add(d);
    }
    else {
      list = new ArrayList <Dato>();
      list.add(d);  
      
      droplist.addItem(country, j);
      j++;
    }
    hm.put(country, list);
  }
  customize(droplist);
}
 
void draw(){
  background(0);
  for(int i = 0; i < branches.size(); i++){
    Branch b = (Branch) branches.get(i);
    pushMatrix();
    translate(width/2, height);
    rotate(radians(b.startAngle));
    b.branch(b.segments);
    popMatrix();
  }
}

void controlEvent(ControlEvent theEvent) {
  // DropdownList is of type ControlGroup.
  // A controlEvent will be triggered from inside the ControlGroup class.
  // therefore you need to check the originator of the Event with
  // if (theEvent.isGroup())
  // to avoid an error message thrown by controlP5.

  if (theEvent.isGroup()) {
    // check if the Event was triggered from a ControlGroup
    DropdownList ddl = (DropdownList) theEvent.getGroup();
    int index = Math.round(theEvent.getGroup().getValue());
    String country = ddl.getItem(index).getName();
    println("event from group : " + country);
  }
}
 
class Branch {
  float segments, startAngle, theta, num;
  Branch(){
    //Largo
    //segments = random(150, 250);
    segments = 300;
    startAngle = random(-30, 30);
  }
   
  void branch(float len){
    float t = map(len, 1, 160, 1, 5);
    theta = sin(len+num) * 3;
    strokeWeight(t);
    line(0, 0, 0, -len);
    ellipse(0, 0, t, t);
    translate(0, -len);
    len *= 0.50;
    if(len > 2){
      pushMatrix();
      rotate(radians(-20+theta));
      branch(len);
      popMatrix();
      
      pushMatrix();
      rotate(radians(20-theta));
      branch(len);
      popMatrix();

    }else{
      ellipse(0, 0, 3, 3);
    }
    num += 0.001;
  }
}

class Dato {
  String year, value;
  
  Dato(){};
  
  void setYear(String y){
    this.year = y; 
  }
  
  void setValue(String v){
    this.value = v; 
  }
  
  String getYear(){
    return this.year; 
  }
 
  String getValue(){
    return this.value; 
  }
}

void customize(DropdownList ddl) {
  // a convenience function to customize a DropdownList
  ddl.setWidth(280);
  ddl.setHeight(160);
  ddl.setBackgroundColor(color(190));
  ddl.setItemHeight(22);
  ddl.setBarHeight(22);
  ddl.captionLabel().style().marginTop = 3;
  ddl.captionLabel().style().marginLeft = 3;
  ddl.valueLabel().style().marginTop = 3;
  //ddl.scroll(0);
  ddl.setColorBackground(color(60));
  ddl.setColorActive(color(255, 128));
}




