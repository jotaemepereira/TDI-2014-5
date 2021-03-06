import ddf.minim.spi.*;
import ddf.minim.signals.*;
import ddf.minim.*;
import ddf.minim.analysis.*;
import ddf.minim.ugens.*;
import ddf.minim.effects.*;

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
HashMap<String,Double> co2 = new HashMap<String,Double>();
ArrayList allDrops = new ArrayList();
ArrayList <Cloud> clouds = new ArrayList <Cloud>();
int sentido = -1;
int dropsCount = 0;
String actualCountry = "Angola";


//Variables de la musica
Minim minim;
AudioPlayer player;
AudioInput input;

//Sol
float num;
  
void setup(){
  
  size(displayWidth, displayHeight);
  if (frame != null) {
    frame.setResizable(true);
  }
  
  
  minim = new Minim(this);
  
  noStroke();
  colorMode(HSB, 100);
  
  XML xml = loadXML("dataCO2Emission.xml");
  XML[] data = xml.getChildren("data");
  XML[] records = data[0].getChildren("record");
  XML[] fields;
  
  for (int i = 0; i < records.length; i++) {
    
    fields = records[i].getChildren("field");
    if (fields[1].getContent().equals("2010")){
      
      String country = fields[0].getContent();
      String metric = fields[2].getContent();
      co2.put(country, Double.parseDouble(metric));
    }
  }
  
  Double metric = co2.get(actualCountry);
  if (metric != null) {
    player = minim.loadFile("data/rainSoft.mp3");
    metric = Math.ceil(metric);
    emissionMusic(metric);
    for (int k = 0; k < metric; k++){
      sentido = sentido*(-1);
      clouds.add(new Cloud(Math.round(random(100, displayWidth -100)), Math.round(random(60, 80)), Math.round(random(70, 90)), sentido));
    }
  }
  
  cp5 = new ControlP5(this);
  cp5.setControlFont(new ControlFont(createFont("Verdana", 10), 10));
  DropdownList droplist = cp5.addDropdownList("Select the Country or Area").setPosition(20, 35);
  
  xml = loadXML("dataForestacion.xml");
  data = xml.getChildren("data");
  records = data[0].getChildren("record");
  
  
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
  background(30);
  int j = 3;
  for(int i = 0; i < branches.size(); i++){
  
    stroke(i*20, (i*2)+50, 150, 70);
    Branch b = (Branch) branches.get(i);
    pushMatrix();
    translate((width/5)+(250*i), height);
    rotate(radians(b.startAngle));
    b.branch(b.segments, b.hojas);
    popMatrix();
    
    fill(i*20, (i*2)+50, 150, 70);
    rect(20,(i*30) + height - 130, 20, 20);
    text(b.year, 47, height - 130 + j, width, height);
    j = j + 30;
  }
  
  Double emissions = co2.get(actualCountry);
  if (emissions != null && emissions != 0){
    
    if (emissions <= 1 && dropsCount % 10 == 0){
      addDrop();
    }
    else if (emissions > 1 && emissions <= 3 && dropsCount % 5 == 0){
      addDrop();
    }
    else if (emissions > 3 && emissions <= 7 && dropsCount % 1 == 0){
      addDrop();
    }
    else if (emissions > 7 && emissions <= 11){
      addDrop();
      addDrop();
    }
    else if (emissions > 11 && emissions <= 15){
      addDrop();
      addDrop();
      addDrop();
    }
    else if (emissions > 15 && emissions <= 18){
      addDrop();
      addDrop();
      addDrop();
      addDrop();
      addDrop();
    }
    else if (emissions > 18){
      addDrop();
      addDrop();
      addDrop();
      addDrop();
      addDrop();
      addDrop();
      addDrop();
    };
  }
  else {
    dibujarSol(); 
  }
  
  dropsCount++;
  
  for (int k = 0; k < allDrops.size(); k++) {
    Raindrop drop = (Raindrop) allDrops.get(k);
    drop.update();
  }
  
  for (int w = 0; w < clouds.size(); w++) {
    Cloud c = clouds.get(w);
    c.update();
  }

}

void controlEvent(ControlEvent theEvent) {
  
  if (theEvent.isGroup()) {
    
    DropdownList ddl = (DropdownList) theEvent.getGroup();
    int index = Math.round(theEvent.getGroup().getValue());
    actualCountry = ddl.getItem(index).getName();
    println("Country | Area selected : " + actualCountry);
    
    Dato datoMenor, datoMedioBajo, datoMedioAlto, datoMayor;
    
    ArrayList <Dato> datos = hm.get(actualCountry);
    datoMenor = datos.get(0);
    datoMedioBajo = datos.get(1);
    datoMedioAlto = datos.get(2);
    datoMayor = datos.get(3);
    
    /*println("dato Menor: " + datoMenor.value + " - año: " + datoMenor.year);
    println("dato Medio Bajo: " + datoMedioBajo.value+ " - año: " + datoMedioBajo.year);
    println("dato Medio Alto : " + datoMedioAlto.value+ " - año: " + datoMedioAlto.year);
    println("dato alto : " + datoMayor.value+ " - año: " + datoMayor.year);*/
          
    branches.clear();
    if (datoMenor.year.equals("1990")){
      branches.add(new Branch(actualCountry, 4*parseFloat(datoMenor.value), 16.0, datoMenor.year));
    }else if (datoMedioBajo.year.equals("1990")){
      branches.add(new Branch(actualCountry, 4*parseFloat(datoMedioBajo.value), 8.0, datoMedioBajo.year));
    }else if (datoMedioAlto.year.equals("1990")){
      branches.add(new Branch(actualCountry, 4*parseFloat(datoMedioAlto.value), 4.0, datoMedioAlto.year));
    }else{
      branches.add(new Branch(actualCountry, 4*parseFloat(datoMayor.value), 2.0, datoMayor.year));  
    }

    if (datoMenor.year.equals("2000")){
      branches.add(new Branch(actualCountry, 4*parseFloat(datoMenor.value), 16.0, datoMenor.year));
    }else if (datoMedioBajo.year.equals("2000")){
      branches.add(new Branch(actualCountry, 4*parseFloat(datoMedioBajo.value), 8.0, datoMedioBajo.year));
    }else if (datoMedioAlto.year.equals("2000")){
      branches.add(new Branch(actualCountry, 4*parseFloat(datoMedioAlto.value), 4.0, datoMedioAlto.year));
    }else{
      branches.add(new Branch(actualCountry, 4*parseFloat(datoMayor.value), 2.0, datoMayor.year));  
    }
    
    if (datoMenor.year.equals("2005")){
      branches.add(new Branch(actualCountry, 4*parseFloat(datoMenor.value), 16.0, datoMenor.year));
    }else if (datoMedioBajo.year.equals("2005")){
      branches.add(new Branch(actualCountry, 4*parseFloat(datoMedioBajo.value), 8.0, datoMedioBajo.year));
    }else if (datoMedioAlto.year.equals("2005")){
      branches.add(new Branch(actualCountry, 4*parseFloat(datoMedioAlto.value), 4.0, datoMedioAlto.year));
    }else{
      branches.add(new Branch(actualCountry, 4*parseFloat(datoMayor.value), 2.0, datoMayor.year));  
    }  
    
    if (datoMenor.year.equals("2010")){
      branches.add(new Branch(actualCountry, 4*parseFloat(datoMenor.value), 16.0, datoMenor.year));
    }else if (datoMedioBajo.year.equals("2010")){
      branches.add(new Branch(actualCountry, 4*parseFloat(datoMedioBajo.value), 8.0, datoMedioBajo.year));
    }else if (datoMedioAlto.year.equals("2010")){
      branches.add(new Branch(actualCountry, 4*parseFloat(datoMedioAlto.value), 4.0, datoMedioAlto.year));
    }else{
      branches.add(new Branch(actualCountry, 4*parseFloat(datoMayor.value), 2.0, datoMayor.year));  
    }
    
    allDrops.clear();
    clouds.clear();
    Double metric = co2.get(actualCountry);
    
    if (metric != null) {
      metric = Math.ceil(metric);
      emissionMusic(metric);
      println("metric " + metric);
      for (int k = 0; k < metric; k++){
        sentido = sentido*(-1);
        clouds.add(new Cloud(Math.round(random(100, displayWidth -100)), Math.round(random(60, 80)), Math.round(random(70, 90)), sentido));
      }
    }
    else {
      dibujarSol();
      emissionMusic(0);
    }
  };
};

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
///*************///

//*** BRANCH ***///

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
      rotate(radians(-40+theta));
      branch(len, h);
      popMatrix();
      
      pushMatrix();
      rotate(radians(40+theta));
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
///************///

//*** DATOS ***///

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
///*************///

//*** CLOUDS ***///

class Cloud {
  int x, y, r;
  float xSpeed;
 
  Cloud(int x_, int y_, int r_, float xSpeed_) {
    x=x_;
    y=y_;
    r=r_;
    xSpeed= xSpeed_;
  }
   
  void update(){
    display();
    drift();
  }
 
  void display() {
    noStroke();
    fill(60, 70);
    ellipse(x, y, r, r); 
    ellipse(x-(r/2), y, r*.8, r*.8);
  }
   
  void drift(){
    x+=xSpeed;
    if (x>width || x < 0) xSpeed=xSpeed*-1;
  }
   
}
///***********///

//*** RAIN ***///

void addDrop() {
 
  int dropX=int(random(0, displayWidth));
  int dropY=int(random(40, 100));
  int dropSpeed=int(random(1, 2));
  Raindrop drop = new Raindrop(dropX, dropY, 10);
  allDrops.add(drop);
}

class Raindrop {
  int x, y, len;
  float ySpeed = 4.5;
 
  Raindrop(int x_, int y_, int len_) {
    x=x_;
    y=y_;
    len = len_;
  }
 
  void update(){
    display();
    fall(); 
  }
 
  void display() {
    line(x, y, x, y+len);
  }
   
  void fall(){
    y+=ySpeed;
  }
}
///**************///


///*** MUSICA ***///
void emissionMusic(double emission) {  
  if (emission <= 0) {
    musicPlayer("birds.mp3");
  }
  else if (emission < 8) {
    musicPlayer("rainSoft.mp3");
  }
  else if (emission >= 8 && emission < 16) {
    musicPlayer("rainMed.mp3");
  }
  else if (emission >= 16) {
    musicPlayer("thunder.mp3");
  }
}

void musicPlayer(String fileName) {  
    
  if (player.isPlaying()) 
    player.close();
  
  player = minim.loadFile("data/" + fileName);
  input = minim.getLineIn();
  player.play();
}
///***********///


///*** SOL ***///
void dibujarSol() {
  //Sol
  noStroke();
  translate(width/2, 0);
  for (int i = -180; i < 180; i+=12) {
    float x = sin(radians(i)) * 15;
    float y = cos(radians(i)) * 15;
       
    //float x = i;
    //float y = 0;
    pushMatrix();
    translate(x, y);
    rotate(radians(-i));
    for(int q = 0; q < 200; q+=5){
      float d = map(q, 0, 200, 40, 0);
      float a = sin(-i+q+num) * 2;
      fill(15, 52, 150, 20);
      ellipse(a, q, d, d);
    }
    popMatrix();
  }
   
  num += 0.2;
  translate(-displayWidth/2, 0);
}

