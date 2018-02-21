#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    receiver.setup(PORT);
    
    depth_width = 512;
    depth_height = 424;
    
    kinect.open();
    
    depth_image.allocate(depth_width, depth_height, OF_IMAGE_GRAYSCALE);
    
    gui.setup();
    gui.add(radius.set("Radius", 10, 2, 50));
    gui.add(max_depth.set("Max Depth", 10, 0, 255));
    gui.add(min_depth.set("Min Depth", 255, 0, 255));
    gui.add(zoom.set("Zoom", 0, 0, 5));
    for(int h = 0; h < depth_height; h += 10){
        for(int w = 0; w < depth_width; w += 10) {
            circles.push_back(ofVec4f(w+5, h+5, 0, 0));
        }
    }
    
    ofBackground(0);
    

}

//--------------------------------------------------------------
void ofApp::update(){
    while(receiver.hasWaitingMessages()) {
        ofxOscMessage m;
        receiver.getNextMessage(m);
        
        if(m.getAddress() == "/amplitude"){
            amplitude = m.getArgAsFloat(0);
        }else if(m.getAddress() == "/pitch"){
            if(m.getArgAsFloat(0) != -1500){
            pitch = m.getArgAsFloat(0);
            }
        }else if(m.getAddress() == "/percussion"){
            percussion = m.getArgAsFloat(0);
        }
    }
    
    kinect.update();
    
    if(kinect.isFrameNew()) {
        depth_image.setFromPixels(kinect.getDepthPixels());
        depth_image.mirror(true, false);
        ofPixels & pix = depth_image.getPixels();
        
        // map_high & map_low are used for the min and max inputs for ofMap
        float map_high = 0;
        float map_low = 255;
        
        //loop through all pixels
        for(int i = 0; i < pix.size(); i++) {
            
            // set all pixels not in range to black
            if(pix[i] < max_depth || pix[i] > min_depth) {
                pix[i] = 0;
            }
            
            // set lowest pixel value
            if(pix[i] != 0 && pix[i] < map_low) {
                map_low = pix[i];
            }
            
            //set highest pixel value
            if(pix[i] != 0 && pix[i] > map_high) {
                map_high = pix[i];
            }
        }
        
        for(int i = 0; i < pix.size(); i++) {
            if(pix[i] != 0) {
                pix[i] = ofMap(pix[i], map_low, map_high, 10, 255);
            }
        }
        
        depth_image.update();
        circles.clear();
        for(int h = 0; h < depth_height; h += radius){
            for(int w = 0; w < depth_width; w += radius) {
                circles.push_back(ofVec4f(w+ radius/2, h+ radius/2, 0, 0));
            }
        }
        
        for(int i = 0; i < circles.size(); i++) {
            ofColor color = depth_image.getColor(circles[i].x, circles[i].y);
            float brightness = ofMap(color.getBrightness(), 0, 255, 0, radius/2);
            circles[i].w = brightness;
            circles[i].z = color.getBrightness() / percussion * 500;
            
            colors.push_back(color);
            
        }
    }
    

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    //depth_image.draw(0,0);
    
    easycam.begin();
    
    for(int i = 0; i < circles.size(); i++) {
//        ofSetColor(ofMap(circles[i].w, 0, radius, 0, 255));
        ofSetColor(255, pitch, 0);
        ofDrawCircle(circles[i].x, circles[i].y, circles[i].z, circles[i].w);
    }
    
    easycam.end();
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
