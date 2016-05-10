//
//  CGScene.cpp
//  GLUT3DApp
//
//  Created by Ben Johnson on 8/05/2016.
//  Copyright © 2016 Benjamin Johnson. All rights reserved.
//

#include "CGScene.hpp"

GLenum CGScene::currentLightID() {
    switch (lightCount) {
        case 0:
            return GL_LIGHT0;
        case 1:
            return GL_LIGHT1;
        case 2:
            return GL_LIGHT2;
        case 3:
            return GL_LIGHT3;
        case 4:
            return GL_LIGHT4;
        case 5:
            return GL_LIGHT5;
        case 6:
            return GL_LIGHT6;
        case 7:
            return GL_LIGHT7;
        default:
            return GL_LIGHT7;
    }
}

void CGScene::renderNode(CGNode *node) {
    
    if(node->hidden) {
        return;
    }
    
    glPushMatrix();
    translate(node->position);
    glRotatef(node->rotation.w, node->rotation.x, node->rotation.y, node->rotation.z);
    
    // Add Geometry
    if (node->geometry != NULL) {
    
        // Load Material
        CGMaterial *material = node->geometry->firstMaterial();
        if (material != NULL) {
            
          //  material->loadMaterial();
            
        }
        
        node->geometry->presentationGeometry();
     
    }
    
    // Add Light
    if (node->light != NULL) {
        
        CGLight *light = node->light;
        
        GLenum lightID = currentLightID();
        GLfloat position[] = {node->position.x, node->position.y, node->position.z, 1.0};
        
        // Set position
        glLightfv(lightID, GL_POSITION, position);
        
        float colorValues[] = {light->color.r, light->color.g, light->color.b, light->color.a};
        
        // Set Color
        glLightfv(lightID, GL_AMBIENT, colorValues);
        glLightfv(lightID, GL_DIFFUSE, colorValues);
        
        // Enable Light
        glEnable(lightID);
    
        lightCount++;
        
    }
    
    glPopMatrix();
}

CGScene::CGScene() {
    
    rootNode = new CGNode();
    
    backgroundColor = CGColorWhite();
    
    globalAmbientColor = CGColor(0.2, 0.2, 0.2, 1.0);
    
    lightCount = 0;
    
}

void CGScene::render() {
    // Setup Lighting
    lightCount = 0;
    

    //Multi-colored side - FRONT
    if (rootNode == NULL) {
        return;
    }
    
    // Render Child nodes
    for (int i = 0; i < rootNode->childNodes.size(); i++) {
        CGNode *node = rootNode->childNodes[i];
        renderNode(node);
    }
    
    
    
}