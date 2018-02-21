#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    receiver.setup(PORT);
}

//--------------------------------------------------------------
void ofApp::update(){
    while(receiver.hasWaitingMessages()) {
        ofxOscMessage m;
        receiver.getNextMessage(m);
        
        if(m.getAddress() == "/amplitude"){
            amplitude = m.getArgAsFloat(0);
        }else if(m.getAddress() == "/pitch"){
            pitch = m.getArgAsFloat(0);
        }else if(m.getAddress() == "/percussion"){
            percussion = m.getArgAsFloat(0);
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetBackgroundColor(0, 120, 120);
    ofDrawBitmapString("Amplitude :" + ofToString(amplitude), 0, 20);
    ofDrawBitmapString("Pitch :" + ofToString(pitch), 0, 40);
    ofDrawBitmapString("Percussion :" + ofToString(percussion), 0, 60);
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
