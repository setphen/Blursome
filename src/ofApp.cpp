#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    fbo.allocate(ofGetWidth(),ofGetHeight());
    
    ofSetFullscreen(true);
    
    // print input ports to console
    midiIn.listPorts(); // via instance
    //ofxMidiIn::listPorts(); // via static as well
    
    // open port by number (you may need to change this)
    midiIn.openPort(0);
    //midiIn.openPort("IAC Pure Data In");	// by name
    //midiIn.openVirtualPort("ofxMidiIn Input"); // open a virtual port
    
    // don't ignore sysex, timing, & active sense messages,
    // these are ignored by default
    midiIn.ignoreTypes(false, false, false);
    
    // add ofApp as a listener
    midiIn.addListener(this);
    
    // print received messages to the console
    midiIn.setVerbose(true);
    
    //Log verbosity
    //ofSetLogLevel(OF_LOG_VERBOSE);
    
    //load video
    vidA.loadMovie("d.mov");
    vidA.setVolume(0);
    vidA.play();
    
    //shader uniform, affects kaleidoscope
    div = 1.2;
    dDiv = div;
    
    //we loopin?
    loop = false;
    
    //alpha mask for vidA
    vidAlpha = 20;
    
    plane.set(ofGetWidth(),ofGetHeight());
    plane.mapTexCoords(0,0,vidA.width,vidA.height);
    plane.enableColors();
    shader.load("shader");
    
}

//--------------------------------------------------------------
void ofApp::update(){
    ofBackground(0,0,0);
    //cout << midiMessage.control << endl;
    //get midi messages and DO THE THINGS
    
    //SLICES
    if (midiMessage.control == 7){
        dDiv = ofMap(midiMessage.value,0,127,1,3.);
    }
    
    //VIDEO SPEED
    if (midiMessage.control == 6){
        vidA.setSpeed(ofMap(midiMessage.value,0,127,1,5));
    }
    
    //VIDEO ALPHA
    if (midiMessage.control == 15){
        vidAlpha = ofMap(midiMessage.value,0,127,0,255);
    }
    
    //SCRUB VIDEO POSITION
    if (midiMessage.control == 8){
        vidA.setFrame(ofMap(midiMessage.value,0,127,0,vidA.getTotalNumFrames()));
        midiMessage.clear();
    }
    
    //SCRUB && SET VIDEO POSITION
    if (midiMessage.control == 9){
        vidA.setFrame(ofMap(midiMessage.value,0,127,0,vidA.getTotalNumFrames()));
        vidPos = vidA.getCurrentFrame();
        midiMessage.clear();
    }
    
    //CAPTURE VIDEO POSITION
    if (midiMessage.control == 32 and midiMessage.value > 1){
        vidPos = vidA.getCurrentFrame();
        midiMessage.clear();
    }
    
    //SET VIDEO POSITION
    if (midiMessage.control == 33 and midiMessage.value > 1){
        vidA.setFrame(vidPos);
        midiMessage.clear();
    }
    
    //SET LOOPER TIME (TAP TEMPO)
    if (midiMessage.control == 48 and midiMessage.value > 1){
        //vidA.setPosition(vidPos);
        loopTime = ofGetElapsedTimeMillis() - elapsed;
        elapsed = ofGetElapsedTimeMillis();
        cout << elapsed << endl << loopTime << endl;
        midiMessage.clear();
    }
    
    //TOGGLE LOOPER
    if (midiMessage.control == 64){
        loop = !loop;
        cout << loop;
        midiMessage.clear();
    }
    
    if (midiMessage.control == 61 && midiMessage.value > 0){
        vidA.setFrame(vidA.getCurrentFrame()-24);
        vidPos = vidA.getCurrentFrame();
        midiMessage.clear();
    }
    
    if (midiMessage.control == 62 && midiMessage.value > 0){
        vidA.setFrame(vidA.getCurrentFrame()+24);
        vidPos = vidA.getCurrentFrame();
        midiMessage.clear();
    }
    
    //update the looper
    if (loop){
        if (ofGetElapsedTimeMillis() >= looper + loopTime){
            vidA.setFrame(vidPos);
            looper = ofGetElapsedTimeMillis();
        }
    }

    
    //update video
    vidA.update();
    
    //lerp Div
    div += (dDiv - div)/6;
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    fbo.begin();
    ofPushMatrix();
    ofTranslate(fbo.getWidth()*.5,fbo.getHeight()*.5);
    vidA.getTextureReference().bind();
    shader.begin();
    shader.setUniform1f("sides", div);
    plane.draw();
    shader.end();
    vidA.getTextureReference().unbind();
    
    ofPopMatrix();
    fbo.end();
    
    
    
    ofEnableAlphaBlending();
    ofSetColor(255,255,255,vidAlpha);
    fbo.draw(0,0,ofGetWidth(),ofGetHeight());
    ofDisableAlphaBlending();
}

//--------------------------------------------------------------
void ofApp::exit(){
    
    // clean up
    midiIn.closePort();
    midiIn.removeListener(this);
}

//--------------------------------------------------------------
void ofApp::newMidiMessage(ofxMidiMessage& msg){
    
    // make a copy of the latest message
    midiMessage = msg;
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
