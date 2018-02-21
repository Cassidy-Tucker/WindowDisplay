#pragma once

#include "ofMain.h"
#include "Hexagon.hpp"
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
		
    
    ofEasyCam easycam;
    
//    Hexagon hex;
    vector<Hexagon> hexes;
    float width;
    float height;
    
    
    ofxPanel gui;
    ofParameter<float> radius;
    ofParameter<bool> decay;
};
