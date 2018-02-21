//
//  universalKinect.cpp
//  universalKinect
//
//  Created by Matthew Sutton on 2/21/18.
//

#include "universalKinect.hpp"

void UniversalKinect::init() {
    if(kinectv1.getDeviceId() != -1) {
        isNew = false;
        kinectv1.init();
    } else if (kinectv2.getNumDevices() > 0) {
        isNew = true;
        kinectv2.open();
    }
}

void UniversalKinect::update() {
    if(!isNew) {
        kinectv1.update();
    } else {
        kinectv2.update();
    }
}

bool UniversalKinect::isFrameNew() {
    bool isFrameNew;
    
    if(!isNew) {
        isFrameNew = kinectv1.isFrameNew();
    } else {
        isFrameNew = kinectv2.isFrameNew();
    }
    
    return isFrameNew;
}

ofPixels UniversalKinect::getDepthPixels() {
    ofPixels pix;
    
    if(!isNew) {
        pix = kinectv1.getDepthPixels();
    } else {
        pix = kinectv2.getDepthPixels();
    }
    
    return pix;
}

ofPixels UniversalKinect::getRgbPixels() {
    ofPixels pix;
    
    if(!isNew) {
        pix = kinectv1.getPixels();
    } else {
        pix = kinectv2.getRgbPixels();
    }
    
    return pix;
}

void UniversalKinect::setRegistration() {
    if(!isNew) {
        kinectv1.setRegistration();
    }
}
