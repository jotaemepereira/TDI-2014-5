#pragma once

#include "ofxShader.h"
#include "ofxScreenGrab.h"
#include "ofxFilterLibrary.h"
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
    
    ofxShader maskShader;
    
    ofxScreenGrab grabber;
    
    AbstractFilter* filterLayer;
    
    int sock;
    string host;
    
    int i, j;
    float x, y, ultimox, ultimoy;
    
    ofxUICanvas *gui;
    void guiEvent(ofxUIEventArgs &e);
    bool drawPadding;
};

