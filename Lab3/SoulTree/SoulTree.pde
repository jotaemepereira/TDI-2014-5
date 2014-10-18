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
//mili
  
void setup(){
  
  size(displayWidth, displayHeight);
  if (frame != null) {
    frame.setResizable(true);
  }
  noStroke();
  colorMode(HSB, 100);
  //stroke(0, 150, 255, 65);
  
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
      insertOrdered (list, d);
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
  int j = 53;
  for(int i = 0; i < branches.size(); i++){
  
    stroke(i*20, (i*2)+50, 150, 70);
    Branch b = (Branch) branches.get(i);
    pushMatrix();
    translate((width/5)+(250*i), height);
    rotate(radians(b.startAngle));
    b.branch(b.segments, b.hojas);
    popMatrix();
    
    fill(i*20, (i*2)+50, 150, 70);
    rect(20,(i*30)+50, 20, 20);
    text(b.year, 47, j, width, height);
    j = j + 30;
  }
}

void controlEvent(ControlEvent theEvent) {
  
  if (theEvent.isGroup()) {
    
    // check if the Event was triggered from a ControlGroup
    DropdownList ddl = (DropdownList) theEvent.getGroup();
    int index = Math.round(theEvent.getGroup().getValue());
    String country = ddl.getItem(index).getName();
    println("Country | Area selected : " + country);
    
    Dato datoMenor, datoMedioBajo, datoMedioAlto, datoMayor;
    
    ArrayList <Dato> datos = hm.get(country);
    datoMenor = datos.get(0);
    datoMedioBajo = datos.get(1);
    datoMedioAlto = datos.get(2);
    datoMayor = datos.get(3);
    
    println("dato Menor: " + datoMenor.value + " año: " + datoMenor.year);
    println("dato Medio Bajo: " + datoMedioBajo.value+ " año: " + datoMedioBajo.year);
    println("dato Medio Alto : " + datoMedioAlto.value+ " año: " + datoMedioAlto.year);
    println("dato alto : " + datoMayor.value+ " año: " + datoMayor.year);
          
    branches.clear();
    if (datoMenor.year.equals("1990")){
      branches.add(new Branch(country, 4*parseFloat(datoMenor.value), 16.0, datoMenor.year));
    }else if (datoMedioBajo.year.equals("1990")){
      branches.add(new Branch(country, 4*parseFloat(datoMedioBajo.value), 8.0, datoMedioBajo.year));
    }else if (datoMedioAlto.year.equals("1990")){
      branches.add(new Branch(country, 4*parseFloat(datoMedioAlto.value), 4.0, datoMedioAlto.year));
    }else{
      branches.add(new Branch(country, 4*parseFloat(datoMayor.value), 2.0, datoMayor.year));  
    }

    if (datoMenor.year.equals("2000")){
      branches.add(new Branch(country, 4*parseFloat(datoMenor.value), 16.0, datoMenor.year));
    }else if (datoMedioBajo.year.equals("2000")){
      branches.add(new Branch(country, 4*parseFloat(datoMedioBajo.value), 8.0, datoMedioBajo.year));
    }else if (datoMedioAlto.year.equals("2000")){
      branches.add(new Branch(country, 4*parseFloat(datoMedioAlto.value), 4.0, datoMedioAlto.year));
    }else{
      branches.add(new Branch(country, 4*parseFloat(datoMayor.value), 2.0, datoMayor.year));  
    }
    
    if (datoMenor.year.equals("2005")){
      branches.add(new Branch(country, 4*parseFloat(datoMenor.value), 16.0, datoMenor.year));
    }else if (datoMedioBajo.year.equals("2005")){
      branches.add(new Branch(country, 4*parseFloat(datoMedioBajo.value), 8.0, datoMedioBajo.year));
    }else if (datoMedioAlto.year.equals("2005")){
      branches.add(new Branch(country, 4*parseFloat(datoMedioAlto.value), 4.0, datoMedioAlto.year));
    }else{
      branches.add(new Branch(country, 4*parseFloat(datoMayor.value), 2.0, datoMayor.year));  
    }  
    
    if (datoMenor.year.equals("2010")){
      branches.add(new Branch(country, 4*parseFloat(datoMenor.value), 16.0, datoMenor.year));
    }else if (datoMedioBajo.year.equals("2010")){
      branches.add(new Branch(country, 4*parseFloat(datoMedioBajo.value), 8.0, datoMedioBajo.year));
    }else if (datoMedioAlto.year.equals("2010")){
      branches.add(new Branch(country, 4*parseFloat(datoMedioAlto.value), 4.0, datoMedioAlto.year));
    }else{
      branches.add(new Branch(country, 4*parseFloat(datoMayor.value), 2.0, datoMayor.year));  
    }  
  };
};
 
class Branch {
  
  float segments, startAngle, theta, num, hojas;
  String year;
  
  Branch(String c, float l, float h, String y){
    
    segments = l;
    startAngle = random(-5, 5);
    hojas = h;
    year = y;
  }
   
  void branch(float len, float h){
    
    float t = map(len, 1, 160, 1, 5);
    theta = sin(len+num) * 3;
    strokeWeight(t);
    line(0, 0, 0, -len);
    ellipse(0, 0, t, t);
    translate(0, -len);
    len *= 0.50;
    
    if(len > h){
      
      pushMatrix();
      rotate(radians(-35+theta));
      branch(len, h);
      popMatrix();
      
      pushMatrix();
      rotate(radians(35+theta));
      branch(len, h);
      popMatrix();

      if (h == 2.0 && len > 16){
        
          pushMatrix();
          rotate(radians(10-theta));
          branch(len, h);
          popMatrix();
      }
      else if (h == 4.0 && len > 32){
        
          pushMatrix();
          rotate(radians(10-theta));
          branch(len, h);
          popMatrix();
      }
      
    }
    else{
      
      ellipse(0, 0, 3, 3);
    }   
    num += 0.0001;
  }
}

class Dato {
  
  String year, value;
  
  // CONSTRUCTOR
  Dato(){};
  
  // SETTERS
  void setYear(String y){
    this.year = y; 
  }
  
  void setValue(String v){
    this.value = v; 
  }
  
  // GETTERS
  String getYear(){
    return this.year; 
  }
  
  String getValue(){
    return this.value; 
  }
}

void customize(DropdownList ddl) {
  
  ddl.setWidth(280);
  ddl.setHeight(160);
  ddl.setBackgroundColor(color(190));
  ddl.setItemHeight(22);
  ddl.setBarHeight(22);
  ddl.captionLabel().style().marginTop = 3;
  ddl.captionLabel().style().marginLeft = 3;
  ddl.valueLabel().style().marginTop = 3;
  ddl.setColorBackground(color(60));
  ddl.setColorActive(color(255, 128));
  ddl.setValue(5.0);
}

ArrayList <Dato> insertOrdered (ArrayList <Dato> l, Dato d){
  
  int i = 0;
  boolean found = false;
  while(i < l.size() && !found) {

    found = (Float.parseFloat(d.value) <= Float.parseFloat(l.get(i).value));
    if (!found){
      i++;
    }  
  }
  if (!found){
    l.add(d);
  } 
  else {
    l.add(i, d);
  }
  return l;
}




