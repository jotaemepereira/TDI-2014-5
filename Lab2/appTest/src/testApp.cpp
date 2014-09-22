#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    //need this for alpha to come through
    ofEnableAlphaBlending();
    
    //we use 3 images, a bottom layer, a top layer, and a mask image
    //the bottom layer is always drawn first
    //then the top layer is drawn over it,using the mask to punch out
    //some of the alpha
    //in this example, they are all the same size. We move the mask
    //to match the mouse so it looks like you can x-ray through the hand
    
    topLayer.loadImage("/Users/miligaricoits/Development/of_v0.8.4_osx_release/apps/myApps/appTest/src/image1.png");
    mask.loadImage("/Users/miligaricoits/Development/of_v0.8.4_osx_release/apps/myApps/appTest/src/circle.png");
    bottomLayer.loadImage("/Users/miligaricoits/Development/of_v0.8.4_osx_release/apps/myApps/appTest/src/image3.png");
    
    //set the texture parameters for the maks shader. just do this at the beginning
    maskShader.setup("/Users/miligaricoits/Development/of_v0.8.4_osx_release/apps/myApps/appTest/src/composite", "/Users/miligaricoits/Development/of_v0.8.4_osx_release/apps/myApps/appTest/src/composite");
    maskShader.begin();
    maskShader.setTexture("Tex0", topLayer.getTextureReference(), 0);
    maskShader.setTexture("Tex1", mask.getTextureReference(), 1);
    maskShader.end();
}

//--------------------------------------------------------------
void testApp::update(){
    
}

//--------------------------------------------------------------
void testApp::draw(){
    //first draw the bottom layer
    bottomLayer.draw(0, 0);
    
    
    //then draw a quad for the top layer using our composite shader to set the alpha
    maskShader.begin();
    
    //our shader uses two textures, the top layer and the alpha
    //we can load two textures into a shader using the multi texture coordinate extensions
    glActiveTexture(GL_TEXTURE0_ARB);
    topLayer.getTextureReference().bind();
    
    glActiveTexture(GL_TEXTURE1_ARB);
    mask.getTextureReference().bind();
    
    //draw a quad the size of the frame
    glBegin(GL_QUADS);
    
    //move the mask around with the mouse by modifying the texture coordinates
    float maskOffset = 15 - mouseY;
    glMultiTexCoord2d(GL_TEXTURE0_ARB, 0, 0);
    glMultiTexCoord2d(GL_TEXTURE1_ARB, 0, maskOffset);
    glVertex2f( 0, 0);
    
    glMultiTexCoord2d(GL_TEXTURE0_ARB, topLayer.getWidth(), 0);
    glMultiTexCoord2d(GL_TEXTURE1_ARB, mask.getWidth(), maskOffset);
    glVertex2f( ofGetWidth(), 0);
    
    glMultiTexCoord2d(GL_TEXTURE0_ARB, topLayer.getWidth(), topLayer.getHeight());
    glMultiTexCoord2d(GL_TEXTURE1_ARB, mask.getWidth(), mask.getHeight() + maskOffset);
    glVertex2f( ofGetWidth(), ofGetHeight());
    
    glMultiTexCoord2d(GL_TEXTURE0_ARB, 0, topLayer.getHeight());
    glMultiTexCoord2d(GL_TEXTURE1_ARB, 0, mask.getHeight() + maskOffset);
    glVertex2f( 0, ofGetHeight() );
    
    glEnd();
    
    //deactive and clean up
    glActiveTexture(GL_TEXTURE1_ARB);  
    mask.getTextureReference().unbind();  
    
    glActiveTexture(GL_TEXTURE0_ARB);  
    topLayer.getTextureReference().unbind();  
    
    maskShader.end();
}


//--------------------------------------------------------------
void testApp::keyPressed(int key){
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
    
}



