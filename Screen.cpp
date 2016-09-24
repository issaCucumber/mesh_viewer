//
//  Screen.cpp
//  DM6101Assignment
//
//  Created by Christina Lui on 10/11/15.
//  Copyright © 2015 Christina Lui. All rights reserved.
//

#include "Screen.hpp"

namespace Screen {
    const char* windowTitle = "DM6101 Assignment: Mesh Viewer";
    
    const GLfloat __VIEWER_BACKGROUND_COLOR__[4]    = {1.0, 1.0, 1.0, 1.0}; //white background color
    const GLint __VIEWER_SCREEN_SIZE__[2]           = {1000, 800}; //w x h
    const GLint __VIEWER_SCREEN_ANCHOR__[2]         = {100, 100};
    
    static GLfloat screen_w = __VIEWER_SCREEN_SIZE__[0];
    static GLfloat screen_h = __VIEWER_SCREEN_SIZE__[1];
    
    const GLdouble fovy         = 40;
    const GLdouble zNear        = 0.5;
    const GLdouble zFar         = 20.0;
    
    //orthographic projection
    const GLdouble left         = -1.0;
    const GLdouble right        = 1.0;
    const GLdouble bottom       = -1.0;
    const GLdouble top          = 1.0;
    const GLdouble nearVal      = 0.5;
    const GLdouble farVal       = 20.0;
    
    static int win;
    
    static bool in_perspective;
    
    int getWindowObj(){
        return win;
    }
    
    void setupWindow(){
        glutInitWindowSize(__VIEWER_SCREEN_SIZE__[0], __VIEWER_SCREEN_SIZE__[1]);
        glutInitWindowPosition(__VIEWER_SCREEN_ANCHOR__[0], __VIEWER_SCREEN_ANCHOR__[1]);
        
        win = glutCreateWindow(windowTitle);
        
        // set the clearcolor and the callback
        glClearColor(__VIEWER_BACKGROUND_COLOR__[0], __VIEWER_BACKGROUND_COLOR__[1], __VIEWER_BACKGROUND_COLOR__[2], __VIEWER_BACKGROUND_COLOR__[3]); //set background
        
    }
    
    void onWindowResize (int w, int h)
    {
        screen_w = w;
        screen_h = h;
        
        GLdouble aspect = w / h;
        
        glMatrixMode (GL_PROJECTION);
        glLoadIdentity ();
        if(in_perspective){
            gluPerspective(fovy, aspect, zNear, zFar);
        }else{
            glOrtho(left, right, bottom, top, nearVal, farVal);
        }
        
        glMatrixMode (GL_MODELVIEW);
        glLoadIdentity ();
    }
    
    void setViewPortProjection(bool perspective){
        
        in_perspective = perspective;
        
        glViewport (0, 0, screen_w, screen_h);
        
        GLdouble aspect = screen_w / screen_h;
        
        glMatrixMode (GL_PROJECTION);
        glLoadIdentity ();
        
        if(in_perspective){
            gluPerspective(fovy, aspect, zNear, zFar);
        }else{
            glOrtho(left, right, bottom, top, nearVal, farVal);
        }
        
        glMatrixMode (GL_MODELVIEW);
        glLoadIdentity ();
        
    }
    
    
    
}
