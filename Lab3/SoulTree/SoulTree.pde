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
    
    stroke(i*20, (i*2)+50, 150, 70);
    Branch b = (Branch) branches.get(i);
    pushMatrix();
    translate((width/2)+30, height);
    rotate(radians(b.startAngle));
    b.branch(b.segments);
    popMatrix();
    
    fill(i*20, (i*2)+50, 150, 70);
    rect(20,(i*30)+50, 20, 20);
    
  }
  
  text("Año 2010", 47, 53, width, height);
  text("Año 2005", 47, 83, width, height);
  text("Año 2000", 47, 113, width, height);
  text("Año 1990", 47, 143, width, height);
  
}

void controlEvent(ControlEvent theEvent) {
  
  if (theEvent.isGroup()) {
    
    // check if the Event was triggered from a ControlGroup
    DropdownList ddl = (DropdownList) theEvent.getGroup();
    int index = Math.round(theEvent.getGroup().getValue());
    String country = ddl.getItem(index).getName();
    println("Country | Area selected : " + country);
    
    XML xml = loadXML("data.xml");
    XML[] data = xml.getChildren("data");
    XML[] records = data[0].getChildren("record");
    XML[] fields;
    
    int i = 0;
    while (i<records.length){
      
      fields = records[i].getChildren("field");
      
      if (fields[0].getContent().compareTo(country)==0){
        
        branches.clear();
    
        branches.add(new Branch(country, 4*parseInt(fields[2].getContent())));
        println("2010" + parseFloat(fields[2].getContent()));
        i++;
        
        fields = records[i].getChildren("field");
        branches.add(new Branch(country, 4*parseInt(fields[2].getContent())));
        println("2005" + parseFloat(fields[2].getContent()));
        i++;
        
        fields = records[i].getChildren("field");
        branches.add(new Branch(country, 4*parseInt(fields[2].getContent())));
        println("2000" + parseFloat(fields[2].getContent()));
        i++;
        
        fields = records[i].getChildren("field");
        branches.add(new Branch(country, 4*parseInt(fields[2].getContent())));  
        println("1990" + parseFloat(fields[2].getContent()));
        
        break;
        
      }
      else
        i++;
        
    };
    
    if (i==records.length){
       println("Error! | "+country+" no encontrado.");
       return;
    };

  };

};
 
class Branch {
  
  float segments, startAngle, theta, num;
  
  Branch(String c, int i){
    
    /*Largo
    segments = random(100, 300);
    segments = 64; */
    segments = i;
    startAngle = random(-20, 20);
    
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

    }
    else{
      
      ellipse(0, 0, 3, 3);
      
    }
    
    num += 0.001;
    
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
  ddl.setValue(214.0);
  
}




