#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    ofBackground(0,0,0);
    ofEnableSmoothing();
    ofEnableAlphaBlending();
    ofSetWindowTitle("Image Sounds");
    
    //ofSetRectMode(OF_RECTMODE_CENTER);
    
    ofSetFrameRate(60); // if vertical sync is off, we can go a bit fast... this caps the framerate at 60fps.
    
    // initialise member variables to the centre of the screen
    //mouseXPercent = 0.5f;
    //mouseYPercent = 0.5f;
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofDrawBitmapString("Press spacebar to open an image", 20, 15);
    
    //float hue = fmodf(ofGetElapsedTimef()*10,255);
        
    image.draw(0, 0);
        
    // now we will draw a larger rectangle taking the color under the mouse
    // calculate the color under the mouse, using the same calculations as when drawing the grid,
    // using mouseX and mouseY in place of i and j; draw a rectangle with this color. here we use
    // ofColor::fromHsb which allows us to set the HSB color in a single line of code.
    /*ofColor color = ofColor::fromHsb(hue,
        ofMap( mouseX, 0,ofGetWidth(), 0,255 ),
        ofMap( mouseY, ofGetHeight(),0, 0,255 ) );*/
        
    if (image.getWidth() > 0 && image.getHeight() > 0)
    {
        unsigned char *pixels=image.getPixels();
        int index = mouseY*image.width*3 + mouseX*3;
        
        int red = pixels[index];
        int green = pixels[index+1];
        int blue = pixels[index+2];
        
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
                           200, ofGetHeight()-13 );
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

    if (key == ' ')
    {
        //Open the Open File Dialog
        ofFileDialogResult openFileResult= ofSystemLoadDialog("Select a jpg or png");
        
        //Check if the user opened a file
        if (openFileResult.bSuccess)
        {
            ofLogVerbose("User selected a file");
            
            //We have a file, check it and process it
            processOpenFileSelection(openFileResult);
            
        }
        else {
            ofLogVerbose("User hit cancel");
        }
    }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    //mouseXPercent = float(x) / ofGetWidth();
    //mouseYPercent = float(y) / ofGetHeight();
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

//Sort function for stl::sort http://www.cplusplus.com/reference/algorithm/sort/
bool sortColorFunction (ofColor i,ofColor j) {
    return (i.getBrightness()<j.getBrightness());
}


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
            if (image.getWidth()>ofGetWidth() || image.getHeight() > ofGetHeight())
            {
                image.resize(image.getWidth()/2, image.getHeight()/2);
            }
        }
    }
    
}

