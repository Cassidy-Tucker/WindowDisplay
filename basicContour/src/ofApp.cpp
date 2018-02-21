#include "ofApp.h"

using namespace cv;
using namespace ofxCv;

//--------------------------------------------------------------
void ofApp::setup(){
    kinect.init();
    
    ofSetVerticalSync(true);
    
    gui.setup();
    
    gui.add(min_depth.set("Min Depth", 135, 0, 255 ));
    gui.add(max_depth.set("Max Depth", 169, 0, 255));
    gui.add(min_area.set("Min Area", 41, 1, 100));
    gui.add(max_area.set("Max Area", 1000, 1, 1000));
    gui.add(threshold.set("Threshold", 128, 0, 255));
    gui.add(smooth.set("Smooth", 6, 0, 255));
    gui.add(draw_holes.set("Fill Holes", true));
    gui.add(draw_cam.set("Draw Depth", false));
    
    gui.add(draw_contour.set("Contour", false));
    gui.add(draw_polylines.set("Polylines", true));

}

//--------------------------------------------------------------
void ofApp::update(){
    kinect.update();
    
    if(kinect.isFrameNewDepth()){
        depth_image.setFromPixels(kinect.getDepthPixels());
        
        ofPixels & pix = depth_image.getPixels();
        
        for(int i=0; i<pix.size() ; i++){
            if(pix[i] > min_depth && pix[i] < max_depth){
                pix[i] = 255;
            }else{
                pix[i] = 0;
            }
        }
        depth_image.update();
        
        contour_finder.setMinAreaRadius(min_area);
        contour_finder.setMaxAreaRadius(max_area);
        contour_finder.setThreshold(threshold);
        contour_finder.findContours(depth_image);
        contour_finder.setFindHoles(draw_holes);
        contour_finder.setSimplify(true);
        polylines = contour_finder.getPolylines();
        
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackgroundGradient(ofColor(64), ofColor(0));
    
    ofSetColor(255);
    
    
    if(draw_cam){
        depth_image.draw(0,0);
    }
    
    if(draw_contour){
       contour_finder.draw();
    }
    
    if(draw_polylines){
        for(int i = 0; i < polylines.size(); i++){
            polylines[i] = polylines[i].getSmoothed(smooth);
            polylines[i].draw();
        }
    }
    gui.draw();

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
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
