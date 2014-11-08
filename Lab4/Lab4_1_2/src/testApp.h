/*
 * Copyright (c) 2013 Dan Wilcox <danomatika@gmail.com>
 *
 * BSD Simplified License.
 * For information on usage and redistribution, and for a DISCLAIMER OF ALL
 * WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 *
 * See https://github.com/danomatika/ofxMidi for documentation
 *
 */
#pragma once

#include "ofMain.h"
#include "ofxMidi.h"

class testApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
	void exit();
	
	void keyPressed (int key);
	void keyReleased (int key);
	
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased();
	
    
    //**** IMAGE & COLORS
    
    void processOpenFileSelection(ofFileDialogResult openFileResult);
    int mapNote(int note);
    
    vector<ofImage>loadedImages;
    vector<ofImage>processedImages;
    string originalFileExtension;
    ofImage image, imgTmp;
    
    
    //**** MIDI
    
    ofxMidiOut midiOut;
    int channel;
    unsigned int currentPgm;
    int note, velocity;
    int pan, bend, touch, polytouch, altura;
    bool port1, port2, port3;
    int noteRed = -1;
    int noteGreen = -1;
    int noteBlue = -1;
    int red, green, blue;
    
};
