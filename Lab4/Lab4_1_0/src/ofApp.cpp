#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    ofBackground(0,0,0);
    ofEnableSmoothing();
    ofEnableAlphaBlending();
    ofSetWindowTitle("Image Sounds");
}

//--------------------------------------------------------------
void ofApp::update(){
    /*if (image.getWidth() >= 0 && image.getHeight() >= 0)
    {
        ofColor c;
        for (int i=0; i<128; i++) {
            for (int j=0; j<128; j++) {
                c = image.getColor(i, j);
                image.setColor(i, j, ofColor(c.r+10, c.g+10, c.b+10));
            }
        }
        image.update();
    }*/
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    if (image.getWidth() == 0 && image.getHeight() == 0)
    {
        ofDrawBitmapString("Press spacebar to open an image", 20, 15);
    }
    else
    {
        image.draw(ofGetWidth()/2 - image.getWidth()/2, ofGetHeight()/2 - image.getHeight()/2);
    
        imgTmp.grabScreen(mouseX,mouseY,1,1);
        unsigned char *pixels = imgTmp.getPixels();
        
        int red = pixels[0];
        int green = pixels[1];
        int blue = pixels[2];
        
        ofSetColor(red, green, blue);
        ofFill();
        ofRect( mouseX, mouseY, 60, 60 );
        
        // now draw a white border around the rectangle
        ofNoFill();
        ofSetHexColor(0xFFFFFF);
        ofRect( mouseX, mouseY, 60, 60 );
        ofFill();
        
        // finally we draw text over the rectangle giving the resulting HSB and RGB values
        // under the mouse
        ofSetHexColor(0xFFFFFF);
        /*ofDrawBitmapString("HSB: "+ofToString(int(hue))+
            " "+ofToString(int(color.getSaturation()))+
            " "+ofToString(int(color.getBrightness())),
            10, ofGetHeight()-13 );*/
        ofDrawBitmapString("RGB: "+ofToString(int(red))+
                           " "+ofToString(int(green))+
                           " "+ofToString(int(blue)),
                           10, ofGetHeight()-13 );
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
    if (key == ' ')
    {
        ofFileDialogResult openFileResult= ofSystemLoadDialog("Select a jpg or png");
        
        if (openFileResult.bSuccess)
        {
            ofLogVerbose("User selected a file");
            
            //We have a file, check it and process it
            processOpenFileSelection(openFileResult);
        }
    }
    
    if (key == OF_KEY_UP)
    {
        ofColor c;
        for (int i=0; i<image.getWidth(); i++) {
            for (int j=0; j<image.getHeight(); j++) {
                c = image.getColor(i, j);
                image.setColor(i, j, ofColor(c.r+10, c.g, c.b));
            }
        }
        image.update();
    }
    if (key == OF_KEY_DOWN)
    {
        ofColor c;
        for (int i=0; i<image.getWidth(); i++) {
            for (int j=0; j<image.getHeight(); j++) {
                c = image.getColor(i, j);
                image.setColor(i, j, ofColor(c.r-10, c.g, c.b));
            }
        }
        image.update();
    }

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


//--------------------------------------------------------------
//Sort function for stl::sort http://www.cplusplus.com/reference/algorithm/sort/
bool sortColorFunction (ofColor i,ofColor j) {
    return (i.getBrightness()<j.getBrightness());
}


//--------------------------------------------------------------
void ofApp::processOpenFileSelection(ofFileDialogResult openFileResult){
    
    ofLogVerbose("getName(): "  + openFileResult.getName());
    ofLogVerbose("getPath(): "  + openFileResult.getPath());
    
    ofFile file (openFileResult.getPath());
    
    if (file.exists())
    {
        ofLogVerbose("The file exists - now checking the type via file extension");
        string fileExtension = ofToUpper(file.getExtension());
        
        //We only want images
        if (fileExtension == "JPG" || fileExtension == "PNG")
        {
            //Save the file extension to use when we save out
            originalFileExtension = fileExtension;
            
            //Load the selected image
            image.loadImage(openFileResult.getPath());
            /*if (image.getWidth()>ofGetWidth() || image.getHeight() > ofGetHeight())
            {
                image.resize(image.getWidth()/2, image.getHeight()/2);
            }*/
        }
    }
    
}
