//
//  universalKinect.hpp
//  universalKinect
//
//  Created by Matthew Sutton on 2/21/18.
//

#ifndef universalKinect_hpp
#define universalKinect_hpp

#include <stdio.h>
#include "ofxKinect.h"
#include "ofxKinectV2.h"


class UniversalKinect {
public:
    void init();
    void update();
    
    bool isFrameNew();
    
    ofPixels getDepthPixels();
    ofPixels getRgbPixels();
    
    void setRegistration();
    
    int getRgbWidth();
    int getDepthWidth();
    
private:
    ofxKinect kinectv1;
    ofxKinectV2 kinectv2;
    
    bool isNew;
};



#endif /* universalKinect_hpp */
