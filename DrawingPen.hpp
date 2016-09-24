//
//  DrawingPen.hpp
//  DM6101Assignment
//
//  Created by Christina Lui on 10/11/15.
//  Copyright © 2015 Christina Lui. All rights reserved.
//

#ifndef DrawingPen_hpp
#define DrawingPen_hpp

//C++ library
#include <stdio.h>
#include <iostream>
#include <map>

//Graphics
#ifdef __APPLE__
#   include <OpenGL/OpenGL.h>
#   include <GLUT/GLUT.h>
#else
#   include <GL/gl.h>
#   include <GL/glu.h>
#   include <GL/glut.h>
#endif

//internal files
#include "MeshDataStruct.hpp"
#include "Controller.hpp"

using namespace MeshDataStruct;
using namespace Controller;

namespace DrawingPen {
    
    //draw x, y, z axis on the screen
    void drawXaxis();
    void drawYaxis();
    void drawZaxis();
    
    void drawFloorGrid();
    
    //draw all vertices of the selected model
    void drawModel();
    
    //draw bounding box around the model
    void drawBoundingBox();
}


#endif /* DrawingPen_hpp */
