#pragma once

#include "ofMain.h"
#include "ofxShader.h"
#include "ofxScreenGrab.h"
#include "ofxFilterLibrary.h"

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
};  

