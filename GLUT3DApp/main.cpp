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
#include "CGParametricGeometry.hpp"
#include <math.h>


int mainWindow;
CGScene *scene;

CGNode *pointOfView;

enum ContextMenu {
    Clear,
    Exit
};


GLfloat aspect;

GLfloat movementSpeed = 1;


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

void setPolygonMode(CGPolygonMode mode) {
    switch (mode) {
        case CGPolygonModeWire:
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);    //wireframe mode
        case CGPolygonModeSolid:
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);    //fill mode
    }
    
    windowShouldRedraw();
}

void updateCamera() {
    
    glLoadIdentity();
    
    // Enable perspective projection with fovy, aspect, zNear and zFar
    CGCamera *camera = pointOfView->camera;
    gluPerspective(camera->yFov, aspect, camera->zNear, camera->zFar);
    
    // actual vector representing the camera's direction
    float lookX = sinf(pointOfView->rotation.w);
    float lookZ = -cos(pointOfView->rotation.w);
    //  lz=-1.0f;
    
    float x = pointOfView->position.x ;
    float z = pointOfView->position.z;
    
    gluLookAt(pointOfView->position.x, pointOfView->position.y, pointOfView->position.z, x + lookX, 1.0, z + lookZ, 0, 1, 0);
    
    glutPostRedisplay();
   // windowShouldRedraw();
}


void keyboardHandler(unsigned char key, int x, int y)
{
    switch(key)
    {
            //if ESC pressed, quit program
        case 27: exit(1);     //quit
            break;
        case 'w':  setPolygonMode(CGPolygonModeWire);
            break;
        case 's':  setPolygonMode(CGPolygonModeSolid);
            break;
        default: break;
    };
}


//called when non-ASCII key pressed
void specialKeyHandler(int key, int x, int y)
{
    switch(key)
    {
            //if home pressed
        case GLUT_KEY_HOME:
            //  gCameraPosition[1] += gMovementSensitivity;       //increment camera height
            //  gCameraLookAt[1] += gMovementSensitivity;
            break;
            //if end pressed
        case GLUT_KEY_END:
            //gCameraPosition[1] -= gMovementSensitivity;       //decrement camera height
            //     gCameraLookAt[1] -= gMovementSensitivity;
            break;
            //if arrow up pressed
        case GLUT_KEY_UP:
            pointOfView->position.x += movementSpeed;
            
            //gMoveForward += gMovementSensitivity;             //increment forward movement
            break;
            //if arrow down pressed
        case GLUT_KEY_DOWN:
            pointOfView->position.x -= movementSpeed;

            //gMoveForward -= gMovementSensitivity;             //increment backward movement
            break;
            //if left pressed
        case GLUT_KEY_LEFT:
            pointOfView->position.x -= movementSpeed;

            //gCameraYaw -= gRotationSensitivity;               //increment camera yaw
            break;
            //if right pressed
        case GLUT_KEY_RIGHT:
            pointOfView->position.x += movementSpeed;

            //gCameraYaw += gRotationSensitivity;              //decrement camera yaw
            break;
        default: break;
    };
    updateCamera();
    
    //   updateCamera();       //call function to update camera and refresh the scene
}





void resize(int width, int height) {
    
    // Compute aspect ratio of the new window
    if (height == 0) height = 1;                // To prevent divide by 0
    aspect = (GLfloat)width / (GLfloat)height;
    
    // Set the viewport to cover the new window
    glViewport(0, 0, width, height);
    
    // Set the aspect ratio of the clipping volume to match the viewport
    glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
   // glLoadIdentity();             // Reset
    updateCamera();
    
  }


CGRect getWindowRect() {
    int x = glutGet(GLUT_WINDOW_X);
    int y = glutGet(GLUT_WINDOW_Y);
    int width = glutGet(GLUT_WINDOW_WIDTH);
    int height = glutGet(GLUT_WINDOW_HEIGHT);
    
    return CGRectMake((float)x, (float)y, (float)width, (float)height);
}

void render(void){
    
    // Setup Scene background color
    CGColor backgroundColor = scene->backgroundColor;
    glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
    
    //  Clear screen and Z-buffer
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix

    // Set background color to white and opaque
   // glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    
    scene->render();
    
    glutSwapBuffers();
    
}

void setupScene() {
    
    // Setup Camera
    CGCamera *sceneCamera = new CGCamera();
    CGNode *cameraNode = new CGNode();
    cameraNode->position = CGVector3(0,1,0);
    cameraNode->camera = sceneCamera;
    pointOfView = cameraNode;
    
    glutDisplayFunc(render);
    glutReshapeFunc(resize);
    glutMouseFunc(mouseHandler);
    
    scene = new CGScene();
    // Create Cube node
    CGNode *cubeNode = new CGNode();
    cubeNode->geometry = new CGBox(1,1,1);
    cubeNode->position = CGVector3(1.5, 0, -7);
    cubeNode->rotation = CGVector4(1, 1, 0, 45);
    
    CGNode *cubeNode2 = new CGNode();
    cubeNode2->geometry = new CGBox(1,1,1);
    cubeNode2->position = CGVector3(0, 0, -7);
    cubeNode2->hidden = true;
    
    CGNode *pyramidNode = new CGNode(new CGPyramid(1,1,1));
    pyramidNode->position = CGVector3(0, 0, -7);
    
    CGNode *planeNode  = new CGNode(new CGPlane(1,1));
    planeNode->position = CGVector3(0, 0, -7);
    planeNode->rotation = CGVector4(1, 0, 0, 45);
    
    CGNode *teapotNode = new CGNode(new CGTeapot(1));
    teapotNode->position = CGVector3(0 , 1, -7);
    
    CGLight *light1 = new CGLight();
    CGNode *lightNode = new CGNode();
    lightNode->position = CGVector3(5.0, 15.0, 5.0);
    lightNode->light = light1;
    light1->color = CGColorWhite();
    
    scene->rootNode->addChildNode(lightNode);
    scene->rootNode->addChildNode(planeNode);
    scene->rootNode->addChildNode(teapotNode);
    
    scene->backgroundColor = CGColorWhite();
  //  scene->rootNode->addChildNode(cubeNode);
  //  scene->rootNode->addChildNode(cubeNode2);
  //  scene->rootNode->addChildNode(pyramidNode);
    
    
}

void initOpenGL() {
    
    setupScene();
    
    glClearDepth(1.0f);                   // Set background depth to farthest
    glEnable(GL_LIGHTING);    //enable lighting
    glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
    
    glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
    glShadeModel(GL_SMOOTH);   // Enable smooth shading
    glutKeyboardFunc(keyboardHandler);
    glutSpecialFunc(specialKeyHandler);
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