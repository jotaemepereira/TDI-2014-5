#include "ofApp.h"
#include "stdlib.h"
#include <string>

/**
 C++ client example using sockets
 */
#include<iostream>    //cout
#include<stdio.h> //printf
#include<string.h>    //strlen
#include<string>  //string
#include<sys/socket.h>    //socket
#include<arpa/inet.h> //inet_addr
#include<netdb.h> //hostent

using namespace std;


int connect(string address , int port)
{
    //create socket if it is not already created
    
    struct sockaddr_in server;
    
    //Create socket
    int sock = socket(AF_INET , SOCK_STREAM , 0);
    if (sock == -1)
    {
        //perror("Could not create socket");
    }
    
    //cout<<"Socket created\n";
    
    //setup address structure
    
    if(inet_addr(address.c_str()) == -1)
    {
        struct hostent *he;
        struct in_addr **addr_list;
        
        //resolve the hostname, its not an ip address
        if ( (he = gethostbyname( address.c_str() ) ) == NULL)
        {
            //gethostbyname failed
            herror("gethostbyname");
            //cout<<"Failed to resolve hostname\n";
            
            return 0;
        }
        
        //Cast the h_addr_list to in_addr , since h_addr_list also has the ip address in long format only
        addr_list = (struct in_addr **) he->h_addr_list;
        
        for(int i = 0; addr_list[i] != NULL; i++)
        {
            //strcpy(ip , inet_ntoa(*addr_list[i]) );
            server.sin_addr = *addr_list[i];
            
            //cout<<address<<" resolved to "<<inet_ntoa(*addr_list[i])<<endl;
            
            break;
        }
    }
    
    //plain ip address
    else
    {
        server.sin_addr.s_addr = inet_addr( address.c_str() );
    }
    
    server.sin_family = AF_INET;
    server.sin_port = htons( port );
    
    //Connect to remote server
    if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        //perror("connect failed. Error");
        return 1;
    }
    
    //cout<<"Connected\n";
    
    return sock;
}

/**
 Send data to the connected host
 */

bool send_data(string data, int sock)
{
    //Send some data
    if( send(sock , data.c_str() , strlen( data.c_str() ) , 0) < 0)
    {
        //perror("Send failed : ");
        return false;
    }
    //cout<<"Data send\n";
    
    return true;
}

/**
 Receive data from the connected host
 */

string receive(int size, int sock)
{
    char buffer[size];
    string reply;
    
    //Receive a reply from the server
    if( recv(sock , buffer , sizeof(buffer) , 0) < 0)
    {
        //puts("recv failed");
    }
    
    reply = buffer;
    return reply;
}



//--------------------------------------------------------------
void ofApp::setup(){
    
    this->width = ofGetWidth();
    this->height = ofGetHeight();
    
    this->ultimox = 0;
    this->ultimoy = 0;
    
    this->ganaste = false;
    this->intentos = 0;
    
    //Obtengo imagen al azar
    int random = rand() % 13 + 1;
    stringstream ss;
    ss << random;
    this->ganadora_img = "face" + ss.str() + ".jpg";
    this->ganadora = "face" + ss.str();
    
    bottomLayer.loadImage(this->ganadora);
    mask.loadImage("circle.png");
    perdiste.loadImage("perdiste.png");
    ofganaste.loadImage("ganaste.png");
    
    bool retina = true;
    grabber.setup(this->width, this->height, retina);
    
    maskShader.setup("composite", "composite");
    maskShader.begin();
    maskShader.setTexture("Tex0", bottomLayer.getTextureReference(), 0);
    maskShader.setTexture("Tex1", mask.getTextureReference(), 1);
    maskShader.end();
    
    host = "127.0.0.1";
    sock = connect(host , 6555);
    
    ofSetVerticalSync(true);
    ofEnableSmoothing();
    
    drawPadding = false;
    gui = new ofxUICanvas();
    gui->setName("Botones");
    gui->setGlobalButtonDimension(92.3);
    gui->setPosition(0, this->height-90);
    gui->setWidgetPosition(OFX_UI_WIDGET_POSITION_DOWN);
    gui->setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT);
    gui->addMultiImageButton("face1", "face1_small.png", false);
    gui->addMultiImageButton("face2", "face2_small.png", false);
    gui->addMultiImageButton("face3", "face3_small.png", false);
    gui->addMultiImageButton("face4", "face4_small.png", false);
    gui->addMultiImageButton("face5", "face5_small.png", false);
    gui->addMultiImageButton("face6", "face6_small.png", false);
    gui->addMultiImageButton("face7", "face7_small.png", false);
    gui->addMultiImageButton("face8", "face8_small.png", false);
    gui->addMultiImageButton("face9", "face9_small.png", false);
    gui->addMultiImageButton("face10", "face10_small.png", false);
    gui->addMultiImageButton("face11", "face11_small.png", false);
    gui->addMultiImageButton("face12", "face12_small.png", false);
    gui->addMultiImageButton("face13", "face13_small.png", false);
    gui->autoSizeToFitWidgets();
    
    gui2 = new ofxUICanvas();
    gui2->setName("New Game");
    gui2->setColorBack(ofxUIColor(255, 255, 255, 0));
    gui2->setPadding(100);
    gui2->setGlobalButtonDimension(140);
    gui2->setPosition(this->width/2 - 180, this->height/2 + 140);
    gui2->addMultiImageButton("newGame", "jugar.png", false);
    gui2->setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT);
    gui2->addMultiImageButton("exit", "salir.png", false);
    gui2->setVisible(false);
    gui2->autoSizeToFitWidgets();
    
    gui3 = new ofxUICanvas();
    gui3->setName("Intentos");
    gui3->setColorBack(ofxUIColor(255, 255, 255, 0));
    stringstream intento_int;
    intento_int << this->intentos;
    gui3->addLabel("Intentos: " + intento_int.str(), OFX_UI_FONT_LARGE);
    gui3->setDimensions(120, 30);

    
    ofAddListener(gui2->newGUIEvent,this,&ofApp::guiEvent);
    ofAddListener(gui->newGUIEvent,this,&ofApp::guiEvent);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    grabber.grabScreen(0, 0);
    
    send_data("{\"category\": \"tracker\",\"request\" : \"get\",\"values\": [ \"frame\" ]}", sock);
    
    //receive and echo reply
    //cout<<"--------------------------\n\n";
    
    string s(receive(2048,sock));
    
    float x = 0;
    float y = 0;
    
    if (false){//if (s.length()){
        
        i = 0;
        while(s.data()[i]!='x' && i<s.length()){
            i++;
        }
        
        if (i==s.length()){
            //cout << s << endl;
            return 0;
        };
        
        i+=3;
        
        j=i;
        while(s.data()[j]!=',' && j<s.length()){
            j++;
        }
        
        if (j==s.length()){
            //cout << s << endl;
            return 0;
        };
        
        x = atof(s.substr(i,j-i).data());
        
        i = j;
        while(s.data()[i]!='y'  && i<s.length()){
            i++;
        }
        
        if (i==s.length()){
            //cout << s << endl;
            return 0;
        };
        
        i+=3;
        
        j=i;
        while(s.data()[j]!='}' && j<s.length()){
            j++;
        }
        
        
        if (j==s.length()){
            //cout << s << endl;
            return 0;
        };
        
        y = atof(s.substr(i,j-i).data());
        
        
        //x
        
        if (x==0/* || abs(x-this->ultimox)<10*/){
            this->x = this->ultimox;
        }
        else{
            this->x = x;
            this->ultimox = x;
        }
        
        //y
        
        if (y==0/* || abs(y-this->ultimoy)<10*/){
            this->y = this->ultimoy;
        }
        else{
            this->y = y;
            this->ultimoy = y;
        }
        
        //cout << "x: " << x << " " << "y: " << y << endl;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    if (intentos < 3) {

    grabber.draw(0, 0);
        
    maskShader.begin();
    
    glActiveTexture(GL_TEXTURE0_ARB);
    bottomLayer.getTextureReference().bind();
    
    glActiveTexture(GL_TEXTURE1_ARB);
    mask.getTextureReference().bind();
    
    glBegin(GL_QUADS);
    
    float maskOffsetY = this->height/2 - this->y;
    float maskOffsetX = this->width/2 - this->x;
    glMultiTexCoord2d(GL_TEXTURE0_ARB, 0, 0);
    glMultiTexCoord2d(GL_TEXTURE1_ARB, maskOffsetX, maskOffsetY);
    glVertex2f( 0, 0);
    
    glMultiTexCoord2d(GL_TEXTURE0_ARB, bottomLayer.getWidth(), 0);
    glMultiTexCoord2d(GL_TEXTURE1_ARB, mask.getWidth() + maskOffsetX, maskOffsetY);
    glVertex2f( ofGetWidth(), 0);
    
    glMultiTexCoord2d(GL_TEXTURE0_ARB, bottomLayer.getWidth(), bottomLayer.getHeight());
    glMultiTexCoord2d(GL_TEXTURE1_ARB, mask.getWidth() + maskOffsetX, mask.getHeight() + maskOffsetY);
    glVertex2f( ofGetWidth(), ofGetHeight());
    
    glMultiTexCoord2d(GL_TEXTURE0_ARB, 0, bottomLayer.getHeight());
    glMultiTexCoord2d(GL_TEXTURE1_ARB, maskOffsetX, mask.getHeight() + maskOffsetY);
    glVertex2f( 0, ofGetHeight() );
    
    glEnd();
    
    glActiveTexture(GL_TEXTURE1_ARB);
    mask.getTextureReference().unbind();  
    
    glActiveTexture(GL_TEXTURE0_ARB);  
    bottomLayer.getTextureReference().unbind();
    
    maskShader.end();
    
    }
    if (this->ganaste) {
        //Ganaste!
        gui2->setVisible(true);
        grabber.draw(0, 0);
        ofganaste.draw(0, 0);
        
    }
    
    if (this->intentos >= 3) {
        //Perdiste!
        grabber.draw(0, 0);
        perdiste.draw(0, 0);
        gui2->setVisible(true);
        gui->setVisible(false);
    }
    
}

//--------------------------------------------------------------
void ofApp::guiEvent(ofxUIEventArgs &e)
{
    string name = e.widget->getName();
    int kind = e.widget->getKind();
    
    ofxUIImageButton *button = (ofxUIImageButton *) e.widget;
    
    if (name.compare("newGame") == 0 && (button->getValue() == 1)) {
        this->intentos = 0;
        gui2->setVisible(false);
        gui->setVisible(true);
        stringstream intento_int;
        intento_int << this->intentos;
        gui3->removeWidgets();
        gui3->addLabel("Intentos: " + intento_int.str(), OFX_UI_FONT_LARGE);
        gui3->setDimensions(120, 30);
        this->ganaste = false;
        
        //Obtengo imagen al azar
        int random = rand() % 13 + 1;
        stringstream ss;
        ss << random;
        this->ganadora_img = "face" + ss.str() + ".jpg";
        this->ganadora = "face" + ss.str();
        
        bottomLayer.loadImage(this->ganadora);
    }
    
    if (name.compare("exit") == 0 && (button->getValue() == 1)) {
        exit();
    }
    
    if (name.compare(this->ganadora) == 0 && (button->getValue() == 1)) {
        this->ganaste = true;
        gui2->setVisible(true);
        gui->setVisible(false);
        
    }
    if ((name.find("face") != string::npos) && (name.compare(this->ganadora) != 0) && (button->getValue() == 1))  {
        this->intentos += 1;
        stringstream intento_int;
        intento_int << this->intentos;
        gui3->removeWidgets();
        gui3->addLabel("Intentos: " + intento_int.str(), OFX_UI_FONT_LARGE);
        gui3->setDimensions(120, 30);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}



