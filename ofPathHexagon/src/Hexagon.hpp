//
//  Hexagon.hpp
//  ofPathHexagon
//
//  Created by Matthew Sutton on 2/19/18.
//

#ifndef _HEXAGON
#define _HEXAGON

#include "ofMain.h"

class Hexagon {
public:
    
    // initial methods
    void setup(float _x, float _y, float _z, float _radius);
    void update();
    void draw();
    
    // color methods
    void setColor(ofColor _color);
    ofColor getColor();
    
    //radius methods
    void setRadius(float _radius);
    
    // ofPoint methods
    void setPoint(ofPoint _point);
    ofPoint getPoint();
    
    // class variables
    ofPath path;
    
    float x;
    float y;
    float z;
    float radius;
    float oldRadius;
    float inRadius;
    
    
    float decay;
//    
//    Hexagon();
    
private:
    ofColor color;
};

#endif /* Hexagon_hpp */
