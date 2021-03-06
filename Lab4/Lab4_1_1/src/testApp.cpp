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
#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup() {
    
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    ofBackground(0,0,0);
    ofEnableSmoothing();
    ofEnableAlphaBlending();
    ofSetWindowTitle("Image Sounds");

	ofSetVerticalSync(true);
	
	// print the available output ports to the console
	midiOut.listPorts(); // via instance
	//ofxMidiOut::listPorts(); // via static too
	
	// connect
	midiOut.openPort(0); // by number
	//midiOut.openPort("IAC Driver Pure Data In"); // by name
	//midiOut.openVirtualPort("ofxMidiOut"); // open a virtual port
	
	channel = 1;
	currentPgm = 0;
	note = 0;
	velocity = 0;
	pan = 0;
	bend = 0;
	touch = 0;
	polytouch = 0;
}

//--------------------------------------------------------------
void testApp::update() {}

//--------------------------------------------------------------
void testApp::draw() {
    
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

        int noteRed = ofMap(red, 48, 122, 0, 127);
        velocity = 64;
        midiOut.sendNoteOn(1, noteRed,  velocity);
        
        int noteGreen = ofMap(green, 48, 122, 0, 127);
        velocity = 64;
        midiOut.sendNoteOn(2, noteGreen,  velocity);
        
        int noteBlue = ofMap(blue, 48, 122, 0, 127);
        velocity = 64;
        midiOut.sendNoteOn(3, noteBlue,  velocity);
        
        
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

	// let's see something
	//ofSetColor(0);
	stringstream text;
	text << "connected to port " << midiOut.getPort() 
		 << " \"" << midiOut.getName() << "\"" << endl
		 << "is virtual?: " << midiOut.isVirtual() << endl << endl
		 << "sending to channel " << channel << endl << endl
		 << "current program: " << currentPgm << endl << endl
		 << "note: " << note << endl
		 << "velocity: " << velocity << endl
		 << "pan: " << pan << endl
		 << "bend: " << bend << endl
		 << "touch: " << touch << endl
		 << "polytouch: " << polytouch;
	ofDrawBitmapString(text.str(), 20, 50);
}

//--------------------------------------------------------------
void testApp::exit() {
	
	// clean up
	midiOut.closePort();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key) {

	// send a note on if the key is a letter or a number
	if(isalnum((unsigned char) key)) {
	
		// scale the ascii values to midi velocity range 0-127
		// see an ascii table: http://www.asciitable.com/
		note = ofMap(key, 48, 122, 0, 127);
		velocity = 64;
		midiOut.sendNoteOn(channel, note,  velocity);
	}
	
	if(key == 'l') {
		ofxMidiOut::listPorts();
	}
    
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
void testApp::keyReleased(int key) {
	
	switch(key) {
	
		// send pgm change on arrow keys
		case OF_KEY_UP:
			currentPgm = (int) ofClamp(currentPgm+1, 0, 127);
			midiOut.sendProgramChange(channel, currentPgm);
			break;
		case OF_KEY_DOWN:
			currentPgm = (int) ofClamp(currentPgm-1, 0, 127);
			midiOut << ProgramChange(channel, currentPgm); // stream interface
			break;

		// aftertouch
		case '[':
			touch = 64;
			midiOut.sendAftertouch(channel, touch);
			break;
		case ']':
			touch = 127;
			midiOut << Aftertouch(channel, touch); // stream interface
			break;

		// poly aftertouch
		case '<':
			polytouch = 64;
			midiOut.sendPolyAftertouch(channel, 64, polytouch);
			break;
		case '>':
			polytouch = 127;
			midiOut << PolyAftertouch(channel, 64, polytouch); // stream interface
			break;
			
		// sysex using raw bytes (use shift + s)
		case 'S': {
			// send a pitch change to Part 1 of a MULTI on an Akai sampler
			// from http://troywoodfield.tripod.com/sysex.html
			//
			// do you have an S2000 to try?
			//
			// note: this is probably not as efficient as the next two methods
			//       since it sends only one byte at a time, instead of all
			//       at once
			//
			midiOut.sendMidiByte(MIDI_SYSEX);
			midiOut.sendMidiByte(0x47);	// akai manufacturer code
			midiOut.sendMidiByte(0x00); // channel 0
			midiOut.sendMidiByte(0x42); // MULTI
			midiOut.sendMidiByte(0x48); // using an Akai S2000
			midiOut.sendMidiByte(0x00); // Part 1
			midiOut.sendMidiByte(0x00);	// transpose
			midiOut.sendMidiByte(0x01); // Access Multi Parts
			midiOut.sendMidiByte(0x4B); // offset
			midiOut.sendMidiByte(0x00);	// offset
			midiOut.sendMidiByte(0x01); // Field size = 1
			midiOut.sendMidiByte(0x00); // Field size = 1
			midiOut.sendMidiByte(0x04); // pitch value = 4
			midiOut.sendMidiByte(0x00); // offset
			midiOut.sendMidiByte(MIDI_SYSEX_END);
			
			// send again using a vector
			//
			// sends all bytes within one message
			//
			vector<unsigned char> sysexMsg;
			sysexMsg.push_back(MIDI_SYSEX);
			sysexMsg.push_back(0x47);
			sysexMsg.push_back(0x00);
			sysexMsg.push_back(0x42);
			sysexMsg.push_back(0x48);
			sysexMsg.push_back(0x00);
			sysexMsg.push_back(0x00);
			sysexMsg.push_back(0x01);
			sysexMsg.push_back(0x4B);
			sysexMsg.push_back(0x00);
			sysexMsg.push_back(0x01);
			sysexMsg.push_back(0x00);
			sysexMsg.push_back(0x04);
			sysexMsg.push_back(0x00);
			sysexMsg.push_back(MIDI_SYSEX_END);
			midiOut.sendMidiBytes(sysexMsg);
			
			// send again with the byte stream interface
			//
			// builds the message, then sends it on FinishMidi()
			//
			midiOut << StartMidi() << MIDI_SYSEX
					<< 0x47 << 0x00 << 0x42 << 0x48 << 0x00 << 0x00 << 0x01
					<< 0x4B << 0x00 << 0x01 << 0x00 << 0x04 << 0x00
					<< MIDI_SYSEX_END << FinishMidi();
			break;
		}
		
		// print the port list
		case '?':
			midiOut.listPorts();
			break;
		
		// note off using raw bytes
		case ' ':	
			// send with the byte stream interface, noteoff for note 60
			midiOut << StartMidi() << 0x80 << 0x3C << 0x40 << FinishMidi();
			break;

		default:
    
			// send a note off if the key is a letter or a number
			if(isalnum(key)) {
				note = ofMap(key, 48, 122, 0, 127);
				velocity = 0;
				midiOut << NoteOff(channel, note, velocity); // stream interface
			}
			break;
	}
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ) {
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button) {

	// x pos controls the pan (ctl = 10)
	pan = ofMap(x, 0, ofGetWidth(), 0, 127);
	midiOut.sendControlChange(channel, 10, pan);
	
	// y pos controls the pitch bend
	bend = ofMap(y, 0, ofGetHeight(), 0, MIDI_MAX_BEND);
	midiOut.sendPitchBend(channel, bend);
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button) {	
}

//--------------------------------------------------------------
void testApp::mouseReleased() {
}


//--------------------------------------------------------------
//Sort function for stl::sort http://www.cplusplus.com/reference/algorithm/sort/
bool sortColorFunction (ofColor i,ofColor j) {
    return (i.getBrightness()<j.getBrightness());
}


//--------------------------------------------------------------
void testApp::processOpenFileSelection(ofFileDialogResult openFileResult){
    
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
