#include "ofApp.h"

using namespace cv;
using namespace ofxCv;
//--------------------------------------------------------------
void ofApp::setup(){
    if(kinect.getDeviceId() != -1) {
        kinect.init();
        new_kinect = false;
    } else if (kinect_v2.getNumDevices() > 0) {
        kinect_v2.open();
        new_kinect = true;
    }
    
    
    outputFbo.allocate(ofGetWidth(), ofGetHeight());
    depthFbo.allocate(ofGetWidth(), ofGetHeight());
    
    ofSetVerticalSync(true);
    
    //ofSetFrameRate(10);
    //ofEnableAlphaBlending();
    //kinect_image.load("before.png");
    //kinect_image.setImageType(OF_IMAGE_GRAYSCALE);
    
    gui.setup();
    gui.add(max_depth.set("Max Depth", 154, 0, 255));
    gui.add(min_depth.set("Min Depth", 135, 0, 255));
    gui.add(min_radius.set("Min Radius", 62, 0, 100));
    gui.add(max_radius.set("Max Radius", 805, 0, 1000));
    gui.add(threshold.set("Threshold", 128, 0, 255));
    gui.add(smooth.set("Smooth", 6, 0, 255));
    gui.add(simplify.set("Simplify", 0, 0, 10));
    gui.add(draw_depth.set("Draw Depth", false));
    gui.add(draw_contours.set("Draw Contours", false));
    gui.add(draw_polylines.set("Draw Polylines", false));
    gui.add(draw_mesh.set("Draw mesh", false));
    gui.add(draw_tri_meshes.set("Draw Tri Meshes", false));
    gui.add(draw_vertices.set("Draw Verts", false));
    gui.add(make_3d.set("Make 3d", false));
    gui.add(fade_color.set("Fade", ofColor(0,0,0,0)));
    
    outputFbo.begin();
    ofClear(0, 0, 0, 0);
    outputFbo.end();
    
    depthFbo.begin();
    ofClear(255, 255, 255, 0);
    depthFbo.end();
}

//--------------------------------------------------------------
void ofApp::update(){
    if(new_kinect) {
        kinect_v2.update();
    } else {
        kinect.update();
    }
    
    if(kinect.isFrameNewDepth() || kinect_v2.isFrameNew()){
        // depth image range and increased definition
        if(new_kinect) {
            depth_image.setFromPixels(kinect_v2.getDepthPixels());
        } else {
            depth_image.setFromPixels(kinect.getDepthPixels());
        }
        
        depth_image.resize(ofGetWidth(), ofGetHeight());
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
        
    // loop through pix again to set new mapped range
//    for(int i = 0; i < pix.size(); i++) {
//        if(pix[i] != 0) {
//            pix[i] = ofMap(pix[i], map_low, map_high, 10, 255);
//        }
//    }
//    
    
    depth_image.update();
    
    // user OpenCV to get contours
    // stupid hole finder not working... will need to look into
    contour_finder.setMinAreaRadius(min_radius);
    contour_finder.setMaxAreaRadius(max_radius);
    contour_finder.setThreshold(threshold);
    contour_finder.findContours(depth_image);
    contour_finder.setFindHoles(true);
    
    // set vector of polylines based of mesh
        polylines.clear();
    polylines = contour_finder.getPolylines();
    }
    // vector cleanup
    tri_meshes.clear();
    meshes.clear();
  
    
    // loop through all poly lines and add to tri_meshes and meshes;
    for(int i = 0; i < polylines.size(); i++) {
        
        // smooth simplify and close the polyline
        polylines[i] = polylines[i].getSmoothed(smooth);
        polylines[i].simplify(simplify);
        polylines[i].close();
        
        // create temp ofxTriangleMesh and triangulate it
        ofxTriangleMesh tri_mesh;
        tri_mesh.triangulate(polylines[i], 28, -1);
        
        // add the tri_mesh to the meshes vector
        tri_meshes.push_back(tri_mesh);
        meshes.push_back(tri_mesh.triangulatedMesh);
        
        // make the mesh 3d-ish
        if(make_3d) {
            // loop through all vertexes
            for(int j = 0; j < meshes[i].getNumVertices(); j++) {
                // temp ofVec3f to modify values
                ofVec3f point = meshes[i].getVertex(j);
                // get the color of the x, y pixel in depth_image
                ofColor color = depth_image.getColor(point.x, point.y);
                // set the temp ofVec3f y value to the total brightness
                point.z = ofMap(color.getBrightness(), 10, 255, 0, 75);
                //set the vertex with you temp vec
                meshes[i].setVertex(j, point);
            }
        }
    }
    
    outputFbo.begin();
    
    //clear the fbo trail
    if(ofGetKeyPressed('c')){
        ofClear(0,0,0,0);
    }
    ofFill();
    ofSetColor(fade_color);
    ofDrawRectangle(0,0,ofGetWidth(),ofGetHeight());
    ofNoFill();
    
    
    
    
    easycam.begin();
    
    ofSetColor(255);
    
    if(draw_depth) {
        depth_image.draw(-ofGetWidth()/2,-ofGetHeight()/2);
    }
    
    if(draw_contours) {
        contour_finder.draw();
    }
    
    if(draw_polylines) {
        for(int i = 0; i < polylines.size(); i++) {
            polylines[i].draw();
        }
    }
    
    if(draw_tri_meshes) {
        for(int i = 0; i < tri_meshes.size(); i++) {
            tri_meshes[i].draw();
        }
    }
    
    if(draw_mesh) {
        for(int i = 0; i < meshes.size(); i++) {
            meshes[i].drawWireframe();
        }
    }
    
    if(draw_vertices) {
        for(int i = 0; i < polylines.size(); i++) {
            for(int j = 0; j < polylines[i].size(); j++) {
                ofDrawCircle(polylines[i][j], 5);
            }
        }
    }
    easycam.end();
    gui.draw();
    outputFbo.end();
    
    depthFbo.begin();
    kinect.drawDepth(0,0,ofGetWidth(),ofGetHeight());
    depthFbo.end();
}

//--------------------------------------------------------------
void ofApp::draw(){
    outputFbo.draw(0, 0);
    syphon.publishTexture(&outputFbo.getTexture());
//    ofBackgroundGradient(ofColor(64), ofColor(0));
//    easycam.begin();
//
//    ofSetColor(255);
//
//    if(draw_depth) {
//        depth_image.draw(0,0);
//    }
//
//    if(draw_contours) {
//        contour_finder.draw();
//    }
//
//    if(draw_polylines) {
//        for(int i = 0; i < polylines.size(); i++) {
//            polylines[i].draw();
//        }
//    }
//
//    if(draw_tri_meshes) {
//        for(int i = 0; i < tri_meshes.size(); i++) {
//            tri_meshes[i].draw();
//        }
//    }
//
//    if(draw_mesh) {
//        for(int i = 0; i < meshes.size(); i++) {
//            meshes[i].drawWireframe();
//        }
//    }
//
//    if(draw_vertices) {
//        for(int i = 0; i < polylines.size(); i++) {
//            for(int j = 0; j < polylines[i].size(); j++) {
//                ofDrawCircle(polylines[i][j], 5);
//            }
//        }
//    }
//    easycam.end();
//    gui.draw();
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
