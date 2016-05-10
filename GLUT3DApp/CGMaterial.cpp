//
//  CGMaterial.cpp
//  GLUT3DApp
//
//  Created by Ben Johnson on 9/05/2016.
//  Copyright © 2016 Benjamin Johnson. All rights reserved.
//

#include "CGMaterial.hpp"

#ifdef __APPLE__
#include <GLUT/GLUT.h> //GLUT Library, will make you life easier
#include <OpenGL/OpenGL.h> //OpenGL Library
#elif defined _WIN32 || defined _WIN64
#    include <glut.h>
#endif


void CGMaterial::loadMaterial() {

        
        GLenum faceType = doubleSided ? GL_FRONT_AND_BACK : GL_FRONT;
    
        if(locksAmbientWithDiffuse) {
            
            glMaterialfv(faceType, GL_AMBIENT_AND_DIFFUSE, diffuse.values());
            
        } else {
            
            glMaterialfv(faceType, GL_AMBIENT, ambient.values());
            
            glMaterialfv(faceType, GL_DIFFUSE, diffuse.values());
            
        }
        
        glMaterialfv(faceType, GL_SPECULAR, specular.values());
        
        glMaterialfv(faceType, GL_EMISSION, emission.values());
        
        glMaterialf(faceType, GL_SHININESS, shininess);
        
 }