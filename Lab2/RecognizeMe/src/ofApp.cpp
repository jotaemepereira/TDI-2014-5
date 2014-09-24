#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    topImage.loadImage("top.png");
    backImage.loadImage("back.png");
    maskImage.loadImage("circle.png");
    
    topLayer.allocate(1024,768);
    bottomLayer.allocate(1024,768);
    mask.allocate(1024,768);
}

//--------------------------------------------------------------
void ofApp::update(){
    //topLayer.setFromPixels(topImage.getPixels(), 1024, 768);
    //bottomLayer.setFromPixels(backImage.getPixels(), 1024, 768);
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    //bottomLayer.draw(0, 0);
    //topLayer.draw(0, 0);
    //mask.draw(mouseX, mouseY);
    
    //topLayer.operator-=(mask);
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

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
