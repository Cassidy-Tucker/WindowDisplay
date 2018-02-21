//
//  Hexagon.cpp
//  ofPathHexagon
//
//  Created by Matthew Sutton on 2/19/18.
//

#include "Hexagon.hpp"

//Hexagon::Hexagon() {
//}

// initial methods
void Hexagon::setup(float _x, float _y, float _z, float _radius) {
    x = _x;
    y = _y;
    z = _z;
    
    radius = _radius;
    inRadius = radius / (2 * tan(PI / 6));
}

void Hexagon::update() {
    path.clear();
    path.setColor(color);
    
    for(int i = 0; i <= 360; i += 60) {
        path.lineTo(cos(ofDegToRad(i))  * radius + x, sin(ofDegToRad(i)) * radius + y, z);
    }
    
    path.close();
}

void Hexagon::draw() {
    path.draw();
}

// Color Methods
void Hexagon::setColor(ofColor _color) {
    color.set(_color);
}

ofColor Hexagon::getColor() {
    return color;
}

// Radius Methods
void Hexagon::setRadius(float _radius) {
    radius = _radius;
}

// Point Methods
void Hexagon::setPoint(ofPoint _point) {
    x = _point.x;
    y = _point.y;
    z = _point.z;
}

ofPoint Hexagon::getPoint() {
    return ofPoint(x, y, z);
}

