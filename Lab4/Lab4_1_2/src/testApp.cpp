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
#include "stdlib.h"


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
	velocity = 64;
	pan = 0;
	bend = 0;
	touch = 0;
	polytouch = 0;
    altura = 0;
    
    port1 = true;
    port2 = true;
    port3 = true;
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
        
        red = pixels[0];
        green = pixels[1];
        blue = pixels[2];
        
        ofSetColor(red, green, blue);
        ofFill();
        ofRect( mouseX, mouseY, 60, 60 );
        
        ofNoFill();
        ofSetHexColor(0xFFFFFF);
        ofRect( mouseX, mouseY, 60, 60 );
        ofFill();
        
        ofSetHexColor(0xFFFFFF);
        ofDrawBitmapString("RGB: "+ofToString(int(red))+
                           " "+ofToString(int(green))+
                           " "+ofToString(int(blue)),
                           10, ofGetHeight()-13 );
    }

    string canales;
    
    if (port1)
        canales += "1,";
    
    if (port2)
        canales += " 2,";
    
    if (port3)
        canales += " 3";
    
	stringstream text;
	text << "connected to port " << midiOut.getPort()
		 << " \"" << midiOut.getName() << "\"" << endl
		 << "Red Note: " << noteRed << endl
         << "Green Note: " << noteGreen << endl
         << "Blue Note: " << noteBlue << endl
         << "Velocidad: " << velocity << endl
         << "Altura: " << altura << endl
         << "Enviando a Canales: " << canales << endl;
    
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
        altura += 12 % 128;
    }
    if (key == OF_KEY_DOWN)
    {
        altura -= 12 % 128;
    }
    if(key == '+')
    {
        velocity += 1;
    }
    if(key == '-')
    {
        velocity -= 1;
    }
    if(key == '1')
    {
        if (port1) {
            port1 = false;
        }
        else {
            port1 = true;
        }
    }
    if(key == '2')
    {
        if (port2) {
            port2 = false;
        }
        else {
            port2 = true;
        }
    }
    if(key == '3')
    {
        if (port3) {
            port3 = false;
        }
        else {
            port3 = true;
        }
    }
    if (key == 'R')
    {
        ofColor c;
        for (int i=0; i<image.getWidth(); i++) {
            for (int j=0; j<image.getHeight(); j++) {
                c = image.getColor(i, j);
                image.setColor(i, j, ofColor(c.r+1, c.g, c.b));
            }
        }
        image.update();
    }
    if (key == 'r')
    {
        ofColor c;
        for (int i=0; i<image.getWidth(); i++) {
            for (int j=0; j<image.getHeight(); j++) {
                c = image.getColor(i, j);
                image.setColor(i, j, ofColor(c.r-1, c.g, c.b));
            }
        }
    }
    
    if (key == 'G')
    {
        ofColor c;
        for (int i=0; i<image.getWidth(); i++) {
            for (int j=0; j<image.getHeight(); j++) {
                c = image.getColor(i, j);
                image.setColor(i, j, ofColor(c.r, c.g+1, c.b));
            }
        }
        image.update();
    }
    if (key == 'g')
    {
        ofColor c;
        for (int i=0; i<image.getWidth(); i++) {
            for (int j=0; j<image.getHeight(); j++) {
                c = image.getColor(i, j);
                image.setColor(i, j, ofColor(c.r-10, c.g-1, c.b));
            }
        }
    }
    if (key == 'B')
    {
        ofColor c;
        for (int i=0; i<image.getWidth(); i++) {
            for (int j=0; j<image.getHeight(); j++) {
                c = image.getColor(i, j);
                image.setColor(i, j, ofColor(c.r, c.g, c.b+1));
            }
        }
        image.update();
    }
    if (key == 'b')
    {
        ofColor c;
        for (int i=0; i<image.getWidth(); i++) {
            for (int j=0; j<image.getHeight(); j++) {
                c = image.getColor(i, j);
                image.setColor(i, j, ofColor(c.r, c.g, c.b-1));
            }
        }
    }
      
                

}

//--------------------------------------------------------------
void testApp::keyReleased(int key) {
	
	/*switch(key) {
	
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
	}*/
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ) {
    
    if (image.getWidth() != 0 && image.getHeight() != 0)
    {
        if (port1)
        {
            noteRed = mapNote(red/2); //ofMap(red, 48, 122, 0, 127);
            midiOut.sendNoteOn(1, altura+noteRed,  velocity);
        }
    
        if (port2)
        {
            noteGreen = mapNote(green/2); //ofMap(green, 48, 122, 0, 127);
            midiOut.sendNoteOn(2, altura+noteGreen,  velocity);
        }
    
        if (port3)
        {
            noteBlue = mapNote(blue/2); //ofMap(blue, 48, 122, 0, 127);
            midiOut.sendNoteOn(3, altura+noteBlue,  velocity);
        }
    }
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


int testApp::mapNote(int note){
    
    switch(note){
            
        case 0: case 12: case 24: case  36: case 48: case 60: case 72: case 84: case 96: case 108: case 120:
        case 1: case 13: case 25: case  37: case 49: case 61: case 73: case 85: case 97: case 109: case 121://do
            return 48;
        break;

        case 2: case 14: case 26: case 38: case 50: case 62: case 74: case 86: case 98: case 110: case 122:
        case 3: case 15: case 27: case 39: case 51: case 63: case 75: case 87: case 99: case 111: case 123://re
            return 50;
        break;
            
        case 4: case 16: case 28: case 40: case 52: case 64: case 76: case 88: case 100: case 112: //mi
            return 52;
        break;
        
        case 5: case 17: case 29: case 41: case 53: case 65: case 77: case 89: case 101: case 113: case 125: // fa
        case 6: case 18: case 30: case 42: case 54: case 66: case 78: case 90: case 102: case 114: case 126: // fa
            return 53;
        break;
            
        case 7: case 19: case 31: case 43: case 55: case 67: case 79: case 91: case 103: case 115: case 127: // sol
        case 8: case 20: case 32: case 44: case 56: case 68: case 80: case 92: case 104: case 116: case 128: // sol
            return 55;
        break;
        
        case 9: case 21: case 33: case 45: case 57: case 69: case 81: case 93: case 105: case 117: case 129: // la
        case 10: case 22: case 34: case 46: case 58: case 70: case 82: case 94: case 106: case 118: case 130: // la
            return 57;
        break;
            
        case 11: case 23: case 35: case 47: case 59: case 71: case 83: case 95: case 107: case 119: case 131: // si
            return 59;
        break;
        
    }
}
