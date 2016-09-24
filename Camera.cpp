//
//  Camera.cpp
//  DM6101Assignment
//
//  Created by Christina Lui on 10/11/15.
//  Copyright © 2015 Christina Lui. All rights reserved.
//

#include "Camera.hpp"

namespace Camera {
    
    const GLdouble __CAMERA_DEFAULT_POSITION__[3] = {1.0f, 1.0f, 2.0f};
    const GLdouble __CAMERA_DEFAULT_CENTRE__[3] = {0.0f, 0.0f, 0.0f};
    const GLdouble __CAMERA_DEFAULT_UPDIRECTION__[3] = {0.0f, 1.0f, 0.0f};
    
    void setCameraLocation(){
        /* viewing transformation  */
        gluLookAt (__CAMERA_DEFAULT_POSITION__[0],
                   __CAMERA_DEFAULT_POSITION__[1],
                   __CAMERA_DEFAULT_POSITION__[2],
                   __CAMERA_DEFAULT_CENTRE__[0],
                   __CAMERA_DEFAULT_CENTRE__[1],
                   __CAMERA_DEFAULT_CENTRE__[2],
                   __CAMERA_DEFAULT_UPDIRECTION__[0],
                   __CAMERA_DEFAULT_UPDIRECTION__[1],
                   __CAMERA_DEFAULT_UPDIRECTION__[2]);
    }
}
