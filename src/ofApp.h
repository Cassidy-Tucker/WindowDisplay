#pragma once

#include "ofMain.h"
#include "ofxKinect.h"
#include "ofxGui.h"
#include "ofxCv.h"
#include "ofxOpenCv.h"

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
		
    
    ofxKinect kinect;
    ofxPanel gui;
    ofMesh mesh;
    
    
    ofParameter<int> max_depth, min_depth, max_area, min_area, threshold, smooth;
    ofParameter<bool> draw_holes, draw_cam, draw_contour, draw_polylines;
    
    ofImage depth_image;
    ofImage contour_image;
    
    ofxCv::ContourFinder contour_finder;
    
    vector<ofPolyline> polylines;

    
};
