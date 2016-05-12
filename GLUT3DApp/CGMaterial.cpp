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
    
    float diffuseValues[] = {diffuse.r, diffuse.g, diffuse.b, diffuse.a};
    
    float ambientValues[] = {ambient.r, ambient.g, ambient.b, ambient.a};
    
    float specularValues[] = {specular.r, specular.g, specular.b, specular.a};
    
    float emissionValues[] = {emission.r, emission.g, emission.b, emission.a};

    
        glMaterialfv(faceType, GL_DIFFUSE, diffuseValues);

    
        if(locksAmbientWithDiffuse) {
            
            glMaterialfv(faceType, GL_AMBIENT, ambientValues);
            
            glMaterialfv(faceType, GL_DIFFUSE, diffuseValues);
           // glMaterialfv(faceType, GL_AMBIENT_AND_DIFFUSE, ambient.values());
            
        } else {
            
            glMaterialfv(faceType, GL_AMBIENT, ambientValues);
            
            glMaterialfv(faceType, GL_DIFFUSE, diffuseValues);
            
        }
        
        glMaterialfv(faceType, GL_SPECULAR, specularValues);
        
        glMaterialfv(faceType, GL_EMISSION, emissionValues);
        
        glMaterialf(faceType, GL_SHININESS, shininess);
    
 }