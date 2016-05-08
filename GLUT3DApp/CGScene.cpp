//
//  CGScene.cpp
//  GLUT3DApp
//
//  Created by Ben Johnson on 8/05/2016.
//  Copyright © 2016 Benjamin Johnson. All rights reserved.
//

#include "CGScene.hpp"
#ifdef __APPLE__
#include <GLUT/GLUT.h> //GLUT Library, will make you life easier
#include <OpenGL/OpenGL.h> //OpenGL Library
#elif defined _WIN32 || defined _WIN64
#include <glut.h>
#endif


void CGScene::renderNode(CGNode *node) {
    
    glLoadIdentity();
    translate(node->position);
    glRotatef(node->rotation.w, node->rotation.x, node->rotation.y, node->rotation.z);
    
    // Add Geometry
    if (node->geometry != NULL) {
        node->geometry->render();
    }
    
    // Add Light
    if (node->light != NULL) {
        CGLight *light = node->light;
        GLenum lightID = GL_LIGHT0;
        GLfloat position[] = {node->position.x, node->position.y, node->position.z, 1.0};
        GLfloat color[] = {light->color.r, light->color.g, light->color.b, light->color.a};
        
        // Set position
        glLightfv(lightID, GL_POSITION, position);
        glLightfv(lightID, GL_DIFFUSE, color);
    
        
        
    }
}

CGScene::CGScene() {
    rootNode = new CGNode();
    
}

void CGScene::render() {
    
    
    
    // Reset transformations

    // Other Transformations
    // glTranslatef( 0.1, 0.0, 0.0 );      // Not included
    // glRotatef( 180, 0.0, 1.0, 0.0 );    // Not included
    
    // Rotate when user changes rotate_x and rotate_y
 //   glRotatef( 45, 1.0, 0.0, 0.0 );
 //   glRotatef( rotate_y, 0.0, 1.0, 0.0 );
    
    // Other Transformations
    // glScalef( 2.0, 2.0, 0.0 );          // Not included
    
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