import java.io.File;
import java.io.FileInputStream;
import java.io.InputStream;
import java.util.Map;
import org.apache.commons.io.IOUtils;
import processing.data.XML;

ArrayList branches = new ArrayList();
HashMap<String,ArrayList <Dato>> hm = new HashMap<String,ArrayList <Dato>>();
 
void setup(){
  
  size(640, 640);
  stroke(0, 150, 255, 65);
  for(int i = 0; i < 5; i++){branches.add(new Branch());}

  XML xml = loadXML("data.xml");
  XML[] data = xml.getChildren("data");
  XML[] records = data[0].getChildren("record");
  XML[] fields;
  
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
    }
    hm.put(country, list);
  }
  
  ArrayList val = hm.get("Uruguay");
  for(int i = 0; i < val.size(); i++){
    println("Uruguay is " + ((Dato) val.get(i)).getYear());
  }
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
 
class Branch {
  float segments, startAngle, theta, num;
  Branch(){
    //Largo
    //segments = random(100, 250);
    segments = 64;
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




