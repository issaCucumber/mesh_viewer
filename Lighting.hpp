//
//  Lighting.hpp
//  DM6101Assignment
//
//  Created by Christina Lui on 10/11/15.
//  Copyright © 2015 Christina Lui. All rights reserved.
//

#ifndef Lighting_hpp
#define Lighting_hpp

#include <stdio.h>

//Graphics
#ifdef __APPLE__
#   include <OpenGL/OpenGL.h>
#   include <GLUT/GLUT.h>
#else
#   include <GL/gl.h>
#   include <GL/glu.h>
#   include <GL/glut.h>
#endif

namespace Lighting {
    void lettherebelight();
}

#endif /* Lighting_hpp */
