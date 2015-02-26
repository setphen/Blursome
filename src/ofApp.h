#pragma once

#include "ofMain.h"
#include "ofxMidi.h"

class ofApp : public ofBaseApp, public ofxMidiListener {

	public:
		void setup();
		void update();
		void draw();
        void exit();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    ofShader            shader;
    
    ofFbo               fbo;
    int                 looper;
    int                 elapsed;
    int                 loopTime;
    bool                loop;
    float               div;
    float               dDiv;
    float               vidPos;
    int                 vidAlpha;
    
    ofPlanePrimitive    plane;
    ofVideoPlayer       vidA;
    
    void newMidiMessage(ofxMidiMessage& eventArgs);

    ofxMidiIn midiIn;
    ofxMidiMessage midiMessage;
};
