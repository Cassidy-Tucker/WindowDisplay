#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxKinectV2.h"
#include "ofxGui.h"


#define PORT 9997

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    ofxOscReceiver receiver;
    
    float amplitude, pitch, percussion;
    
    ofImage depth_image;
    ofImage rgb_image;
    
    int depth_width, depth_height;
    vector<ofVec4f> circles;
    vector<ofColor> colors;
    
    ofEasyCam easycam;
    
    ofxKinectV2 kinect;
    
    ofxPanel gui;
    ofParameter<float> radius, max_depth, min_depth, zoom;
    
		
};
