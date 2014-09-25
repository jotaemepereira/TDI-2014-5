#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    this->width = ofGetWidth();
    this->height = ofGetHeight();
    
    //need this for alpha to come through
    ///*ofEnableAlphaBlending();
    
    mask.loadImage("circle.png");
    bottomLayer.loadImage("image1.jpg");
    
    filterLayer = new PerlinPixellationFilter(this->width, this->height);
    
    //desktopImage.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
    bool retina = true;
    grabber.setup(this->width, this->height, retina);
    
    //set the texture parameters for the maks shader. just do this at the beginning
    maskShader.setup("composite", "composite");
    maskShader.begin();
    maskShader.setTexture("Tex0", bottomLayer.getTextureReference(), 0);
    maskShader.setTexture("Tex1", mask.getTextureReference(), 1);
    maskShader.end();
    
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    grabber.grabScreen(0, 0);
}

//--------------------------------------------------------------
void ofApp::draw(){
    //first draw the bottom layer
    //ofDisableArbTex();
    //filterLayer->begin();
    grabber.draw(0, 0);
    //filterLayer->end();
    //ofEnableArbTex();
    
    //then draw a quad for the top layer using our composite shader to set the alpha
    maskShader.begin();
    
    //our shader uses two textures, the top layer and the alpha
    //we can load two textures into a shader using the multi texture coordinate extensions
    glActiveTexture(GL_TEXTURE0_ARB);
    bottomLayer.getTextureReference().bind();
    
    glActiveTexture(GL_TEXTURE1_ARB);
    mask.getTextureReference().bind();
    
    //draw a quad the size of the frame
    glBegin(GL_QUADS);
    
    //move the mask around with the mouse by modifying the texture coordinates
    float maskOffsetY = this->height/2 - mouseY;
    float maskOffsetX = this->width/2 - mouseX;
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
    
    //deactive and clean up
    glActiveTexture(GL_TEXTURE1_ARB);  
    mask.getTextureReference().unbind();  
    
    glActiveTexture(GL_TEXTURE0_ARB);  
    bottomLayer.getTextureReference().unbind();
    
    maskShader.end();
    
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



