#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxCv.h"
#include "ofxOpenCv.h"
#include "ofxTriangleMesh.h"
#include "ofxKinect.h"
#include "ofxSyphonServer.h"

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
    
        // setting up kinect
        ofxKinect kinect;
    
        // setting up images
        //ofImage kinect_image;
        ofImage depth_image;
        ofImage contour_image;
    
        // setting up gui
        ofxPanel gui;
        ofParameter<float> max_depth, min_depth, min_radius, max_radius, threshold, smooth, simplify;
        ofParameter<bool> draw_depth, draw_contours, draw_polylines, draw_mesh;
        ofParameter<bool> draw_vertices, draw_tri_meshes, make_3d;

    
        // setting up contourFinder
        ofxCv::ContourFinder contour_finder;
    
        // setting up vectors for poly, tri and mesh
        // using vectors to handle multiple vectors
        // the index of all three vectors refer to the same contour
        vector<ofPolyline> polylines;
        vector<ofxTriangleMesh> tri_meshes;
        vector<ofMesh> meshes;

        ofEasyCam easycam;
        ofxSyphonServer syphon;
        ofFbo outputFbo, depthFbo, rainbowFbo;
    
        ofParameter<ofColor> fade_color;
    
        ofShader rainbowShader;
    };

