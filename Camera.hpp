//
//  Camera.hpp
//  DM6101Assignment
//
//  Created by Christina Lui on 10/11/15.
//  Copyright © 2015 Christina Lui. All rights reserved.
//

#ifndef Camera_hpp
#define Camera_hpp

//C++ library
#include <stdio.h>
#include <iostream>

//Graphics
#ifdef __APPLE__
#   include <OpenGL/OpenGL.h>
#   include <GLUT/GLUT.h>
#else
#   include <GL/gl.h>
#   include <GL/glu.h>
#   include <GL/glut.h>
#endif

namespace Camera {
    //the camera location
    //stores the modelview matrix
    
    void setCameraLocation();
}


#endif /* Camera_hpp */
