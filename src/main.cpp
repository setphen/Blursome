#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
    ofSetCurrentRenderer(ofGLProgrammableRenderer::TYPE);
	ofSetupOpenGL(1280,720,OF_WINDOW);			// <-------- setup the GL context
    //ofSetBackgroundAuto(false);
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

}
