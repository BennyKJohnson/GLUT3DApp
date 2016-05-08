//
//  main.cpp
//  GLUTDrawingApp
//
//  Created by Benjamin Johnson on 12/04/2016.
//  Copyright © 2016 Benjamin Johnson. All rights reserved.
//

#include <iostream>
#include <string>

#ifdef __APPLE__
#include <GLUT/GLUT.h> //GLUT Library, will make you life easier
#include <OpenGL/OpenGL.h> //OpenGL Library
#elif defined _WIN32 || defined _WIN64
#include <glut.h>
#endif

#include "CG.hpp"
#include "CGScene.hpp"
#include "CGBox.hpp"


int mainWindow;
CGScene *scene;

CGNode *pointOfView;

enum ContextMenu {
    Clear,
    Exit
};



void setOGLProjection(int width, int height) {
    glViewport(0, 0, width, height);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    glOrtho(0, width, height, 0, -1, 1);
    
    //Back to the modelview so we can draw stuff
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
}

void windowShouldRedraw() {
    glutSetWindow(mainWindow);
    glutPostRedisplay();
}

void mouseHandler(int button, int state, int x, int y) {
    
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        
        windowShouldRedraw();
        
    }
}

void resize(int width, int height) {
    
    // Compute aspect ratio of the new window
    if (height == 0) height = 1;                // To prevent divide by 0
    GLfloat aspect = (GLfloat)width / (GLfloat)height;
    
    // Set the viewport to cover the new window
    glViewport(0, 0, width, height);
    
    // Set the aspect ratio of the clipping volume to match the viewport
    glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
    glLoadIdentity();             // Reset
    
    // Enable perspective projection with fovy, aspect, zNear and zFar
    CGCamera *camera = pointOfView->camera;
    gluPerspective(camera->yFov, aspect, camera->zNear, camera->zFar);
    
}


CGRect getWindowRect() {
    int x = glutGet(GLUT_WINDOW_X);
    int y = glutGet(GLUT_WINDOW_Y);
    int width = glutGet(GLUT_WINDOW_WIDTH);
    int height = glutGet(GLUT_WINDOW_HEIGHT);
    
    return CGRectMake((float)x, (float)y, (float)width, (float)height);
}

void render(void){
    
    //  Clear screen and Z-buffer
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix

    // Set background color to white and opaque
   // glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    
    scene->render();
    
    glutSwapBuffers();
    
}



void initOpenGL() {
    
    // Setup Camera
    CGCamera *sceneCamera = new CGCamera();
    CGNode *cameraNode = new CGNode();
    cameraNode->camera = sceneCamera;
    pointOfView = cameraNode;
    
    glutDisplayFunc(render);
    glutReshapeFunc(resize);
    glutMouseFunc(mouseHandler);
    
    scene = new CGScene();
    // Create Cube node
    CGNode *cubeNode = new CGNode();
    cubeNode->geometry = new CGBox();
    cubeNode->position = CGVector3(1.5, 0, -7);
    cubeNode->rotation = CGVector4(1, 1, 0, 45);
    
    CGNode *cubeNode2 = new CGNode();
    cubeNode2->geometry = new CGBox();
    cubeNode2->position = CGVector3(0, 0, -7);
    
    scene->rootNode->addChildNode(cubeNode);
    scene->rootNode->addChildNode(cubeNode2);
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
    glClearDepth(1.0f);                   // Set background depth to farthest
    glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
    glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
    glShadeModel(GL_SMOOTH);   // Enable smooth shading
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections

}


int main(int argc, char * argv[]) {
    
#ifdef __APPLE__
    //Init glut passing some args
    glutInit(&argc, argv);
#endif
    
    glutInitDisplayMode(GLUT_DOUBLE);

    //Specify the Display Mode, this one means there is a single buffer and uses RGB to specify colors
    // glutInitDisplayMode(GLUT_DEPTH| GLUT_DOUBLE |GLUT_RGB);
    
    //Set the window size
    glutInitWindowSize(800, 600);
    
    //Where do we want to place the window initially?
    glutInitWindowPosition(100,100);
    
    //Name the window and create it
    mainWindow = glutCreateWindow("3D App");
    
    //  Enable Z-buffer depth test
    glEnable(GL_DEPTH_TEST);
    
    initOpenGL();
    
    //Start the main loop running, nothing after this will execute for all eternity (right now)
    glutMainLoop();
    
    return 0;
}