//
//  CGBox.hpp
//  GLUT3DApp
//
//  Created by Ben Johnson on 8/05/2016.
//  Copyright © 2016 Benjamin Johnson. All rights reserved.
//

#ifndef CGBox_hpp
#define CGBox_hpp

#include <stdio.h>
#include "CGGeometry.hpp"
#ifdef __APPLE__
#include <GLUT/GLUT.h> //GLUT Library, will make you life easier
#include <OpenGL/OpenGL.h> //OpenGL Library
#elif defined _WIN32 || defined _WIN64
#include <glut.h>
#endif

class CGBox: public CGGeometry {
    
    
public:
    
    float width;
    
    float height;
    
    float length;
    
    CGBox(float width, float height, float length) {
        
        this->width = width;
        
        this->height = height;
        
        this->length = length;
        
    }
    
    void presentationGeometry();
};

class CGPlane: public CGGeometry {
    
public:
    
    float width;
    
    float height;
    
    int widthSegmentCount;
    
    int heightSegmentCount;
    
    CGPlane(float width, float height) {
        
        this->width = width;
        
        this->height = height;
        
        widthSegmentCount = 1;
        
        heightSegmentCount = 1;
        
    }
    
    void presentationGeometry();
};

class CGPyramid: public CGGeometry {
    
public:
    
    float width;
    
    float height;
    
    float length;
    
    CGPyramid(float width, float height, float length) {
        
        
    }
    
    void presentationGeometry();

};

class CGSphere: public CGGeometry {
    
    float radius;
    
    int segmentCount;
    
public:
    
    CGSphere(float radius) {
        this->radius = radius;
        segmentCount = 48;
        
    }
    
    void presentationGeometry();
    
};

class CGTeapot: public CGGeometry {
    
    float size;
    
public:
    
    CGTeapot(float size) {
        
        this->size = size;
        
    }
    
    void presentationGeometry();
};

class CGCone {
    
    
public:
    
    float width;
    
    float height;
    
    int segments;
    
    CGCone(float width, float height, int segments) {
        
        this->width = width;
        this->height = height;
        this->segments = segments;
        
    }
    
    void presentationGeometry() {
        glutSolidCone(width, height, segments, segments);
    }
};


class CGTorus {
    
    
public:
    
    float ringRadius;
    
    float pipeRadius;
    
    int ringSegmentCount;
    
    int pipeSegmentCount;
    
    CGTorus(float ringRadius, float pipeRadius) {
        
        this->ringRadius = ringRadius;
        
        this->pipeRadius = pipeRadius;
        
        ringSegmentCount = 48;
        
        pipeSegmentCount = 24;
        
    }
    
    void presentationGeometry() {
        glutSolidTorus(pipeRadius, ringRadius, pipeSegmentCount, ringSegmentCount);
    }
};


#endif /* CGBox_hpp */
