#pragma once

#include "ofxShader.h"
#include "ofxScreenGrab.h"
#include "ofxUI.h"
#include <string>
#include <unistd.h>
#include <cstring>

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed  (int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    
    int height, width;
    
    ofImage mask;
    ofImage bottomLayer;
    ofImage desktopImage;
    ofImage perdiste;
    ofImage ofganaste;
    
    ofxShader maskShader;
    ofxScreenGrab grabber;
    
    //enum estado {JUGANDO, TERMINADO};
    
    int sock;
    string host;
    
    string ganadora_img;
    string ganadora;
    bool ganaste;
    int intentos;
    
    int i, j;
    float x, y, ultimox, ultimoy;
    
    ofxUICanvas *gui;
    ofxUICanvas *gui2;
    ofxUICanvas *gui3;
    
    void guiEvent(ofxUIEventArgs &e);
    bool drawPadding;
    
    ofSoundPlayer fail;
    ofSoundPlayer gameover;
    ofSoundPlayer win;
};

