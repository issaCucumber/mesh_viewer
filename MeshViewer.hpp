//
//  MeshViewer.hpp
//  DM6101Assignment
//
//  Created by Christina Lui on 10/11/15.
//  Copyright © 2015 Christina Lui. All rights reserved.
//

#ifndef MeshViewer_hpp
#define MeshViewer_hpp

//C++ libraries
#include <stdio.h>
#include <map>
#include <math.h>

//Graphics
#ifdef __APPLE__
#   include <OpenGL/OpenGL.h>
#   include <GLUT/GLUT.h>
#   include <GLUI/GLUI.h>
#else
#   include <GL/gl.h>
#   include <GL/glu.h>
#   include <GL/glut.h>
#endif

//App files
#include "mFileParser.hpp"
#include "HEDataStruct.h"
#include "MeshDataStruct.hpp"
#include "DrawingPen.hpp"
#include "Camera.hpp"
#include "Controller.hpp"
#include "Screen.hpp"
#include "Lighting.hpp"

//namespaces
using namespace mFileParser;
using namespace HEDataStruct;
using namespace MeshDataStruct;
using namespace Screen;
using namespace Camera;
using namespace DrawingPen;
using namespace Controller;
using namespace Lighting;

// This is the application wrapper
// Framework:
// 1. parse the selected mfile ( mFileParser ) -->
// 2. translate it to vertex map, face map and half edge map ( MeshDataStruct ) -->
// 3. set up camera ( Camera ) --> [viewing transformation]
// 4. draw the feature on the stage ( DrawingPen ) --> [model transformation]
// 5. set viewing volume ( 3DViewer ) --> [projection transformation]
// 6. start controller/ init event listener and handle events ( Controller )-->

namespace MeshViewer {
    
    int startApplication(int argc, char **argv);
}


#endif /* MeshViewer_hpp */
