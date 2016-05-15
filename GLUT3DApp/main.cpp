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
#include "CGPresetMaterials.hpp"
#include <math.h>

#define MY_PI 		(3.14159265359)    //declare PI value
#define DEG2RAD(a) 	(MY_PI/180*(a))    //convert degrees into radians


int mainWindow;

CGScene *scene;

CGNode *pointOfView;

enum ContextMenu {
    Clear,
    Exit
};

GLfloat aspect;

GLfloat movementSpeed = 0.2;

GLfloat cameraYaw = 0.0;

GLfloat moveForward = 1.0;

GLfloat rotationSpeed = 2;

GLenum shadeModel = GL_SMOOTH;

GLenum cullFaceMode = GL_BACK;

bool yellowAmbientEnabled = false;

void resetCamera();

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

void toggleShadeModel() {
    if (shadeModel == GL_SMOOTH) {
        shadeModel = GL_FLAT;
        
    } else {
        shadeModel = GL_SMOOTH;
    }
    
    glShadeModel(shadeModel);
    glutPostRedisplay();
}

void toggleOpenGLSetting(GLenum property) {
    if (glIsEnabled(property)) {
        glDisable(property);
    } else {
        glEnable(property);
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
    
    if (cameraYaw > 360.0) {
        cameraYaw -= 360.0;
    } else if(cameraYaw < 0.0)
        cameraYaw += 360.0;
    
    pointOfView->position.x += sinf(DEG2RAD(cameraYaw)) * moveForward;
    pointOfView->position.z += -cos(DEG2RAD(cameraYaw)) * moveForward;
    
    moveForward = 0;
    
    float lookAtX =  pointOfView->position.x + sin(DEG2RAD(cameraYaw));
    float lookAtZ =  pointOfView->position.z - cos(DEG2RAD(cameraYaw));
    
    
    glLoadIdentity();
    
    // Enable perspective projection with fovy, aspect, zNear and zFar
    CGCamera *camera = pointOfView->camera;
    gluPerspective(camera->yFov, aspect, camera->zNear, camera->zFar);
    
    gluLookAt(pointOfView->position.x, pointOfView->position.y, pointOfView->position.z, lookAtX, 1.0, lookAtZ, 0, 1, 0);
 

    glutPostRedisplay();
   // windowShouldRedraw();
}


void toggleAmbientLighting() {
    if (!scene->autoenablesDefaultLighting) {
        return;
    }

    if (yellowAmbientEnabled) {
        scene->globalAmbientColor = CGColor(0.2, 0.2, 0.2, 1.0);
        yellowAmbientEnabled = false;
    } else {
        scene->globalAmbientColor = CGColorSimpleYellow();
        yellowAmbientEnabled = true;
    }
    
    float values[] {scene->globalAmbientColor.r, scene->globalAmbientColor.b, scene->globalAmbientColor.g, scene->globalAmbientColor.a};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, values);
}

void toggleCullFace() {
    if (cullFaceMode == GL_BACK) {
        cullFaceMode = GL_FRONT;
    } else {
        cullFaceMode = GL_BACK;
    }
    
    glCullFace(cullFaceMode);
    
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
        case 'z':
            toggleShadeModel();
            break;
        
        case 'd':
            toggleOpenGLSetting(GL_DEPTH_TEST);
            break;
        case 'c':
            toggleOpenGLSetting(GL_CULL_FACE);
            break;
        case 'f':
            toggleCullFace();
            break;
        case 'm':
            toggleOpenGLSetting(GL_COLOR_MATERIAL);
            break;
        case 'l':
            toggleAmbientLighting();
            break;
        case 'r':
            resetCamera();
            break;
        default:
            break;
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
          //  teapotNode->position.x += 1;
           // pointOfView->position.x += movementSpeed;
            moveForward += movementSpeed;
            //gMoveForward += gMovementSensitivity;             //increment forward movement
            break;
            //if arrow down pressed
        case GLUT_KEY_DOWN:
            moveForward -= movementSpeed;

            //gMoveForward -= gMovementSensitivity;             //increment backward movement
            break;
            //if left pressed
        case GLUT_KEY_LEFT:
          //  pointOfView->position.x -= movementSpeed;
            cameraYaw -= rotationSpeed;
            
            //gCameraYaw -= gRotationSensitivity;               //increment camera yaw
            break;
            //if right pressed
        case GLUT_KEY_RIGHT:
            //pointOfView->position.x += movementSpeed;
            cameraYaw += rotationSpeed;
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

void render(void) {
  
    // Setup Scene background color
    CGColor backgroundColor = scene->backgroundColor;
    glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);

    //  Clear screen and Z-buffer
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix

    glLoadIdentity();
    
    // Setup Camera
    // actual vector representing the camera's direction
    float lookAtX =  pointOfView->position.x + sin(DEG2RAD(cameraYaw));
    float lookAtZ =  pointOfView->position.z - cos(DEG2RAD(cameraYaw));
    
    gluLookAt(pointOfView->position.x, pointOfView->position.y, pointOfView->position.z, lookAtX, 1.0, lookAtZ, 0, 1, 0);

    scene->render();
    
    glFlush();

}

void setupLights() {
    
    CGLight *light1 = new CGLight();
    CGNode *lightNode = new CGNode();
    lightNode->position = CGVector3(5.0, 15.0, 5.0);
    lightNode->light = light1;
    light1->color = CGColorWhite();
    
    CGLight *light2 = new CGLight();
    light2->color = CGColorBlue();
    CGNode *lightNode2 = new CGNode();
    lightNode2->position = CGVector3(6.0, 15.0, 5.0);
    lightNode2->light = light2;
    
    scene->rootNode->addChildNode(lightNode);
  //  scene->rootNode->addChildNode(lightNode2);
}

void setupCamera() {
    // Setup Camera
    CGCamera *sceneCamera = new CGCamera();
    CGNode *cameraNode = new CGNode();
    // x, y ,z modifiying in z- is back
    cameraNode->position = CGVector3(0,1,5);
    //cameraNode->position = CGVector3(0,10,15);
    cameraNode->camera = sceneCamera;
    pointOfView = cameraNode;
    
}

void resetCamera() {
    pointOfView->position = CGVector3(0,1,5);
    moveForward = 0;
    cameraYaw = 0;
    
    glutPostRedisplay();
}

CGNode* createTable() {
    
    float zPosition = 0;

    // Table
    float tableLeftPosition = -0.9;
    float tableRightPosition = 0.9;
    float tableVerticalPosition = -0.1;
    
    CGNode *tableNode = new CGNode();
    tableNode->position = CGVector3(0, 0, zPosition);
    //cubeNode->rotation = CGVector4(1, 1, 0, 45);
    
    CGBox *tableComponent = new CGBox(1,1,1);
    tableComponent->setMaterial(CGPresentMaterial::orangeMaterial());
    
    
    CGNode *tableTopNode = new CGNode(tableComponent);
    tableTopNode->scale = CGVector3(1,0.05,1);
    tableTopNode->position = CGVector3(0,0.95,0);
    
    
    CGNode *leftBottomLegNode = new CGNode(tableComponent);
    leftBottomLegNode->scale = CGVector3(0.1,1,0.11);
    leftBottomLegNode->position = CGVector3(tableLeftPosition, tableVerticalPosition, 1);
    
    CGNode *rightBottomLegNode = new CGNode(*leftBottomLegNode);
    rightBottomLegNode->position = CGVector3(tableRightPosition,tableVerticalPosition,1);
    
    CGNode *leftTopLegNode = new CGNode(*leftBottomLegNode);
    leftTopLegNode->position = CGVector3(tableLeftPosition,tableVerticalPosition,-0.8);
    
    CGNode *rightTopLegNode = new CGNode(*leftBottomLegNode);
    rightTopLegNode->position = CGVector3(tableRightPosition,tableVerticalPosition,-0.8);
    
    
    tableNode->addChildNode(tableTopNode);
    tableNode->addChildNode(leftBottomLegNode);
    tableNode->addChildNode(rightBottomLegNode);
    tableNode->addChildNode(leftTopLegNode);
    tableNode->addChildNode(rightTopLegNode);

    
    return tableNode;
}

void setupObjects() {
    float zPosition = 0;

    CGNode *tableNode = createTable();
    
    float roomHeight = 10;
    
    // Floor
    CGNode *floorNode  = new CGNode(new CGPlane(100,100));
    floorNode->position = CGVector3(0, 0, zPosition);
    
    // Roof
    CGNode *roofNode  = new CGNode(new CGPlane(100,100));
    roofNode->position = CGVector3(0, roomHeight, 0);
    roofNode->rotation = CGVector4(1, 0, 0, 180);
    
    // Front wall
    CGNode *frontWallNode  = new CGNode(new CGPlane(15,roomHeight));
    frontWallNode->position = CGVector3(0, 0, 7.2);
    frontWallNode->rotation = CGVector4(1, 0, 0, -90);
    
    // Back Wall
    CGNode *backWallNode  = new CGNode(new CGPlane(15,roomHeight));
    backWallNode->position = CGVector3(0, 0, -5);
    backWallNode->rotation = CGVector4(1, 0, 0, -90);
    
    // Left Wall
    CGNode *leftWallNode  = new CGNode(new CGPlane(15,roomHeight));
    leftWallNode->position = CGVector3(-7, 0, 0);
    leftWallNode->eulerAngles = CGVector3(90, 0, 90);
    
    // Left Wall
    CGNode *rightWallNode  = new CGNode(new CGPlane(15,roomHeight));
    rightWallNode->position = CGVector3(7, 0, 0);
    rightWallNode->eulerAngles = CGVector3(90, 0, 90);
    
    
    // Teapot
    CGGeometry *teapot = new CGTeapot(0.3);
    teapot->setMaterial(CGPresentMaterial::goldMaterial());
    CGNode *teapotNode = new CGNode(teapot);
    teapotNode->position = CGVector3(0 , 1.15, zPosition);
    
    // Sphere
    CGSphere *sphere = new CGSphere(0.2);
    sphere->setMaterial(CGPresentMaterial::jadeMaterial());
    CGNode *sphereNode = new CGNode(sphere);
    sphereNode->position = CGVector3(-1, 1.2, zPosition);
    
    // Cone
    CGCone *cone = new CGCone(0.15 , 0.3);
    cone->setMaterial(CGPresentMaterial::blueMaterial());
    CGNode *coneNode = new CGNode(cone);
    coneNode->position = CGVector3(1, 1.0, zPosition);
    coneNode->rotation = CGVector4(1,0,0,-90);
    
    // Torus
    CGTorus *torus = new CGTorus(0.1,0.05);
    torus->setMaterial(CGPresentMaterial::copperMaterial());
    CGNode *torusNode = new CGNode(torus);
    
    torusNode->position = CGVector3(0.7, 1.2, zPosition);

    // Dodecahedron
    CGDodecahedron *dodecahedron = new CGDodecahedron();
    dodecahedron->setMaterial(CGPresentMaterial::rubyMaterial());
    CGNode *dodecahedronNode = new CGNode(dodecahedron);
    dodecahedronNode->position = CGVector3(0.7, 1.2, zPosition);
    dodecahedronNode->scale = CGVector3(0.1,0.1,0.1);
    
    // Octahedron
    CGOctahedron *octahedron = new CGOctahedron();
    octahedron->setMaterial(CGPresentMaterial::cyanMaterial());
    CGNode *octahedronNode = new CGNode(octahedron);
    octahedronNode->position = CGVector3(-0.1,0.9, zPosition);
    octahedronNode->scale = CGVector3(0.2,0.2,0.2);
    
    // Tetrahedron
    CGTetrahedron *tetrahedron = new CGTetrahedron();
    tetrahedron->setMaterial(CGPresentMaterial::redMaterial());
    CGNode *tetrahedronNode = new CGNode(tetrahedron);
    tetrahedronNode->position = CGVector3(0.7,0.7, zPosition);
    tetrahedronNode->scale = CGVector3(0.5,0.5,0.5);
    
    // Icosahedron
    CGIcosahedron *icosahedron = new CGIcosahedron();
    icosahedron->setMaterial(CGPresentMaterial::rubyMaterial());
    CGNode *icosahedronNode = new CGNode(icosahedron);
    icosahedronNode->position = CGVector3(0.7,0.9, zPosition);
    icosahedronNode->scale = CGVector3(0.3,0.3,0.3);
    
    // Setup Room
    scene->rootNode->addChildNode(floorNode);
    scene->rootNode->addChildNode(roofNode);
    scene->rootNode->addChildNode(frontWallNode);
    scene->rootNode->addChildNode(backWallNode);
    scene->rootNode->addChildNode(leftWallNode);
    scene->rootNode->addChildNode(rightWallNode);
    
    scene->rootNode->addChildNode(tableNode);
    
    // Add ornaments
    scene->rootNode->addChildNode(teapotNode);
    scene->rootNode->addChildNode(sphereNode);
    scene->rootNode->addChildNode(coneNode);
    scene->rootNode->addChildNode(torusNode);
    scene->rootNode->addChildNode(dodecahedronNode);
    scene->rootNode->addChildNode(octahedronNode);
    scene->rootNode->addChildNode(tetrahedronNode);
    scene->rootNode->addChildNode(icosahedronNode);

}

void setupScene() {
    
    scene = new CGScene();
    
    scene->backgroundColor = CGColorWhite();

    setupCamera();
    
    setupObjects();
    
    setupLights();

}

void initOpenGL() {
    
    glutDisplayFunc(render);
    glutReshapeFunc(resize);
    glutMouseFunc(mouseHandler);
    glutIdleFunc(render);
    glEnable(GL_MULTISAMPLE_ARB);

    setupScene();
    
    glClearDepth(1.0f);       // Set background depth to farthest
    glEnable(GL_LIGHTING);    //enable lighting
    glEnable(GL_DEPTH_TEST);  // Enable depth testing for z-culling
    
    glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
    glShadeModel(shadeModel);   // Enable smooth shading
    glutKeyboardFunc(keyboardHandler);
    glutSpecialFunc(specialKeyHandler);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections

}

int main(int argc, char * argv[]) {
    
#ifdef __APPLE__
    //Init glut passing some args
    glutInit(&argc, argv);
#endif
    
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);      //requests properties for the window (sets up the rendering context)

    //Specify the Display Mode, this one means there is a single buffer and uses RGB to specify colors
    // glutInitDisplayMode(GLUT_DEPTH| GLUT_DOUBLE |GLUT_RGB);
    
    //Set the window size
    glutInitWindowSize(800, 600);
    
    //Where do we want to place the window initially?
    glutInitWindowPosition(100,100);
    


    
    //Name the window and create it
    mainWindow = glutCreateWindow("Tea Time");
    glutSetWindow(mainWindow);

    //  Enable Z-buffer depth test
    glEnable(GL_DEPTH_TEST);
    
    initOpenGL();
    
    //Start the main loop running, nothing after this will execute for all eternity (right now)
    glutMainLoop();
    
    return 0;
}