//
//  Screen.hpp
//  DM6101Assignment
//
//  Created by Christina Lui on 10/11/15.
//  Copyright © 2015 Christina Lui. All rights reserved.
//

#ifndef Screen_hpp
#define Screen_hpp

#include <stdio.h>
#include <iostream>

#ifdef __APPLE__
#   include <OpenGL/OpenGL.h>
#   include <GLUT/GLUT.h>
#else
#   include <GL/gl.h>
#   include <GL/glu.h>
#   include <GL/glut.h>
#endif

namespace Screen {
    //define the size of the window
    
    //get window
    int getWindowObj();
    
    //init window
    void setupWindow();
    
    //set view port / projection in default value
    void setViewPortProjection(bool perspective);
    
    //event handler: when the window has been resized
    void onWindowResize(int w, int h);
    
}


#endif /* Screen_hpp */
