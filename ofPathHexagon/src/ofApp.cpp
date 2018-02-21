#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(75);
    
    gui.setup();
    gui.add(radius.set("Radius", 50, 0, 255));
    gui.add(decay.set("Decay", true));
    
    width = ofGetWidth();
    height = ofGetHeight();
    
    long double hex_height = radius / (2 * tan(PI / 6));
    
//    hex.setup(500, 500, ofRandom(100), ofRandom(100));
//    hex.setColor(ofColor(ofRandom(100, 255)));
    
    for(long double y = 0; y < height + radius; y += hex_height) {
        for(long double x = 0; x < width + radius; x += radius * 1.5) {
            Hexagon hex;
            hex.setColor(ofColor(ofRandom(10, 100), 0, 0));
            
            //pure magic
            if(fmod(y, hex_height * 2.0) != 0 && fmod(x, radius * 1.5 * 2.0) == 0) {
                hex.setup(x, y, 0, ofRandom(radius / 2, radius));
                hexes.push_back(hex);
            } else if (fmod(y, hex_height * 2.0) == 0 && fmod(x, radius * 1.5 * 2.0) != 0) {
                hex.setup(x, y, 0, ofRandom(radius / 2, radius));
                hexes.push_back(hex);
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    for(int i = 0; i < hexes.size(); i++) {
        hexes[i].setRadius(radius);

        ofColor color = hexes[i].getColor();

        if(color.r > 0) {
            color.r -= 1;
        }

        if(decay) {
            hexes[i].setColor(color);
        }

        ofPoint point = hexes[i].getPoint();

        point.z = color.r * 5;

        hexes[i].setPoint(point);

        if(ofGetMousePressed() && ofGetMouseX() < point.x + radius && ofGetMouseX() > point.x - radius) {
            if(ofGetMouseY() < point.y + radius && ofGetMouseY() > point.y - radius) {
                hexes[i].setColor(ofColor(100, 0, 0));
            }
        }

        hexes[i].update();
    }
    
//    hex.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofEnableDepthTest();
//    easycam.begin();
//    hex.draw();
    for(int i = 0; i < hexes.size(); i++) {
        hexes[i].draw();
    }
    ofDisableDepthTest();
//    easycam.end();
     gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'c') {
        for(int i = 0; i < hexes.size(); i++) {
            hexes[i].setColor(ofColor(ofRandom(100), 0, 0));
        }
    }
    
    if(key == 'd') {
        decay = !decay;
    }
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
