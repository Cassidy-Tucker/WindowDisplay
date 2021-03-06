#pragma once

#include "ofMain.h"
#include "ofxKinect.h"
#include "ofxGui.h"

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
		
        ofImage depth_image;
        ofImage rgb_image;
    
        int depth_width, depth_height;
    vector<ofVec4f> circles;
    vector<ofColor> colors;
    
    ofEasyCam easycam;
    
    ofxKinect kinect;
    
    ofxPanel gui;
    ofParameter<float> radius, max_depth, min_depth, zoom;
    
};
