//
//  Controller.hpp
//  DM6101Assignment
//
//  Created by Christina Lui on 10/11/15.
//  Copyright © 2015 Christina Lui. All rights reserved.
//

#ifndef Controller_hpp
#define Controller_hpp

#include <stdio.h>
#include <iostream>

//Graphics library - Mac OS
#ifdef __APPLE__
#   include <OpenGL/OpenGL.h>
#   include <GLUT/GLUT.h>
#   include <GLUI/GLUI.h>
#else
#   include <GL/gl.h>
#   include <GL/glu.h>
#   include <GL/glut.h>
#endif

#include "Screen.hpp"
#include "Camera.hpp"
#include "mFileParser.hpp"

using namespace Screen;
using namespace Camera;
using namespace mFileParser;

namespace Controller {
    
    //GETTER
    float getScaleFactor();
    float getMoveXFactor(); //returns distance moved by mouse on window in x direction (in px)
    float getMoveYFactor(); //returns distance moved by mouse on window in y direction (in px)
    float getMoveObjectXFactor(); //returns relative distance moved by mouse in model space in x direction (in model space unit)
    float getMoveObjectYFactor(); //returns relative distance moved by mouse in model space in y direction (in model space unit)
    float getMoveObjectZFactor(); //returns relative distance moved by mouse in model space in z direction (in model space unit)
    float getMoveXAngle();
    float getMoveYAngle();
    float getTransformMode();
    bool showPoints();
    bool showWireframe();
    bool showFlatshading();
    bool showSmoothshading();
    bool showBoundingBox();
    bool showPerspective();
    
    //Motion EventHandler
    void motionHandler(int x, int y);
    
    //Mouse EventHandler
    void mouseHandler(int button, int state, int x, int y);
    
    //Keyboard EventHandler
    void keyPressHandler(unsigned char key, int x, int y);
    
    //Model Selector
    int selectModel();
    
    //GLUI menu
    void createGLUIMenu(int main_window);
}


#endif /* Controller_hpp */
