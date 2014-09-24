#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    topImage.allocate(320,240, OF_IMAGE_COLOR_ALPHA);
    backImage.allocate(320,240, OF_IMAGE_COLOR);
    maskImage.allocate(320,240, OF_IMAGE_COLOR_ALPHA);
    
    topImage.loadImage("top.png");
    backImage.loadImage("back.png");
    maskImage.loadImage("circle.png");
    
    topLayer.allocate(320,240);
    bottomLayer.allocate(320,240);
    mask.allocate(320,240);
}

//--------------------------------------------------------------
void ofApp::update(){
    topLayer.setFromPixels(topImage.getPixelsRef());
    bottomLayer.setFromPixels(backImage.getPixels(), 1024, 768);
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    bottomLayer.draw(0, 0);
    topLayer.draw(0, 0);
    mask.draw(mouseX, mouseY);
    
    topLayer.operator-=(mask);
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
